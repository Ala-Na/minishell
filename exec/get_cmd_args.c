/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_cmd_args.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlichir <hlichir@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/21 11:03:41 by anadege           #+#    #+#             */
/*   Updated: 2021/09/25 21:51:10 by hlichir          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

/*
** sub_function to check if the loop should continue for both "get_args_nbr"
** & get_exec_args funcions.
*/
int	get_arg_loop(t_cmd **cmd, t_token **curr_token)
{
	printf("cmd op: %d - %s\n", (*cmd)->next_operator, (*cmd)->start->token);
	printf("token : %s - l : %d\n", (*curr_token)->token, (*curr_token)->length);
	if (*curr_token == (*cmd)->end)
	{
		if ((*cmd)->next_operator == -1 || (*cmd)->next_operator == PIPE)
			return (-1);
		else
		{
			while((*cmd) && (*cmd)->next_operator != -1 && \
				(*cmd)->next_operator != PIPE)
			{
				*cmd = (*cmd)->next;
				*curr_token = (*curr_token)->next->next;
			}
		}
	}
	return (0);
}

/*
** Function which returns the number of executable arguments.
** The number is at least of 1 (for filename).
*/
int	get_args_nbr(t_cmd *first_cmd, t_token *exec_token)
{
	int		nbr_args;
	t_token	*curr_token;
	t_cmd	*cmd;

	nbr_args = 1;
	curr_token = exec_token;
	cmd = first_cmd;
	if (curr_token == cmd->end)
		return (1);
	curr_token = curr_token->next;
	while (cmd && curr_token)
	{
		nbr_args++;
		if (get_arg_loop(&cmd, &curr_token) < 0)
			break ;
		curr_token = (curr_token)->next;
	}
	return (nbr_args);
}

/*
** Function which return an array of string containing arguments
** of current executable. The array is NULL terminated.
** Arguments are non-NULL (execept if error) as it contains at least
** the filename (or executable path).
*/
char	**get_exec_args(t_infos *infos, t_cmd *first_cmd, t_token *exec_token)
{
	t_token	*curr_token;
	t_cmd	*cmd;
	char	**exec_args;
	int		nbr_args;
	int		i;

	i = 0;
	curr_token = exec_token;
	nbr_args = get_args_nbr(first_cmd, exec_token);
	exec_args = malloc(sizeof(*exec_args) * (nbr_args + 1));
	if (!exec_args)
		return (NULL);
	cmd = first_cmd;
	while (cmd && curr_token)
	{
		exec_args[i] = ft_strndup(curr_token->token, curr_token->length);
		printf(">>> args: %s\n", exec_args[i]);
		i++;
		if (get_arg_loop(&cmd, &curr_token) < 0)
			break ;
		curr_token = (curr_token)->next;
	}
	exec_args[i] = NULL;
	return (exec_args);
}

/*
** Function which return token corresponding to executable absolute or
** relative path and register assignments variables inside exec_env.
** Return NULL if error.
*/
t_token	*move_to_exec(t_infos *infos, t_cmd *cmd, char ***exec_env)
{
	int	diff_exec_env_size;
	int	modif;

	*exec_env = NULL;
	diff_exec_env_size = get_exec_env_diff_size(infos, cmd, &modif);
	if (diff_exec_env_size < 0)
		return (NULL);
	else if (diff_exec_env_size == 0 && modif == 0)
		*exec_env = infos->env;
	else if (copy_env(infos, infos->env, exec_env, diff_exec_env_size) < 0)
		return (NULL);
	while (cmd->start->type == ASSIGNMENT)
	{
		if (add_elem_to_exec_env(infos, exec_env, cmd->start) < 0)
		{
			free_env(*exec_env, -1);
			return (NULL);
		}
		if (cmd->start == cmd->end)
			break ;
		cmd->start = cmd->start->next;
	}
	return (cmd->start);
}

/*
** Function which return exec_path and set up the executable environment
** variables inside exec_env.
** Return NULL if an error occurs.
*/
char	*get_exec_path(t_infos *infos, t_cmd *cmd, char ***exec_env,
		t_token **exec_token)
{
	char		*path;
	char		*full_path;
	struct stat	buf;

	*exec_token = move_to_exec(infos, cmd, exec_env);
	if (!*exec_token)
		return (NULL);
	path = ft_strndup((*exec_token)->token, (*exec_token)->length);
	full_path = get_path(path, *exec_env);
	if (!full_path)
		error_exit_status(ft_strjoin(path, " : command not found"),
			1, infos, "?=127");
	else if (!stat(full_path, &buf) && !(buf.st_mode & S_IXUSR))
	{
		error_exit_status(ft_strjoin(path, " : permission denied"),
			1, infos, "?=126");
		if (full_path != path)
			free(full_path);
		full_path = NULL;
	}
	if (path && (!full_path || full_path != path))
		free(path);
	return (full_path);
}

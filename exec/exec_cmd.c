/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlichir <hlichir@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/09 15:00:10 by anadege           #+#    #+#             */
/*   Updated: 2021/09/20 21:00:59 by anadege          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

/*
** Function which returns the number of executable arguments.
** The number is at least of 1 (for filename).
*/
int	get_args_nbr(t_cmd *cmd, t_token *exec_token)
{
	int		nbr_args;
	t_token	*curr_token;

	nbr_args = 1;
	curr_token = exec_token;
	if (curr_token == cmd->end)
		return (1);
	curr_token = curr_token->next;
	while (curr_token)
	{
		nbr_args++;
		if (curr_token == cmd->end)
			break;
		curr_token = curr_token->next; 
	}
	return (nbr_args);
}

/*
** Function which return an array of string containing arguments
** of current executable. The array is NULL terminated.
** Arguments are non-NULL (execept if error) as it contains at least
** the filename (or executable path).
*/
char	**get_exec_args(t_infos *infos, t_cmd *cmd, t_token *exec_token)
{
	t_token	*curr_token;
	char	**exec_args;
	int		nbr_args;
	int		i;

	i = 0;
	curr_token = exec_token;
	nbr_args = get_args_nbr(cmd, exec_token);
	exec_args = malloc(sizeof(*exec_args) * (nbr_args + 1));
	if (!exec_args)
		return (NULL);
	while (curr_token)
	{
		exec_args[i] = ft_strndup(curr_token->token, curr_token->length);
		i++;
		if (curr_token == cmd->end)
			break ;
		curr_token = curr_token->next;
	}
	exec_args[i] = NULL;
	return (exec_args);
}

/*
** Function which return token corresponding to executable absolute or relative path
** and register assignments variables inside exec_env.
** Return NULL if error.
*/
t_token	*move_to_exec(t_infos *infos, t_cmd *cmd, char ***exec_env)
{
	int	diff_exec_env_size;

	*exec_env = NULL;
	diff_exec_env_size = get_exec_env_diff_size(infos, cmd);
	if (diff_exec_env_size < 0 ||
			copy_env(infos, infos->env, exec_env, diff_exec_env_size) < 0)
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
char	*get_exec_path(t_infos *infos, t_cmd *cmd, char ***exec_env, t_token **exec_token)
{
	char	*path;
	char	*full_path;

	*exec_token = move_to_exec(infos, cmd, exec_env);
	if (!*exec_token)
		return (NULL);
	path = ft_strndup((*exec_token)->token, (*exec_token)->length);
	full_path = get_path(path, *exec_env);
	if (!full_path)
		error_exit_status(NULL, infos, "?=1");
	if (path && full_path != path)
		free(path);
	return (full_path);
}

/*
** exec_elems[0] is equivalent to executable environmentals variables.
** exec_elems[1] is equivalent to executable arguments.
** WARNING : Value of ? may need to be modified in case of errors.
*/
int	execute_simple_cmd(t_infos *infos)
{
	pid_t	pid;
	int		res;
	int		wstatus;
	char	*exec_path;
	char	**exec_elems[2];
	t_token	*exec_token;

	pid = fork();
	if (pid < 0)
		return (error_exit_status(strerror(errno), infos, "?=1"));
	else if (pid > 0)
	{
		waitpid(pid, &wstatus, 0);
		kill(pid, SIGTERM);
	}
	else
	{
		exec_path = get_exec_path(infos, infos->lst_cmds, &exec_elems[0], &exec_token);
		if (!exec_path || !exec_elems[0])
		{
			if (exec_elems[0])
				free_env(exec_elems[0], -1);
			return (-1);
		}
		exec_elems[1] = get_exec_args(infos, infos->lst_cmds, exec_token);
		if (!exec_elems[1])
		{
			free(exec_path);
			free_env(exec_elems[0], -1);
			return (error_exit_status("error", infos, "?=1"));
		}
		if (execve(exec_path, exec_elems[1], exec_elems[0]) == -1)
		{
			free(exec_path);
			free_env(exec_elems[0], -1);
			free_env(exec_elems[1], -1);
			return (error_exit_status(strerror(errno), infos, "?=1"));
		}
		free(exec_path);
		free_env(exec_elems[0], -1);
		free_env(exec_elems[1], -1);
		exit(EXIT_FAILURE);
	}
	return (0);
}

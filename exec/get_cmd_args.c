/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_cmd_args.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlichir <hlichir@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/21 11:03:41 by anadege           #+#    #+#             */
/*   Updated: 2021/09/30 18:08:06 by anadege          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

/*
** sub_function to check if the loop should continue for both "get_args_nbr"
** & get_exec_args funcions.
*/
int	get_arg_loop(t_cmd **cmd, t_token **curr_token)
{
	if (!*cmd || !*curr_token)
		return (return_error(1, "something went wrong", 0, -1));
	if (*curr_token == (*cmd)->end)
	{
		if ((*cmd)->next_operator == -1 || (*cmd)->next_operator == PIPE)
			return (1);
		else
		{
			while ((*cmd) && (*cmd)->next_operator != -1
				&& (*cmd)->next_operator != PIPE)
			{
				*cmd = (*cmd)->next;
				*curr_token = (*curr_token)->next->next;
			}
		}
	}
	return (0);
}

/*
** Sub function of get_exec_args.
** Returns -1 in case of error, 0 otherwise.
*/
int	sub_get_args(t_infos *infos, t_cmd *cmd, t_token *exec_token,
		char ***exec_args)
{
	int		i;
	int		loop;

	i = 0;
	while (cmd && exec_token)
	{
		(*exec_args)[i] = ft_strndup(exec_token->token, exec_token->length);
		if (!(*exec_args)[i++])
		{
			free_env(exec_args, i - 1);
			return (return_error(1, "memory allocation error", 0, -1));
		}
		loop = get_arg_loop(&cmd, &exec_token);
		if (loop > 0)
			break ;
		else if (loop < 0)
		{
			free_env(exec_args, i - 1);
			return (-1);
		}
		exec_token = exec_token->next;
	}
	(*exec_args)[i] = NULL;
	return (0);
}

/*
** Function which return an array of string containing arguments
** of current executable. The array is NULL terminated.
** Arguments are non-NULL (execept if error) as it contains at least
** the filename (or executable path).
*/
char	**get_exec_args(t_infos *infos, t_cmd *first_cmd, t_token *exec_token)
{
	t_cmd	*cmd;
	char	**exec_args;
	int		nbr_args;

	if (!infos || !first_cmd || !exec_token)
		return ((char **)return_null_error(1, "something went wrong", 0));
	nbr_args = get_args_nbr(first_cmd, exec_token);
	if (nbr_args < 0)
		return (NULL);
	exec_args = malloc(sizeof(*exec_args) * (nbr_args + 1));
	if (!exec_args)
		return ((char **)return_null_error(1, "memory allocation error", 0));
	cmd = first_cmd;
	if (sub_get_args(infos, cmd, exec_token, &exec_args) == -1)
		return (NULL);
	if (check_add_input(infos, &exec_args, nbr_args) < 0)
		return (NULL);
	return (exec_args);
}

/*
** Sub function of get_exec_path to display "permission denied"
** message and set g_exit_value to 126 when needed.
*/
void	permission_denied_msg(char **full_path, char *path)
{
	char	*str;

	str = ft_strjoin(path, " : permission denied");
	if (!str)
		return_error(1, "memory allocation error", 0, 0);
	return_error(126, str, 1, 0);
	if (*full_path != path)
		free(*full_path);
	*full_path = NULL;
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

	if (!infos || !cmd)
		return (return_null_error(1, "something went wrong", 0));
	*exec_token = move_to_exec(infos, cmd, exec_env);
	if (!*exec_token)
		return (NULL);
	path = ft_strndup((*exec_token)->token, (*exec_token)->length);
	if (!path)
		return (return_null_error(1, "memory allocation error", 0));
	full_path = get_path(path, *exec_env);
	if (!full_path)
		return (NULL);
	else if (!stat(full_path, &buf) && !(buf.st_mode & S_IXUSR))
		permission_denied_msg(&full_path, path);
	if (path && (!full_path || full_path != path))
		free(path);
	return (full_path);
}

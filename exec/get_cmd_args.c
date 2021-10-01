/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_cmd_args.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlichir <hlichir@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/21 11:03:41 by anadege           #+#    #+#             */
/*   Updated: 2021/10/01 22:00:05 by hlichir          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

/*
** Sub_function to check if the loop should continue for both "get_args_nbr"
** and get_exec_args functions.
** It returns 1 when the current cmd is the last of a pipeline, 0 if the current
** token wasn't the last of a cmd and that more arguments need to be retrieved.
** 
** When the current token is the last of a command, 2 cases are possible :
**  - It was the last token of the last command of a simple command or a 
**    pipeline : 1 is returned directly.
**  - It was the last token of a command inside a pipeline (the command end with
**    a redirection operator), we'll move cmd and token pointers to seek the next
**    valid token (which is not a redirection instruction) when returning to 
**    sub_get_args.
*/
int	get_arg_loop(t_cmd **cmd, t_token **curr_token)
{
	if (!*cmd || !*curr_token)
		return (return_error(1, "something went wrong", 0, -1));
	while (*curr_token == (*cmd)->end)
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
				if (*curr_token != (*cmd)->end)
					return (0);
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
		(*exec_args)[i] = ft_strdup_linked_string(exec_token);
		if (!(*exec_args)[i++])
			return (return_free_args(exec_args, i - 1, 1));
		loop = get_arg_loop(&cmd, &exec_token);
		if (loop > 0)
			break ;
		else if (loop < 0)
			return (return_free_args(exec_args, i - 1, 0));
		exec_token = (exec_token)->next;
		while (exec_token && exec_token->prev->linked_to_next)
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
	nbr_args = get_args_nbr(first_cmd, exec_token, 1);
	if (nbr_args < 0)
		return (NULL);
	exec_args = malloc(sizeof(*exec_args) * (nbr_args + 1));
	if (!exec_args)
		return ((char **)return_null_error(1, "memory allocation error", 0));
	cmd = first_cmd;
	if (sub_get_args(infos, cmd, exec_token, &exec_args) == -1)
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
	path = ft_strdup_linked_string(*exec_token);
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

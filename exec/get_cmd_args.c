/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_cmd_args.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlichir < hlichir@student.42.fr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/21 11:03:41 by anadege           #+#    #+#             */
/*   Updated: 2021/10/21 23:48:32 by anadege          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

/*
** Sub function of get_exec_args.
** Returns -1 in case of error, 0 otherwise.
*/
int	sub_get_args(t_infos *infos, t_cmd *exec_cmd, t_token *exec_token,
		char ***exec_args)
{
	int		i;
	t_cmd	*curr_cmd;

	i = 0;
	curr_cmd = exec_cmd;
	while (curr_cmd && exec_token)
	{
		(*exec_args)[i] = ft_strdup_linked_string(exec_token);
		if (!(*exec_args)[i++])
		{
			free_env(exec_args, i);
			return (return_error(1, "memory allocation error", 0, -1));
		}
		exec_token = get_next_token(infos, exec_cmd, &curr_cmd, exec_token);
	}
	(*exec_args)[i] = NULL;
	if (!exec_token && g_exit_status != 0)
		return (-1);
	return (0);
}

/*
** Function which return an array of string containing arguments
** of current executable. The array is NULL terminated.
** Arguments are non-NULL (execept if error) as it contains at least
** the filename (or executable path).
*/
char	**get_exec_args(t_infos *infos, t_cmd *exec_cmd, t_token *exec_token)
{
	char	**exec_args;
	int		nbr_args;

	if (!infos || !exec_cmd || !exec_token)
		return ((char **)return_null_error(1, "something went wrong", 0));
	nbr_args = get_args_nbr(infos, exec_cmd, exec_token);
	if (nbr_args < 0)
		return (NULL);
	exec_args = malloc(sizeof(*exec_args) * (nbr_args + 2));
	if (!exec_args)
		return ((char **)return_null_error(1, "memory allocation error", 0));
	if (sub_get_args(infos, exec_cmd, exec_token, &exec_args) == -1)
		return (NULL);
	return (exec_args);
}

/*
** Function which return exec_path and set up the executable environment
** variables inside exec_env.
*/
char	*get_exec_path(t_infos *infos, t_cmd **cmd, char ***exec_env,
		t_token **exec_token)
{
	char		*path;
	char		*full_path;

	if (!infos || !cmd)
		return (return_null_error(1, "something went wrong", 0));
	*exec_env = NULL;
	*exec_token = move_to_exec_and_fill_env(infos, cmd, exec_env);
	if (!*exec_token)
		return (NULL);
	path = ft_strdup_linked_string(*exec_token);
	if (!path)
		return (return_null_error(1, "memory allocation error", 0));
	full_path = get_path(infos, &path, *exec_env);
	if (!full_path)
	{
		free(path);
		return (NULL);
	}
	if (path && full_path != path)
		free(path);
	return (full_path);
}

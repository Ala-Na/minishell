/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlichir <hlichir@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/30 16:59:11 by anadege           #+#    #+#             */
/*   Updated: 2021/10/05 16:14:37 by anadege          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

/*
** Function to change the current directory.
** To use when the buil in cd is called.
** Use the function chdir.
** Return -1 and display corresponding error if an error
** occurs, 0 otherwise.
** Exit = 126 > command is found but not executable
** Exit = 1 Somehing went wrong (memory allocation error)
*/
int	change_directory(t_infos *infos, char *new_dir_path, int is_alloc)
{
	char	*str;

	if (!infos || !new_dir_path)
	{
		if (is_alloc && new_dir_path)
			free(new_dir_path);
		return (return_error(1, "something went wrong", 0, -1));
	}
	if (chdir(new_dir_path) == -1)
	{
		if (is_alloc)
			free(new_dir_path);
		str = strerror(errno);
		str = ft_strjoin("cd : ", str);
		if (!str)
			return (return_error(1, "memory allocation error", 0, -1));
		return (return_error(1, str, 1, -1));
	}
	if (is_alloc)
		free(new_dir_path);
	return (0);
}

/*
** Function to call when the first element of a t_cmd structure is "cd".
** Exit status = 1 : something went wrong (memory allocation ...)
** Exit status = 2 : Misuse of a Shell builtin
*/
int	cmd_change_directory(t_infos *infos, t_cmd *cmd, t_token *token)
{
	int		i;
	char	*home_path;
	t_token	*curr;
	t_token	*next;

	i = -1;
	if (!infos || !cmd)
		return (return_error(1, "something went wrong", 0, -1));
	curr = get_next_token(infos, cmd, &cmd, token);
	if (!curr && g_exit_status != 0)
		return (-1);
	if (!curr && g_exit_status == 0)
	{
		home_path = get_env_elem(infos->env, "HOME");
		if (!home_path)
			return (return_error(1, "cd: « HOME » not defined", 0, -1));
		return (change_directory(infos, home_path, 0));
	}
	next = get_next_token(infos, cmd, &cmd, curr);
	if (curr && next)
		return (return_error(1, "cd: too many arguments", 0, -1));
	home_path = ft_strdup_linked_string(curr);
	if (!home_path)
		return (return_error(1, "memory allocation error", 0, -1));
	return (change_directory(infos, home_path, 1));
}

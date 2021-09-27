/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlichir < hlichir@student.42.fr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/30 16:59:11 by anadege           #+#    #+#             */
/*   Updated: 2021/09/24 21:36:24 by anadege          ###   ########.fr       */
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
int	change_directory(t_infos *infos, char *new_dir_path)
{
	char	*str;

	if (!infos || !new_dir_path)
		return (return_error(1, "something went wrong", 0, -1));
	if (chdir(new_dir_path) == -1)
	{
		str = strerror(errno);
		str = ft_strjoin("cd : ", str);
		if (!str)
			return (return_error(1, "memory allocation error", 0, -1));
		return (return_error(1, str, 1, -1));
	}
	return (0);
}

/*
** Function to call when the first element of a t_cmd structure is "cd".
** Exit status = 1 : something went wrong (memory allocation ...)
** Exit status = 2 : Misuse of a Shell builtin
*/
int	cmd_change_directory(t_infos *infos, t_cmd *cmd)
{
	int		i;
	char	*home_path;
	char	dir_path[4097];

	i = -1;
	if (!infos || !cmd
		|| ft_strncmp(cmd->start->token, "cd", cmd->start->length))
		return (return_error(1, "something went wrong", 0, -1));
	if (cmd->start == cmd->end)
	{
		home_path = get_env_elem(infos->env, "HOME");
		if (!home_path)
			return (return_error(1, "cd: « HOME » not defined", 0, -1));
		return (change_directory(infos, home_path));
	}
	if (cmd->start->next && cmd->start->next != cmd->end)
		return (return_error(1, "cd: too many arguments", 0, -1));
	while (++i < cmd->end->length && i < 4097)
		dir_path[i] = cmd->end->token[i];
	dir_path[i] = 0;
	return (change_directory(infos, dir_path));
}

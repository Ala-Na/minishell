/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_builtin.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlichir <hlichir@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/02 14:46:17 by anadege           #+#    #+#             */
/*   Updated: 2021/10/01 22:00:53 by hlichir          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

/*
** Function to check that the first argument of the command line is a built in.
** Return the corresponding value of enum t_builtin.
*/
t_builtin	check_builtin(char *first_elem)
{
	int	size;

	if (!first_elem)
		return (return_error(1, "something went wrong", 0, -1));
	size = ft_strlen(first_elem);
	if (!ft_strncmp(first_elem, "echo", size))
		return (ECHO);
	else if (!ft_strncmp(first_elem, "cd", size))
		return (CD);
	else if (!ft_strncmp(first_elem, "pwd", size))
		return (PWD);
	else if (!ft_strncmp(first_elem, "export", size))
		return (EXPORT);
	else if (!ft_strncmp(first_elem, "unset", size))
		return (UNSET);
	else if (!ft_strncmp(first_elem, "env", size))
		return (ENV);
	return (NONE);
}

/*
** FONCTION A REMPLIR AU FUR ET A MESURE
** Warning ; Pour le moment, lance les assignements
** sans prendre en compte ce qu'il y a derrière.
** Warning : IL FAUT CREER FONCTION POUR VERIFIER SI QUE ASSIGNMENTS
** OU SI CMD 
*/
int	launch_builtin(t_infos *infos, t_cmd *cmd, t_builtin builtin)
{
	if (!infos || !cmd)
		return (return_error(1, "something went wrong", 0, -1));
	if (add_redirections(cmd, 0) < 0)
		return (-1);
	if (builtin == CD)
		return (cmd_change_directory(infos, cmd));
	else if (builtin == ECHO)
		return (cmd_echo(infos, cmd));
	else if (builtin == ENV)
		return (show_env(infos, cmd, 0));
	else if (builtin == EXPORT)
		return (add_elem_to_env(infos, cmd, 0));
	else if (builtin == PWD)
		return (show_current_dir(infos, cmd));
	else if (builtin == UNSET)
		return (unset_var(infos, cmd));
	return (return_error(1, "something went wrong", 0, -1));
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_builtin.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlichir < hlichir@student.42.fr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/02 14:46:17 by anadege           #+#    #+#             */
/*   Updated: 2021/09/21 14:40:25 by anadege          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

/*
** Function to check that the first argument of the command line is a built in.
** Return the corresponding value of enum t_builtin.
*/
t_builtin	check_builtin(char	*first_elem)
{
	if (!ft_strncmp(first_elem, "echo", 4) && (first_elem[4] == ' '
			|| first_elem[4] == '\t' || first_elem[4] == 0))
		return (ECHO);
	else if (!ft_strncmp(first_elem, "cd", 2) && (first_elem[2] == ' '
			|| first_elem[2] == '\t' || first_elem[2] == 0))
		return (CD);
	else if (!ft_strncmp(first_elem, "pwd", 3) && (first_elem[3] == ' '
			|| first_elem[3] == '\t' || first_elem[3] == 0))
		return (PWD);
	else if (!ft_strncmp(first_elem, "export", 6) && (first_elem[6] == ' '
			|| first_elem[6] == '\t' || first_elem[6] == 0))
		return (EXPORT);
	else if (!ft_strncmp(first_elem, "unset", 5) && (first_elem[5] == ' '
			|| first_elem[5] == '\t' || first_elem[5] == 0))
		return (UNSET);
	else if (!ft_strncmp(first_elem, "env", 3) && (first_elem[3] == ' '
			|| first_elem[3] == '\t' || first_elem[3] == 0))
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
int	launch_cmd(t_infos *infos, t_cmd *cmd)
{
	t_builtin	builtin;

	if (!cmd || !cmd->start)
		return (error_exit_status("Error!", infos, "?=1"));
	builtin = check_builtin(cmd->start->token);
	if (builtin == CD)
		return (cmd_change_directory(infos, cmd));
	else if (builtin == ECHO)
		return (cmd_echo(infos, cmd));
	else if (builtin == ENV)
		return (show_env(infos, cmd, 0));
	else if (builtin == EXPORT)
		return (add_elem_to_env(infos, cmd));
	else if (builtin == PWD)
		return (show_current_dir(infos, cmd));
	else if (builtin == UNSET)
		return (unset_var(infos, cmd));
	else if (cmd->next_operator == -1)
		return (execute_simple_cmd(infos));
	else if (cmd->start->type == ASSIGNMENT)
		return (check_assignment(infos, cmd));
	return (0);
}

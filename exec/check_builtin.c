/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_builtin.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlichir <hlichir@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/02 14:46:17 by anadege           #+#    #+#             */
/*   Updated: 2021/10/25 18:53:06 by hlichir          ###   ########.fr       */
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
		return ((t_builtin)(return_error(1, "something went wrong", 0, -1)));
	size = ft_strlen(first_elem);
	if (!ft_strncmp(first_elem, "echo", ft_max(size, 5)))
		return (ECHO);
	else if (!ft_strncmp(first_elem, "cd", ft_max(size, 3)))
		return (CD);
	else if (!ft_strncmp(first_elem, "pwd", ft_max(size, 4)))
		return (PWD);
	else if (!ft_strncmp(first_elem, "export", ft_max(size, 7)))
		return (EXPORT);
	else if (!ft_strncmp(first_elem, "unset", ft_max(size, 6)))
		return (UNSET);
	else if (!ft_strncmp(first_elem, "env", ft_max(size, 4)))
		return (ENV);
	else if (!ft_strncmp(first_elem, "exit", ft_max(size, 5)))
		return (EXIT);
	return (NONE);
}

int	sub_launch_builtin(t_infos	*infos, t_cmd *cmd, t_token *builtin_token,
		t_builtin builtin)
{
	if (builtin == EXIT)
		return (exit_builtin(infos, cmd, builtin_token));
	return (return_error(1, "something went wrong", 0, -1));
}

/*
** Fonction called when t_builtin is not NONE.
** Lead programm to the corresponding builtin function after making
** redirections and recuperation of builtin_token.
** Returns depends of the called builtin.
*/
int	launch_builtin(t_infos *infos, t_cmd *cmd, t_builtin builtin)
{
	t_token	*builtin_token;
	t_cmd	*builtin_cmd;

	if (!infos || !cmd)
		return (return_error(1, "something went wrong", 0, -1));
	builtin_cmd = NULL;
	builtin_token = get_exec_token(infos, cmd, &builtin_cmd);
	if (!builtin_token)
		return (return_error(1, "something went wrong", 0, -1));
	if (builtin == CD)
		return (cmd_change_directory(infos, cmd, cmd, builtin_token));
	else if (builtin == ECHO)
		return (cmd_echo(infos, cmd, builtin_cmd, builtin_token));
	else if (builtin == ENV)
		return (show_env(infos, cmd, builtin_token, 0));
	else if (builtin == EXPORT)
		return (add_elem_to_env(infos, cmd, builtin_token, 0));
	else if (builtin == PWD)
		return (show_current_dir(infos, cmd));
	else if (builtin == UNSET)
		return (unset_var(infos, cmd, builtin_token));
	return (sub_launch_builtin(infos, builtin_cmd, builtin_token, builtin));
}

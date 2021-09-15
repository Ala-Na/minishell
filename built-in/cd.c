/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anadege <anadege@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/30 16:59:11 by anadege           #+#    #+#             */
/*   Updated: 2021/09/15 15:55:47 by anadege          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

/*
** Function to change the current directory.
** To use when the buil in cd is called.
** Use the function chdir.
** Return -1 and display corresponding error if an error
** occurs, 0 otherwise.
*/
int	change_directory(char *new_dir_path)
{
	char	*str;

	if (chdir(new_dir_path) == -1)
	{
		str = strerror(errno);
		printf("%s\n", str);
		return (-1);
	}
	return (0);
}

/*
** Function to call when the first element of a t_cmd structure is "cd".
** It checks 
*/
int	cmd_change_directory(t_infos *infos, t_cmd *cmd)
{
	int		i;
	char	*home_path;
	char	dir_path[4097];

	i = -1;
	if (!infos || !cmd
		|| ft_strncmp(cmd->start->token, "cd", cmd->start->length))
		return (-1);
	if (cmd->start == cmd->end)
	{
		home_path = get_env_elem(infos->env, "HOME");
		return (change_directory(home_path));
	}
	if (cmd->start->next != cmd->end)
	{
		printf("cd : too many arguments\n");
		return (-1);
	}
	while (++i < cmd->end->length && i < 4097)
		dir_path[i] = cmd->end->token[i];
	dir_path[i] = 0;
	return (change_directory(dir_path));
}

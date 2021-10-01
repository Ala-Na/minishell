/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlichir <hlichir@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/15 17:18:48 by anadege           #+#    #+#             */
/*   Updated: 2021/10/01 19:47:35 by hlichir          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	show_env_for_export(t_infos *infos, t_cmd *cmd, char **env, int i)
{
	int		j;
	int		exist;

	j = 0;
	exist = 0;
	if (!infos || !env || !cmd)
		return (return_error(1, "something went wrong", 0, -1));
	while (env[i][j])
	{
		if (env[i][j++] == '=')
		{
			exist = 1;
			break ;
		}
	}
	write(cmd->fd_output, "declare -x ", ft_strlen("declare -x "));
	write(cmd->fd_output, env[i], j);
	if (exist)
	{
		write(cmd->fd_output, "\"", 1);
		write(cmd->fd_output, &env[i][j], ft_strlen(env[i]) - j);
		write(cmd->fd_output, "\"", 1);
	}
	write(cmd->fd_output, "\n", 1);
	return (0);
}

int	check_for_assignment(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '=')
			return (1);
		i++;
	}
	return (0);
}

/*
** Loop function for show_env (thank you norminette)
*/
int	show_env_loop(t_infos *infos, t_cmd *cmd, int export, int fd)
{
	int	i;
	int	exist;

	i = 0;
	if (!infos || !infos->env || !cmd)
		return (return_error(1, "something went wrong", 0, -1));
	while ((infos->env)[i])
	{
		if (export)
		{
			if (show_env_for_export(infos, cmd, infos->env, i) < 0)
				return (-1);
		}
		else
		{
			exist = check_for_assignment((infos->env)[i]);
			if (exist)
			{
				write(fd, (infos->env)[i], ft_strlen((infos->env)[i]));
				write(fd, "\n", 1);
			}
		}
		i++;
	}
	return (0);
}

/*
** Function to display environment variables.
** To call when the built in "env" is inside the commande line.
** Need to received infos->env as argument.
*/
int	show_env(t_infos *infos, t_cmd *cmd, int export)
{
	if (!infos || !infos->env || !cmd)
		return (return_error(1, "something went wrong", 0, -1));
	if (!export && cmd->start != cmd->end)
		return (return_error(127, "env : take no options or arguments", 0, -1));
	if (show_env_loop(infos, cmd, export, cmd->fd_output) < 0)
		return (-1);
	return (0);
}

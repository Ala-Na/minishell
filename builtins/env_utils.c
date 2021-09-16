/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anadege <anadege@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/15 17:18:48 by anadege           #+#    #+#             */
/*   Updated: 2021/09/15 17:37:13 by anadege          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	show_env_for_export(t_cmd *cmd, char **env, int i)
{
	int	j;

	j = 0;
	write(1, "declare -x ", 11);
	while (env[i][j] != '=' && env[i][j])
		j++;
	write(1, env[i], j++);
	write(1, "=\"", 2);
	write(1, &env[i][j], ft_strlen(&env[i][j]));
	write(1, "\"\n", 2);
}

/*
** Function to display environment variables.
** To call when the built in "env" is inside the commande line.
** Need to received infos->env as argument.
*/
int	show_env(t_cmd *cmd, char **env, int export)
{
	int	i;

	i = 0;
	if (!env || !cmd)
		return (-1);
	if (!export && cmd->start != cmd->end)
	{
		ft_putstr("env : take no options or arguments\n");
		return (-1);
	}
	while (env[i])
	{
		if (export)
			show_env_for_export(cmd, env, i);
		else
		{
			write(1, env[i], ft_strlen(env[i]));
			write(1, "\n", 1);
		}
		i++;
	}
	return (0);
}

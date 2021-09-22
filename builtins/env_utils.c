/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlichir < hlichir@student.42.fr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/15 17:18:48 by anadege           #+#    #+#             */
/*   Updated: 2021/09/22 14:39:30 by anadege          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	show_env_for_export(t_infos *infos, t_cmd *cmd, char **env, int i)
{
	int	j;

	j = 0;
	if (!cmd->output)
		return (error_exit_status("Memory allocation error", 0, infos, "?=1"));
	cmd->output = ft_strjoin(cmd->output, "declare -x ");
	if (!cmd->output)
		return (error_exit_status("Memory allocation error", 0, infos, "?=1"));
	while (env[i][j] != '=' && env[i][j])
		j++;
	cmd->output = ft_strjoin(cmd->output, env[i]);
	if (!cmd->output)
		return (error_exit_status("Memory allocation error", 0, infos, "?=1"));
	cmd->output = ft_strjoin(cmd->output, "=\"");
	if (!cmd->output)
		return (error_exit_status("Memory allocation error", 0, infos, "?=1"));
	cmd->output = ft_strjoin(cmd->output, &env[i][j]);
	if (!cmd->output)
		return (error_exit_status("Memory allocation error", 0, infos, "?=1"));
	cmd->output = ft_strjoin(cmd->output, "\"\n");
	if (!cmd->output)
		return (error_exit_status("Memory allocation error", 0, infos, "?=1"));
	return (0);
}

/*
** Loop function for show_env (thank you norminette)
*/
int	show_env_loop(t_infos *infos, t_cmd *cmd, int export)
{
	int	i;

	i = 0;
	while ((infos->env)[i])
	{
		if (export)
		{
			if (show_env_for_export(infos, cmd, infos->env, i) < 0)
				return (-1);
		}
		else
		{
			cmd->output = ft_strnjoin(cmd->output, (infos->env)[i], \
				ft_strlen((infos->env)[i]));
			if (!cmd->output)
				return (error_exit_status("Malloc error", 0, infos, "?=1"));
			cmd->output = ft_strjoin(cmd->output, "\n");
			if (!cmd->output)
				return (error_exit_status("Malloc error", 0, infos, "?=1"));
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
	if (!infos->env || !cmd)
		return (error_exit_status("Error!", 0, infos, "?=1"));
	cmd->output = ft_strdup("");
	if (!cmd->output)
		return (error_exit_status("Memory allocation error", 0, infos, "?=1"));
	if (!export && cmd->start != cmd->end)
	{
		ft_puterr("env : take no options or arguments", 1);
		g_exit_status = 127;
		return (-1);
	}
	if (show_env_loop(infos, cmd, export) < 0)
		return (-1);
	if (modify_var_in_list(infos, "?=0", NULL) < 0)
		return (error_exit_status("Memory allocation error", 0, infos, "?=1"));
	return (0);
}

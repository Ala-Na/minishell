/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlichir < hlichir@student.42.fr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/15 17:18:48 by anadege           #+#    #+#             */
/*   Updated: 2021/09/24 22:39:44 by anadege          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	join_for_export_env(t_cmd *cmd, char *to_add, int size)
{
	char	*fusion;

	if (!cmd || !cmd->output || !to_add)
		return (return_error(1, "something went wrong", 0, -1));
	if (size)
		fusion = ft_strnjoin(cmd->output, to_add, size);
	else
		fusion = ft_strjoin(cmd->output, to_add);
	free(cmd->output);
	if (!fusion)
		return (return_error(1, "memory allocation error", 0, -1));
	cmd->output = fusion;
	return (0);
}

int	show_env_for_export(t_infos *infos, t_cmd *cmd, char **env, int i)
{
	int		j;
	char	*tmp;

	j = 0;
	if (!infos || !env || !cmd || !cmd->output)
		return (return_error(1, "something went wrong", 0, -1));
	while (env[i][j])
	{
		if (env[i][j++] == '=')
			break ;
	}
	if (join_for_export_env(cmd, "declare -x ", 0) < 0
			|| join_for_export_env(cmd, env[i], j) < 0
			|| join_for_export_env(cmd, "\"", 0) < 0
			|| join_for_export_env(cmd, &env[i][j], 0) < 0
			|| join_for_export_env(cmd, "\"\n", 0) < 0)
		return (-1);
	return (0);
}

/*
** Loop function for show_env (thank you norminette)
*/
int	show_env_loop(t_infos *infos, t_cmd *cmd, int export)
{
	int		i;
	char	*tmp;

	i = 0;
	if (!infos || !infos->env || !cmd || !cmd->output)
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
			tmp = ft_strnjoin(cmd->output, (infos->env)[i], \
				ft_strlen((infos->env)[i]));
			free(cmd->output);
			if (!tmp)
				return (return_error(1, "memory allocation error", 0, -1));
			cmd->output = ft_strjoin(tmp, "\n");
			free(tmp);
			if (!cmd->output)
				return (return_error(1, "memory allocation error", 0, -1));
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
	cmd->output = ft_strdup("");
	if (!cmd->output)
		return (return_error(1, "memory allocation error", 0, -1));
	if (!export && cmd->start != cmd->end)
		return (return_error(127, "env : take no options or arguments", 0, -1));
	if (show_env_loop(infos, cmd, export) < 0)
		return (-1);
	return (0);
}

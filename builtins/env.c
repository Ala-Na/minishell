/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlichir < hlichir@student.42.fr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/15 17:18:48 by anadege           #+#    #+#             */
/*   Updated: 2021/11/01 18:58:17 by anadege          ###   ########.fr       */
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
	while (str && str[i])
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
int	show_env_loop(t_infos *infos, t_cmd *cmd, int fd, int export)
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
int	show_env(t_infos *infos, t_cmd *head_cmd, t_token *builtin_token,
		int export)
{
	t_token	*curr;
	t_cmd	*cmd;

	if (!infos || !infos->env || !head_cmd || !builtin_token)
		return (return_error(1, "something went wrong", 0, -1));
	cmd = head_cmd;
	curr = get_next_token(infos, head_cmd, &cmd, builtin_token);
	if (!export && curr)
		return (return_error(127, "env : take no options or arguments", 0, -1));
	if (show_env_loop(infos, head_cmd, head_cmd->fd_output, export) < 0)
		return (-1);
	return (0);
}

/*
** Function which aim to save environment variables inside a structure
** containing the minishell's informations.
** Allocations are realised to free the array without complications.
** Return -1 if an error occurs, 0 otherwise.
*/
int	save_env(t_infos *infos, char **env)
{
	int		i;
	char	**tmp_env;

	i = 0;
	while (env && env[i])
		i++;
	tmp_env = malloc(sizeof(*tmp_env) * (i + 1));
	if (!tmp_env)
		return (return_error(1, "memory allocation error", 0, -1));
	i = 0;
	while (env && env[i])
	{
		tmp_env[i] = ft_strdup(env[i]);
		if (!tmp_env[i])
		{
			free_env(&tmp_env, i);
			return (return_error(1, "memory allocation error", 0, -1));
		}
		i++;
	}
	tmp_env[i] = NULL;
	infos->env = tmp_env;
	return (0);
}

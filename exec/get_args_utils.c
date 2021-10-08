/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_args_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlichir < hlichir@student.42.fr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/30 17:30:12 by anadege           #+#    #+#             */
/*   Updated: 2021/10/08 12:08:30 by hlichir          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

/*
** Function which returns the number of executable arguments.
** The number is at least of 1 (for filename).
*/
int	get_args_nbr(t_infos *infos, t_cmd *exec_cmd, t_token *exec_token)
{
	t_token	*curr_token;
	t_cmd	*cmd;
	int		nbr_args;

	if (!infos || !exec_cmd || !exec_token)
		return_error(1, "something went wrong", 0, -1);
	nbr_args = 0;
	cmd = exec_cmd;
	curr_token = get_next_token(infos, exec_cmd, &cmd, exec_token);
	while (cmd && curr_token)
	{
		nbr_args++;
		curr_token = get_next_token(infos, exec_cmd, &cmd, curr_token);
	}
	if (!curr_token && g_exit_status != 0)
		return (-1);
	return (nbr_args);
}

/*
** Function which return token corresponding to executable absolue or
** relative path and register assignments variables inside exec_env.
** Return NULL if error.
*/
t_token	*move_to_exec_and_fill_env(t_infos *infos, t_cmd **cmd,
		char ***exec_env)
{
	int		diff_exec_env_size;
	int		modif;
	t_token	*exec_token;
	t_cmd	*exec_cmd;

	if (!infos || !cmd || !*cmd || !infos->env)
		return ((t_token *)return_null_error(1, "something went wrong", 0));
	*exec_env = NULL;
	modif = 0;
	diff_exec_env_size = get_exec_env_diff_size(infos, *cmd, &modif);
	if (diff_exec_env_size < 0)
		return (NULL);
	else if (diff_exec_env_size == 0 && modif == 0)
		*exec_env = infos->env;
	else if (copy_env(infos, infos->env, exec_env, diff_exec_env_size) < 0)
		return (NULL);
	else if (complete_exec_env_with_assignments(infos, *cmd, exec_env) == -1)
		return (NULL);
	exec_cmd = NULL;
	exec_token = get_exec_token(infos, *cmd, &exec_cmd);
	if (!exec_token)
		return ((t_token *)return_null_error(1, "something went wrong", 0));
	*cmd = exec_cmd;
	return (exec_token);
}

/*
** Subfunction of get_cmd_args to free_env & return -1 with or without an 
**	error.
*/
int	return_free_args(char ***env, int i, int error_msg)
{
	free_env(env, i);
	if (error_msg)
		return_error(1, "memory allocation error", 0, -1);
	return (-1);
}

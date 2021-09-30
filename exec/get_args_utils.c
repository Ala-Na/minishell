/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_args_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlichir <hlichir@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/30 17:30:12 by anadege           #+#    #+#             */
/*   Updated: 2021/09/30 21:33:24 by hlichir          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

/*
** Function which returns the number of executable arguments.
** The number is at least of 1 (for filename).
*/
int	get_args_nbr(t_cmd *first_cmd, t_token *exec_token)
{
	int		nbr_args;
	t_token	*curr_token;
	t_cmd	*cmd;
	int		loop;

	if (!first_cmd || !exec_token)
		return_error(1, "something went wrong", 0, -1);
	nbr_args = 1;
	curr_token = exec_token;
	cmd = first_cmd;
	if (curr_token == cmd->end)
		return (1);
	curr_token = curr_token->next;
	while (cmd && curr_token)
	{
		nbr_args++;
		loop = get_arg_loop(&cmd, &curr_token);
		if (loop > 0)
			break ;
		else if (loop < 0)
			return (-1);
		curr_token = (curr_token)->next;
	}
	return (nbr_args);
}

/*
** Function which return token corresponding to executable absolute or
** relative path and register assignments variables inside exec_env.
** Return NULL if error.
*/
t_token	*move_to_exec(t_infos *infos, t_cmd *cmd, char ***exec_env)
{
	int	diff_exec_env_size;
	int	modif;

	if (!infos || !cmd || !infos->env || !cmd->start || !cmd->end)
		return ((t_token *)return_null_error(1, "something went wrong", 0));
	*exec_env = NULL;
	diff_exec_env_size = get_exec_env_diff_size(infos, cmd, &modif);
	if (diff_exec_env_size < 0)
		return (NULL);
	else if (diff_exec_env_size == 0 && modif == 0)
		*exec_env = infos->env;
	else if (copy_env(infos, infos->env, exec_env, diff_exec_env_size) < 0)
		return (NULL);
	while (cmd->start->type == ASSIGNMENT)
	{
		if (add_elem_to_exec_env(infos, exec_env, cmd->start) < 0)
		{
			free_env(exec_env, -1);
			return (NULL);
		}
		if (cmd->start == cmd->end)
			break ;
		cmd->start = cmd->start->next;
	}
	return (cmd->start);
}

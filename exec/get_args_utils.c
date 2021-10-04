/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_args_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlichir <hlichir@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/30 17:30:12 by anadege           #+#    #+#             */
/*   Updated: 2021/10/04 22:54:31 by anadege          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

/*
** Function which returns the number of executable arguments.
** The number is at least of 1 (for filename).
*/
int	get_args_nbr(t_cmd *first_cmd, t_token *exec_token, int nbr_args)
{
	t_token	*curr_token;
	t_cmd	*cmd;
	int		loop;

	if (!first_cmd || !exec_token)
		return_error(1, "something went wrong", 0, -1);
	curr_token = exec_token;
	cmd = first_cmd;
	if (curr_token == cmd->end)
		return (1);
	move_to_next_token(&curr_token, 1);
	while (cmd && curr_token)
	{
		nbr_args++;
		loop = get_arg_loop(&cmd, &curr_token);
		if (loop > 0)
			break ;
		else if (loop < 0)
			return (-1);
		curr_token = (curr_token)->next;
		while (curr_token && curr_token->prev->linked_to_next)
			curr_token = curr_token->next;
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

	if (!infos || !cmd || !infos->env)
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

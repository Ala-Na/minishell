/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_assignments.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anadege <anadege@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/22 16:53:14 by anadege           #+#    #+#             */
/*   Updated: 2021/09/22 21:09:49 by anadege          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

/*
** Function to check if the assignment variable already exist inside **env.
** If it's the case, the variable inside **env will be modified.
** If not, it'll be saved inside *lst_var.
*/
int	do_assignment(t_infos *infos, t_token *token)
{
	char	*var_name;
	int		res;

	if (!infos || !token || token->type != ASSIGNMENT)
		return (-1);
	var_name = get_elem_name(token->token, token->length);
	if (!var_name)
		return (-1);
	if (get_env_elem(infos->env, var_name) != NULL)
		res = modify_existing_elem_to_env(infos, infos->env,
				token, var_name);
	else
		res = assign_variable_to_list(infos, token);
	free(var_name);
	return (res);
}

/*
** Check if the given command cmd is only filled with assignments.
** If it's the case, it returns 1. Else, it returns 0.
** Returns -1 in case of error.
*/
int	is_only_assignments(t_cmd *cmd)
{
	t_token	*current;
	if (!cmd)
		return (-1);
	current = cmd->start;
	if (!current)
		return (-1);
	while (current && current->type == ASSIGNMENT)
	{
		if (current == cmd->end)
			return (1);
		current = current->next;
	}
	return (0);
}

/*
** Check if a command is only made of assignments. When it is, it set all
** the variable (either in lst_var or in env if the variable was already
** existing).
** Return -1 in cas of error, 1 if the command was only made of assignments,
** 0 otherwise.
*/
int	check_assignments(t_infos *infos, t_cmd *cmd)
{
	int		assignments;
	t_token	*curr_token;

	assignments = is_only_assignments(cmd);
	if (assignments == -1)
		return (-1);
	else if (assignments == 0)
		return (0);
	curr_token = cmd->start;
	while (curr_token)
	{
		if (do_assignment(infos, curr_token) == -1)
			return (-1);
		if (curr_token == cmd->end)
			break ;
		curr_token = curr_token->next;
	}
	return (1);
}

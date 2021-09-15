/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   before_assignment.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anadege <anadege@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/15 11:48:01 by anadege           #+#    #+#             */
/*   Updated: 2021/09/15 20:56:03 by anadege          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

/*
** Function to check if the assignment variable already exist inside **env.
** If it's the case, the variable inside **env will be modified.
** If not, it'll be saved inside *lst_var.
*/

int	check_assignment(t_infos *infos, t_cmd *cmd)
{
	char	*var_name;
	int		res;

	if (!infos || !cmd || cmd->start->type != ASSIGNMENT
		|| cmd->start != cmd->end)
		return (-1);
	var_name = get_elem_name(cmd->start->token, cmd->start->length);
	if (!var_name)
		return (-1);
	if (get_env_elem(infos->env, var_name) != NULL)
		res = modify_existing_elem_to_env(infos->env,
				cmd->start->token, cmd->start->length, var_name);
	else
		res = assign_variable(infos, cmd);
	free(var_name);
	return (res);
}

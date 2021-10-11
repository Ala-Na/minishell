/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_assignments.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlichir < hlichir@student.42.fr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/22 16:53:14 by anadege           #+#    #+#             */
/*   Updated: 2021/10/11 22:55:02 by anadege          ###   ########.fr       */
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
		return (return_error(1, "something went wrong", 0, -1));
	var_name = get_elem_name(token);
	if (!var_name)
		return (-1);
	if (get_env_elem(infos->env, var_name, ft_strlen(var_name)) != NULL)
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
int	is_only_assignments(t_infos *infos, t_cmd *cmd, t_token *first_non_redir)
{
	t_cmd	*curr_cmd;
	t_token	*current;

	if (!cmd || !first_non_redir)
		return (return_error(1, "something went wrong", 0, -1));
	curr_cmd = cmd;
	current = first_non_redir;
	while (curr_cmd && current)
	{
		if (current->type != ASSIGNMENT)
			return (0);
		if (check_if_end_pipeline(curr_cmd, current) == 1)
			return (1);
		current = get_next_token(infos, cmd, &curr_cmd, current);
	}
	return (1);
}

/*
** Check if a command is only made of assignments. When it is, it set all
** the variable (either in lst_var or in env if the variable was already
** existing).
** Return -1 in cas of error, 1 if the command was only made of assignments,
** 0 otherwise.
*/
int	check_assignments(t_infos *infos, t_cmd *head_cmd, t_cmd *cmd,
		t_token *first_non_redir)
{
	int		assignments;
	t_token	*curr_token;
	t_cmd	*curr_cmd;

	if (!infos || !head_cmd || !cmd || !first_non_redir)
		return (return_error(1, "something went wrong", 0, -1));
	assignments = is_only_assignments(infos, cmd, first_non_redir);
	if (assignments <= 0)
		return (assignments);
	add_redirections(head_cmd, 0);
	curr_token = first_non_redir;
	curr_cmd = cmd;
	while (cmd && curr_token)
	{
		if (do_assignment(infos, curr_token) == -1)
			return (-1);
		curr_token = get_next_token(infos, cmd, &curr_cmd, curr_token);
	}
	return (1);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_assignments.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlichir <hlichir@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/22 16:53:14 by anadege           #+#    #+#             */
/*   Updated: 2021/10/04 17:49:41 by anadege          ###   ########.fr       */
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
int	is_only_assignments(t_cmd *cmd, t_token *first_non_redir)
{
	t_token	*current;
	int		prev_was_redir;

	if (!cmd || !first_non_redir)
		return (return_error(1, "something went wrong", 0, -1));
	prev_was_redir = 0;
	current = first_non_redir;
	while (cmd && current)
	{
		if (prev_was_redir == 0 && current->type != ASSIGNMENT)
			return (0);
		if (current == cmd->end && cmd->next_operator <= 0)
			return (1);
		else if (current == cmd->end)
		{
			cmd = cmd->next;
			if (cmd && cmd->start)
			{
				current = cmd->start;
				prev_was_redir = 1;
			}
		}
		else
		{
			current = current->next;
			prev_was_redir = 0;
		}
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
int	check_assignments(t_infos *infos, t_cmd *cmd, t_token *first_non_redir)
{
	int		assignments;
	t_token	*curr_token;
	int		prev_was_redir;

	assignments = is_only_assignments(cmd, first_non_redir);
	if (assignments <= 0)
		return (assignments);
	curr_token = first_non_redir;
	prev_was_redir = 0;
	while (cmd && curr_token)
	{
		if (prev_was_redir == 0 && do_assignment(infos, curr_token) == -1)
			return (-1);
		if (curr_token == cmd->end && cmd->next_operator <= 0)
			break ;
		if (curr_token == cmd->end && cmd->next_operator > 0)
		{
			cmd = cmd->next;
			if (cmd && cmd->start)
			{
				curr_token = cmd->start;
				prev_was_redir = 1;
			}
		}
		else
		{
			prev_was_redir = 0;
			curr_token = curr_token->next;
		}
	}
	return (1);
}

/*
** Function to free the linked list of variables if assignments were set!
*/
int	free_lst_var(t_infos *infos)
{
	t_var	*current;
	t_var	*tmp;

	current = infos->lst_var;
	while (current)
	{
		tmp = current;
		current = current->next;
		free(tmp->name);
		free(tmp->value);
		free(tmp);
	}
	infos->lst_var = NULL;
	return (0);
}

/*
** Function which is useful to recuperate only the name of a variable
** from it's format "NAME=value".
** Returns NULL if an error occurs.
*/
char	*extract_name(char *elem, int size)
{
	char	*elem_name;
	int		i;

	i = 0;
	if (!elem)
	{
		return_error(1, "something went wrong", 0, 0);
		return (NULL);
	}
	while (elem[i] != '=' && i < size)
		i++;
	elem_name = malloc(sizeof(*elem_name) * (i + 1));
	if (!elem_name)
	{
		return_error(1, "memory allocation error", 0, 0);
		return (NULL);
	}
	i = 0;
	while (elem[i] != '=' && i < size)
	{
		elem_name[i] = elem[i];
		i++;
	}
	elem_name[i] = 0;
	return (elem_name);
}

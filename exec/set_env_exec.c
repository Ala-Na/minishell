/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_env_exec.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anadege <anadege@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/17 16:53:57 by anadege           #+#    #+#             */
/*   Updated: 2021/09/21 11:04:32 by anadege          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

/*
** Function which add a new element to char **exec_env.
** Strategy is slightly different from add_elem_to_env when the element
** doesn't exist because here exec_env is supposed to already have the right
** size.
** Returns -1 if an errors occurs, 0 otherwise.
*/
int	add_elem_to_exec_env(t_infos *infos, char ***exec_env, t_token *new_elem)
{
	int		i;
	char	*elem_name;
	int		res;

	if (!infos || !(*exec_env) || !new_elem)
		return (-1);
	i = 0;
	res = -1;
	while ((*exec_env)[i])
		i++;
	elem_name = get_elem_name(new_elem->token, new_elem->length);
	if (!elem_name)
		return (-1);
	if (!get_env_elem(*exec_env, elem_name))
	{
		(*exec_env)[i] = ft_strndup(new_elem->token, new_elem->length);
		if (!(*exec_env)[i])
			return (-1);
		res = 0;
	}
	else
		res = modify_existing_elem_to_env(infos, *exec_env, new_elem,
				elem_name);
	free(elem_name);
	return (res);
}

/*
** Function to calculate the positive difference between minishell
** env and executable env.
*/
int	get_exec_env_diff_size(t_infos *infos, t_cmd *cmd)
{
	t_token	*curr_token;
	char	**env;
	int		diff_size;
	char	*elem_name;

	diff_size = 0;
	env = infos->env;
	curr_token = cmd->start;
	while (curr_token->type == ASSIGNMENT)
	{
		elem_name = get_elem_name(curr_token->token, curr_token->length);
		if (!elem_name)
			return (-1);
		if (!get_env_elem(env, elem_name))
			diff_size++;
		free(elem_name);
		curr_token = curr_token->next;
	}
	return (diff_size);
}

/*
** Function to copy the minishell char **env variable for the command
** executed, which is susceptible to contains a largest env.
** Allocations are realised to free the array without complications.
** Return -1 if an error occurs, 0 otherwise.
*/
int	copy_env(t_infos *infos, char **env, char ***cpy_env, int cpy_diff_size)
{
	int		i;
	int		y;

	y = 0;
	while (env && env[y])
		y++;
	*cpy_env = malloc(sizeof(**cpy_env) * (y + 1 + cpy_diff_size));
	if (!*cpy_env)
		return (-1);
	i = 0;
	while (env[i])
	{
		(*cpy_env)[i] = ft_strdup(env[i]);
		if (!(*cpy_env)[i])
		{
			free_env(*cpy_env, i);
			return (-1);
		}
		i++;
	}
	while (i < y + 1 + cpy_diff_size)
		(*cpy_env)[i++] = NULL;
	return (0);
}

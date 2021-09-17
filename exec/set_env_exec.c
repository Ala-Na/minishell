/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_env_exec.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anadege <anadege@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/17 16:53:57 by anadege           #+#    #+#             */
/*   Updated: 2021/09/17 23:29:34 by anadege          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
** Function which add a new element to char **exec_env.
** Returns -1 if an errors occurs, 0 otherwise.
*/
int	add_elem_to_exec_env(t_infos *infos, char ***exec_env, t_token *new_elem)
{
	int		env_size;
	char	*elem_name;
	int		res;

	if (!infos || !(*exec_env) || !new_elem)
		return (error_exit_status("Error!", infos, "?=1"));
	env_size = 0;
	res = -1;
	while ((*exec_env)[env_size])
		env_size++;
	elem_name = get_elem_name(new_elem->token, new_elem->length);
	if (!elem_name)
		return (error_exit_status("Memory allocation error", infos, "?=1"));
	if (!get_env_elem(*exec_env, elem_name))
		res = add_not_existing_elem_to_env(exec_env, new_elem, env_size);
	else
		res = modify_existing_elem_to_env(infos, *exec_env, new_elem,
			elem_name);
	free(elem_name);
	return (res);
}

/*
** Function to copy the minishell char **env variable for the command
** executed, which is susceptible to contains a largest env.
** Allocations are realised to free the array without complications.
** Return -1 if an error occurs, 0 otherwise.
*/
int	copy_env(t_infos *infos, char **env, char ***cpy_env)
{
	int		i;
	int		y;
	char	**tmp_env;

	i = 0;
	while (env && env[i])
		i++;
	tmp_env = malloc(sizeof(*tmp_env) * (i + 1));
	if (!tmp_env)
		return (error_exit_status("Malloc error", infos, "?=1"));
	i = 0;
	while (env[i])
	{
		y = 0;
		tmp_env[i] = ft_strdup(env[i]);
		if (!tmp_env[i])
		{
			free_env(tmp_env, i);
			return (error_exit_status("Malloc error", infos, "?=1"));
		}
		i++;
	}
	tmp_env[i] = NULL;
	*cpy_env = tmp_env;
	return (0);
}

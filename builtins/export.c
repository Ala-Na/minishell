/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlichir <hlichir@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/01 21:56:08 by anadege           #+#    #+#             */
/*   Updated: 2021/10/11 14:42:18 by anadege          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

/*
** Function which augment the size of env array in order to add a new element
** new_elem.
** Return -1 if an error occurs, 0 otherwise.
*/
int	add_not_existing_elem_to_env(char ***env, t_token *new_elem, int env_size)
{
	char	**tmp_env;
	int		j;

	if (!env || !*env || !new_elem)
		return (return_error(1, "something went wrong", 0, -1));
	tmp_env = malloc(sizeof(*tmp_env) * (env_size + 2));
	if (!tmp_env)
		return (return_error(1, "memory allocation error", 0, -1));
	j = -1;
	while (++j < env_size + 1)
	{
		if ((*env)[j])
			tmp_env[j] = (*env)[j];
		else
			tmp_env[j] = ft_strdup_linked_string(new_elem);
		if (!tmp_env[j])
		{
			free(tmp_env);
			return (return_error(1, "memory allocation error", 0, -1));
		}
	}
	tmp_env[j] = NULL;
	free(*env);
	*env = tmp_env;
	return (0);
}

/*
** Function which modify an element elem_name of env which already exist
** and replace it's value by new_elem/
** Returns -1 if an error occurs, 0 otherwise.
*/
int	modify_existing_elem_to_env(t_infos *infos, char **env, t_token *new_elem,
		char *elem_name)
{
	int	elem_pos;

	if (!infos || !env || !new_elem || !elem_name)
		return (return_error(1, "something went wrong", 0, -1));
	elem_pos = seek_elem_pos(env, elem_name);
	if (elem_pos < 0)
		return (return_error(1, "something went wrong", 0, -1));
	free(env[elem_pos]);
	env[elem_pos] = ft_strdup_linked_string(new_elem);
	if (!env[elem_pos])
		return (-1);
	return (0);
}

int	sub_add_elem_to_env(t_infos *infos, t_token *new_elem,
		int env_size, int *ptr_res)
{
	int		res;
	char	*elem_name;

	elem_name = NULL;
	res = -1;
	if (!infos || !new_elem)
		return (return_error(1, "something went wrong", 0, -1));
	elem_name = get_elem_name(new_elem);
	if (!elem_name)
		return (-1);
	delete_elem_from_var_lst(&infos->lst_var, elem_name);
	if (!get_env_elem(infos->env, elem_name, ft_strlen(elem_name)))
		res = add_not_existing_elem_to_env(&infos->env, new_elem,
				env_size);
	else
		res = modify_existing_elem_to_env(infos, infos->env, new_elem,
				elem_name);
	free(elem_name);
	if (res == 0)
		*ptr_res = 0;
	return (res);
}

/*
** Function to call when the built in export is inside the command.
** It adds the new variable new_elem (format "NAME=value") to the array
** env.
** Returns -1 if an errors occurs, 0 otherwise.
*/
int	add_elem_to_env(t_infos *infos, t_cmd *builtin_cmd,
		t_token *builtin_token, int env_size)
{
	t_token	*new_elem;
	int		res;
	t_cmd	*cmd;

	if (!infos->env || !builtin_cmd || !builtin_token)
		return (return_error(1, "something went wrong", 0, -1));
	cmd = builtin_cmd;
	new_elem = get_next_token(infos, builtin_cmd, &cmd, builtin_token);
	res = -1;
	while (new_elem)
	{
		if (check_validity_token(&new_elem, 1, &res) < 0)
		{
			new_elem = get_next_token(infos, builtin_cmd, &cmd, new_elem);
			continue ;
		}
		while ((infos->env)[env_size])
			env_size++;
		if (sub_add_elem_to_env(infos, new_elem, env_size, &res) < 0)
			return (-1);
		new_elem = get_next_token(infos, builtin_cmd, &cmd, new_elem);
	}
	if (res == -1)
		return (show_env(infos, builtin_cmd, builtin_token, 1));
	return (res);
}

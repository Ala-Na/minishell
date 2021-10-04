/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlichir <hlichir@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/01 21:56:08 by anadege           #+#    #+#             */
/*   Updated: 2021/10/04 12:55:37 by hlichir          ###   ########.fr       */
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

	if (!*env || !new_elem)
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
** Function to obtains the position of an element identified
** by the name elem_name inside **env.
** Returns index (or position insided **env) if success, -1 if
** env or elem_name is NULL, -2 if the element isn't found inside **env.
*/
int	seek_elem_pos(char **env, char *elem_name)
{
	int	i;
	int	elem_pos;

	i = 0;
	elem_pos = 0;
	if (!env || !elem_name)
		return (return_error(1, "something went wrong", 0, -1));
	while (env[i])
		i++;
	while (env[elem_pos])
	{
		if (!ft_strncmp(env[elem_pos], elem_name, ft_strlen(elem_name)))
			break ;
		elem_pos++;
	}
	if (elem_pos == i)
		return (-2);
	return (elem_pos);
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
		return (return_error(1, "memory allocation error", 0, -1));
	return (0);
}

int	sub_add_elem_to_env(t_infos *infos, t_token *new_elem,
		int env_size, int *ptr_res)
{
	int		res;
	char	*elem_name;
	int		i;

	elem_name = NULL;
	res = -1;
	i = 0;
	if (!infos || !new_elem)
		return (return_error(1, "something went wrong", 0, -1));
	elem_name = get_elem_name(new_elem);
	if (!elem_name)
		return (-1);
	delete_elem_from_var_lst(&infos->lst_var, elem_name);
	if (!get_env_elem(infos->env, elem_name))
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
** WARNING : Does not check for the conformity of the string new_elem.
** Must received &infos->env as first argument.
*/
int	add_elem_to_env(t_infos *infos, t_cmd *cmd, int env_size)
{
	t_token	*new_elem;
	int		res;

	if (!infos->env || !cmd || !cmd->start)
		return (return_error(1, "something went wrong", 0, -1));
	new_elem = NULL;
	if (cmd->next_operator != PIPE)
		new_elem = cmd->start;
	move_to_next_token(&new_elem, 1);
	res = -1;
	while (new_elem)
	{
		if (check_validity_token(&new_elem, 1, &res) < 0)
			continue ;
		while ((infos->env)[env_size])
			env_size++;
		if (sub_add_elem_to_env(infos, new_elem, env_size, &res) < 0)
			return (-1);
		if (new_elem == cmd->end)
			break ;
		move_to_next_token(&new_elem, 1);
	}
	if (res == -1)
		return (show_env(infos, cmd, 1));
	return (res);
}

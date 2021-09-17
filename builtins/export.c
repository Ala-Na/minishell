/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlichir < hlichir@student.42.fr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/01 21:56:08 by anadege           #+#    #+#             */
/*   Updated: 2021/09/17 14:40:04 by hlichir          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

/*
** Function which augment the size of env array in order to add a new element
** new_elem.
** Return -1 if an error occurs, 0 otherwise.
*/
int	add_not_existing_elem_to_env(char ***env, char *new_elem, int elem_size,
		int env_size)
{
	char	**tmp_env;
	int		j;

	tmp_env = malloc(sizeof(*tmp_env) * (env_size + 2));
	if (!tmp_env)
		return (set_g_status_to_error(1));
	j = -1;
	while (++j < env_size + 1)
	{
		if ((*env)[j])
			tmp_env[j] = (*env)[j];
		else
			tmp_env[j] = ft_strndup(new_elem, elem_size);
		if (!tmp_env[j])
		{
			free(tmp_env);
			return (set_g_status_to_error(1));
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
	{
		g_exit_status = 1;
		return (-1);
	}
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
int	modify_existing_elem_to_env(t_infos *infos, char *new_elem, int elem_size,
		char *elem_name)
{
	int	elem_pos;

	elem_pos = seek_elem_pos((infos->env), elem_name);
	if (elem_pos < 0)
		return (-1);
	free((infos->env)[elem_pos]);
	(infos->env)[elem_pos] = ft_strndup(new_elem, elem_size);
	if (!(infos->env)[elem_pos])
		return (error_exit_status("Memory allocation error", infos, "?=1"));
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
	if (new_elem->type != ASSIGNMENT)
		return (0);
	elem_name = get_elem_name(new_elem->token, new_elem->length);
	if (!elem_name)
		return (error_exit_status("Memory allocation error", infos, "?=1"));
	delete_elem_from_var_lst(&infos->lst_var, elem_name);
	if (!get_env_elem(infos->env, elem_name))
		res = add_not_existing_elem_to_env(&infos->env, new_elem->token,
				new_elem->length, env_size);
	else
		res = modify_existing_elem_to_env(infos, new_elem->token,
				new_elem->length, elem_name);
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
int	add_elem_to_env(t_infos *infos, t_cmd *cmd)
{
	t_token	*new_elem;
	int		env_size;
	int		tmp_res;
	int		res;

	if (!infos->env || !cmd || !cmd->start)
		return (error_exit_status("Error!", infos, "?=1"));
	new_elem = cmd->start->next;
	env_size = 0;
	res = -1;
	while (new_elem)
	{
		while ((infos->env)[env_size])
			env_size++;
		tmp_res = sub_add_elem_to_env(infos, new_elem, env_size, &res);
		if (new_elem == cmd->end)
			break ;
		new_elem = new_elem->next;
	}
	if (res == -1)
		show_env(infos, cmd, 1);
	if (modify_var_in_list(infos, "?=0", NULL) < 0)
		return (error_exit_status("Memory allocation error", infos, "?=1"));
	return (res);
}

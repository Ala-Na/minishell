/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlichir <hlichir@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/01 21:57:01 by anadege           #+#    #+#             */
/*   Updated: 2021/10/06 23:17:46 by anadege          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

/*
** Sub function of delete_elem_from_env, which permits the replacment of **env
** array by a new array minus one case (env_size), while skipping the element
** to delete in position elem_pos.
*/
int	fill_env_with_deletion(char ***env, int elem_pos, int env_size)
{
	int		i;
	int		j;
	char	**tmp_env;

	tmp_env = malloc(sizeof(*tmp_env) * (env_size));
	if (!tmp_env)
		return (return_error(1, "memory allocation error", 0, -1));
	i = -1;
	j = 0;
	while (++i < env_size - 1)
	{
		tmp_env[i] = (*env)[j++];
		if (j == elem_pos)
		{
			free((*env)[elem_pos]);
			j++;
		}
	}
	tmp_env[i] = NULL;
	free(*env);
	*env = tmp_env;
	return (0);
}

/*
** Function to suppress an environmental variable when unset
** built in is called.
** WARNING : Does not check the conformity of the name elem_name
** (should not be an assignment with an '=').
** Must receive &infos->env as first argument.
*/
int	delete_elem_from_env(char ***env, char *elem_name)
{
	int		env_size;
	int		elem_pos;

	if (!*env || !elem_name)
		return (return_error(1, "something went wrong", 0, -1));
	elem_pos = seek_elem_pos(*env, elem_name);
	if (elem_pos == -2)
		return (0);
	else if (elem_pos == -1)
		return (-1);
	env_size = 0;
	while ((*env)[env_size])
		env_size++;
	return (fill_env_with_deletion(env, elem_pos, env_size));
}

int	delete_elem_from_var_lst(t_var **var_lst, char *elem_name)
{
	t_var	*prev_var;
	t_var	*tmp_var;
	t_var	*curr_var;

	if (!*var_lst || !elem_name)
		return (return_error(1, "something went wrong", 0, -1));
	prev_var = NULL;
	curr_var = *var_lst;
	while (curr_var)
	{
		if (ft_strlen(elem_name) == ft_strlen(curr_var->name)
			&& !ft_strncmp(elem_name, curr_var->name, ft_strlen(elem_name)))
		{
			if (prev_var)
				prev_var->next = curr_var->next;
			tmp_var = curr_var;
			curr_var = curr_var->next;
			free_var(&tmp_var);
			return (0);
		}
		prev_var = curr_var;
		curr_var = curr_var->next;
	}
	return (0);
}

int	sub_unset_var(t_infos *infos, t_token *to_unset)
{
	int		tmp_res;
	char	*elem_name;
	char	*tmp;

	tmp_res = -1;
	if (!infos || !to_unset)
		return (return_error(1, "something went wrong", 0, -1));
	elem_name = get_elem_name(to_unset);
	if (elem_name && get_env_elem(infos->env, elem_name, ft_strlen(elem_name)))
		tmp_res = delete_elem_from_env(&infos->env, elem_name);
	else if (elem_name)
		tmp_res = delete_elem_from_var_lst(&infos->lst_var, elem_name);
	if (elem_name)
		free(elem_name);
	return (tmp_res);
}

int	unset_var(t_infos *infos, t_cmd *head_cmd, t_token *builtin_token)
{
	t_token	*to_unset;
	t_cmd	*cmd;
	char	*elem_name;
	int		tmp_res;

	if (!infos || !cmd)
		return (return_error(1, "something went wrong", 0, -1));
	cmd = head_cmd;
	to_unset = get_next_token(infos, head_cmd, &cmd, builtin_token);
	while (to_unset)
	{
		if (check_validity_token(&to_unset, 0, NULL) < 0)
		{
			to_unset = get_next_token(infos, head_cmd, &cmd, to_unset);
			continue ;
		}
		tmp_res = sub_unset_var(infos, to_unset);
		if (tmp_res < 0)
			return (-1);
		to_unset = get_next_token(infos, head_cmd, &cmd, to_unset);
	}
	return (0);
}

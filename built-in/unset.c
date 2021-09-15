/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anadege <anadege@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/01 21:57:01 by anadege           #+#    #+#             */
/*   Updated: 2021/09/12 17:16:04 by anadege          ###   ########.fr       */
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
		return (-1);
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

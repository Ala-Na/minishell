/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anadege <anadege@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/01 21:57:01 by anadege           #+#    #+#             */
/*   Updated: 2021/09/06 17:42:18 by anadege          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

/*
** Sous-fonction de delete_elem_from_env, permettant le remplacement
** du tableau ***env par un nouveau tableau avec une case de moinsi (env_size), 
** et sautant l'element en position elem_pos.
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
** Fonction pour la suppression d'une variable environnementale
** lorsque le builtin unset est appelé.
** ATTENTION : Ne vérifie pas le conformité du nom elem_name
** (ex : ne doit pas contenir de =).
** Lui passer &infos->env comme 1er argument.
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

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anadege <anadege@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/01 21:56:08 by anadege           #+#    #+#             */
/*   Updated: 2021/09/06 17:41:55 by anadege          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

/*
** Fonction qui augmente la taille du tableau env pour y ajouter
** un nouvel element new_elem.
** Renvoie -1 en cas d'erreur, 0 sinon.
*/
int	add_not_existing_elem_to_env(char ***env, char *new_elem, int env_size)
{
	char	**tmp_env;
	int		j;

	tmp_env = malloc(sizeof(*tmp_env) * (env_size + 2));
	if (!tmp_env)
		return (-1);
	j = -1;
	while (++j < env_size + 1)
	{
		if ((*env)[j])
			tmp_env[j] = (*env)[j];
		else
			tmp_env[j] = ft_strdup(new_elem);
		if (!tmp_env[j])
		{
			free(tmp_env);
			return (-1);
		}
	}
	tmp_env[j] = NULL;
	free(*env);
	*env = tmp_env;
	return (0);
}

/*
** Fonction pour obtenir la position d'un élement identifié
** par le nom elem_name dans **env.
** Renvoie l'index / 'la position dans **env, -1 si env ou
** elem_name est NULL, -2 si l'élement n'est pas dans **env.
*/
int	seek_elem_pos(char **env, char *elem_name)
{
	int	i;
	int	elem_pos;

	i = 0;
	elem_pos = 0;
	if (!env || !elem_name)
		return (-1);
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
** Function qui modifie un element de env deja existant (de nom elem_name)
** et le remplace par new_elem.
** Retourne -1 en cas d'erreur, 0 sinon.
*/
int	modify_existing_elem_to_env(char **env, char *new_elem, char *elem_name)
{
	int	elem_pos;

	elem_pos = seek_elem_pos(env, elem_name);
	if (elem_pos < 0)
		return (-1);
	free(env[elem_pos]);
	env[elem_pos] = ft_strdup(new_elem);
	if (!env[elem_pos])
		return (-1);
	return (0);
}

/*
** Fonction d'utilité pour récupérer uniquement la nom d'une variable
** depuis son format sous la forme "NOM=valeur".
** Retourne NULL en cas d'erreur.
*/
char	*get_elem_name(char *elem)
{
	char	*elem_name;
	int		i;

	i = 0;
	if (!elem)
		return (NULL);
	while (elem[i] != '=')
		i++;
	elem_name = malloc(sizeof(*elem_name) * (i + 1));
	if (!elem_name)
		return (NULL);
	i = 0;
	while (elem[i] != '=')
	{
		elem_name[i] = elem[i];
		i++;
	}
	elem_name[i] = 0;
	return (elem_name);
}

/*
** Fonction a appeler lorsque le bultin export est en ligne de commande.
** Va ajouter la nouvelle variable new_elem (format "VAR=value") au tableau
** env.
** Renvoie -1 en cas d'erreur, 0 sinon.
** ATTENTION : Ne verifie pas la conformite de la string new_elem.
** Lui passer &infos->env en 1er argument.
*/
int	add_elem_to_env(char ***env, char *new_elem)
{
	char	*elem_name;
	int		env_size;
	int		res;

	if (!env || !new_elem)
		return (-1);
	env_size = 0;
	while ((*env)[env_size])
		env_size++;
	elem_name = get_elem_name(new_elem);
	if (!elem_name)
		return (-1);
	if (!get_env_elem(*env, elem_name))
		res = add_not_existing_elem_to_env(env, new_elem, env_size);
	else
		res = modify_existing_elem_to_env(*env, new_elem, elem_name);
	free(elem_name);
	return (res);
}

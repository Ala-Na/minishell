/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlichir < hlichir@student.42.fr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/31 15:39:01 by anadege           #+#    #+#             */
/*   Updated: 2021/10/15 12:56:21 by hlichir          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

/*
** Loop to browse all linked token to get the name.
*/
void	get_elem_name_loop(t_token *elem, char **elem_name, int fill_str)
{
	t_token	*curr;
	int		i;
	int		j;

	i = 0;
	j = 0;
	curr = elem;
	while (curr)
	{
		j = 0;
		while (curr->token[j] != '=' && j < curr->length)
		{
			if (fill_str)
				(*elem_name)[i] = curr->token[j];
			i++;
			j++;
		}
		if (j != curr->length || !curr->linked_to_next)
			break ;
		curr = curr->next;
	}
	if (fill_str)
		(*elem_name)[i] = 0;
	else
		*elem_name = malloc(sizeof(**elem_name) * (i + 1));
}

/*
** Function which is useful to recuperate only the name of a variable
** from it's format "NAME=value".
** Returns NULL if an error occurs.
*/
char	*get_elem_name(t_token *elem)
{
	char	*elem_name;

	elem_name = NULL;
	if (!elem)
		return (return_null_error(1, "something went wrong", 0));
	get_elem_name_loop(elem, &elem_name, 0);
	if (!elem_name)
		return (return_null_error(1, "memory allocation error", 0));
	get_elem_name_loop(elem, &elem_name, 1);
	return (elem_name);
}

/*
** Function which returns environment's variable corresponding to the given 
** element (ex : For HOME, returns "/home/user42").
** Do the same as getenv function but for minishell environment where variables
** can be added.
** Returns NULL if the element is not found.
*/
char	*get_env_elem(char **env, char *elem, int elem_size)
{
	int		i;
	char	*elem_value;
	char	*tmp;

	i = 0;
	while (env[i])
	{
		if (!ft_strncmp(env[i], elem, elem_size))
		{
			tmp = extract_name(env[i], ft_strlen(env[i]));
			if (!tmp)
				return (NULL);
			if (ft_strncmp(tmp, elem, ft_max(elem_size, ft_strlen(tmp))))
			{
				free(tmp);
				i++;
				continue ;
			}
			free(tmp);
			set_value_for_get_env_elem(env[i], elem_size, &elem_value);
			return (elem_value);
		}
		i++;
	}
	return (NULL);
}

void	set_value_for_get_env_elem(char *env_elem, int elem_size, char **value)
{
	if ((int)ft_strlen(env_elem) == elem_size)
		*value = "\0";
	else
		*value = env_elem + elem_size + 1;
}

/*
** Function to free the allocated memory for the array **env and for each
** of its element.
** last argument represents the last element of the array which was allocated.
** If last is equal to -1, every elements of the array is freed.
*/
void	free_env(char ***env, int last)
{
	int	i;

	i = 0;
	if (!env || !*env)
		return ;
	if (last > 0)
	{
		while (env && *env && (*env)[i] && i < last)
			free((*env)[i++]);
	}
	else if (last == -1)
	{
		while (env && *env && (*env)[i])
			free((*env)[i++]);
	}
	free(*env);
}

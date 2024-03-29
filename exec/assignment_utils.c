/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   assignment_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlichir < hlichir@student.42.fr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/05 14:22:09 by hlichir           #+#    #+#             */
/*   Updated: 2021/10/15 13:54:53 by anadege          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

/*
** Function to free the linked list of variables if assignments were set!
*/
int	free_lst_var(t_infos *infos)
{
	t_var	*current;
	t_var	*tmp;

	if (!infos)
		return (return_error(1, "something went wrong", 0, -1));
	current = infos->lst_var;
	while (current)
	{
		tmp = current;
		current = current->next;
		free(tmp->name);
		free(tmp->value);
		free(tmp);
	}
	infos->lst_var = NULL;
	return (0);
}

/*
** Function which is useful to recuperate only the name of a variable
** from it's format "NAME=value".
** Returns NULL if an error occurs.
*/
char	*extract_name(char *elem, int size)
{
	char	*elem_name;
	int		i;

	i = 0;
	if (!elem)
		return_null_error(1, "something went wrong", 0);
	while (elem[i] != '=' && i < size)
		i++;
	elem_name = malloc(sizeof(*elem_name) * (i + 1));
	if (!elem_name)
		return_null_error(1, "memory allocation error", 0);
	i = 0;
	while (elem[i] != '=' && i < size)
	{
		elem_name[i] = elem[i];
		i++;
	}
	elem_name[i] = 0;
	return (elem_name);
}

/*
** Function which is useful to recuperate only the value of a variable
** from it's format "NAME=value".
** Returns NULL if an error occurs or if there is no assignment (no =)
*/
char	*extract_value(char *elem, int size)
{
	char	*elem_value;
	int		i;
	int		j;

	i = 0;
	j = 0;
	if (!elem)
		return_null_error(1, "something went wrong", 0);
	while (elem[i] != '=' && i < size)
		i++;
	if (elem[i] == '\0')
		return (NULL);
	elem_value = malloc(sizeof(*elem_value) * (size - i + 1));
	if (!elem_value)
		return_null_error(1, "memory allocation error", 0);
	i++;
	while (elem[i] && i < size)
		elem_value[j++] = elem[i++];
	elem_value[j] = 0;
	return (elem_value);
}

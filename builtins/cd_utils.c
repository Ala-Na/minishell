/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlichir <hlichir@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/05 13:05:41 by hlichir           #+#    #+#             */
/*   Updated: 2021/10/05 13:20:31 by hlichir          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

/*
** Function to create the new string that will be put in the environment,
** as well as the token needed to change the env.
*/
int	create_tmp_new_elem(t_token **new_elem, char *name, char *value, char *str)
{
	str = ft_strjoin(name, "=");
	if (!str)
		return (return_error(1, "memory allocation error", 0, -1));
	str = ft_strjoin_free(str, value, 1, 0);
	if (!str)
		return (return_error(1, "memory allocation error", 0, -1));
	*new_elem = malloc(sizeof(t_token));
	if (!new_elem)
	{
		free(str);
		return (return_error(1, "memory allocation error", 0, -1));
	}
	(*new_elem)->type = ASSIGNMENT;
	(*new_elem)->token = ft_strdup_free(str, 1);
	if (!(*new_elem)->token)
	{
		free(str);
		return (return_error(1, "memory allocation error", 0, -1));
	}
	(*new_elem)->length = ft_strlen((*new_elem)->token);
	(*new_elem)->linked_to_next = NULL;
	(*new_elem)->prev = NULL;
	(*new_elem)->next = NULL;
	return (0);
}

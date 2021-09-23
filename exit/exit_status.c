/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_status.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anadege <anadege@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/21 15:27:47 by anadege           #+#    #+#             */
/*   Updated: 2021/09/22 16:54:57 by anadege          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	modify_exit_value_variable(t_infos *infos, int new_value)
{
	char	*full_var;
	char	*value;
	t_var	*current;

	current = infos->lst_var;
	value = ft_itoa(new_value);
	if (!value)
		return ;
	while (current)
	{
		if (!ft_strncmp(current->name, "?", ft_strlen(current->name)))
		{
			free(current->value);
			current->value = value;
			return ;
		}
		current = current->next;
	}
	full_var = ft_strjoin("?=", value);
	if (!full_var)
	{
		free(value);
		return ;
	}
	add_new_var_to_list(infos, full_var);
}

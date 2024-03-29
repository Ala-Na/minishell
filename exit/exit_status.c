/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_status.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlichir < hlichir@student.42.fr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/21 15:27:47 by anadege           #+#    #+#             */
/*   Updated: 2021/10/09 17:14:42 by anadege          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

/*
** Function which modify the exit value variable "?=value" with
** new_value integer value.
** Call the function add_new_var_to_list.
*/
int	modify_exit_value_variable(t_infos *infos, int new_value)
{
	char	*value;
	t_var	*curr_lst_var;

	if (!infos)
		return (return_error(1, "something went wrong", 0, -1));
	curr_lst_var = infos->lst_var;
	value = ft_itoa(new_value);
	if (!value)
		return (return_error(1, "memory allocation error", 0, -1));
	while (curr_lst_var)
	{
		if (!ft_strncmp(curr_lst_var->name, "?", 2))
		{
			free(curr_lst_var->value);
			curr_lst_var->value = value;
			return (0);
		}
		curr_lst_var = curr_lst_var->next;
	}
	free(value);
	return (-1);
}

/*
**	Function to change the exit status to 130 when ctrl+c is used!
*/
int	check_for_signal(t_infos *infos)
{
	if (!infos)
		return (-1);
	if (g_exit_status == 130)
	{
		if (modify_exit_value_variable(infos, 130) < 0)
			return (-1);
	}
	g_exit_status = 0;
	return (0);
}

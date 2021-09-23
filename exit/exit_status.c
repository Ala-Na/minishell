/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_status.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anadege <anadege@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/21 15:27:47 by anadege           #+#    #+#             */
/*   Updated: 2021/09/23 20:23:02 by anadege          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

/*
** Function which modify the exit value variable "?=value" with
** new_value integer value.
** Call the function add_new_var_to_list.
*/
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

/*
** Function to set g_exit_status to error
*/
int	set_g_status_to_error(int status)
{
	g_exit_status = status;
	return (-1);
}

/*
**	Function to update the exit status in case of an error!
**	exit(1) => an error happened
*/
int	error_exit_status(char *str, int str_is_alloc, t_infos *infos, char *new_status)
{
	if (modify_var_in_list(infos, new_status, NULL) < 0)
	{
		if (str)
		{
			ft_puterr("Memory allocation error", 1);
			if (str_is_alloc)
				free(str);
		}
		return (-1);
	}
	if (str)
	{
		ft_puterr(str, 1);
		if (str_is_alloc)
			free(str);
	}
	return (-1);
}

/*
**	Function to change the exit status to 130 when ctrl+c is used!
*/
int	check_for_signal(t_infos *infos)
{
	if (g_exit_status == 130)
	{
		if (modify_var_in_list(infos, "?=130", NULL) < 0)
			return (-1);
	}
/*	else idf (g_exit_status == 1)
	{
		if (modify_var_in_list(infos, "?=1", NULL) < 0)
			return (-1);
	}
	else if (g_exit_status == 127)
	{
		if (modify_var_in_list(infos, "?=127", NULL) < 0)
			return (-1);
	}*/
	g_exit_status = 0;
	return (0);
}

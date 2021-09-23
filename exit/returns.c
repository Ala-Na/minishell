/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   returns.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anadege <anadege@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/23 16:14:03 by anadege           #+#    #+#             */
/*   Updated: 2021/09/23 16:21:29 by anadege          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

/*
** Function to display error message, modify value of g_exit_status and return
** return_value.
** It free error_msg if msg_is_alloc is non zero.
** If g_exit_status was different of 0, it doesn't modify it.
*/
int	return_error(int exit_value, char *error_msg, int msg_is_alloc,
		int return_value)
{
	if (g_exit_status != 0)
	{
		g_exit_status == exit_value;
		if (error_msg)
			perror(error_msg);
	}
	if (error_msg && msg_is_alloc)
		free(error_msg);
	return (return_value);
}

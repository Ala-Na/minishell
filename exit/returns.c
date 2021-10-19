/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   returns.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anadege <anadege@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/23 16:14:03 by anadege           #+#    #+#             */
/*   Updated: 2021/10/19 14:45:39 by anadege          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

/*
** Function to set g_exit_status with value of pipeline.
*/
void	return_pipeline(int last_child_status)
{
	if (last_child_status == 0)
		return ;
	if (WIFEXITED(last_child_status))
		return_value(WEXITSTATUS(last_child_status));
	else if (WIFSIGNALED(last_child_status))
		return_signal(WIFSIGNALED(last_child_status));
}

/*
** Function which call return_error but return NULL instead of return_value.
*/
char	*return_null_error(int exit_value, char *error_msg, char **alloc_msg)
{
	return_error(exit_value, error_msg, alloc_msg, 0);
	return (NULL);
}

/*
** Function to display error message, modify value of g_exit_status and return
** return_value.
** It free error_msg if msg_is_alloc is non zero.
** If g_exit_status was different of 0, it doesn't modify it.
*/
int	return_error(int exit_value, char *error_msg, char **alloc_msg,
		int return_value)
{
	if (g_exit_status == 0 || g_exit_status == -1)
	{
		g_exit_status = exit_value;
		if (error_msg)
			ft_puterr(error_msg, 1);
		else if (alloc_msg && *alloc_msg)
			ft_puterr(*alloc_msg, 1);
	}
	if (alloc_msg && *alloc_msg)
		free(*alloc_msg);
	return (return_value);
}

/*
** Function which set g_exit_status according to the exit value of child process.
** exit_value is WEXITSTATUS(wstatus).
** g_exit_status is set to 255 if exit_value is superior to 255 or inferior to 0
** (non valid exit value).
*/
int	return_value(int exit_value)
{
	if (g_exit_status == 0 && exit_value != 0)
	{
		if (exit_value > 255 || exit_value < 0)
			g_exit_status = 255;
		else
			g_exit_status = exit_value;
	}
	return (0);
}

/*
** Function which set g_exit_status to the corresponding value when 
** a signal is encounted.
*/
int	return_signal(int signal_value)
{
	int	exit_value;

	if (g_exit_status == 0)
	{
		exit_value = signal_value + 128;
		g_exit_status = exit_value;
		if (signal_value == SIGSEGV)
			ft_puterr("segfault", 1);
		else if (signal_value == SIGILL)
			ft_puterr("illegal instruction", 1);
		else if (signal_value == SIGBUS)
			ft_puterr("bus error", 1);
		else if (signal_value == SIGINT)
			ft_putstr("\n");
		else
			ft_puterr("error signal received", 1);
	}
	return (0);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlichir <hlichir@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/11 13:44:45 by hlichir           #+#    #+#             */
/*   Updated: 2021/10/12 15:55:51 by anadege          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	sig_handler_function(int signum)
{
	if (signum == SIGINT)
	{
		ft_putchar('\n');
		if (g_exit_status == -1 || g_exit_status == 130)
		{	
			rl_on_new_line();
			rl_replace_line("", 0);
			rl_redisplay();
		}
		g_exit_status = 130;
	}
}

/*
**	Handling CTRL + C who print an new prompt line
**	Ignore SIGQUIT
*/
void	handle_signals(void)
{
	signal(SIGINT, sig_handler_function);
	signal(SIGQUIT, SIG_IGN);
}

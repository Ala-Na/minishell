/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlichir <hlichir@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/11 13:44:45 by hlichir           #+#    #+#             */
/*   Updated: 2021/09/23 20:28:04 by anadege          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
**	Gestion du ctrl + c qui permet d'afficher une nouvelle ligne de prompt
**	Ignorer le signal SIGQUIT (mais à tester, je n'arrive pas à trouver 
**	le raccourci sur mac)
*/

void	sig_handler_function(int signum)
{
	if (signum == SIGINT)
	{
		ft_putchar('\n');
		if (g_exit_status == -1)
		{
			rl_on_new_line();
			rl_replace_line("", 0);
			rl_redisplay();
		}
		g_exit_status = 130;
	}
}

void	handle_signals(void)
{
	signal(SIGINT, sig_handler_function);
	signal(SIGQUIT, SIG_IGN);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlichir <hlichir@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/11 13:44:45 by hlichir           #+#    #+#             */
/*   Updated: 2021/09/23 14:18:48 by anadege          ###   ########.fr       */
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
		g_exit_status = 130;
		ft_putchar('\n');
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
}

void	handle_signals(void)
{
	signal(SIGINT, sig_handler_function);
	signal(SIGQUIT, SIG_IGN);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlichir <hlichir@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/02 11:40:02 by anadege           #+#    #+#             */
/*   Updated: 2021/09/11 18:32:11 by hlichir          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
** Fonction pour verifier condition de sortie du minishell.
** Si non, libere memoire allouee pour prochaine boucle.
*/
int	check_if_exit_or_continue(t_infos *infos)
{
	if (!ft_strncmp(infos->curr_cmd, "exit", 5))
	{
		ft_putstr("exit\n");
		return (1);
	}
	if (infos->curr_cmd)
		free(infos->curr_cmd);
	if (infos->prompt)
		free(infos->prompt);
	return (0);
}

/*
** Fonction pour liberer la memoire allouee avant de quitter minishell.
*/
int	clean_exit(t_infos *infos)
{
	if (!infos)
		return (-1);
	if (infos->curr_cmd)
		free(infos->curr_cmd);
	if (infos->env)
		free_env(infos->env, -1);
	if (infos->prompt)
		free(infos->prompt);
	rl_clear_history();
	close(infos->fd_history);
	return (0);
}

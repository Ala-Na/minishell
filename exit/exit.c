/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlichir < hlichir@student.42.fr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/02 11:40:02 by anadege           #+#    #+#             */
/*   Updated: 2021/10/14 16:59:58 by hlichir          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

/*
** Function to free all allocated memory before leaving minishell.
*/
int	clean_exit(t_infos *infos, int init_exit)
{
	if (!infos)
		return (-1);
	clean_to_continue(infos, init_exit);
	if (infos->env)
		free_env(&infos->env, -1);
	if (infos->lst_var)
		free_lst_var(infos);
	rl_clear_history();
	if (close(infos->fd_history) == -1)
		return (-1);
	return (0);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anadege <anadege@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/02 11:40:02 by anadege           #+#    #+#             */
/*   Updated: 2021/09/02 11:52:29 by anadege          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

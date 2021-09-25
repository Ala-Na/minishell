/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlichir <hlichir@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/02 11:52:56 by anadege           #+#    #+#             */
/*   Updated: 2021/09/24 11:55:33 by anadege          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
** Function to initialize minishell
** Will fill the structure 'infos' and add the previous history from file
** Returns -1 in case of an error, 0 if not.
*/
int	init_minishell(t_infos *infos, char **env)
{	
	g_exit_status = -1;
	infos->prompt = NULL;
	infos->curr_cmd = NULL;
	infos->lst_tokens = NULL;
	infos->lst_cmds = NULL;
	infos->lst_var = NULL;
	if (add_new_var_to_list(infos, "?=0") < 0)
		return (-1);
	infos->fd_history = 0;
	infos->env = NULL;
	infos->fd_history = get_previous_history();
	if (infos->fd_history == 0)
		return (-1);
	if (save_env(infos, env) == -1 || infos->env == NULL)
		return (-1);
	return (0);
}

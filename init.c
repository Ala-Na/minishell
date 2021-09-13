/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlichir <hlichir@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/02 11:52:56 by anadege           #+#    #+#             */
/*   Updated: 2021/09/13 18:18:42 by hlichir          ###   ########.fr       */
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
	infos->prompt = NULL;
	infos->curr_cmd = NULL;
	infos->lst_var = NULL;
	add_new_var_to_list(infos, "?=0");
	infos->fd_history = 0;
	infos->env = NULL;
	infos->fd_history = get_previous_history();
	if (infos->fd_history == 0)
		return (-1);
	save_env(infos, env);
	if (infos->env == NULL)
		return (-1);
	return (0);
}

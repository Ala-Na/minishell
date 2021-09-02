/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anadege <anadege@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/02 11:52:56 by anadege           #+#    #+#             */
/*   Updated: 2021/09/02 12:03:36 by anadege          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
** Fonction d'initialisation de minishell.
** Remplie la structure infos et obtient l'historique.
** Retourne -1 en cas d'erreur, 0 sinon.
*/
int	init_minishell(t_infos *infos, char **env)
{
	infos->prompt = NULL;
	infos->curr_cmd = NULL;
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

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlichir < hlichir@student.42.fr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/02 11:40:02 by anadege           #+#    #+#             */
/*   Updated: 2021/09/28 14:51:29 by anadege          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

/*
** Function to free all allocated memory before leaving minishell.
*/
int	clean_exit(t_infos *infos)
{
	if (!infos)
		return (-1);
	if (infos->curr_cmd)
		free(infos->curr_cmd);
	if (infos->env)
		free_env(&infos->env, -1);
	if (infos->prompt)
		free(infos->prompt);
	if (infos->lst_tokens)
		free_token_list_from_extremity(&infos->lst_tokens, 0);
	if (infos->lst_cmds)
		free_cmd_list_from_extremity(&infos->lst_cmds, 0);
	if (infos->lst_var)
		free_lst_var(infos);
	rl_clear_history();
	close(infos->fd_history);
	return (0);
}

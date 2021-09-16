/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlichir <hlichir@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/02 11:40:02 by anadege           #+#    #+#             */
/*   Updated: 2021/09/16 17:50:57 by anadege          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
**	Function to change the exit status to 130 when ctrl+c is used!
*/
int	check_exit_status(t_infos *infos)
{
	if (g_exit_status == 130)
	{
		if (modify_var_in_list(infos, "?=130", NULL) < 0)
			return (-1);
		g_exit_status = 0;
	}
	return (0);
}

/*
** Function to check if "exit" was called as a command.
** If not, free allocated memory to prepare the next loop.
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
	if (infos->lst_cmds)
		free_cmd_list_from_extremity(infos->lst_cmds, 0);
	if (infos->lst_tokens)
		free_token_list_from_extremity(infos->lst_tokens, 0);
	infos->curr_cmd = NULL;
	infos->prompt = NULL;
	infos->lst_cmds = NULL;
	infos->lst_tokens = NULL;
	return (0);
}

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
		free_env(infos->env, -1);
	if (infos->prompt)
		free(infos->prompt);
	if (infos->lst_tokens)
		free_token_list_from_extremity(infos->lst_tokens, 0);
	if (infos->lst_cmds)
		free_cmd_list_from_extremity(infos->lst_cmds, 0);
	if (infos->lst_var)
		free_lst_var(infos);
	rl_clear_history();
	close(infos->fd_history);
	return (0);
}

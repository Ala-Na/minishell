/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlichir < hlichir@student.42.fr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/02 11:40:02 by anadege           #+#    #+#             */
/*   Updated: 2021/09/17 14:22:42 by hlichir          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
** Function to set g_exit_status to error
*/
int	set_g_status_to_error(int status)
{
	g_exit_status = status;
	return (-1);
}

/*
**	Function to update the exit status in case of an error!
**	exit(1) => an error happened 
*/
int	error_exit_status(char *str, t_infos *infos, char *new_status)
{
	if (modify_var_in_list(infos, new_status, NULL) < 0)
	{
		ft_puterr("Memory allocation error", 1);
		return (-1);
	}
	ft_puterr(str, 1);
	return (-1);
}

/*
**	Function to change the exit status to 130 when ctrl+c is used!
*/
int	check_exit_status(t_infos *infos)
{
	if (g_exit_status == 130)
	{
		if (modify_var_in_list(infos, "?=130", NULL) < 0)
			return (-1);
	}
	else if (g_exit_status == 1)
	{
		if (modify_var_in_list(infos, "?=130", NULL) < 0)
			return (-1);
	}
	else if (g_exit_status == 127)
	{
		if (modify_var_in_list(infos, "?=127", NULL) < 0)
			return (-1);
	}
	g_exit_status = 0;
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

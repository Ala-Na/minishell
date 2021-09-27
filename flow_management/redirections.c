/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlichir < hlichir@student.42.fr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/20 14:13:23 by hlichir           #+#    #+#             */
/*   Updated: 2021/09/27 12:10:46 by hlichir          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	adapt_final_output(t_infos *infos)
{
	t_cmd	*cmd;

	cmd = infos->lst_cmds;
	while (cmd)
	{
		if (cmd->next_operator == LT || cmd->next_operator == LT_DBL)
		{
			if (cmd->next && cmd->output)
				cmd->next->output = ft_strdup(cmd->output);
		}
		cmd = cmd->next;
	}
}

/*
** Comment to do
*/
int	check_output_redirections(t_infos *infos)
{
	t_cmd	*cmd;

	cmd = infos->lst_cmds;
	while (cmd)
	{
		if (cmd->next_operator == GT && cmd->next)
		{
			if (single_right_redirect(infos, cmd) < 0)
				return (-1);
		}
		else if (cmd->next_operator == GT_DBL && cmd->next)
		{
			if (double_right_redirect(infos, cmd) < 0)
				return (-1);
		}
		cmd = cmd->next;
	}
//	adapt_final_output(infos);
	return (0);
}

/*
** Comment to do
*/
int	check_input_redirections(t_infos *infos)
{
	t_cmd	*cmd;

	cmd = infos->lst_cmds;
	while (cmd)
	{
		if ((cmd->next_operator == LT || cmd->next_operator == LT_DBL) \
			&& cmd->next)
		{
			if (handle_multiple_redirections(infos, &cmd) < 0)
				return (-1);
		}
		cmd = cmd->next;
	}
	return (0);
}

/*
** Comment to do
*/
int	handle_multiple_redirections(t_infos *infos, t_cmd **cmd)
{
	t_cmd	*current;
	t_cmd	*next_cmd;

	current = *cmd;
	next_cmd = (*cmd)->next;
	while (next_cmd)
	{
		if (current->next_operator == LT)
		{
			if (single_left_redirect(infos, *cmd, next_cmd) < 0)
				return (-1);
		}
		else if (current->next_operator == LT_DBL)
		{
			if (double_left_redirect(infos, *cmd, next_cmd) < 0)
				return (-1);
		}
		else
			break ;
		current = current->next;
		next_cmd = next_cmd->next;
	}
	*cmd = current;
	return (0);
}

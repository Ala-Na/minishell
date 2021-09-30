/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   launch_cmds.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlichir < hlichir@student.42.fr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/22 17:28:50 by anadege           #+#    #+#             */
/*   Updated: 2021/09/30 17:06:36 by anadege          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

/*
** Function to check and do assignments when cmd is not called inside a pipeline.
** Set exec_token to the first non assignment token.
** Return -1 in case of error, 0 otherwise.
*/
int	assignments_management(t_infos *infos, t_cmd *cmd, t_token **exec_token)
{
	int		assignments;
	t_token	*first_non_assignment;

	assignments = check_assignments(infos, cmd);
	if (assignments == 1)
		return (1);
	else if (assignments == -1)
		return (-1);
	first_non_assignment = cmd->start;
	while (first_non_assignment && first_non_assignment->type == ASSIGNMENT)
	{
		first_non_assignment = first_non_assignment->next;
		if (first_non_assignment == infos->lst_cmds->end)
			break ;
	}
	if (!first_non_assignment || first_non_assignment->type == ASSIGNMENT)
		return (return_error(1, "something went wrong", 0, -1));
	*exec_token = first_non_assignment;
	return (0);
}

/*
** Function to start launch of a simple command.
** First, redirections are checked and interpreted.
** Secondary, a check is made to verify if the command is only made assignments
** and assignments are made if it's the case.
** Tertiary, the first token which is not an assignment is found. It's checked
** if it corresponds to a builtin. If it is, the builtin is called. If not,
** the command is executated as a programm.
*/
int	launch_simple_cmd(t_infos *infos, t_cmd *cmd, int from_pipe)
{
	int			only_assignments;
	t_builtin	builtin;

	if (!infos || !cmd || !cmd->start)
		return (return_error(1, "something went wrong", 0, -1));
	only_assignments = assignments_management(infos, cmd, &cmd->start);
	if (only_assignments == -1)
		return (-1);
	else if (only_assignments == 1)
		return (0);
	builtin = check_builtin(cmd->start->token);
	if (builtin == -1)
		return (-1);
	else if (builtin != NONE)
		return (launch_builtin(infos, cmd, builtin));
	if (!from_pipe)
		return (execute_simple_cmd(infos));
	else
		child_execution(infos, cmd);
	return (0);
}

/*
** Function to check if any pipe is present.
** Return -1 in case of error, 0 if no pipe is present, 1 otherwise.
*/
int	check_if_pipes(t_infos *infos)
{
	t_cmd	*curr_cmd;
	int		nbr_pipes;

	if (!infos || !infos->lst_cmds)
		return (-1);
	curr_cmd = infos->lst_cmds;
	nbr_pipes = 0;
	while (curr_cmd)
	{
		if (curr_cmd->next_operator == PIPE)
			nbr_pipes += 1;
		curr_cmd = curr_cmd->next;
	}
	return (nbr_pipes);
}

/*
** Function to start launch of commands.
** WARNING : Remplace return(0) par return (launch_pipes)
*/
int	launch_cmds(t_infos *infos)
{
	int	nbr_pipes;

	if (!infos)
		return (return_error(1, "something went wrong", 0, -1));
	nbr_pipes = check_if_pipes(infos);
	if (nbr_pipes == -1)
		return (return_error(1, "something went wrong", 0, -1));
	else if (nbr_pipes == 0)
		return (launch_simple_cmd(infos, infos->lst_cmds, 0));
	return (launch_pipes_cmds(infos, infos->lst_cmds, nbr_pipes));
}

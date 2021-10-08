/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   launch_cmds.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlichir <hlichir@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/22 17:28:50 by anadege           #+#    #+#             */
/*   Updated: 2021/10/08 10:50:41 by anadege          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

/*
** Function to check and do assignments when cmd is not called inside a pipeline.
** Set exec_token to the first non assignment token.
** Return -1 in case of error, 0 if only assignments are presents in the command
** 1 otherwise.
*/
int	assignments_management(t_infos *infos, t_cmd *head_cmd, t_cmd *cmd,
		t_token **exec_token)
{
	int		assignments;
	t_cmd	*curr_cmd;

	assignments = check_assignments(infos, head_cmd, cmd, *exec_token);
	if (assignments == 1)
		return (0);
	else if (assignments == -1)
		return (-1);
	curr_cmd = NULL;
	if ((*exec_token)->type == ASSIGNMENT)
		*exec_token = get_exec_token(infos, head_cmd, &curr_cmd);
	return (1);
}

/*
** Second an main part of launch_simple_cmd.
** Tertiary, the first token which is not an assignment is found. It's checked
** if it corresponds to a builtin. If it is, the builtin is called. If not,
** the command is executated as a programm.
*/
int	launch_simple_cmd(t_infos *infos, t_cmd *cmd,
		t_token *exec_token, int from_pipe)
{
	char		*str;
	t_builtin	builtin;

	str = ft_strdup_linked_string(exec_token);
	if (!str)
		return (return_error(1, "memory allocation error", 0, -1));
	builtin = check_builtin(str);
	free(str);
	if ((int)builtin == -1)
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
** Function to start launch of a simple command.
** First, redirections are checked and interpreted.
** Secondary, a check is made to verify if the command is only made assignments
** and assignments are made if it's the case.
*/
int	init_launch_simple_cmd(t_infos *infos, t_cmd *cmd, int from_pipe)
{
	int			only_assignments;
	t_cmd		*curr_cmd;
	t_token		*exec_token;

	curr_cmd = NULL;
	exec_token = NULL;
	if (!infos || !cmd)
		return (return_error(1, "something went wrong", 0, -1));
	exec_token = get_next_token(infos, cmd, &curr_cmd, exec_token);
	if (!exec_token && g_exit_status == 0)
		return (add_redirections(cmd, 0));
	else if (!exec_token)
		return (-1);
	only_assignments = assignments_management(infos, cmd, curr_cmd,
			&exec_token);
	if (only_assignments <= 0)
		return (only_assignments);
	return (launch_simple_cmd(infos, cmd, exec_token, from_pipe));
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
		return (init_launch_simple_cmd(infos, infos->lst_cmds, 0));
	return (launch_pipes_cmds(infos, infos->lst_cmds, nbr_pipes));
}

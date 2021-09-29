/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_pipe.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anadege <anadege@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/27 17:16:19 by anadege           #+#    #+#             */
/*   Updated: 2021/09/29 14:43:03 by anadege          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

#define WRITE_SIDE 1
#define READ_SIDE 0

/*
**
*/
void	pipe_loop(t_infos *infos, t_cmd *cmd, int prev_pipe[2], int **child_pids, int i)
{
	int		fd[2];
	int		wstatus;
	int		res;

	if (!infos || !cmd)
	{
		return_error(1, "something went wrong", 0, 0);
		exit(g_exit_status);
	}
	if (pipe(fd) == -1)
	{
		return_error(1, "pipe failed", 0, 0);
		exit(g_exit_status);
	}
	(*child_pids)[i] = fork();
	if ((*child_pids)[i] == -1)
	{
		return_error(1, "fork failed", 0, 0);
		exit(g_exit_status);
	}
	else if ((*child_pids)[i] == 0)
	{
		close(fd[1]);
		if (prev_pipe)
			dup2(prev_pipe[0], 0);
		close(fd[0]);
		if (cmd->next)
			pipe_loop(infos, cmd->next, fd, child_pids, i + 1);
		child_execution(infos, cmd);
	}
	else
	{
		close(fd[0]);
		if (cmd->next)
			dup2(fd[1], 1);
		close(fd[1]);
	}
}

/*
** Function to call when a command line contains at least 1 pipe.
** Assignments are skipped.
** WARNING : ONLY WORK FOR CMDS WITH ONLY PIPES
*/
int	launch_pipes_cmds(t_infos *infos, t_cmd *cmd, int prev_pipe[2], int nbr_pipes)
{
	int		res;
	int		wstatus;
	pid_t	*child_pids;
	int		i;

	if (!infos || !cmd)
		return (return_error(1, "something went wrong", 0, -1));
	child_pids = malloc(sizeof(*child_pids) * (nbr_pipes + 1));
	i = 0;
	while (i < nbr_pipes + 1)
		child_pids[i++] = 0;
	pipe_loop(infos, cmd, prev_pipe, &child_pids, 0);
	i = nbr_pipes;
	while (i >= 0) 
	{
		if (child_pids[i])
			res = waitpid(child_pids[i], &wstatus, 0);
		i--;
	}
	return (wstatus);
}

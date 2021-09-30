/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_pipe.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anadege <anadege@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/27 17:16:19 by anadege           #+#    #+#             */
/*   Updated: 2021/09/30 13:19:26 by anadege          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

#define WRITE_SIDE 1
#define READ_SIDE 0
#define UNSET -1

/*
**
*/
void	pipe_loop(t_infos *infos, t_cmd *cmd, int **child_pids)
{
	int		i;
	int		new_pid;
	int		pipe_fd[2];
	int		wstatus;
	int		res;
	int		prev_fd[2];

	if (!infos || !cmd)
	{
		return_error(1, "something went wrong", 0, 0);
		exit(g_exit_status);
	}
	i = 0;
	prev_fd[READ_SIDE] = UNSET;
	prev_fd[WRITE_SIDE] = UNSET;
	while (cmd)
	{
		if (pipe(pipe_fd) == -1)
		{
			return_error(1, "pipe failed", 0, 0);
			exit(g_exit_status);
		}
		new_pid = fork();
		if (new_pid == -1)
		{
			return_error(1, "fork failed", 0, 0);
			exit(g_exit_status);
		}
		else if (new_pid == 0)
		{
			if (prev_fd[READ_SIDE] != UNSET || prev_fd[WRITE_SIDE] != UNSET)
			{
				close(prev_fd[WRITE_SIDE]);
				dup2(prev_fd[READ_SIDE], STDIN_FILENO);
				close(prev_fd[READ_SIDE]);
			}
			if (cmd->next)
			{
				close(pipe_fd[READ_SIDE]);
				dup2(pipe_fd[WRITE_SIDE], STDOUT_FILENO);
				close(pipe_fd[WRITE_SIDE]);
			}
			res = launch_simple_cmd(infos, cmd, 1);
			exit(res);
			i++;
		}
		else
		{
			(*child_pids)[i] = new_pid; 
			if (prev_fd[READ_SIDE] != UNSET && prev_fd[WRITE_SIDE] != UNSET)
			{
				close(prev_fd[READ_SIDE]);
				close(prev_fd[WRITE_SIDE]);
				prev_fd[READ_SIDE] = UNSET;
				prev_fd[WRITE_SIDE] = UNSET;
			}
			if (cmd->next)
			{
				prev_fd[READ_SIDE] = pipe_fd[READ_SIDE];
				prev_fd[WRITE_SIDE] = pipe_fd[WRITE_SIDE];
			}
			cmd = cmd->next;
		}
	}
}

/*
** Function to call when a command line contains at least 1 pipe.
** Assignments are skipped.
** WARNING : ONLY WORK FOR CMDS WITH ONLY PIPES
*/
int	launch_pipes_cmds(t_infos *infos, t_cmd *cmd, int nbr_pipes)
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
	pipe_loop(infos, cmd, &child_pids);
	i = nbr_pipes;
	while (i >= 0) 
	{
		if (child_pids[i])
			res = waitpid(child_pids[i], &wstatus, 0);
		i--;
	}
	free(child_pids);
	return (wstatus);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_pipe.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anadege <anadege@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/27 17:16:19 by anadege           #+#    #+#             */
/*   Updated: 2021/09/28 11:29:02 by anadege          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	pipes_fork_and_dup(t_infos *infos, t_cmd *curr_cmd)
{
	pid_t	cmd_pid;
	int		pipefd[2];
	int		res;
	int		wstatus;

	if (pipe(pipefd) == -1)
	{
		return (return_error(1, "pipe failed", 0, -1));
	}
	cmd_pid = fork();
	if (cmd_pid == -1)
		return (return_error(1, "fork failed", 0, -1));
	else if (cmd_pid > 0) //Parent of cmd execve
	{
		close(pipefd[1]);
		dup2(pipefd[0], 0);
		res = waitpid(cmd_pid, &wstatus, 0);
		if (res == -1)
			return (return_error(1, strerror(errno), 0, -1));
		else if (WIFEXITED(wstatus))
			return (return_value(WEXITSTATUS(wstatus), 0));
		else if (WIFSIGNALED(wstatus))
			return (return_signal(WTERMSIG(wstatus), 0));
	}
	else
	{
		close(pipefd[0]);
		dup2(pipefd[1], 1);
		child_execution(infos, curr_cmd);
	}
	return (return_error(1, "something went wrong", 0, -1));

}

void	pipes_child_preparation(t_infos *infos)
{
	t_cmd	*curr_cmd;
	t_cmd	*next_cmd;

	if (!infos || !infos->lst_cmds)
	{
		return_error(1, "something went wrong", 0, -1);
		exit(g_exit_status);
	}
	curr_cmd = infos->lst_cmds;
	while (curr_cmd && curr_cmd->next_operator != -1)
	{
		pipes_fork_and_dup(infos, curr_cmd);
		curr_cmd = curr_cmd->next;
	}
	child_execution(infos, curr_cmd);
	exit (g_exit_status);
}


/*
** Function to call when a command line contains at least 1 pipe.
** Assignments are skipped.
** WARNING : ONLY WORK FOR CMDS WITH ONLY PIPES
*/
int	launch_pipes_cmds(t_infos *infos)
{
	pid_t	child_pid;
	int		wstatus;
	int		res;

	child_pid = fork();
	if (child_pid == -1)
		return (return_error(1, "fork failed", 0, -1));
	else if (child_pid > 0) //Main parent to keep minishell open
	{
		res = waitpid(child_pid, &wstatus, 0);
		if (res == -1)
			return (return_error(1, strerror(errno), 0, -1));
		else if (WIFEXITED(wstatus))
			return (return_value(WEXITSTATUS(wstatus), 0));
		else if (WIFSIGNALED(wstatus))
			return (return_signal(WTERMSIG(wstatus), 0));
	}
	else
		pipes_child_preparation(infos);
	return (return_error(1, "something went wrong here", 0, -1));
}

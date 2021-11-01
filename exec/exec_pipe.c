/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_pipe.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlichir <hlichir@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/27 17:16:19 by anadege           #+#    #+#             */
/*   Updated: 2021/10/27 18:50:24 by hlichir          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	last_close(int pipe_fd[2])
{
	if (close(pipe_fd[READ_SIDE]) == -1)
		return (return_error(1, strerror(errno), 0, -1));
	if (close(pipe_fd[WRITE_SIDE]) == -1)
		return (return_error(1, strerror(errno), 0, -1));
	if (g_exit_status != 0)
		return (-1);
	return (0);
}

/*
** Function for child execution of pipe_loop function.
** If no previous error is meeted (because of close or dup2 calls)
** it goes to launch_simple_cmd function.
** 3 cases are possible :
**  - The command only contains assignments which are performed
**    (but they don't have any impact on the rest of pipeline as 
**    each child is memory-separated from it's parent). It returns
**    -1 in case of error, 0 otherwise. Exit returns g_exit_status.
**  - The command contains a builtin, which is executed by going
**    into the corresponding functions. It returns -1 in case of
**    error, 0 otherwise. Exit returns g_exit_status.
**  - None of the previous case: it goes to child_execution and a
**    call to execve is made. Exit is made in child_exection.
** It always exit on the value of g_exit_status.
*/
void	pipe_child_execution(t_infos *infos, t_cmd *cmd, int pipe_fd[2],
		int prev_fd[2])
{
	if (prev_fd[READ_SIDE] != FD_UNSET && prev_fd[WRITE_SIDE] != FD_UNSET)
	{
		if (close(prev_fd[WRITE_SIDE]) == -1)
			return_error(1, strerror(errno), 0, 0);
		if (dup2(prev_fd[READ_SIDE], STDIN_FILENO) == -1)
			return_error(1, strerror(errno), 0, 0);
		if (close(prev_fd[READ_SIDE]) == -1)
			return_error(1, strerror(errno), 0, 0);
	}
	if (get_next_cmd(cmd) != NULL)
		close_and_duplicate_pipe_fd(pipe_fd);
	infos->pipe_read_side = pipe_fd[READ_SIDE];
	infos->pipe_write_side = pipe_fd[WRITE_SIDE];
	if (g_exit_status == 0)
		init_launch_simple_cmd(infos, cmd, 1);
	clean_exit(infos, 0);
	if (infos->curr_cmd)
		free(infos->curr_cmd);
	exit(g_exit_status);
}

/*
** Function to manipulate fd between prev_fd and pipe_fd in parent
** for next iteration of pipe_loop.
** Returns -1 in case of error, 0 otherwise.
*/
int	pipe_parent_fd_manipulation(t_cmd *cmd, int pipe_fd[2],
		int (*prev_fd)[2])
{
	if ((*prev_fd)[READ_SIDE] != FD_UNSET
		&& (*prev_fd)[WRITE_SIDE] != FD_UNSET)
	{
		if (close((*prev_fd)[READ_SIDE]) == -1)
			return (return_error(1, strerror(errno), 0, -1));
		if (close((*prev_fd)[WRITE_SIDE]) == -1)
			return (return_error(1, strerror(errno), 0, -1));
		(*prev_fd)[READ_SIDE] = FD_UNSET;
		(*prev_fd)[WRITE_SIDE] = FD_UNSET;
	}
	if (get_next_cmd(cmd) != NULL)
	{
		(*prev_fd)[READ_SIDE] = pipe_fd[READ_SIDE];
		(*prev_fd)[WRITE_SIDE] = pipe_fd[WRITE_SIDE];
	}
	return (0);
}

/*
** Loop function for pipelines. It creates a pipe for each command and then
** fork. Command is executed in child.
*/
int	pipe_loop(t_infos *infos, t_cmd *cmd, int **child_pids, int i)
{
	int		new_pid;
	int		pipe_fd[2];
	int		prev_fd[2];

	if (!infos || !cmd || !*child_pids)
		return (return_error(1, "something went wrong", 0, -1));
	init_variables(&(prev_fd[READ_SIDE]), &(prev_fd[WRITE_SIDE]), FD_UNSET);
	while (cmd)
	{
		if (pipe(pipe_fd) == -1)
			return (return_error(1, "pipe failed", 0, -1));
		new_pid = fork();
		if (new_pid == -1)
			return (return_error(1, "fork failed", 0, -1));
		else if (new_pid == 0)
		{
			free(*child_pids);
			pipe_child_execution(infos, cmd, pipe_fd, prev_fd);
		}
		(*child_pids)[i++] = new_pid;
		if (pipe_parent_fd_manipulation(cmd, pipe_fd, &prev_fd) == -1)
			return (-1);
		cmd = get_next_cmd(cmd);
	}
	return (last_close(pipe_fd));
}

/*
** Function to call when a command line contains at least 1 pipe.
** Wait for all child_pids.
*/
int	launch_pipes_cmds(t_infos *infos, t_cmd *cmd, int nbr_pipes)
{
	int		res;
	t_cmd	*redir_cmd;
	pid_t	*child_pids;
	int		i;

	if (!infos || !cmd)
		return (return_error(1, "something went wrong", 0, -1));
	child_pids = malloc(sizeof(*child_pids) * (nbr_pipes + 1));
	if (!child_pids)
		return (return_error(1, "memory allocation error", 0, -1));
	i = 0;
	while (i < nbr_pipes + 1)
		child_pids[i++] = 0;
	redir_cmd = cmd;
	while (redir_cmd)
	{
		if (add_redirections(infos, redir_cmd) < 0)
			return (free_child_pids(&child_pids));
		redir_cmd = get_next_cmd(redir_cmd);
	}
	res = pipe_loop(infos, cmd, &child_pids, 0);
	if (res == -1)
		return (free_child_pids(&child_pids));
	return (wait_for_pipeline_childs(nbr_pipes, &child_pids));
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_pipe_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlichir <hlichir@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/30 16:51:37 by anadege           #+#    #+#             */
/*   Updated: 2021/10/27 18:50:17 by hlichir          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

/*
** Function to get next command in pipeline.
** Returns NULL if the previous command was the last of the pipeline
** or in case of error.
*/
t_cmd	*get_next_cmd(t_cmd *cmd)
{
	t_cmd	*next_cmd;

	if (!cmd)
		return ((t_cmd *)(return_null_error(1, "something went wrong", 0)));
	next_cmd = cmd;
	while (next_cmd)
	{
		if (next_cmd->next_operator == PIPE
			|| (int)next_cmd->next_operator == -1)
			break ;
		next_cmd = next_cmd->next;
	}
	if ((int)next_cmd->next_operator == -1)
		return (NULL);
	next_cmd = next_cmd->next;
	return (next_cmd);
}

/*
** Function to wait for all childs of a pipeline.
** Calls return_pipeline to modify g_exit_status with exit value
** of last child.
** Returns -1 in case of error, 0 otherwise.
*/
int	wait_for_pipeline_childs(int nbr_pipes, pid_t **child_pids)
{
	int	i;
	int	res;
	int	wstatus;

	i = 0;
	wstatus = 0;
	while (i < nbr_pipes + 1)
	{
		if ((*child_pids)[i] != 0)
			res = waitpid((*child_pids)[i], &wstatus, 0);
		if (res == -1)
		{
			free(*child_pids);
			return (return_error(1, strerror(errno), 0, -1));
		}
		i++;
	}
	return_pipeline(wstatus);
	free(*child_pids);
	return (0);
}

/*
**	Sub_function for the function pipe_child_execution
*/
void	close_and_duplicate_pipe_fd(int pipe_fd[2])
{
	if (close(pipe_fd[READ_SIDE]) == -1)
		return_error(1, strerror(errno), 0, 0);
	if (dup2(pipe_fd[WRITE_SIDE], STDOUT_FILENO) == -1)
		return_error(1, strerror(errno), 0, 0);
	if (close(pipe_fd[WRITE_SIDE]) == -1)
		return_error(1, strerror(errno), 0, 0);
}

/*
**	Sub_function for the function 
*/
int	free_child_pids(pid_t **child_pids)
{
	free(*child_pids);
	return (-1);
}

void	close_pipe_fds(t_infos *infos)
{
	if (infos->pipe_write_side != 1)
		close(infos->pipe_write_side);
	if (infos->pipe_read_side != 0)
		close(infos->pipe_read_side);
}

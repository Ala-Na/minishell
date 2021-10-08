/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_pipe_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlichir < hlichir@student.42.fr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/30 16:51:37 by anadege           #+#    #+#             */
<<<<<<< HEAD
/*   Updated: 2021/10/08 10:36:35 by hlichir          ###   ########.fr       */
=======
/*   Updated: 2021/10/08 11:01:47 by anadege          ###   ########.fr       */
>>>>>>> errors Werror corrected
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
	{
		return_error(1, "something went wrong", 0, 0);
		return (NULL);
	}
	next_cmd = cmd;
	while (next_cmd)
	{
<<<<<<< HEAD
		if (next_cmd->next_operator == PIPE \
			|| next_cmd->next_operator == (t_operator)(-1))
			break ;
		next_cmd = next_cmd->next;
	}
	if (next_cmd->next_operator == (t_operator)(-1))
=======
		if (next_cmd->next_operator == PIPE || (int)next_cmd->next_operator == -1)
			break ;
		next_cmd = next_cmd->next;
	}
	if ((int)next_cmd->next_operator == -1)
>>>>>>> errors Werror corrected
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

	(void)infos;
	i = 0;
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

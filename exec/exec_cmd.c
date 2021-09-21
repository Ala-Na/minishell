/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlichir <hlichir@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/09 15:00:10 by anadege           #+#    #+#             */
/*   Updated: 2021/09/21 11:24:48 by anadege          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

/*
** Function to free arguments of execve command, previously set.
*/
void	free_child_exec_var(char *exec_path, char **exec_env, char **exec_args)
{
	if (exec_path)
		free(exec_path);
	if (exec_env)
		free_env(exec_env, -1);
	if (exec_args)
		free_env(exec_args, -1);
}

/*
** Function for child execution calling execve function after set up of
** differents execve arguments.
** Child should normally end inside the execve function. If not, we 
** arrive at the end of the function where an exit failure is issued.
*/
int	child_execution(t_infos *infos)
{
	char	*exec_path;
	char	**exec_env;
	char	**exec_args;
	t_token	*exec_token;

	exec_path = get_exec_path(infos, infos->lst_cmds, &exec_env, &exec_token);
	if (!exec_path || !exec_env)
	{
		free_child_exec_var(NULL, exec_env, NULL);
		return (-1);
	}
	exec_args = get_exec_args(infos, infos->lst_cmds, exec_token);
	if (!exec_args)
	{
		free_child_exec_var(exec_path, exec_env, NULL);
		return (error_exit_status("error", infos, "?=1"));
	}
	if (execve(exec_path, exec_args, exec_env) == -1)
	{
		free_child_exec_var(exec_path, exec_env, exec_args);
		return (error_exit_status(strerror(errno), infos, "?=1"));
	}
	free_child_exec_var(exec_path, exec_env, exec_args);
	exit(1);
	return (-1);
}

/*
** exec_elems[0] is equivalent to executable environmentals variables.
** exec_elems[1] is equivalent to executable arguments.
** WARNING : Value of ? may need to be modified in case of errors.
*/
int	execute_simple_cmd(t_infos *infos)
{
	pid_t	pid;
	int		wstatus;

	pid = fork();
	if (pid < 0)
		return (error_exit_status(strerror(errno), infos, "?=1"));
	else if (pid > 0)
	{
		waitpid(pid, &wstatus, 0);
		kill(pid, SIGTERM);
	}
	else
	{
		return (child_execution(infos));
	}
	return (0);
}

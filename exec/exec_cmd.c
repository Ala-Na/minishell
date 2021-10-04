/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlichir <hlichir@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/09 15:00:10 by anadege           #+#    #+#             */
/*   Updated: 2021/10/04 21:11:35 by anadege          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

/*
** Function to free arguments of execve command, previously set.
*/
void	free_child_exec_var_and_exit(t_infos *infos, char **exec_path,
			char ***exec_env, char ***exec_args)
{
	if (exec_path && *exec_path)
		free(*exec_path);
	if (exec_env && *exec_env && *exec_env != infos->env)
		free_env(exec_env, -1);
	if (exec_args && *exec_args)
		free_env(exec_args, -1);
	exit(g_exit_status);
}

/*
** Function for child execution calling execve function after set up of
** differents execve arguments.
** Child should normally end inside the execve function. If not, we 
** arrive at the end of the function where an exit failure is issued.
*/
void	child_execution(t_infos *infos, t_cmd *exec_cmd)
{
	char	*exec_path;
	char	**exec_env;
	char	**exec_args;
	t_token	*exec_token;

	if (add_redirections(exec_cmd, 1) < 0)
		free_child_exec_var_and_exit(infos, NULL, NULL, NULL);
	if (!infos || !exec_cmd)
	{
		return_error(1, "something went wrong", 0, 0);
		exit(g_exit_status);
	}
	exec_path = get_exec_path(infos, exec_cmd, &exec_env, &exec_token);
	if (!exec_path || !exec_env)
		free_child_exec_var_and_exit(infos, NULL, &exec_env, NULL);
	exec_args = get_exec_args(infos, exec_cmd, exec_token);
	if (!exec_args)
		free_child_exec_var_and_exit(infos, &exec_path, &exec_env, NULL);
	if (execve(exec_path, exec_args, exec_env) == -1)
	{
		return_error(126, strerror(errno), 0, 0);
		free_child_exec_var_and_exit(infos, &exec_path, &exec_env, &exec_args);
	}
	free_child_exec_var_and_exit(infos, &exec_path, &exec_env, &exec_args);
}

/*
** exec_elems[0] is equivalent to executable environmentals variables.
** exec_elems[1] is equivalent to executable arguments.
** WARNING : Value of ? may need to be modified in case of errors.
*/
int	execute_simple_cmd(t_infos *infos)
{
	pid_t	child_pid;
	int		wstatus;
	int		res;
	char	*str;

	child_pid = fork();
	if (child_pid == -1)
		return (return_error(1, "fork failed", 0, -1));
	else if (child_pid > 0)
	{
		res = waitpid(child_pid, &wstatus, 0);
		if (res == -1)
			return (return_error(1, strerror(errno), 0, -1));
		else if (WIFEXITED(wstatus))
			return (return_value(WEXITSTATUS(wstatus)));
		else if (WIFSIGNALED(wstatus))
			return (return_signal(WTERMSIG(wstatus)));
	}
	else
		child_execution(infos, infos->lst_cmds);
	return (return_error(1, "something went wrong", 0, -1));
}

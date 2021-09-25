/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlichir <hlichir@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/09 15:00:10 by anadege           #+#    #+#             */
/*   Updated: 2021/09/25 23:16:05 by hlichir          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

/*
** Function to free arguments of execve command, previously set.
*/
void	free_child_exec_var(t_infos *infos, char *exec_path, char **exec_env,
			char **exec_args)
{
	if (exec_path)
		free(exec_path);
	if (exec_env && exec_env != infos->env)
		free_env(exec_env, -1);
	if (exec_args)
		free_env(exec_args, -1);
	if (exec_path && infos->lst_cmds->input)
		if (unlink("./tmp_file") < 0)
			perror(strerror(errno));
}

/*
** Function for child execution calling execve function after set up of
** differents execve arguments.
** Child should normally end inside the execve function. If not, we 
** arrive at the end of the function where an exit failure is issued.
*/
void	child_execution(t_infos *infos, int fds[2])
{
	char	*exec_path;
	char	**exec_env;
	char	**exec_args;
	t_token	*exec_token;

	exec_path = get_exec_path(infos, infos->lst_cmds, &exec_env, &exec_token);
	if (!exec_path || !exec_env)
	{
		free_child_exec_var(infos, NULL, exec_env, NULL);
		exit(1);
	}
	exec_args = get_exec_args(infos, infos->lst_cmds, exec_token);
	if (!exec_args)
	{
		free_child_exec_var(infos, exec_path, exec_env, NULL);
		exit(1);
	}
	else if (execve(exec_path, exec_args, exec_env) == -1)
	{
		free_child_exec_var(infos, exec_path, exec_env, exec_args);
		printf("Errno value is %i\n", errno);
		exit (errno);
	}
	free_child_exec_var(infos, exec_path, exec_env, exec_args);
	exit(1);
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
	int		fds[2];

	child_pid = fork();
	if (child_pid < 0)
		return (error_exit_status(strerror(errno), 0, infos, "?=1"));
	else if (child_pid > 0)
	{
		res = waitpid(child_pid, &wstatus, 0);
		if (res == -1)
		{
			ft_puterr(strerror(errno), 2);
			modify_exit_value_variable(infos, errno);
		}
		else if (WIFEXITED(wstatus))
			modify_exit_value_variable(infos, WEXITSTATUS(wstatus));
		else if (WIFSIGNALED(wstatus))
		{
			if (WTERMSIG(wstatus) == SIGSEGV)
			{
				ft_puterr("Segfault", 2);
				modify_exit_value_variable(infos, 137);
			}
			else
				modify_exit_value_variable(infos, WTERMSIG(wstatus));
		}
	}
	else
	{
		if (pipe(fds) == -1)
			return (error_exit_status("Error on pipes\n", 1, infos, "?=1"));
		child_execution(infos, fds);
	}
	return (0);
}

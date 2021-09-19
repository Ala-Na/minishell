/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlichir <hlichir@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/09 15:00:10 by anadege           #+#    #+#             */
/*   Updated: 2021/09/19 23:30:51 by anadege          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"
/*
char	**get_exec_args(t_infos *infos, t_cmd *cmd, t_token *exec_path)
{
	char	**exec_args;
}
*/
/*
** Function which return token corresponding to executable absolute or relative path
** and register assignments variables inside exec_env.
** Return NULL if error.
*/
t_token	*move_to_exec(t_infos *infos, t_cmd *cmd, char ***exec_env)
{
	int	diff_exec_env_size;

	diff_exec_env_size = get_exec_env_diff_size(infos, cmd);
	if (copy_env(infos, infos->env, exec_env, diff_exec_env_size) < 0)
		return (NULL);
	while (cmd->start->type == ASSIGNMENT)
	{
		if (add_elem_to_exec_env(infos, exec_env, cmd->start) < 0)
		{
			free_env(*exec_env, -1);
			return (NULL);
		}
		if (cmd->start == cmd->end)
			break ;
		cmd->start = cmd->start->next;
	}
	return (cmd->start);
}

/*
** Function which return exec_path and set up the executable environment
** variables inside exec_env.
** Return NULL if an error occurs.
*/
char	*get_exec_path(t_infos *infos, t_cmd *cmd, char ***exec_env)
{
	t_token	*exec_token;
	char	*path;

	exec_token = move_to_exec(infos, cmd, exec_env);
	if (!exec_token)
		return (NULL);
	path = ft_strndup(exec_token->token, exec_token->length);
	return (get_path(path, *exec_env));
}

/*
int	execute_simple_cmd(t_infos *infos)
{
	pid_t	pid;
	int		wstatus;
	char	*exec_path;
	char	**exec_args;
	char	**exec_env;

	pid = fork();
	if (pid < 0) // Cas où fork a foiré
		return (-1); //erreur fork, cf errno
	else if (pid > 0)
	{
		waitpid(pid, &wstatus, 0);
		kill(pid, SIGTERM);
	}
	else
	{
		exec_path = get_exec_path(infos, cmd, &exec_env);
		exec_args = get_exec_args(infos, cmd, exec_path);

		if (execve(filename, args, exec_env) == -1)
			//print message erreur; //Cas ou execution a echoue, + errno
		free(exec_path);
		free_env(exec_env, -1);
		exit(EXIT_FAILURE); //On arrive ici que si execve a échoué, car normalement 
		//le child est exit quand execve est successfull
	}
	return (0);
}*/

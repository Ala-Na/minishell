/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlichir <hlichir@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/09 15:00:10 by anadege           #+#    #+#             */
/*   Updated: 2021/09/17 23:34:45 by anadege          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_token	*move_to_exec(t_infos *infos, t_cmd *cmd, char ***exec_env)
{
	if (copy_env(infos, infos->env, exec_env) < 0)
		return (NULL); //gestion exit status dans copy_env
	while (cmd->start != cmd->end && cmd->start->type == ASSIGNMENT)
	{
		if (add_elem_to_exec_env(infos, exec_env, cmd->start) < 0)
		{
			free_env(*exec_env, -1);
			return (NULL); // gestion exit status dans add_elem_to_exec_env
		}
		cmd->start = cmd->start->next;
	}
	if (cmd->start->type == ASSIGNMENT)
		return (NULL); // pas de gestion exit status
	return (cmd->start);
}


char	*get_exec(t_infos *infos, t_cmd *cmd, char ***exec_env)
{
	t_token	*exec_token;

	exec_token = move_to_exec(infos, cmd, exec_env);
	if (!exec_token)
		return (NULL);
	//get path et return path
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
		//On est dans le parent
		waitpid(pid, &wstatus, 0);
		kill(pid, SIGTERM);
	}
	else
	{
		if (execve(filename, args, infos->env) == -1)
			//print message erreur; //Cas ou execution a echoue, + errno
		exit(EXIT_FAILURE); //On arrive ici que si execve a échoué, car normalement 
		//le child est exit quand execve est successfull
	}
	return (0);
}*/

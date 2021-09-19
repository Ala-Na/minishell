/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlichir < hlichir@student.42.fr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/09 15:00:10 by anadege           #+#    #+#             */
/*   Updated: 2021/09/24 14:09:40 by anadege          ###   ########.fr       */
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
<<<<<<< HEAD
<<<<<<< HEAD
	t_cmd	*cmd;
	t_var	*current;

	cmd = infos->lst_cmds;
	if (cmd && cmd->start->type == ASSIGNMENT)
	{
		if (cmd->next == NULL)
			assign_variable(infos, cmd);
		cmd = cmd->next;
	}
	check_redirections(infos, cmd);
	while (cmd->next)
=======
	if (copy_env(infos, infos->env, exec_env) < 0)
		return (NULL); //gestion exit status dans copy_env
	while (cmd->start != cmd->end && cmd->start->type == ASSIGNMENT)
>>>>>>> begin exec
=======
	int	diff_exec_env_size;

	diff_exec_env_size = get_exec_env_diff_size(infos, cmd);
	if (copy_env(infos, infos->env, exec_env, diff_exec_env_size) < 0)
		return (NULL);
	while (cmd->start->type == ASSIGNMENT)
>>>>>>> Slowly progressing
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
<<<<<<< HEAD
<<<<<<< HEAD
	if (cmd->output)
		ft_putstr(cmd->output);
	return (0);
=======
	if (cmd->start->type == ASSIGNMENT)
		return (NULL); // pas de gestion exit status
=======
>>>>>>> Slowly progressing
	return (cmd->start);
>>>>>>> begin exec
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

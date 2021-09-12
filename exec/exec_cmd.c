/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anadege <anadege@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/09 15:00:10 by anadege           #+#    #+#             */
/*   Updated: 2021/09/12 21:26:56 by anadege          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* First try
int	execute_simple_cmd(t_infos *infos)
{
	pid_t	pid;
	int		wstatus;

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
		//On est dans l'enfant
		//Besoin de : transformer arguments en char* passé en 2nd argument
		//+ vérifier si builtin et si cas, aller directement dans fonction
		//du builtin
		//Chercher si filename est un chemin absolu. Si non, on le cherche dans PATH
		if (execve(filename, args, envp) == -1)
			//print message erreur; //Cas ou execution a echoue, + errno
		exit(EXIT_FAILURE); //On arrive ici que si execve a échoué, car normalement 
		//le child est exit quand execve est successfull
	}
	return (0);
}
*/

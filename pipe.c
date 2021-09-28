/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anadege <anadege@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/27 16:02:10 by anadege           #+#    #+#             */
/*   Updated: 2021/09/27 17:14:50 by anadege          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int main(int argc, char **argv, char **env)

	int		pipefd[2];
	pid_t	child_pid;
	char	buf;

	if (pipe(pipefd) == -1)
	{
		printf("pipe failed\n");
		exit (EXIT_FAILURE);
	}

	child_pid = fork();
	if (child_pid == -1)
	{
		printf("fork failed\n");
		exit (EXIT_FAILURE);
	}
	else if (child_pid == 0)
	{
		close(pipefd[1]);
		dup2(pipefd[0], 0);
		close(pipefd[0]);
		char	*wc = get_path("wc", env);
		char	*argv_wc[2] = {wc, NULL};
		if (execve(wc, argv_wc, env) == -1)
			printf("wc failed\n");
		exit(1);
	}
	else
	{
		close(pipefd[0]);
		dup2(pipefd[1], 1);
		close(pipefd[1]);
		char	*ls = get_path("ls", env);
		char	*argv_ls[2] = {ls, NULL};
		printf("before ls\n");
		if (execve(ls, argv_ls, env) == -1)
			printf("ls failed\n");
		exit(1);
	}
	printf("end\n");
	return(0);
}

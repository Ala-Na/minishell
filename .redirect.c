/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlichir <hlichir@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/27 16:36:41 by anadege           #+#    #+#             */
/*   Updated: 2021/09/30 21:41:50 by hlichir          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(int argc, char **argv, char **env)
{
	char	*input_file = "main.c";
	char	*output_file = "1";
	char	*cat = get_path("wc", env);
	char	*args[3] = {"wc", "-rrr", NULL};

	int	fd_input = open(input_file, O_RDONLY);
	int	fd_output = open(output_file, O_RDWR | O_TRUNC | O_CREAT, S_IRWXG | S_IRWXU);
	if (dup2(fd_input, 0) < 0)
		printf("error\n");
	dup2(fd_output, 1);
	dup2(fd_output, 2);
	close(fd_input);
	close(fd_output);
	execve(cat, args, env);
	printf("error\n");
}

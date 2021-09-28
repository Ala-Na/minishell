/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anadege <anadege@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/27 16:36:41 by anadege           #+#    #+#             */
/*   Updated: 2021/09/27 17:14:48 by anadege          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int main(int argc, char **argv, char **env)
{
	char	*input_file = "main.c";
	char	*output_file = "1";
	char	*cat = get_path("cat", env);
	char	*args[2] = {"cat", NULL};

	int	fd_input = open(input_file, O_RDONLY);
	int	fd_output = open(output_file, O_RDWR | O_TRUNC | O_CREAT, S_IRWXG | S_IRWXU);
	dup2(fd_input, 0);
	dup2(fd_output, 1);
	dup2(fd_output, 2);
	close(fd_input);
	close(fd_output);
	execve(cat, args, env);
	printf("error\n");
}

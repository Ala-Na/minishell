/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anadege <anadege@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/23 14:58:07 by anadege           #+#    #+#             */
/*   Updated: 2021/09/02 12:09:27 by anadege          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(int argc, char **argv, char **env)
{
	t_infos	infos;

	if (init_minishell(&infos, env) == -1)
		return (1);
	while (1)
	{
		infos.prompt = get_prompt();
		if (!infos.prompt)
			return (1);
		infos.curr_cmd = readline(infos.prompt);
		add_line_to_history(infos.fd_history, infos.curr_cmd);
		if (!ft_strncmp(infos.curr_cmd, "exit", 5))
			break;
		if (infos.curr_cmd)
			free(infos.curr_cmd);
		if (infos.prompt)
			free(infos.prompt);
	}
	clean_exit(&infos);
	(void)argc;
	(void)argv;
	return (0);
}

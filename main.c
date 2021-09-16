/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlichir <hlichir@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/23 14:58:07 by anadege           #+#    #+#             */
/*   Updated: 2021/09/16 17:51:59 by anadege          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	fun_test(t_infos *infos)
{
	int	res;

	res = parse_cmd(infos);
	printf("parse res : %i\n", res);
	if (!infos->curr_cmd || infos->curr_cmd[0] == 0)
		return ;
	launch_cmd(infos, infos->lst_cmds);
}

int	minishell_loop(t_infos *infos)
{
	while (1)
	{
		if (check_exit_status(infos) < 0)
			return (1);
		infos->prompt = get_prompt();
		if (!infos->prompt)
			return (1);
		infos->curr_cmd = readline(infos->prompt);
		if (infos->curr_cmd == NULL)
		{
			ft_putstr("\033[F");
			ft_putstr(infos->prompt);
			ft_putstr("exit\n");
			break ;
		}
		add_line_to_history(infos->fd_history, infos->curr_cmd);
		if (infos->curr_cmd[0] != 0)
			fun_test(infos);
		if (check_if_exit_or_continue(infos) == 1)
			break ;
	}
	return (0);
}

int	main(int argc, char **argv, char **env)
{
	t_infos	infos;

	(void)argc;
	(void)argv;
	if (init_minishell(&infos, env) == -1)
		return (1);
	handle_signals();
	if (minishell_loop(&infos) == 1)
		return (1);
	clean_exit(&infos);
	return (0);
}

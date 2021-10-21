/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_mode.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anadege <anadege@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/21 15:20:31 by anadege           #+#    #+#             */
/*   Updated: 2021/10/21 23:21:19 by anadege          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	exit_non_interactive(int signum)
{
	if (signum == SIGINT)
	{
		ft_putstr("\n");
		exit(130);
	}
}

int	non_interactive_minishell_loop(t_infos *infos)
{
	infos->mode = 1;
	g_exit_status = 0;
	signal(SIGINT, exit_non_interactive);
	while (get_next_line(STDIN_FILENO, &(infos->curr_cmd)) > 0)
	{
		infos->prompt = get_prompt(infos);
		if (!infos->prompt)
			return (return_error(1, "minishell : fatal error", 0, 1));
		if (!infos->curr_cmd)
			break ;
		if (!ft_strncmp(infos->curr_cmd, "exit", 5))
		{
			write(1, "exit\n", 5);
			break ;
		}
		if (infos->curr_cmd[0] != 0)
			parse_and_execute(infos);
		if (modify_exit_value_variable(infos, g_exit_status) < 0)
			return (return_error(1, "minishell : fatal error", 0, 1));
		clean_to_continue(infos, 1);
	}
	return (0);
}

int	check_mode(void)
{
	int	term;

	term = isatty(STDIN_FILENO);
	if (term == 1)
		return (0);
	else if (term == 0 && errno != EBADF)
		return (1);
	else
	{
		ft_puterr(strerror(errno), 1);
		return (-1);
	}
}

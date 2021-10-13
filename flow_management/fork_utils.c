/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fork_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlichir < hlichir@student.42.fr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/12 16:15:52 by anadege           #+#    #+#             */
/*   Updated: 2021/10/13 19:13:18 by hlichir          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	handle_signal_in_input(int signum)
{
	if (signum == SIGINT)
	{
		ft_putstr("\n");
		g_exit_status = 130;
	}
}

int	check_input_signal(void)
{
	if (g_exit_status == 130)
		return (1);
	return (0);
}

int	check_if_end(char **str, char *end_str, int fd)
{
	int	end;

	end = check_end_or_fill_tmp_file(str, end_str, fd);
	if (end == 1)
		return (1);
	else if (end == -1)
	{
		g_exit_status = 1;
		return (1);
	}
	return (0);
}

void	extract_child(t_infos *infos, int fd, char *end_str)
{
	char	*str;

	signal(SIGINT, handle_signal_in_input);
	g_exit_status = 0;
	while (1)
	{
		str = readline("> ");
		if (check_input_signal() == 1)
			break ;
		if (!str)
		{
			ft_puterr("premature end of file input", 1);
			g_exit_status = 3;
			break ;
		}
		if (check_if_end(&str, end_str, fd) == 1)
			break ;
	}
	clean_exit(infos);
	exit(g_exit_status);
}

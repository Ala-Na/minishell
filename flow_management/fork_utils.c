/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fork_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anadege <anadege@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/12 16:15:52 by anadege           #+#    #+#             */
/*   Updated: 2021/10/12 16:16:04 by anadege          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	handle_signal_in_input(int signum)
{
	if (signum == SIGINT)
	{
		ft_putstr("\n");
		exit(130);
	}
}

void	extract_child(int fd, char *end_str)
{
	char	*str;
	int		end;

	signal(SIGINT, handle_signal_in_input);
	while (1)
	{
		str = readline("> ");
		if (!str)
		{
			ft_puterr("premature end of file input", 1);
			exit(3);
		}
		end = check_end_or_fill_tmp_file(&str, end_str, fd);
		if (end == 1)
			break ;
		else if (end == -1)
			exit(1);
	}
	exit(0);
}

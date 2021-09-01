/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   history.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anadege <anadege@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/30 17:16:26 by anadege           #+#    #+#             */
/*   Updated: 2021/09/01 20:40:49 by anadege          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		get_previous_history(void)
{
	int		fd;
	char	*str;

	str = NULL;
	fd = open("./minishell_history", O_RDWR | O_APPEND | O_CREAT, S_IRWXG | S_IRWXU);
	if (fd == -1)
		return (fd);
	while (get_next_line(fd, &str) > 0)
	{
		add_history(str);
		free(str);
	}
	if (str)
		free(str);
	return (fd);
}

void	add_line_to_history(int history_fd, char *str)
{
		write(history_fd, str, ft_strlen(str));
		write(history_fd, "\n", 1);
		add_history(str);
}

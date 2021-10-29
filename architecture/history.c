/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   history.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlichir < hlichir@student.42.fr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/30 17:16:26 by anadege           #+#    #+#             */
/*   Updated: 2021/10/29 14:53:06 by hlichir          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

/*
** Function that will open minishell_history, add a new line of history via
**	add_history(), which will make them available to readline (up arrow)
** Returns the fd of the file that will be stored in the infos structure
**	Returns -1 in case of an error.
*/
int	get_previous_history(void)
{
	int		fd;
	char	*str;

	str = NULL;
	fd = open("/tmp/minishell_history", \
			O_RDWR | O_APPEND | O_CREAT, S_IRWXG | S_IRWXU);
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

/*
**	Function that will add a new line in the file minishell_history 
** when the command is executed.
*/
int	add_line_to_history(int history_fd, char *str, int exit)
{
	static char	*previous;

	if (exit)
	{
		if (previous)
			free(previous);
		return (0);
	}
	if (!history_fd || !str)
	{
		return_error(1, "something went wrong", 0, 0);
		return (-1);
	}
	if (ft_isblanks(str) || (previous
			&& !ft_strncmp(str, previous,
				ft_max(ft_strlen(str), ft_strlen(previous)))))
		return (0);
	write(history_fd, str, ft_strlen(str));
	write(history_fd, "\n", 1);
	add_history(str);
	if (previous)
		free(previous);
	previous = ft_strdup(str);
	return (0);
}

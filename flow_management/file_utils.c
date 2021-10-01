/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlichir <hlichir@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/30 15:22:22 by hlichir           #+#    #+#             */
/*   Updated: 2021/10/01 12:51:58 by hlichir          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

/*
** Function to capture the error message in case the input file
**	doesn't exist.
*/
int	file_error_input(char *filename, char **tmp)
{
	*tmp = ft_strdup(filename);
	if (!(*tmp))
		return (return_error(1, "memory allocation error", 0, -1));
	*tmp = ft_strjoin_free(*tmp, ": ", 1, 0);
	if (!(*tmp))
		return (return_error(1, "memory allocation error", 0, -1));
	*tmp = ft_strjoin_free(*tmp, strerror(errno), 1, 0);
	if (!(*tmp))
		return (return_error(1, "memory allocation error", 0, -1));
	return (0);
}

/*
** Function to extract the name of the file or of the string if the " " are
**	used.
*/
char	*extract_name_in_string(t_cmd *cmd)
{
	char	*name;
	int		start_pos;

	start_pos = 0;
	if (cmd->start->type == STRING)
		start_pos = 1;
	name = ft_strndup(cmd->start->token + start_pos, cmd->start->length);
	if (!name)
		return (NULL);
	return (name);
}

/*
** Check if the file "tmp_file exists".
*/
int	check_file(char	*filename)
{
	int	fd;

	fd = open(filename, O_RDONLY);
	if (fd < 0)
		return (-1);
	if (close(fd) < 0)
		return (return_error(1, "Error while closing file", 0, -1));
	return (0);
}

/*
**	Sub-function of input_utils to fil tmp_file.
*/
int	fill_tmp_file(char **str, int fill_str, int *fd)
{
	if (fill_str)
	{
		*fd = open("tmp_file", O_RDWR | O_TRUNC | O_CREAT, 00777);
		if (*fd < 0)
			return (return_error(1, strerror(errno), 0, -1));
		ft_putstr_fd(*str, *fd);
	}
	return (0);
}

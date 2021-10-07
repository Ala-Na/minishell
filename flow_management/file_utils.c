/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlichir < hlichir@student.42.fr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/30 15:22:22 by hlichir           #+#    #+#             */
<<<<<<< HEAD
/*   Updated: 2021/10/08 10:34:50 by hlichir          ###   ########.fr       */
=======
/*   Updated: 2021/10/08 10:24:45 by anadege          ###   ########.fr       */
>>>>>>> some leaks fixed
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

/*
** Function to capture the error message in case the input file
**	doesn't exist.
*/
int	file_error_input(char *filename, char **tmp)
{
	char	*sep;
	char	*err;

	sep = ": ";
	*tmp = ft_strdup(filename);
	if (!(*tmp))
		return (return_error(1, "memory allocation error", 0, -1));
	*tmp = ft_strjoin_free(tmp, &sep, 1, 0);
	if (!(*tmp))
		return (return_error(1, "memory allocation error", 0, -1));
	err = strerror(errno);
	*tmp = ft_strjoin_free(tmp, &err, 1, 0);
	if (!(*tmp))
		return (return_error(1, "memory allocation error", 0, -1));
	return (0);
}

/*
** Function to extract the name of the file or of the string if the " " are
**	used.
*/
char	*extract_name_in_string(t_cmd *cmd, int *error)
{
	char	*name;

	if (cmd->start->type == VARIABLE && cmd->start->next && \
		cmd->start->next->type == VARIABLE)
	{
		*error = -1;
		return (NULL);
	}
	name = ft_strdup_linked_string(cmd->start);
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

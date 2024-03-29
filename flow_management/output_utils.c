/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   output_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlichir <hlichir@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/30 13:26:21 by hlichir           #+#    #+#             */
/*   Updated: 2021/10/25 23:18:52 by hlichir          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

/*
** Display error message for opening
*/
int	return_and_display_open_error(char **filename, int free_filename)
{
	char	*filename_cpy;
	char	*msg_err;

	if (free_filename == 0)
		filename_cpy = ft_strdup(*filename);
	else
		filename_cpy = *filename;
	msg_err = ": ";
	filename_cpy = ft_strjoin_free(&filename_cpy, &msg_err, 1, 0);
	if (!filename_cpy)
		return (return_error(1, "memory allocation error", 0, -1));
	msg_err = strerror(errno);
	filename_cpy = ft_strjoin_free(&filename_cpy, &msg_err, 1, 0);
	if (!filename_cpy)
		return (return_error(1, "memory allocation error", 0, -1));
	return (return_error(1, 0, &filename_cpy, -1));
}

/*
** Function to create the file when the redirection is used ">"
** Create a new file even if it already exist & return the file descriptor.
*/
int	create_new_file(t_cmd *curr)
{
	int		fd;
	int		error;
	char	*filename;

	if (!curr || !curr->next)
		return (return_error(1, "something went wrong", 0, -1));
	error = 0;
	filename = extract_name_in_string(curr->next, &error);
	if (error == -1)
		return (return_error(1, "Ambiguous redirect!", 0, -1));
	if (!filename)
		return (-1);
	fd = open(filename, O_RDWR | O_TRUNC | O_CREAT, 0644);
	if (fd < 0)
		return (return_and_display_open_error(&filename, 1));
	free(filename);
	return (fd);
}

/*
** Function to create the file when the redirection is used ">>"
** If the file doesn't exist, create it & return the file descriptor.
*/
int	append_to_file(t_cmd *curr, int fd)
{
	int		error;
	char	*filename;

	if (!curr || !curr->next)
		return (return_error(1, "something went wrong", 0, -1));
	error = 0;
	filename = extract_name_in_string(curr->next, &error);
	if (error == -1)
		return (return_error(1, "Ambiguous redirect!", 0, -1));
	if (!filename)
		return (-1);
	fd = open(filename, O_RDWR | O_APPEND | O_CREAT, S_IRWXG | S_IRWXU);
	if (fd < 0)
		return (return_and_display_open_error(&filename, 1));
	free(filename);
	return (fd);
}

/*
** Add the correct fd to the cmd structure.
** If a file is already in the structure (fs_input/outpur != -1), the prev
**	file descriptor is closed.
** Returns -1 if error on the close function or 0 if everthing is good.
*/
int	add_output_fd_to_cmd(t_cmd **cmd, int fd)
{
	if ((*cmd)->fd_output > 1)
		if (close((*cmd)->fd_output) < 0)
			return (return_error(1, strerror(errno), 0, -1));
	(*cmd)->fd_output = fd;
	return (0);
}

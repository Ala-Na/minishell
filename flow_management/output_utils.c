/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   output_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlichir <hlichir@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/30 13:26:21 by hlichir           #+#    #+#             */
/*   Updated: 2021/10/07 22:33:12 by anadege          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

/*
** Function to create the file when the redirection is used ">"
** Create a new file even if it already exist & return the file descriptor.
*/
int	create_new_file(t_cmd *curr)
{
	int		fd;
	char	*filename;
	char	*msg_err;

	filename = extract_name_in_string(curr->next);
	if (!filename)
		return (return_error(1, "memory allocation error", 0, -1));
	fd = open(filename, O_RDWR | O_TRUNC | O_CREAT, S_IRWXG | S_IRWXU);
	if (fd < 0)
	{
		msg_err = "error while opening ";
		filename = ft_strjoin_free(&msg_err, &filename, 0, 1);
		return (return_error(1, filename, 1, -1));
	}
	free(filename);
	return (fd);
}

/*
** Function to create the file when the redirection is used ">>"
** If the file doesn't exist, create it & return the file descriptor.
*/
int	append_to_file(t_cmd *curr)
{
	int		fd;
	char	*filename;
	char	*msg_err;

	filename = extract_name_in_string(curr->next);
	if (!filename)
		return (return_error(1, "memory allocation error", 0, -1));
	fd = open(filename, O_RDWR | O_APPEND | O_CREAT, S_IRWXG | S_IRWXU);
	if (fd < 0)
	{
		msg_err = "error while opening ";
		filename = ft_strjoin_free(&msg_err, &filename, 0, 1);
		return (return_error(1, filename, 1, -1));
	}
	free(filename);
	return (fd);
}

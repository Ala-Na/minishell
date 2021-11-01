/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlichir <hlichir@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/30 15:22:22 by hlichir           #+#    #+#             */
/*   Updated: 2021/10/25 19:10:27 by hlichir          ###   ########.fr       */
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

	if (!cmd || !cmd->start)
		return (return_null_error(1, "something went wrong", 0));
	*error = 0;
	if (cmd->start->type == VARIABLE && cmd->start->next && \
		cmd->start->next->type == VARIABLE)
	{
		*error = -1;
		return (NULL);
	}
	else if (cmd->start->type == VARIABLE && cmd->start->length == 2
		&& !ft_strncmp(cmd->start->token, "\"\'$", 3))
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
		return (return_and_display_open_error(&filename));
	if (close(fd) < 0)
		return (return_error(1, "error while closing file", 0, -1));
	return (0);
}

/*
**	Sub-function of input_utils to fil tmp_file.
*/
int	check_end_or_fill_tmp_file(char **str, char *end, int fd)
{
	if (!str || !*str || !end || fd <= 1)
		return (return_error(1, "something went wrong", 0, -1));
	if (!ft_strncmp(*str, end, ft_max(ft_strlen(*str), ft_strlen(end))))
		return (1);
	ft_putstr_fd(*str, fd);
	ft_putstr_fd("\n", fd);
	free(*str);
	return (0);
}

char	*get_tmp_file_name(int nbr_tmp_file)
{
	char	*tmp_path;
	char	*tmp_name;

	tmp_name = ft_itoa(nbr_tmp_file);
	if (!tmp_name)
		return (return_null_error(1, "memory allocation error", 0));
	tmp_path = "/tmp/tmp_file_minishell_";
	tmp_name = ft_strjoin_free(&tmp_path, &tmp_name, 0, 1);
	if (!tmp_name)
		return (return_null_error(1, "memory allocation error", 0));
	return (tmp_name);
}

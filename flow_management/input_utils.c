/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlichir < hlichir@student.42.fr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/30 13:49:03 by hlichir           #+#    #+#             */
/*   Updated: 2021/09/30 17:26:33 by hlichir          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	display_next_lt_dbl(t_cmd *cmd)
{
	t_cmd	*curr;

	curr = cmd;
	while (curr->next_operator != -1 && curr->next_operator != PIPE)
	{
		if (curr->next_operator == LT_DBL && curr->next)
			if (extract_input_from_stdin(curr, 0) < 0)
				return (-1);
		curr = curr->next;
	}
	return (0);
}

/*
** Function to get the file descriptor of a file.
** If the file doesn't exist -> execute any "<<" left just for the display.
** Then returns -2 to the child execution for exit.
*/
int get_fd(t_cmd *curr)
{
	int		fd;
	char	*tmp;
	char	*filename;

	tmp = NULL;
	filename = extract_name_in_string(curr->next);
	if (!filename)
		return (return_error(1, "memory allocation error", 0, -1));
	fd = open(filename, O_RDONLY);
	if (fd < 0)
	{
		if (file_error_input(filename, &tmp) < 0)
			return (-1);
		display_next_lt_dbl(curr);
		free(filename);
		return (return_error(1, tmp, 1, -1));
	}
	free(filename);
	return (fd);
}

/*
** Sub-function for extract_input_from_stdin
** Check if the string "end" was written
*/
int	check_if_end(char **str, char *end, char c, int i)
{
	char	*tmp;
	int		start_pos;

	if (c != '\n')
		return (0);
	start_pos = 0;
	while ((*str)[i])
	{
		if ((*str)[i] == '\n' && (*str)[i + 1])
			start_pos = i + 1;
		i++;
	}
	tmp = ft_strdup(*str + start_pos);
	if (!tmp)
		return (return_error(1, "memory allocation error", 0, -1));
	if (!ft_strncmp(tmp, end, ft_max(ft_strlen(tmp) - 1, ft_strlen(end))))
	{
		*str = ft_strndup(*str, ft_strlen(*str) - ft_strlen(tmp));
		free(tmp);
		return (1);
	}
	free(tmp);
	write(1, "> ", 2);
	return (0);
}

/*
** Sub-function of extract_input_from_stdin:
**	read the stdin and store the text in a file called "tmp_file" if
**	fill_fd = 1.
** Returns the fd (or -1 if error) & 0 if fill_str = 0.
*/
int	create_tmp_file(t_cmd *curr, char *end_str, char *str, int fill_str)
{
	char	buffer[2];
	int		fd;

	fd = 0;
	while (read(1, buffer, 1) > 0)
	{
		buffer[1] = 0;
		str = ft_strjoin_free(str, buffer, 1, 0);
		if (!str)
		{
			free(end_str);
			return (return_error(1, "memory allocation error", 0, -1));
		}
		if (check_if_end(&str, end_str, buffer[0], 0) > 0)
			break ;
	}
	free(end_str);
	if (fill_str)
	{
		fd = open("tmp_file", O_RDWR | O_TRUNC | O_CREAT, S_IRWXG | S_IRWXU);
		if (fd < 0)
		{
			free(str);
			return (return_error(1, strerror(errno), 0, -1));
		}
		ft_putstr_fd(str, fd);
	}
	free(str);
	return (fd);
}

/*
** Function when "<<" is called.
*/
int	extract_input_from_stdin(t_cmd *curr, int fill_str)
{
	char	buffer[2];
	char	*end_str;
	char	*str;
	int		fd;

	end_str = extract_name_in_string(curr->next);
	if (!end_str)
		return (return_error(1, "memory allocation error", 0, -1));
	str = ft_strdup("");
	if (!str)
	{
		free(end_str);
		return (return_error(1, "memory allocation error", 0, -1));
	}
	write(1, "> ", 2);
	fd = create_tmp_file(curr, end_str, str, fill_str);
	if (fd < 0)
		return (-1);
	return (fd);
}
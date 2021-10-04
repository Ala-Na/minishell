/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exception_cmd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlichir <hlichir@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/04 17:34:23 by hlichir           #+#    #+#             */
/*   Updated: 2021/10/04 18:28:04 by hlichir          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

/*
**	In case a "/" is in the entered file name.
*/
int	print_file_type(char *file)
{
	struct stat	buf;
	char		*str;

	if (stat(file, &buf) < 0)
	{
		ft_puterr(file, 0);
		ft_puterr(": ", 0);
		if (errno != ENOENT)
			return (return_error(126, strerror(errno), 0, -1));
		else
			return (return_error(127, strerror(errno), 0, -1));
	}
	if (S_ISDIR(buf.st_mode))
	{
		str = ft_strjoin(file, ": is a directory");
		if (!str)
			return (return_error(1, "memory allocation error", 0, -1));
		return (return_error(126, str, 1, -1));
	}
	return (1);
}

/*
**	Function to check if the filepath is an exception to a classic execution.
*/
int	check_path_for_exceptions(char *file)
{
	int	i;
	int	check_type;

	i = 0;
	check_type = 0;
	while (file[i])
	{
		if (file[i] == '/')
			check_type = 1;
		i++;
	}
	if (check_type)
		return (print_file_type(file));
	else
	{
		if (!ft_strncmp(file, ".", 2))
			return (return_error(2, ".: built-in not handled", 0, -1));
		else if (!ft_strncmp(file, "..", 3))
			return (return_error(127, "..: command_not_found", 0, -1));
		else if (!ft_strncmp(file, "exit", 5))
			exit(0);
	}
	return (0);
}

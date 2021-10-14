/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exception_cmd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlichir < hlichir@student.42.fr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/04 17:34:23 by hlichir           #+#    #+#             */
/*   Updated: 2021/10/14 16:58:46 by hlichir          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

/*
**	In case a "/" is in the entered file name.
*/
int	print_file_type(char *file)
{
	struct stat	buf;

	if (stat(file, &buf) < 0)
	{
		ft_puterr(file, 0);
		ft_puterr(" : ", 0);
		if (errno != ENOENT)
			return (return_error(126, strerror(errno), 0, -1));
		else
			return (return_error(127, strerror(errno), 0, -1));
	}
	if (S_ISDIR(buf.st_mode))
	{
		ft_puterr(file, 0);
		return (return_error(126, ": is a directory", 0, -1));
	}
	else if (!(buf.st_mode & S_IXUSR))
	{
		ft_puterr(file, 0);
		return (return_error(126, ": permission denied", 0, -1));
	}
	return (1);
}

/*
**	Subfunction to free & exit properly from child
*/
void	free_and_exit(t_infos *infos, int status, char **file)
{
	free(*file);
	clean_exit(infos, 0);
	exit(status);
}

/*
**	Function to check if the filepath is an exception to a classic execution.
*/
int	check_path_for_exceptions(t_infos *infos, char **file)
{
	int	i;
	int	check_type;

	i = 0;
	check_type = 0;
	while ((*file)[i] && (*file)[0] != '~')
	{
		if ((*file)[i] == '/')
			check_type = 1;
		i++;
	}
	if (check_type)
		return (print_file_type(*file));
	else
	{
		if (ft_strlen(*file) == 0)
			return (return_error(127, ": command_not_found", 0, -1));
		else if (!ft_strncmp(*file, ".", 2))
			return (return_error(2, ".: built-in not handled", 0, -1));
		else if (!ft_strncmp(*file, "..", 3))
			return (return_error(127, "..: command_not_found", 0, -1));
		else if (!ft_strncmp(*file, "exit", 5))
			free_and_exit(infos, 0, file);
	}
	return (0);
}

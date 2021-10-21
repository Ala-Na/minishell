/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlichir < hlichir@student.42.fr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/30 13:49:03 by hlichir           #+#    #+#             */
/*   Updated: 2021/10/21 15:26:50 by anadege          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	display_next_lt_dbl(t_infos *infos, t_cmd *cmd)
{
	t_cmd	*curr;
	int		fd;

	curr = cmd;
	while ((int)curr->next_operator != -1 && curr->next_operator != PIPE)
	{
		if (curr->next_operator == LT_DBL && curr->next)
		{
			fd = extract_input_from_stdin(infos, curr);
			if (fd < 0)
				return (-1);
			close(fd);
		}
		curr = curr->next;
	}
	return (0);
}

/*
** Function to get the file descriptor of a file.
** If the file doesn't exist -> execute any "<<" left just for the display.
** Then returns -2 to the child execution for exit.
*/
int	get_fd(t_infos *infos, t_cmd *curr)
{
	int		fd;
	char	*tmp;
	char	*filename;

	tmp = NULL;
	fd = 0;
	filename = extract_name_in_string(curr->next, &fd);
	if (fd == -1)
	{
		display_next_lt_dbl(infos, curr);
		return (return_error(1, "Ambiguous redirect", 0, -1));
	}
	if (!filename)
		return (return_error(1, "memory allocation error", 0, -1));
	fd = open(filename, O_RDONLY);
	if (fd < 0)
	{
		if (file_error_input(filename, &tmp) < 0)
			return (-1);
		display_next_lt_dbl(infos, curr);
		free(filename);
		return (return_error(1, 0, &tmp, -1));
	}
	free(filename);
	return (fd);
}

/*
** Sub-function of extract_input_from_stdin:
**	read the stdin and store the text in a file called "tmp_file" if
**	fill_fd = 1.
** Returns the fd (or -1 if error) & 0 if fill_str = 0.
*/
int	create_tmp_file(int nbr_tmp_file, char **tmp_file_name)
{
	char	*tmp_name;
	int		fd;

	tmp_name = get_tmp_file_name(nbr_tmp_file);
	fd = open(tmp_name, O_RDWR | O_TRUNC | O_CREAT, 00700);
	if (fd < 0)
	{
		free(tmp_name);
		ft_puterr("redirection : ", 0);
		return (return_error(1, strerror(errno), 0, -1));
	}
	*tmp_file_name = tmp_name;
	return (fd);
}

int	fork_for_input(t_infos *infos, char *end_str, int fd)
{
	pid_t	child_pid;
	int		wstatus;
	int		res;

	child_pid = fork();
	if (child_pid == -1)
		return (return_error(1, "fork failed", 0, 1));
	else if (child_pid > 0)
	{
		res = waitpid(child_pid, &wstatus, 0);
		close(fd);
		if (res == -1)
			return (return_error(1, strerror(errno), 0, 1));
		else if (WIFEXITED(wstatus))
			return (WEXITSTATUS(wstatus));
		else if (WIFSIGNALED(wstatus))
			return (WTERMSIG(wstatus) + 127);
	}
	else
		extract_child(infos, fd, end_str);
	return (return_error(1, "something went wrong", 0, 1));
}

/*
** Function when "<<" is called.
*/
int	extract_input_from_stdin(t_infos *infos, t_cmd *curr)
{
	char	*end_str;
	char	*tmp_file_name;
	int		fd;

	if (!curr || !curr->next)
		return (return_error(1, "something went wrong", 0, -1));
	end_str = extract_name_in_string(curr->next, &fd);
	if (!end_str)
		return (return_error(1, "memory allocation error", 0, -1));
	fd = create_tmp_file(curr->nb_tmp_file, &tmp_file_name);
	if (fd < 0)
		return (free_end_str_return(&end_str, -1));
	g_exit_status = fork_for_input(infos, end_str, fd);
	free(end_str);
	expand_variable_to_heredoc(infos, fd, curr->next, tmp_file_name);
	free(tmp_file_name);
	if (g_exit_status != 0)
		return (-1);
	return (fd);
}

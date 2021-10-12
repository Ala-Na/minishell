/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlichir <hlichir@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/30 13:49:03 by hlichir           #+#    #+#             */
/*   Updated: 2021/10/12 16:20:21 by anadege          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	display_next_lt_dbl(t_cmd *cmd)
{
	t_cmd	*curr;

	curr = cmd;
	while ((int)curr->next_operator != -1 && curr->next_operator != PIPE)
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
int	get_fd(t_cmd *curr)
{
	int		fd;
	char	*tmp;
	char	*filename;

	tmp = NULL;
	fd = 0;
	filename = extract_name_in_string(curr->next, &fd);
	if (fd == -1)
	{
		display_next_lt_dbl(curr);
		return (return_error(1, "Ambiguous redirect", 0, -1));
	}
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
** Sub-function of extract_input_from_stdin:
**	read the stdin and store the text in a file called "tmp_file" if
**	fill_fd = 1.
** Returns the fd (or -1 if error) & 0 if fill_str = 0.
*/
int	create_tmp_file(void)
{
	int	fd;

	fd = open("tmp_file", O_RDWR | O_TRUNC | O_CREAT, 00777);
	if (fd < 0)
	{
		ft_puterr("redirection : ", 0);
		return (return_error(1, strerror(errno), 0, -1));
	}
	return (fd);
}

int	fork_for_input(char *end_str, int fd)
{
	pid_t	child_pid;
	int		wstatus;
	int		res;

	child_pid = fork();
	if (child_pid == -1)
		return (return_error(1, "fork failed", 0, -1));
	else if (child_pid > 0)
	{
		res = waitpid(child_pid, &wstatus, 0);
		if (res == -1)
			return (return_error(1, strerror(errno), 0, -1));
		else if (WIFEXITED(wstatus))
			return (WEXITSTATUS(wstatus));
		else if (WIFSIGNALED(wstatus))
			return (WTERMSIG(wstatus) + 127);
	}
	else
		extract_child(fd, end_str);
	return (return_error(1, "something went wrong", 0, -1));
}

/*
** Function when "<<" is called.
*/
int	extract_input_from_stdin(t_cmd *curr, int fill_str)
{
	char	*end_str;
	int		fd;

	if (!curr || !curr->next)
		return (return_error(1, "something went wrong", 0, -1));
	fd = 0;
	end_str = extract_name_in_string(curr->next, &fd);
	if (!end_str)
		return (return_error(1, "memory allocation error", 0, -1));
	fd = create_tmp_file();
	if (fd < 0)
		return (-1);
	if (fill_str)
		g_exit_status = fork_for_input(end_str, fd);
	free(end_str);
	if (g_exit_status != 0)
	{
		if (g_exit_status == 3)
			g_exit_status = 0;
		return (-1);
	}
	return (fd);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlichir <hlichir@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/30 12:59:47 by hlichir           #+#    #+#             */
/*   Updated: 2021/10/25 19:33:53 by hlichir          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

/*
** Add the correct fd to the cmd structure.
** If a file is already in the structure (fs_input/outpur != -1), the prev
**	file descriptor is closed.
** Returns -1 if error on the close function or 0 if everthing is good.
*/

int	add_input_fd_to_cmd(t_cmd **cmd, int fd, int is_tmpfile)
{
	char	*tmp_file;

	if ((*cmd)->fd_input > 1)
		if (close((*cmd)->fd_input) < 0)
			return (return_error(1, strerror(errno), 0, -1));
	if (is_tmpfile)
	{
		close(fd);
		tmp_file = get_tmp_file_name((*cmd)->nb_tmp_file);
		if (!tmp_file)
			return (-1);
		fd = open(tmp_file, O_RDONLY);
		if (fd < 0 || unlink(tmp_file) == -1)
			return (return_error(1, strerror(errno), &tmp_file, -1));
		free(tmp_file);
	}
	(*cmd)->fd_input = fd;
	return (0);
}

/*
** For all ">" create a new file & for all ">>" create or open a file on
**	append mode.
** Each time, store the fd in the command structure - at the end (only the last
**	fd will be stored at the end of the function "add_redirections")
**
**	Returns -1 if error & 0 if everything is good.
*/
int	add_output(t_cmd **cmd, t_cmd *curr)
{
	int		fd;

	if (!cmd || !*cmd || !curr)
		return (return_error(1, "something went wrong", 0, -1));
	if (curr->next_operator == GT && curr->next)
	{
		fd = create_new_file(curr);
		if (fd < 0)
			return (-1);
		if (add_output_fd_to_cmd(cmd, fd))
			return (-1);
	}
	else if (curr->next_operator == GT_DBL && curr->next)
	{
		fd = append_to_file(curr, 0);
		if (fd < 0)
			return (-1);
		if (add_output_fd_to_cmd(cmd, fd))
			return (-1);
	}
	return (0);
}

/*
** For all "<" get the file descriptor of the file & for all "<<" create a
**	a tmp_file to store the input.
** Each time, store the fd in the command structure - at the end (only the last
**	fd will be stored at the end of the function "add_redirections")
**
**	Returns -1 if error & 0 if everything is good.
*/
int	add_input(t_infos *infos, t_cmd **cmd, t_cmd *curr)
{
	int		fd;

	if (!cmd || !*cmd || !curr)
		return (return_error(1, "something went wrong", 0, -1));
	if (curr->next_operator == LT && curr->next)
	{
		fd = get_fd(infos, curr);
		if (fd < 0)
			return (-1);
		if (add_input_fd_to_cmd(cmd, fd, 0))
			return (-1);
	}
	if (curr->next_operator == LT_DBL && curr->next)
	{
		fd = extract_input_from_stdin(infos, curr);
		if (fd <= 0)
			return (-1);
		if (add_input_fd_to_cmd(cmd, fd, 1))
			return (-1);
	}
	return (0);
}

int	dup_redirections(t_infos *infos, t_cmd *head_cmd)
{
	(void)infos;
	if (head_cmd->fd_input > 1)
	{
		if (dup2(head_cmd->fd_input, 0) < 0)
			return (return_error(1, strerror(errno), 0, -1));
	}
	if (head_cmd->fd_output > 1)
	{
		if (dup2(head_cmd->fd_output, 1) < 0)
			return (return_error(1, strerror(errno), 0, -1));
	}
	return (0);
}

/*
** Check all the command until it arrives at the end (next_operqtor = - 1)
** or encounters a pipe.
** If an error occurs -> returns -1, 0 if everything is fine.
*/
int	add_redirections(t_infos *infos, t_cmd *head_cmd)
{
	t_cmd	*curr;

	if (!head_cmd)
		return (return_error(1, "something went wrong", 0, -1));
	curr = head_cmd;
	while (curr && (int)curr->next_operator != -1
		&& curr->next_operator != PIPE)
	{
		if (add_input(infos, &head_cmd, curr) < 0)
			return (-1);
		else if (add_output(&head_cmd, curr) < 0)
			return (-1);
		curr = curr->next;
	}
	return (0);
}

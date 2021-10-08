/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlichir < hlichir@student.42.fr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/30 12:59:47 by hlichir           #+#    #+#             */
<<<<<<< HEAD
/*   Updated: 2021/10/08 12:01:31 by hlichir          ###   ########.fr       */
=======
/*   Updated: 2021/10/08 11:45:59 by anadege          ###   ########.fr       */
>>>>>>> size adapted
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

/*
** Add the correct fd to the cmd structure.
** If a file is already in the structure (fs_input/outpur != -1), the prev
**	file descriptor is closed.
** Returns -1 if error on the close function or 0 if everthing is good.
*/
int	add_fd_to_cmd(t_cmd **cmd, int fd, int is_output, int is_tmpfile)
{
	if (is_output)
	{
		if ((*cmd)->fd_output > 1)
		{
			if (close((*cmd)->fd_output) < 0)
				return (return_error(1, strerror(errno), 0, -1));
		}
		(*cmd)->fd_output = fd;
	}
	else
	{	
		if ((*cmd)->fd_input > 1)
		{
			if (close((*cmd)->fd_input) < 0)
				return (return_error(1, strerror(errno), 0, -1));
		}
		if (is_tmpfile)
		{
			fd = open("./tmp_file", O_RDONLY);
			if (fd < 0)
				return (return_error(1, strerror(errno), 0, -1));
		}
		(*cmd)->fd_input = fd;
	}
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

	if (curr->next_operator == GT && curr->next)
	{
		fd = create_new_file(curr);
		if (fd < 0)
			return (-1);
		if (add_fd_to_cmd(cmd, fd, 1, 0))
			return (-1);
	}
	else if (curr->next_operator == GT_DBL && curr->next)
	{
		fd = append_to_file(curr);
		if (fd < 0)
			return (-1);
		if (add_fd_to_cmd(cmd, fd, 1, 0))
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
int	add_input(t_cmd **cmd, t_cmd *curr)
{
	int		fd;

	if (curr->next_operator == LT && curr->next)
	{
		fd = get_fd(curr);
		if (fd < 0)
			return (-1);
		if (add_fd_to_cmd(cmd, fd, 0, 0))
			return (-1);
	}
	if (curr->next_operator == LT_DBL && curr->next)
	{
		fd = extract_input_from_stdin(curr, 1);
		if (fd <= 0)
			return (-1);
		if (add_fd_to_cmd(cmd, fd, 0, 1))
			return (-1);
	}
	return (0);
}

/*
** Check all the command until it arrives at the end (next_operqtor = - 1)
** or encounters a pipe.
** If an error occurs -> returns -1, 0 if everything is fine.
*/
int	add_redirections(t_cmd *head_cmd, int is_not_builtin)
{
	t_cmd	*curr;

	curr = head_cmd;
	while (curr && (int)curr->next_operator != -1
			&& curr->next_operator != PIPE)
	{
		if (add_input(&head_cmd, curr) < 0)
			return (-1);
		else if (add_output(&head_cmd, curr) < 0)
			return (-1);
		curr = curr->next;
	}
	if (is_not_builtin)
	{
		if (head_cmd->fd_input > 1)
			if (dup2(head_cmd->fd_input, 0) < 0)
				return (return_error(1, strerror(errno), 0, -1));
		if (head_cmd->fd_output > 1)
			if (dup2(head_cmd->fd_output, 1) < 0)
				return (return_error(1, strerror(errno), 0, -1));
	}
	return (0);
}

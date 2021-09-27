/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   right_redirections.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlichir < hlichir@student.42.fr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/17 14:56:38 by hlichir           #+#    #+#             */
/*   Updated: 2021/09/27 11:59:31 by anadege          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

/*
** Function to extract the name of the file or of the string if the " " are
**	used.
*/
char	*extract_name_in_string(t_cmd *cmd)
{
	char	*name;
	int		start_pos;

	start_pos = 0;
	if (cmd->start->type == STRING)
		start_pos = 1;
	name = ft_strndup(cmd->start->token + start_pos, cmd->start->length);
	if (!name)
		return (NULL);
	return (name);
}

/*
** Function to handle the redirection ">"
** Create a new file to have the content of the command output
*/
int	single_right_redirect(t_infos *infos, t_cmd *cmd)
{
	int		fd;
	char	*filename;

	filename = extract_name_in_string(cmd->next);
	if (!filename)
		return (return_error(1, "memory allocation error", 0, -1));
	fd = open(filename, O_RDWR | O_TRUNC | O_CREAT, S_IRWXG | S_IRWXU);
	if (fd < 0)
	{
		filename = ft_strjoin_free("error while opening ", filename, 0, 1);
		return (return_error(1, filename, 1, -1));
	}
	free(filename);
	ft_putstr_fd(cmd->output, fd);
	close(fd);
	if (cmd->next->next_operator != -1)
	{
		cmd->next->output = ft_strdup(cmd->output);
		if (!cmd->next->output)
			return (return_error(1, "memory allocation error", 0, -1));
	}
	return (0);
}

/*
** Function to handle the redirection ">>"
** If the file doesn't existe, create it + add the output at the end of this 
**	file.
*/
int	double_right_redirect(t_infos *infos, t_cmd *cmd)
{
	int		fd;
	char	*filename;

	filename = extract_name_in_string(cmd->next);
	if (!filename)
		return (return_error(1, "memory allocation error", 0, -1));
	fd = open(filename, O_RDWR | O_APPEND | O_CREAT, S_IRWXG | S_IRWXU);
	if (fd < 0)
	{
		filename = ft_strjoin_free("error while opening ", filename, 0, 1);
		return (return_error(1, filename, 1, -1));
	}
	free(filename);
	ft_putstr_fd(cmd->output, fd);
	close(fd);
	if (cmd->next->next_operator != -1)
	{
		cmd->next->output = ft_strdup(cmd->output);
		if (!cmd->next->output)
			return (return_error(1, "memory allocation error", 0, -1));
	}
	return (0);
}

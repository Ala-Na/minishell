/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   left_redirections.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlichir <hlichir@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/17 14:56:38 by hlichir           #+#    #+#             */
/*   Updated: 2021/09/25 23:13:23 by hlichir          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

/*
** Sub-function for single_left_redirect
** Read the file to extract the input
*/
int	extract_file(int fd, t_cmd *cmd)
{
	char	*str;

	if (!cmd->input)
	{
		cmd->input = ft_strdup("");
		if (!cmd->input)
			return (-1);
	}
	while (get_next_line(fd, &str) > 0)
	{
		cmd->input = ft_strjoin(cmd->input, str);
		if (!cmd->input)
			return (-1);
		free(str);
		cmd->input = ft_strjoin(cmd->input, "\n");
		if (!cmd->input)
			return (-1);
	}
	close(fd);
	return (0);
}

/*
** Commen to do
*/
int	file_error_input(t_cmd *cmd, char *str)
{
	cmd->input = ft_strdup(str);
	if (!(cmd->input))
		return (-1);
	cmd->input = ft_strjoin(cmd->input, ": ");
	if (!(cmd->input))
		return (-1);
	cmd->input = ft_strjoin(cmd->input, strerror(errno));
	if (!(cmd->input))
		return (-1);
	cmd->input = ft_strjoin(cmd->input, "\n");
	if (!(cmd->input))
		return (-1);
	return (0);
}

/*
** Function to handle the redirection "<"
*/
int	single_left_redirect(t_infos *infos, t_cmd *cmd, t_cmd *cmd_next)
{
	int		fd;
	char	*str;

	str = extract_name_in_string(cmd_next);
	if (!str)
		return (error_exit_status("Malloc error!", 0, infos, "?=1"));
	fd = open(str, O_RDWR);
	if (fd < 0)
	{
		file_error_input(cmd, str);
		return (error_exit_status(NULL, 0, infos, "?=1"));
	}
	free(str);
	if (extract_file(fd, cmd) < 0)
		return (error_exit_status("Malloc error", 0, infos, "?=1"));
	return (0);
}

/*
** Sub-function for double_left_redirect
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
		return (-1);
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
** Function to handle the redirection "<<"
*/
int	double_left_redirect(t_infos *infos, t_cmd *cmd, t_cmd *cmd_next)
{
	char	buffer[1];
	char	*str;
	char	*end_str;

	end_str = extract_name_in_string(cmd_next);
	str = ft_strdup("");
	if (!end_str || !str)
		return (error_exit_status("Malloc error", 0, infos, "?=1"));
	write(1, "> ", 2);
	while (read(1, buffer, 1) > 0)
	{
		str = ft_strnjoin(str, buffer, 1);
		if (!str)
			return (error_exit_status("Malloc error", 0, infos, "?=1"));
		if (check_if_end(&str, end_str, buffer[0], 0) > 0)
			break ;
	}
	if (!cmd->input)
		cmd->input = ft_strdup("");
	if (cmd->input)
		cmd->input = ft_strjoin(cmd->input, str);
	if (!cmd->input)
		return (error_exit_status("Malloc error", 0, infos, "?=1"));
	free(str);
	return (0);
}

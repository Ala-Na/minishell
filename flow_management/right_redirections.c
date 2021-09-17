/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   right_redirections.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlichir < hlichir@student.42.fr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/17 14:56:38 by hlichir           #+#    #+#             */
/*   Updated: 2021/09/17 15:59:08 by hlichir          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	single_right_redirect(t_infos *infos, t_cmd *cmd)
{
	int		fd;
	char	*filename;

	if (cmd->next_operator != GT)
		return (error_exit_status("Error on >", infos, "?=1"));
	filename = ft_strndup(cmd->next->start->token, cmd->next->start->length);
	if (!filename)
		return (error_exit_status("Malloc error!", infos, "?=1"));
	fd = open(filename, O_RDWR | O_TRUNC | O_CREAT, S_IRWXG | S_IRWXU);
	free(filename);
	if (fd < 0)
		return (error_exit_status("Error on fd!", infos, "?=1"));
	ft_putstr_fd(cmd->output, fd);
	close(fd);
	if (modify_var_in_list(infos, "?=0", NULL) < 0)
		return (error_exit_status("Malloc error", infos, "?=1"));
	return (0);
}

int	double_right_redirect(t_infos *infos, t_cmd *cmd)
{
	int		fd;
	char	*filename;

	if (cmd->next_operator != GT_DBL)
		return (error_exit_status("Error on >>", infos, "?=1"));
	filename = ft_strndup(cmd->next->start->token, cmd->next->start->length);
	if (!filename)
		return (error_exit_status("Malloc error!", infos, "?=1"));
	fd = open(filename, O_RDWR | O_APPEND | O_CREAT, S_IRWXG | S_IRWXU);
	free(filename);
	if (fd < 0)
		return (error_exit_status("Error on fd!", infos, "?=1"));
	ft_putstr_fd(cmd->output, fd);
	close(fd);
	if (modify_var_in_list(infos, "?=0", NULL) < 0)
		return (error_exit_status("Malloc error", infos, "?=1"));
	return (0);
}

/*int main(void)
{
	t_cmd *cmd;
	t_cmd *cmd_next;
	t_infos *infos;

	cmd = malloc(sizeof(t_cmd));
	cmd->next= malloc(sizeof(t_cmd));
	cmd->next->start = malloc(sizeof(t_token));
	cmd->output = ft_strdup("hey");
	cmd->next->start->token = ft_strdup("file");
	cmd->next->start->length = 4;
	double_left_redirect(infos, cmd);
	free(cmd->output);
	free(cmd->next->start->token);
	free(cmd->next->start);
	free(cmd->next);
	free(cmd);
}*/
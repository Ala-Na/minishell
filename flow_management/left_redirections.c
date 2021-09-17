/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   left_redirections.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlichir < hlichir@student.42.fr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/17 14:56:38 by hlichir           #+#    #+#             */
/*   Updated: 2021/09/17 15:59:01 by hlichir          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	single_left_redirect(t_infos *infos, t_cmd *cmd)
{
	int		fd;
	char	*str;

	if (cmd->next_operator != LT)
		return (error_exit_status("Error on <", infos, "?=1"));
	str = ft_str dndup(cmd->next->start->token, cmd->next->start->length);
	if (!str)
		return (error_exit_status("Malloc error!", infos, "?=1"));
	fd = open(str);
	free(str);
	if (fd < 0)
		return (error_exit_status(strerror(errno), infos, "?=1"));
	cmd->input = ft_strdup("");
	if (!cmd->input)
		return (error_exit_status("Malloc error", infos, "?=1"));
	while (get_next_line(fd, &str) > 0)
	{
		cmd->input = ft_strjoin(cmd->input, str);
		if (!cmd->input)
			return (error_exit_status("Malloc error", infos, "?=1"));
		free(str);
	}
	if (modify_var_in_list(infos, "?=0", NULL) < 0)
		return (error_exit_status("Malloc error", infos, "?=1"));
	return (0);
}

/*
** Hind => a coder
*/
/*int	double_left_redirect(t_infos *infos, t_cmd *cmd)
{
	int		fd;
	char	buffer[4096];
	char	*end_str;

	if (cmd->next_operator != LT_DBL)
		return (error_exit_status("Error on <<", infos, "?=1"));
	end_str = ft_strndup(cmd->next->start->token, cmd->next->start->length);
	if (modify_var_in_list(infos, "?=0", NULL) < 0)
		return (error_exit_status("Malloc error", infos, "?=1"));
	return (0);
}*/

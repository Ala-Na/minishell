/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlichir <hlichir@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/06 14:50:47 by hlichir           #+#    #+#             */
/*   Updated: 2021/10/04 20:14:40 by hlichir          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

/*
** Function to display in which directory we are.
** To call for pwd built.
** Return -1 if an error occurs, 0 if not.
*/
int	show_current_dir(t_infos *infos, t_cmd *cmd)
{
	char	*str;
	int		pos;

	pos = seek_elem_pos(infos->env, "PWD");
	if (pos < 0)
		str = get_curr_dir(0);
	else
		str = get_elem_value((infos->env)[pos]);
	if (!str)
	{
		if (pos < 0)
			str = strerror(errno);
		else
			str = ft_strdup_free("memory allocation issue", 0);
		str = ft_strjoin("pwd : ", str);
		if (!str)
			return (return_error(1, "memory allocation error", 0, -1));
		return (return_error(1, str, 1, -1));
	}
	write(cmd->fd_output, str, ft_strlen(str));
	write(cmd->fd_output, "\n", 1);
	free(str);
	return (0);
}

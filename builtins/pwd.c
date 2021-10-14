/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlichir < hlichir@student.42.fr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/06 14:50:47 by hlichir           #+#    #+#             */
/*   Updated: 2021/10/14 12:22:28 by hlichir          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*get_str_pwd(t_infos *infos)
{
	char	*str;
	int		pos;

	pos = seek_elem_pos(infos->env, "PWD");
	if (pos == -2)
		return (return_null_error(1, "something went wrong", 0));
	else if (pos == -1)
		return (-1);
	str = get_elem_value((infos->env)[pos]);
	if (!str)
		return (return_null_error(1, "memory allocation error", 0));
	return (str);
}

/*
** Function to display in which directory we are.
** To call for pwd built.
** Return -1 if an error occurs, 0 if not.
*/
int	show_current_dir(t_infos *infos, t_cmd *cmd)
{
	char	*str;

	str = get_str_pwd(infos);
	if (!str)
		return (-1);
	write(cmd->fd_output, str, ft_strlen(str));
	write(cmd->fd_output, "\n", 1);
	free(str);
	return (0);
}

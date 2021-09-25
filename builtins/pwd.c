/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlichir < hlichir@student.42.fr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/06 14:50:47 by hlichir           #+#    #+#             */
/*   Updated: 2021/09/24 23:08:10 by anadege          ###   ########.fr       */
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

	str = get_curr_dir(0);
	if (!str)
	{
		str = strerror(errno);
		str = ft_strjoin("pwd : ", str);
		if (!str)
			return(return_error(1, "memory allocation error", 0, -1));
		return (return_error(1, str, 1, -1));
	}
	cmd->output = ft_strjoin(str, "\n");
	free(str);
	if (!cmd->output)
			return(return_error(1, "memory allocation error", 0, -1));
	return (0);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlichir < hlichir@student.42.fr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/06 14:50:47 by hlichir           #+#    #+#             */
/*   Updated: 2021/09/23 15:25:16 by anadege          ###   ########.fr       */
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
		return (error_exit_status(str, 0, infos, "?=1"));
	}
	cmd->output = ft_strdup(str);
	if (!cmd->output)
		return (error_exit_status("Memory allocation error", 0, infos, "?=1"));
	cmd->output = ft_strjoin(cmd->output, "\n");
	if (modify_var_in_list(infos, "?=0", NULL) < 0)
		return (error_exit_status("Memory allocation error", 0, infos, "?=1"));
	printf("%s", cmd->output);
	return (0);
}

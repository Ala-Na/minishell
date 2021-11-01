/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_utils2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlichir < hlichir@student.42.fr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/29 11:15:11 by hlichir           #+#    #+#             */
/*   Updated: 2021/11/01 13:06:04 by hlichir          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*get_correct_cdpath(char *cdpath)
{
	char	*str;

	if (cdpath[0] && cdpath[ft_strlen(cdpath) - 1] != '/')
		str = ft_strjoin(cdpath, "/");
	else
		str = ft_strdup(cdpath);
	return (str);
}

int	go_to_home(t_infos *infos, t_cmd *head)
{
	int		nb;
	char	*home_path;

	nb = seek_elem_pos(infos->env, "HOME");
	home_path = NULL;
	if (nb >= 0)
		home_path = extract_value(infos->env[nb], ft_strlen(infos->env[nb]));
	if (!home_path)
		return (return_error(1, "cd: « HOME » not defined", 0, -1));
	if (ft_strlen(home_path) == 0)
	{
		free(home_path);
		return (0);
	}
	return (change_directory(infos, head, &home_path, 1));
}

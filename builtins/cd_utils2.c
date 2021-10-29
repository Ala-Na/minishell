/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_utils2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlichir < hlichir@student.42.fr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/29 11:15:11 by hlichir           #+#    #+#             */
/*   Updated: 2021/10/29 11:17:01 by hlichir          ###   ########.fr       */
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

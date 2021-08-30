/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anadege <anadege@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/30 16:59:11 by anadege           #+#    #+#             */
/*   Updated: 2021/08/30 17:05:15 by anadege          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	change_directory(char *new_dir_path)
{
	char	*str;

	if (chdir(new_dir_path) == -1)
	{
		str = strerror(errno);
		write(1, str, ft_strlen(str));
		write(1, "\n", 1);
		return (-1);
	}
	return (0);
}

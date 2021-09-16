/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlichir <hlichir@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/06 14:50:47 by hlichir           #+#    #+#             */
/*   Updated: 2021/09/12 16:32:56 by anadege          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

/*
** Function to display in which directory we are.
** To call for pwd built.
** Return -1 if an error occurs, 0 if not.
*/
int	show_current_dir(void)
{
	char	*str;
	char	buffer[1024];

	str = getcwd(buffer, 1024);
	if (!str)
	{
		str = strerror(errno);
		write(2, str, ft_strlen(str));
		write(2, "\n", 1);
		return (-1);
	}
	write(1, str, ft_strlen(str));
	write(1, "\n", 1);
	return (0);
}

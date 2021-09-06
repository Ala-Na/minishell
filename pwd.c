/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlichir <hlichir@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/06 14:50:47 by hlichir           #+#    #+#             */
/*   Updated: 2021/09/06 15:03:05 by hlichir          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
** Fonction pour afficher dans quel dossier on se trouve. 
** À appeler pour le commande pwd.
** Retourne -1 s'il y a une erreur & 0 si tout se passe bien.
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
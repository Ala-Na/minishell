/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   history.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anadege <anadege@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/30 17:16:26 by anadege           #+#    #+#             */
/*   Updated: 2021/09/02 12:10:01 by anadege          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
** Fonction qui va ouvrir le fichier minishell_history, ajouter chaque
** ligne dans l'historique courant via add_history(), ce qui permettra
** de les rendre "disponibles" lorsque la touche fleche vers le haut est pressee.
** Retourne le fd de l'historique qui sera stocke dans la strcuture infos.
** Sinon retourne -1 en cas d'erreur.
*/
int	get_previous_history(void)
{
	int		fd;
	char	*str;

	str = NULL;
	fd = open("./minishell_history", O_RDWR | O_APPEND | O_CREAT,
			S_IRWXG | S_IRWXU);
	if (fd == -1)
		return (fd);
	while (get_next_line(fd, &str) > 0)
	{
		add_history(str);
		free(str);
	}
	if (str)
		free(str);
	return (fd);
}

/*
** Fonction permettant d'ajouter la ligne de commande courante a l'historique.
** Passer infos->fd_history en 1er argument et infos->curr_cmd en 2nd.
*/
void	add_line_to_history(int history_fd, char *str)
{
	write(history_fd, str, ft_strlen(str));
	write(history_fd, "\n", 1);
	add_history(str);
}

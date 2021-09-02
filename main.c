/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anadege <anadege@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/23 14:58:07 by anadege           #+#    #+#             */
/*   Updated: 2021/09/02 14:26:51 by anadege          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
** Debut de main basique pour minishell :
** Appel a une boucle infinie qui va recuperer la commande a executer grace a 
** readline. readline prend en argument le prompteur qu'elle va afficher
** et renvoie la ligne de commande entree. readline gere elle meme les termcaps
** (fait de pouvoir deplacer le curseur dans la ligne de commande).
** Par contre readline genere des leaks still reachable non corrigeables. Mais il
** il est specifie dans le sujet qu'on a pas a le faire.
** Afin d'avoir un historique complet, la nouvelle ligne de commande est ajoutee a
** l'historique (cf history.c) et on peut y acceder par le suite en pressant la
** fleche du haut.
*/
int	main(int argc, char **argv, char **env)
{
	t_infos	infos;

	(void)argc;
	(void)argv;
	if (init_minishell(&infos, env) == -1)
		return (1);
	while (1)
	{
		infos.prompt = get_prompt();
		if (!infos.prompt)
			return (1);
		infos.curr_cmd = readline(infos.prompt);
		add_line_to_history(infos.fd_history, infos.curr_cmd);
		if (check_if_exit_or_continue(&infos) == 1)
			break ;
	}
	clean_exit(&infos);
	return (0);
}

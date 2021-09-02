/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_builtin.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anadege <anadege@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/02 14:46:17 by anadege           #+#    #+#             */
/*   Updated: 2021/09/02 15:19:27 by anadege          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
** Fonction qui verifie si le premier element de la ligne de commande correspond
** a un builtin. Renvoie la valeur de l'enum t_builtin correspondant.
*/
t_builtin	check_builtin(char	*first_elem_cmd_line)
{
	if (!ft_strncmp(first_elem_cmd_line, "echo", 4))
		return (ECHO);
	else if (!ft_strncmp(first_elem_cmd_line, "cd", 2))
		return (CD);
	else if (!ft_strncmp(first_elem_cmd_line, "pwd", 3))
		return (PWD);
	else if (!ft_strncmp(first_elem_cmd_line, "export", 6))
		return (EXPORT);
	else if (!ft_strncmp(first_elem_cmd_line, "unset", 5))
		return (UNSET);
	else if (!ft_strncmp(first_elem_cmd_line, "env", 3))
		return (ENV);
	else if (!ft_strncmp(first_elem_cmd_line, "./", 2))
		return (LAUNCH);
	return (NONE);
}

/*
** PREVOIR FONCTION POUR ENVOYER 1ER ELEMENT DE LA LIGNE
** DE COMMANDE DANS CHECK_BUILTIN
** SINON, RENVOYER ERREUR POUR "COMMAND NOT FOUND".
*/

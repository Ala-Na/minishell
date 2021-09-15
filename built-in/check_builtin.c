/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_builtin.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anadege <anadege@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/02 14:46:17 by anadege           #+#    #+#             */
/*   Updated: 2021/09/12 16:49:04 by anadege          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

/*
** Function to check that the first argument of the command line is a built in.
** Return the corresponding value of enum t_builtin.
*/
t_builtin	check_builtin(char	*first_elem)
{
	if (!ft_strncmp(first_elem, "echo", 4) && (first_elem[4] == ' '
			|| first_elem[4] == '\t'))
		return (ECHO);
	else if (!ft_strncmp(first_elem, "cd", 2) && (first_elem[2] == ' '
			|| first_elem[2] == '\t'))
		return (CD);
	else if (!ft_strncmp(first_elem, "pwd", 3) && (first_elem[3] == ' '
			|| first_elem[3] == '\t'))
		return (PWD);
	else if (!ft_strncmp(first_elem, "export", 6) && (first_elem[6] == ' '
			|| first_elem[6] == '\t'))
		return (EXPORT);
	else if (!ft_strncmp(first_elem, "unset", 5) && (first_elem[5] == ' '
			|| first_elem[5] == '\t'))
		return (UNSET);
	else if (!ft_strncmp(first_elem, "env", 3) && (first_elem[3] == ' '
			|| first_elem[3] == '\t'))
		return (ENV);
	return (NONE);
}

/*
** PREVOIR FONCTION POUR ENVOYER 1ER ELEMENT DE LA LIGNE
** DE COMMANDE DANS CHECK_BUILTIN
** SINON, RENVOYER ERREUR POUR "COMMAND NOT FOUND".
*/

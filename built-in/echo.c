/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlichir <hlichir@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/07 12:14:01 by hlichir           #+#    #+#             */
/*   Updated: 2021/09/07 13:27:46 by hlichir          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

/*
**	Ces fonctions sont appelées après avoir vérifié que les 4 premières lettres
**	de str correspondent bien à "echo" et que la 5ème lettre est soit un 
**	whitespace soit un '\0'.
** /!\ La fonction echo n'imprime qu'un espace quand elle rencontre un tab
** (généralisé aux whitespaces (?)) par défaut.
*/

/*
**	Cette fonction permet de vérifier si l'option n est activée (-n suivi 
**	d'un whitespace ou d'un '\0') pour modifier la valeur de la variable
**	option (en pointeur)
**	Elle renvoit la bonne position dans la string str pour commencer
**	l'impression des arguments.
*/
int	check_n_option(char *str, int str_length, int *option)
{
	int	i;

	i = 4;
	if (str_length <= i)
		return (4);
	while (str[i] && ft_iswhitespace(str[i]))
		i++;
	if (str_length < i + 2)
		return (i);
	if (str[i] && str[i] == '-' && str[i + 1] && str[i + 1] == 'n')
	{
		if (str[i + 2] == '\0' || ft_iswhitespace(str[i + 2]))
		{
			*option = 1;
			return (i + 2);
		}
	}
	return (i);
}

/*
**	La fonciton qui se lance pour exécuter la commande ECHO
**	-> Vérifie si l'option -n est active ou non
**	-> Imprime le reste de str en prenant bien en compte la particularité
**		des whitespaces
**	-> Cette fontion pourrait très bien être un void (à voir à la fin)
*/
int	echo_builtin(char *str, int str_length)
{
	int	option;
	int	i;

	option = 0;
	i = check_n_option(str, str_length, &option);
	while (str[i] && ft_iswhitespace(str[i]))
		i++;
	while (str[i] && i < str_length)
	{
		if (ft_iswhitespace(str[i]))
		{
			write(1, " ", 1);
			while (str[i] && i < str_length && ft_iswhitespace(str[i]))
				i++;
		}
		else
		{
			write(1, str + i, 1);
			i++;
		}
	}
	if (option == 0)
		write(1, "\n", 1);
	return (0);
}

/*int	main(void)
{
	char *str = "echo -n					la deh					oehie 		,oej,de";
	
	echo_builtin(str, ft_strlen(str));
	return (0);
}*/

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlichir <hlichir@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/01 21:57:01 by anadege           #+#    #+#             */
/*   Updated: 2021/09/24 22:07:46 by hlichir          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

/*
** Function used to print when a invalid identifier is encountered.
*/
int	invalid_token_print(t_token *token)
{
	write(2, "unset: « ", 10);
	write(2, token->token, token->length);
	write(2, " » : not a valid identifier\n", 29);
	return (-1);
}

/*
** Function to check if the argument to unset is valid or not.
** 1. Check if all the characters are '_' -> valid
** 2. Check if all the characters are either 0-9 or '_' -> invalid
** 3. Check if all the characters are either alphanumeric or '_' -> valid
** 4. If the third check fails -> invalid
*/
int	check_validity_token(t_token *token)
{
	int	i;
	int	l;

	l = token->length;
	i = 0;
	while (i < l && token->token[i] == '_')
		i++;
	if (i == l)
		return (0);
	i = 0;
	while (i < l && (token->token[i] == '_' || ft_isdigit(token->token[i])))
		i++;
	if (i == l)
		return (invalid_token_print(token));
	i = 0;
	while (i < l && (token->token[i] == '_' || ft_isalnum(token->token[i])))
		i++;
	if (i == l)
		return (0);
	return (invalid_token_print(token));
}

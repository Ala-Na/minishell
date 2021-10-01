/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlichir <hlichir@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/01 21:57:01 by anadege           #+#    #+#             */
/*   Updated: 2021/09/30 22:00:07 by hlichir          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

/*
** Function used to print when a invalid identifier is encountered.
*/
int	invalid_unset_token(t_token *token)
{
	char	*tmp;
	char	*str;

	tmp = ft_strnjoin("unset: « ", token->token, token->length);
	if (!tmp)
		return (return_error(1, "memory allocation error", 0, -1));
	str = ft_strjoin(tmp, " » : not a valid identifier");
	free(tmp);
	if (!str)
		return (return_error(1, "memory allocation error", 0, -1));
	return (return_error(1, str, 1, -1));
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
		return (invalid_unset_token(token));
	i = 0;
	while (i < l && (token->token[i] == '_' || ft_isalnum(token->token[i])))
		i++;
	if (i == l)
		return (0);
	return (invalid_unset_token(token));
}

/*
**	Sub-function to free_var name & value of a var.
*/
void	free_var(t_var **var)
{
	free((*var)->name);
	free((*var)->value);
	free(*var);
}

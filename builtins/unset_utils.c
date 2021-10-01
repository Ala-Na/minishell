/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlichir <hlichir@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/01 21:57:01 by anadege           #+#    #+#             */
/*   Updated: 2021/10/01 17:08:14 by hlichir          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

/*
** Function to get the new token length to only check the name of the variable
*/
int	get_new_length(t_token *token)
{
	int	i;

	i = 0;
	while (i < token->length && token->token[i] && token->token[i] != '=')
		i++;
	return (i);
}

/*
** Function used to print when a invalid identifier is encountered.
*/
int	invalid_token(t_token *token, int is_export)
{
	char	*tmp;
	char	*str;

	if (is_export)
		tmp = ft_strnjoin("export: « ", token->token, token->length);
	else
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
int	check_validity_token(t_token *token, int is_export)
{
	int	i;
	int	l;

	l = token->length;
	i = 0;
	if (l == 0)
		return (invalid_token(token, is_export));
	while (i < l && token->token[i] == '_')
		i++;
	if (i == l)
		return (0);
	i = 0;
	while (i < l && (token->token[i] == '_' || ft_isdigit(token->token[i])))
		i++;
	if (i == l)
		return (invalid_token(token, is_export));
	i = 0;
	while (i < l && (token->token[i] == '_' || ft_isalnum(token->token[i])))
		i++;
	if (i == l)
		return (0);
	return (invalid_token(token, is_export));
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

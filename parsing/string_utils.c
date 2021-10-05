/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   string_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlichir <hlichir@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/05 14:15:54 by hlichir           #+#    #+#             */
/*   Updated: 2021/10/05 14:26:47 by hlichir          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

/*
** Create a string by taking into account the linked_to_next tokens.
*/
char	*ft_strdup_linked_string(t_token *token)
{
	char	*str;

	str = NULL;
	get_string_loop(token, &str, 0);
	if (!str)
		return (return_null_error(1, "memory allocation error", 0));
	get_string_loop(token, &str, 1);
	return (str);
}

/*
** Sub-function to move the next token by taking into account linked_to_next
**	ones.
*/
void	move_to_next_token(t_token **token, int one_more)
{
	while (*token && (*token)->linked_to_next)
		*token = (*token)->next;
	if (*token && one_more)
		*token = (*token)->next;
}

/*
** Function to get all tokens linked together.
*/
void	get_string_loop(t_token *elem, char **str, int fill_str)
{
	t_token	*curr;
	int		i;
	int		j;

	i = 0;
	j = 0;
	curr = elem;
	while (curr)
	{
		j = 0;
		while (j < curr->length)
		{
			if (fill_str)
				(*str)[i] = curr->token[j];
			i++;
			j++;
		}
		if (!curr->linked_to_next)
			break ;
		curr = curr->next;
	}
	if (fill_str)
		(*str)[i] = 0;
	else
		*str = malloc(sizeof(**str) * (i + 1));
}

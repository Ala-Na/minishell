/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlichir <hlichir@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/01 19:29:45 by hlichir           #+#    #+#             */
/*   Updated: 2021/10/01 22:00:29 by hlichir          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

/*
** Create a string by taking into account the linked_to_next tokens.
*/
char	*ft_strdup_linked_string(t_token *token)
{
	char	*str;

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

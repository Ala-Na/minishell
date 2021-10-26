/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   skip_redir_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlichir < hlichir@student.42.fr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/07 23:48:08 by hlichir           #+#    #+#             */
/*   Updated: 2021/10/15 18:55:32 by hlichir          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

/*
** Sub_function for get_next_token (thank you norminette)
*/
t_token	*check_prev_token(t_token *prev_token, t_cmd **prev_cmd)
{
	if (!prev_token || !prev_token->linked_to_next)
		return (prev_token->next);
	else
	{
		if (get_next_token_loop(prev_cmd, &prev_token) == -1)
			return (NULL);
		return (prev_token);
	}
}

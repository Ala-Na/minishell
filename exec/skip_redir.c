/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   skip_redir.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anadege <anadege@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/03 21:22:56 by anadege           #+#    #+#             */
/*   Updated: 2021/10/03 21:52:22 by anadege          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_token	*get_next_non_redir_token(t_infos *infos, t_cmd *head_cmd,
		t_cmd **prev_cmd, t_token *prev_token)
{
	t_token	*curr_token;
	int		prev_was_redir;

	if (!infos || !head_cmd)
		return ((t_token *)return_null_error(1, "something went wrong", 0));
	prev_was_redir = 0;
	if (!*prev_cmd)
	{
		(*prev_cmd) = head_cmd;
		if (!head_cmd->start)
			prev_was_redir = 1;
		else
			return (head_cmd->start);
	}
	else if (prev_token != (*prev_cmd)->end)
		return (prev_token->next);
	else if (prev_token == (*prev_cmd)->end && (*prev_cmd)->next_operator <= 0)
		return (NULL);
	*prev_cmd = (*prev_cmd)->next;
	curr_token = (*prev_cmd)->start;
	while (prev_was_redir)
	{
		if (curr_token == (*prev_cmd)->end && (*prev_cmd)->next_operator <= 0)
			return (NULL);
		else if (curr_token == (*prev_cmd)->end)
		{
			*prev_cmd = (*prev_cmd)->next;
			curr_token = (*prev_cmd)->start;
		}
		else
		{
			curr_token = curr_token->next;
			break ;
		}
	}
	return (curr_token);
}

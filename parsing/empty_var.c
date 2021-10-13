/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   empty_var.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anadege <anadege@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/12 23:20:11 by anadege           #+#    #+#             */
/*   Updated: 2021/10/13 13:48:34 by anadege          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	is_empty_var(char *var)
{
	if (!strncmp(var, "\"\'", 3))
		return (1);
	return (0);
}

void	skip_empty_var_at_end(t_token **tokens, t_token **curr)
{
	t_token	*prev;
	t_token	*next;

	(void)tokens;
	if (!(*curr)->next && (*curr)->prev && (*curr)->prev->type != OPERATOR
		&& (*curr)->type == VARIABLE
		&& !ft_strncmp((*curr)->token, "$\"\'$", (*curr)->length))
	{
		prev = (*curr)->prev;
		prev->next = NULL;
		free(*curr);
	}
	else if ((*curr)->prev && (*curr)->prev->type != OPERATOR
		&& (*curr)->type == VARIABLE
		&& !ft_strncmp((*curr)->token, "$\"\'$", (*curr)->length)
		&& (*curr)->next->type == OPERATOR)
	{
		next = (*curr)->next;
		prev = (*curr)->prev;
		next->prev = prev;
		prev->next = next;
		free(*curr);
		*curr = next;
	}
}

void	skip_empty_var_in_middle(t_token **tokens, t_token **curr,
		t_token **next)
{
	t_token	*prev;

	prev = (*curr)->prev;
	(*next)->prev = prev;
	if (prev)
		prev->next = *next;
	if (*curr == *tokens)
		*tokens = *next;
	free(*curr);
}

void	skip_empty_var(t_token **tokens)
{
	t_token	*curr;
	t_token	*next;

	curr = *tokens;
	next = curr->next;
	while (next)
	{
		if (curr->type == VARIABLE
			&& !ft_strncmp(curr->token, "$\"\'$", curr->length)
			&& (next->type != OPERATOR || (next->type == VARIABLE \
			&& !ft_strncmp(next->token, "$\"\'$", next->length))))
			skip_empty_var_in_middle(tokens, &curr, &next);
		else
			skip_empty_var_at_end(tokens, &curr);
		curr = next;
		next = curr->next;
	}
	skip_empty_var_at_end(tokens, &curr);
}

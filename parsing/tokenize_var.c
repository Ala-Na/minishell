/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize_var.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlichir <hlichir@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/08 00:59:39 by hlichir           #+#    #+#             */
/*   Updated: 2021/10/08 01:20:33 by hlichir          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	add_tokens_for_variables(t_token **tokens)
{
	t_token	*current;
	t_token	*new;
	int		i;
	int		size;

	current = *tokens;
	while (current)
	{
		if (current->type == VARIABLE)
		{
			current->token = current->token + 1;
			size = current->length - 1;
			tokenize_variables(tokens, &current, new, size);
			i = 0;
			while ((current->token)[i] && \
				!ft_strchr(" \n\t", (current->token)[i]) && \
				(current->token)[i] != '$')
				i++;
			current->length = i;
		}
		if (current)
			current = current->next;
	}
}

void	tokenize_variables(t_token **tokens, t_token **current, t_token *new, \
			int size)
{
	int		i;
	t_token	*tmp;

	i = 0;
	while (i < size)
	{
		while (i < size && ((*current)->token)[i] \
			&& !ft_strchr(" \n\t", ((*current)->token)[i]))
			i++;
		(*current)->length = i;
		while (i < size && ((*current)->token)[i] \
			&& ft_strchr(" \n\t", ((*current)->token)[i]))
			i++;
		if (i < size - 1)
		{
			new = init_new_token(tokens, (*current)->token + i, NULL, NULL);
			new->type = VARIABLE;
			tmp = (*current)->next;
			(*current)->next = new;
			new->next = tmp;
			(*current) = (*current)->next;
		}
		size = size - i;
		i = 0;
	}
}

int	set_parsing_error(char **error_pos, char *error, t_token **to_free)
{
	*error_pos = error;
	free(*to_free);
	return (-1);
}

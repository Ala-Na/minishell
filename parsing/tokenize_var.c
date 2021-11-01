/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize_var.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlichir < hlichir@student.42.fr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/08 00:59:39 by hlichir           #+#    #+#             */
/*   Updated: 2021/11/01 16:11:54 by hlichir          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	add_tokens_for_variables(t_token **tokens, t_token *new)
{
	t_token	*current;
	int		size;

	current = *tokens;
	while (current)
	{
		if (current->type == VARIABLE)
		{
			current->token = current->token + 1;
			size = current->length - 1;
			if (current->token[size]
				&& !ft_strncmp(current->token + size, "'$'", 3))
				current->length = current->length - 2;
			else
				separate_var_for_tokenization(tokens, &current, new, size);
		}
		if (current)
			current = current->next;
	}
}

void	separate_var_for_tokenization(t_token **tokens, t_token **current,
			t_token *new, int size)
{
	int	i;

	while ((*current)->token[0] && ft_strchr(" \t\n", (*current)->token[0]))
	{
		(*current)->token = (*current)->token + 1;
		size -= 1;
	}
	i = 0;
	tokenize_variables(tokens, current, new, size);
	while (((*current)->token)[i] && ((*current)->token)[i] != '$'
		&& !ft_strchr(" \n\t", ((*current)->token)[i]))
		i++;
	(*current)->length = i;
}

void	tokenize_variables(t_token **start, t_token **cur, t_token *new, int s)
{
	int		i;
	t_token	*tmp;

	i = 0;
	while (i < s - 1)
	{
		while (i < s - 1 && !ft_strchr(" \n\t", ((*cur)->token)[i]))
			i++;
		(*cur)->length = i;
		while (i < s - 1 && ((*cur)->token)[i] && ft_isblank((*cur)->token[i]))
			i++;
		if (i < s - 1)
		{
			new = init_new_token(start, (*cur)->token + i, NULL, NULL);
			if (!new)
				return ;
			new->type = VARIABLE;
			tmp = (*cur)->next;
			(*cur)->next = new;
			new->next = tmp;
			(*cur) = (*cur)->next;
		}
		s = s - i;
		i = 0;
	}
}

int	set_parsing_error(char **error_pos, char *error, t_token **to_free)
{
	*error_pos = error;
	free(*to_free);
	return (-1);
}

/*
**	Subfunction of string manipulation to change the length & start position
** of a token when it's a string
*/
void	change_token_as_string(t_token **string_token)
{
	(*string_token)->length -= 2;
	(*string_token)->token = (*string_token)->token + 1;
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlichir < hlichir@student.42.fr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/05 14:12:00 by anadege           #+#    #+#             */
/*   Updated: 2021/10/13 19:10:59 by hlichir          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

/*
** Identify token type an return the corresponding enum.
*/
t_tokentype	identify_token_type(char *token, int length)
{
	int			i;
	t_tokentype	tmp_type;

	i = 0;
	if (token[i] == '"' || token[i] == '\'')
		return (STRING);
	else if (token[i] == '$')
		return (VARIABLE);
	else if (ft_strchr("|><", token[i]))
		return (OPERATOR);
	tmp_type = IDENTIFIER;
	while (i < length && token[i])
	{
		if (token[i] == '=')
			tmp_type = ASSIGNMENT;
		i++;
	}
	return (tmp_type);
}

/*
** Function to add new t_token element to the end of 
** a t_token list.
*/
void	add_back_token(t_token **tokens, t_token *new)
{
	t_token	*last;

	if (!new)
		return ;
	else if (!*tokens)
	{
		*tokens = new;
		return ;
	}
	last = *tokens;
	while (last->next)
		last = last->next;
	last->next = new;
}

/*
** Function to create and initialize values of a new token
** placed at the beginning of cmd string.
** Add this token to a linked list thanks to prev argument.
** Return NULL if an error occurs like a string not closed of
** two operators following each other.
*/
t_token	*init_new_token(t_token **tokens, char *cmd,
	int *syntax_error, char **error_pos)
{
	t_token	*prev;
	t_token	*new;

	new = malloc(sizeof(*new));
	if (!new)
		return (NULL);
	new->token = cmd;
	new->length = browse_token(cmd, syntax_error, error_pos);
	if (new->length == -1)
	{
		free(new);
		return (NULL);
	}
	new->type = identify_token_type(new->token, new->length);
	new->prev = NULL;
	new->next = NULL;
	new->linked_to_next = NULL;
	if (!*tokens)
		return (new);
	prev = *tokens;
	while (prev && prev->next)
		prev = prev->next;
	new->prev = prev;
	return (new);
}

/*
** Free list of token from one of it's extremity. If end is equal to 1,
** start freeing struct from the tail. If end is equal to 0, start
** freeing fom the head.
*/
void	free_token_list_from_extremity(t_token **tokens, int end)
{
	t_token	*to_free;

	if (!tokens || !*tokens)
		return ;
	while (*tokens)
	{
		to_free = *tokens;
		if (end)
			*tokens = (*tokens)->prev;
		else
			*tokens = (*tokens)->next;
		free(to_free);
	}
	*tokens = NULL;
}

/*
** Function which move pointer of string beginning and it's
** size.
*/
void	strings_manipulation(t_token **tokens)
{
	t_token	*curr_token;
	char	to_compare;

	add_tokens_for_variables(tokens);
	curr_token = *tokens;
	while (curr_token)
	{
		to_compare = curr_token->token[curr_token->length];
		if (curr_token->type == VARIABLE
			&& curr_token->next && curr_token->next->type != VARIABLE)
			to_compare = curr_token->token[curr_token->length + 1];
		if (curr_token->type != STRING && curr_token->type != VARIABLE
			&& curr_token->token[curr_token->length] && curr_token->next
			&& ft_strchr("\"\'$", to_compare))
			curr_token->linked_to_next = curr_token->next;
		else if ((curr_token->type == STRING || curr_token->type == VARIABLE)
			&& curr_token->token[curr_token->length] && curr_token->next
			&& !ft_strchr(" \n\t", to_compare))
			curr_token->linked_to_next = curr_token->next;
		if (curr_token->type == STRING)
			change_token_as_string(&curr_token);
		curr_token = curr_token->next;
	}
}

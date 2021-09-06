/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anadege <anadege@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/05 14:12:00 by anadege           #+#    #+#             */
/*   Updated: 2021/09/06 14:01:39 by anadege          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
	else if (ft_strchr("|><", token[i]))
		return (OPERATOR);
	tmp_type = IDENTIFIER;
	while (i < length && token[i])
	{
		if (token[i] == '=')
			tmp_type = ASSIGNEMENT;
		i++;
	}
	return (tmp_type);
}

/*
** Browse a string begin_token until the end of the token.
** Return the token size or -1 if an error occurs (ex: string with
** no end).
** Doesn't check for any other syntax error except for a string to end 
** by the same char it stopped.
*/
int	browse_token(char *begin_token)
{
	int		i;
	char	string_char;
	char	operator_char;

	i = 0;
	string_char = 0;
	operator_char = 0;
	if (begin_token[i] == '\'' || begin_token[i] == '"'
		|| begin_token[i] == '$')
		string_char = begin_token[i];
	else if (ft_strchr("|><", begin_token[i++]))
		operator_char = begin_token[i];
	while (!operator_char && begin_token[i])
	{
		i++;
		if (string_char && (string_char != '$' && begin_token[i] == string_char)
			|| (string_char == '$' && !ft_isalnum(begin_token[i])
				&& begin_token[i] != '_'))
			break ;
		else if (!string_char && ft_strchr("\"' \t$|><", begin_token[i]))
			break ;
	}
	if (string_char && string_char != '$' && begin_token[i] != string_char)
		return (-1); //erreur syntax
	return (i);
}

/*
** Function to create and initialize values of a new token
** placed at the beginning of cmd string.
** Add this token to a linked list thanks to prev argument.
** Return NULL if an error occurs.
*/
t_token	*init_new_token(t_token *prev, char *cmd)
{
	t_token	*new;

	new = malloc(sizeof(*new));
	if (!new)
		return (NULL);
	new->token = cmd;
	new->length = browse_token(cmd);
	if (new->length == -1)
	{
		free(new);
		return (NULL);
	}
	new->type = identify_token_type(new->token, new->length);
	new->prev = prev;
	new->next = NULL;
	return (new);
}

/*
** Free list of token from one of it's extremity. If end is equal to 1,
** start freeing struct from the tail. If end is equal to 0, start
** freeing fom the head.
*/
void	free_token_list_from_extremity(t_token *tokens, int end)
{
	t_token *to_free;

	while (tokens)
	{
		to_free = tokens;
		if (end)
			tokens = tokens->prev;
		else
			tokens = tokens->next;
		free(to_free);
	}
}

/*
** Function to start parsing/lexing of command line into token.
** Return a doubly linked structure t_token where each element
** consist of the command line string placed at the beginning
** of each token, the length/size of each token in that string,
** the kind of token it represent in enum t_tokentype.
** Each token is linked to the previous and next one in the string
** (with NULL as previous for the first element and NULL as nest for
** the last).
*/
t_token	*scan_cmd(char	*cmd)
{
	t_token	*tokens;
	t_token	*tmp;
	int		i;

	i = 0;
	tokens = NULL;
	if (!cmd)
		return (NULL);
	while (cmd[i])
	{
		while (cmd[i] && (cmd[i] == ' ' || cmd[i] == '\t'))
			i++;
		if (cmd[i] == 0)
			break ;
		tmp = init_new_token(tokens, &cmd[i]);
		if (!tmp)
		{
			free_token_list_from_extremity(tokens, 1);
			return (NULL);
		}
		if (tokens && tmp)
			tokens->next = tmp;
		i += tmp->length;
		tokens = tmp;
	}
	while (tokens && tokens->prev)
		tokens = tokens->prev;
	return (tokens);
}

/*
** Main to check if lexing is fonctionning correctly
**int	main(int argc, char **argv)
**{
**	t_token *lst;
**
**	char *cmd = ft_strdup("$con=truc|chouette>>><lol?");
**	lst = scan_cmd(cmd);
**	while (lst)
**	{
**		printf("%s of size %i is %i type\n", lst->token, lst->length, lst->type);
**		lst = lst->next;
**	}
**	free_token_list_from_extremity(lst, 1);
**	free(cmd);
**	return (0);
**}
*/

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anadege <anadege@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/05 14:12:00 by anadege           #+#    #+#             */
/*   Updated: 2021/09/09 21:10:04 by anadege          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

/*
** Sub-function to browse_token, when token begin with quote.
*/
int	browse_string(char *begin_token, char stop_char, int *syntax_error,
	char **error_pos)
{
	int	i;

	i = 0;
	while (begin_token[i])
	{
		i++;
		if (begin_token[i] == stop_char)
			break ;
	}
	if (begin_token[i] != stop_char)
	{
		*syntax_error = -1;
		*error_pos = begin_token;
		return (-1);
	}
	i++;
	return (i);
}

/*
** Browse a string token until the end of the token.
** Return the token size or -1 if an error occurs (ex: string with
** no end).
** Doesn't check for any other syntax error except for a string to end 
** by the same char it stopped.
*/
int	browse_token(char *token, int *syntax_error, char **error_pos)
{
	int		i;
	char	var_char;
	char	ope_char;

	i = 0;
	var_char = 0;
	ope_char = 0;
	if (ft_strchr("\"'", token[i]))
		return (browse_string(token, token[i], syntax_error, error_pos));
	else if (ft_strchr("|><", token[i]))
		ope_char = token[i++];
	else if (token[i] == '$' || token[i] == '~')
		var_char = token[i];
	while (!ope_char && token[i] && ++i)
	{
		if (var_char == '$' && !ft_isalnum(token[i]) && token[i] != '_')
			break ;
		else if (ft_strchr("\"' \t$|><~", token[i]) || var_char == '~')
			break ;
	}
	if (ope_char && ft_strchr("><", ope_char) && ope_char == token[i])
		i++;
	return (i);
}

/*
** Check syntax error from tokens.
** WARNING : Does not consider "special case" like <> >| |> |< >>| |>>.
** Consider \ ; & ( ) and \n [ ] as undefined special characters.
*/
int	check_operators_and_undefined_char(t_token *curr, t_token *prev,
		int *syntax_error, char **error_pos)
{
	int	i;

	i = 0;
	if (!curr)
		return (-1);
	while (curr->type != STRING && curr->token[i])
	{
		if (ft_strchr("\\;&()\n[]", curr->token[i]))
		{
			*syntax_error = -3;
			*error_pos = &curr->token[i];
			return (-1);
		}
		i++;
	}
	if (prev && curr->type == OPERATOR && prev->type == OPERATOR)
	{
		*syntax_error = -2;
		*error_pos = prev->token;
		return (-1);
	}
	return (0);
}

t_token	*check_cmd_extremity_is_not_operator(t_token **tokens,
	int *syntax_error, char **error_pos)
{
	t_token	*first;
	t_token	*last;

	first = *tokens;
	last = *tokens;
	if (first->type == OPERATOR)
	{
		*error_pos = first->token;
		*syntax_error = -5;
		free_token_list_from_extremity(last, 0);
		return (NULL);
	}
	while (last->next)
		last = last->next;
	if (last->type == OPERATOR)
	{
		*error_pos = last->token;
		*syntax_error = -4;
		free_token_list_from_extremity(last, 1);
		return (NULL);
	}
	return (*tokens);
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
t_token	*tokenize_cmd(char	*cmd, int *syntax_error, char **error_pos)
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
		tmp = init_new_token(&tokens, &cmd[i], syntax_error, error_pos);
		if (!tmp || check_operators_and_undefined_char(tmp, tmp->prev,
				syntax_error, error_pos) < 0)
		{
			free_token_list_from_extremity(tokens, 0);
			return (NULL);
		}
		add_back_token(&tokens, tmp);
		i += tmp->length;
	}
	return (check_cmd_extremity_is_not_operator(&tokens, syntax_error, error_pos));
}

/*
// Main to check if tokenizing is fonctionning correctly
int	main(int argc, char **argv)
{
	t_token *lst;
	int		a;
	char	*error_pos;

	char *cmd = ft_strdup("$machin=truc|choue~tte>>\"lol\"?");
	lst = tokenize_cmd(cmd, &a, &error_pos);
	while (lst && lst->next)
	{
		printf("%s of size %i is %i type\n", lst->token, lst->length, lst->type);
		lst = lst->next;
	}
	if (lst)
		free_token_list_from_extremity(lst, 1);
	free(cmd);
	return (0);
}
*/

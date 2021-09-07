/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokeniser.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anadege <anadege@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/05 14:12:00 by anadege           #+#    #+#             */
/*   Updated: 2021/09/07 11:45:59 by anadege          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

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
	if (ft_strchr("\\\"'", begin_token[i]))
		string_char = begin_token[i];
	else if (ft_strchr("|><", begin_token[i]))
		operator_char = begin_token[i++];
	while (!operator_char && begin_token[i] && ++i)
	{
		if (string_char && ((string_char != '$' && begin_token[i] == string_char)
			|| (string_char == '$' && !ft_isalnum(begin_token[i])
				&& begin_token[i] != '_')))
			break ;
		else if (!string_char && ft_strchr("\"' \t$|><", begin_token[i]))
			break ;
	}
	if (operator_char && ft_strchr("><", operator_char) && operator_char == begin_token[i])
		i++;
	if (string_char && string_char != '$' && begin_token[i] != string_char)
		return (-1); //erreur syntax
	return (i);
}

/*
** Check syntax error from tokens
*/
int	check_operators_and_undefined_char(t_token *curr, t_token *prev, int *syntax_error)
{
	int	i;

	i = 0;
	if (!curr)
		return (-1);
	while (curr->type != STRING && curr->token[i])
	{
		if (ft_strchr("\\;&()\n", curr->token[i]))
		{
			*syntax_error = -3;
			return (-1);
		}
		i++;
	}
	if (prev && curr->type == OPERATOR && prev->type == OPERATOR)
	{
		*syntax_error = -2;
		return (-1);
	}
	return (0);
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
t_token	*tokenize_cmd(char	*cmd, int *syntax_error)
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
		tmp = init_new_token(&tokens, &cmd[i], syntax_error);
		if (!tmp)
		{
			free_token_list_from_extremity(tokens, 0);
			return (NULL);
		}
		add_back_token(&tokens, tmp);
		if (check_operators_and_undefined_char(tmp, tmp->prev, syntax_error) < 0)
		{
			free_token_list_from_extremity(tokens, 0);
			return (NULL);
		}
		i += tmp->length;
	}
	return (tokens);
}

// Main to check if tokenizing is fonctionning correctly
int	main(int argc, char **argv)
{
	t_token *lst;
	int		a;

	char *cmd = ft_strdup("$con=truc|chouette>>><lol?");
	lst = tokenize_cmd(cmd, &a);
	while (lst)
	{
		printf("%s of size %i is %i type\n", lst->token, lst->length, lst->type);
		lst = lst->next;
	}
	free_token_list_from_extremity(lst, 1);
	free(cmd);
	return (0);
}
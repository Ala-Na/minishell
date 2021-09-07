/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anadege <anadege@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/06 14:21:38 by anadege           #+#    #+#             */
/*   Updated: 2021/09/06 15:19:19 by anadege          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
** Check if operators are following other operators and if it's compatible.
** WARNING : If bonus are aimed, change conditions.
*/
int	check_operators(t_token *curr, t_token *prev, t_token *next)
{
	char	operator;
	int		operator_repetition;

	operator = curr->token[0];
	operator_repetition = 0;
	if (prev && prev->type == OPERATOR)
	{
		if (prev->token[0] == operator)
			operator_repetition++;
		else
			return (-1); //two consecutives differents operators
	}
	if (next && next->type == OPERATOR)
	{
		if (next->token[0] == operator)
			operator_repetition++;
		else
			return (-1); // two consectives differents operators
	}
	if (operator_repetition > 1)
		return (-1); //more than 2 consecutives same operators
	else if (operator_repetition == 1 && operator == '|')
		return (-1); //repetition of two pipe
	return (0);
}

/*
** Check if an undefined special character is present or not.
** Pour compatibilité avec bonus, modifier char *undefined_char.
*/
int	check_undefined_special_char(char *cmd, int length)
{
	int		i;
	char	*undefined_char;

	i = 0;
	undefined_char = "\\;&()\n";
	while (i < length)
	{
		if (ft_strchr(undefined_char, cmd[i]))
			return (-1);
		i++;
	}
	return (0);
}

/*
** Check if tokens have a correct syntax
*/
void	check_syntax(t_token *tokens, int *syntax_error)
{
	int	error;

	while (tokens)
	{
		if (tokens->type == OPERATOR)
			error = check_operators(tokens, tokens->prev, tokens->next);
		if (tokens->type != STRING)
			error = check_undefined_special_char(tokens->token, tokens->length);
		if (error)
		{
			*syntax_error = error;
			return ;
		}
		tokens = tokens->next;
	}
}

int	scan_cmd(t_infos *infos)
{
	int	syntax_error;

	syntax_error = 0;
	infos->cmd_tokens = tokenize_cmd(infos->curr_cmd, &syntax_error);
	if (infos->curr_cmd && syntax_error != -1)
		check_syntax(infos->cmd_tokens, &syntax_error);
	return (syntax_error);
}

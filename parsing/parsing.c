/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anadege <anadege@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/07 14:43:01 by anadege           #+#    #+#             */
/*   Updated: 2021/09/07 16:36:18 by anadege          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

/*
** Penser à free infos avant exit
*/
int	parsing_error(int syntax_error, char *error_pos)
{
	if (syntax_error == -1)
		printf("minishell : syntax error with unclosed quotes %s\n", error_pos);
	else if (syntax_error == -2)
		printf("minishell : syntax error with consecutive operators found near %c\n", *error_pos);
	else if (syntax_error == -3)
		printf("minishell : syntax error with undefined special character %c\n", *error_pos);
	else if (syntax_error == -4)
		printf("minishell : syntax error with operator at the end %s\n", error_pos);
	else
		printf("minishell : parsing error\n");
	return (1);
}

int	parse_cmd(t_infos *infos)
{
	int		syntax_error;
	char	*error_pos;

	syntax_error = 0;
	error_pos = NULL;
	infos->cmd_tokens = tokenize_cmd(infos->curr_cmd, &syntax_error, &error_pos);
	if (!infos->cmd_tokens || syntax_error < 0)
		return (parsing_error(syntax_error, error_pos));
	return (0);
}

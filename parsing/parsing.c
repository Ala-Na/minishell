/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anadege <anadege@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/07 14:43:01 by anadege           #+#    #+#             */
/*   Updated: 2021/09/08 17:07:25 by anadege          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

/*
** Free list of cmd from one of it's extremity. If end is equal to 1,
** start freeing struct from the tail. If end is equal to 0, start
** freeing fom the head.
*/
void	free_cmd_list_from_extremity(t_cmd *cmds, int end)
{
	t_cmd	*to_free;

	while (cmds)
	{
		to_free = cmds;
		if (end)
			cmds = cmds->prev;
		else
			cmds = cmds->next;
		free(to_free);
	}
}

t_operator	identify_operator(t_token *operator)
{
	if (!ft_strncmp("|", operator->token, 1))
		return (PIPE);
	else if (!ft_strncmp(">>", operator->token, 2))
		return (GT_DBL);
	else if (!ft_strncmp("<<", operator->token, 2))
		return (LT_DBL);
	else if (!ft_strncmp(">", operator->token, 1))
		return (GT);
	return (LT);
}

void	add_back_cmd(t_cmd **cmds, t_cmd *new)
{
	t_cmd	*last;

	if (!new)
		return ;
	else if (!*cmds)
	{
		*cmds = new;
		return ;
	}
	last = *cmds;
	while (last->next)
		last = last->next;
	last->next = new;
}

t_cmd	*init_new_cmd(t_token *start, t_cmd **head_lst)
{
	t_cmd	*new;
	t_cmd	*prev;

	new = malloc(sizeof(*new));
	if (!new)
		return (NULL);
	new->start = start;
	new->end = start;
	new->next_operator = -1;
	new->output = NULL;
	new->return_value = 0;
	new->next = NULL;
	new->prev = NULL;
	if (!*head_lst)
		return (new);
	prev = *head_lst;
	while (prev && prev->next)
		prev = prev->next;
	new->prev = prev;
	return (new);

}

t_cmd	*separate_simple_cmd(t_infos *infos)
{
	t_cmd	*new;
	t_cmd	*lst_cmds;
	t_token	*lst_tokens;
	int		new_cmd;

	new_cmd = 1;
	lst_cmds = NULL;
	lst_tokens = infos->lst_tokens;
	while (lst_tokens)
	{
		if (lst_tokens->type != OPERATOR && new_cmd)
		{
			new = init_new_cmd(lst_tokens, &lst_cmds);
			if (!new)
			{
				free_cmd_list_from_extremity(lst_cmds, 0);
				return (NULL); // free previous
			}
			new_cmd = 0;
			add_back_cmd(&lst_cmds, new);
		}
		else if (lst_tokens->type == OPERATOR)
		{
			new->end = lst_tokens->prev;
			new->next_operator = identify_operator(lst_tokens);
			new_cmd = 1;
		}
		else
			new->end = lst_tokens;
		lst_tokens = lst_tokens->next;
	}
	return (lst_cmds);
}

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
	else if (syntax_error == -5)
		printf("minishell : syntax error with command starting with operator %c\n", *error_pos);
	else
		printf("minishell : parsing error\n");
	return (1);
}

void	print_tokens(t_token *tokens)
{
	while (tokens)
	{
		printf("token start at %s with size %i and kind %i\n", tokens->token, tokens->length, tokens->type);
		tokens = tokens->next;
	}
}

void	print_cmds(t_cmd *cmds)
{
	while (cmds)
	{
		printf("cmd begin with token %s ", cmds->start->token);
		if (cmds->start != cmds->end)
			printf("and finish with token %s ", cmds->end->token);
		printf("next_operator is %i\n", cmds->next_operator);
		cmds = cmds->next;
	}
}

int	parse_cmd(t_infos *infos)
{
	int		syntax_error;
	char	*error_pos;

	syntax_error = 0;
	error_pos = NULL;
	infos->lst_tokens = tokenize_cmd(infos->curr_cmd, &syntax_error, &error_pos);
	if (!infos->lst_tokens || syntax_error < 0)
		return (parsing_error(syntax_error, error_pos));
	print_tokens(infos->lst_tokens);
	infos->lst_cmds = separate_simple_cmd(infos);
	if (!infos->lst_cmds)
		return (parsing_error(0, NULL));
	print_cmds(infos->lst_cmds);
	free_cmd_list_from_extremity(infos->lst_cmds, 0);
	free_token_list_from_extremity(infos->lst_tokens, 0);
	return (0);
}

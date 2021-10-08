/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlichir <hlichir@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/07 14:43:01 by anadege           #+#    #+#             */
/*   Updated: 2021/10/08 10:39:50 by anadege          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

/*
** Function to init empty command when redirection is meeted.
*/
int	init_empty_cmd(t_cmd **new, t_token **lst_tokens)
{
	t_cmd	*empty;

	if ((*lst_tokens)->type == OPERATOR)
	{
		empty = malloc(sizeof(*empty));
		if (!empty)
			return (-1);
		empty->start = NULL;
		empty->end = NULL;
		empty->next_operator = identify_operator(*lst_tokens);
		empty->next = NULL;
		empty->prev = NULL;
		empty->fd_input = 0;
		empty->fd_output = 1;
		*lst_tokens = (*lst_tokens)->next;
		*new = empty;
		return (1);
	}
	return (0);
}

/*
** Subfunction of separate_simple_cmd function.
** Initialize the new element new, check if it returned NULL
** or not (free struct lst_cmds if an error occurs) and call
** the function add_back_cmd.
** Return -1 if an error occurs or 0 otherwise.
*/
int	check_init_new_cmd(t_cmd **new, t_token *lst_tokens,
		t_cmd **lst_cmds, int *new_cmd)
{
	int	res;

	res = 0;
	*new = NULL;
	if (lst_tokens->type == OPERATOR)
		res = init_empty_cmd(new, &lst_tokens);
	else
		*new = init_new_cmd(lst_tokens, lst_cmds);
	if (!*new || res == -1)
	{
		free_cmd_list_from_extremity(lst_cmds, 0);
		return (-1);
	}
	if (!res)
		*new_cmd = 0;
	add_back_cmd(lst_cmds, *new);
	return (0);
}

void	token_identifier(t_token *lst_tokens, t_cmd **new, int *new_cmd)
{
	(*new)->end = lst_tokens->prev;
	(*new)->next_operator = identify_operator(lst_tokens);
	*new_cmd = 1;
}

/*
** Function which browse the t_tokens linked list infos->lst_tokens
** and separate it inside a t_cmds structure depending on operators.
** Returns NULL if an errors occurs, the t_cmd structure lst_cmds otherwise.
*/
t_cmd	*separate_simple_cmd(t_infos *infos, t_cmd *lst_cmds, int new_cmd)
{
	t_cmd	*new;
	t_token	*lst_tokens;

	lst_tokens = infos->lst_tokens;
	if (check_init_new_cmd(&new, lst_tokens, &lst_cmds, &new_cmd) == -1)
		return (NULL);
	while (lst_tokens)
	{
		if (lst_tokens->type == OPERATOR && lst_tokens->prev
			&& lst_tokens->prev->type == OPERATOR)
		{
			if (check_init_new_cmd(&new, lst_tokens, &lst_cmds, &new_cmd) == -1)
				return (NULL);
		}
		else if (lst_tokens->type != OPERATOR && new_cmd
			&& check_init_new_cmd(&new, lst_tokens, &lst_cmds, &new_cmd) == -1)
			return (NULL);
		else if (lst_tokens->type == OPERATOR)
			token_identifier(lst_tokens, &new, &new_cmd);
		else
			new->end = lst_tokens;
		lst_tokens = lst_tokens->next;
	}
	return (lst_cmds);
}

/*
** Function to parse the command line received.
** First, a tokenization is made and sytnax errors are checked. Infos are
** stocked inside a t_token structure.
** Then, a cutting by operators is made to get a linked list of simple commands.
** The function return 1 if an error occurs, 0 otherwise.
** WARNING : Returns value for error may be changed accordingly to the error
** occuring.
** Delete lines for print_tokens and print_cmds (test purpose only)
*/
int	parse_cmd(t_infos *infos)
{
	int		syntax_error;
	char	*error_pos;

	syntax_error = 0;
	error_pos = NULL;
	expand_variables(infos, 0, 0, 0);
	if (infos->curr_cmd[0] == 0 || !infos->curr_cmd)
		return (parsing_error(syntax_error, error_pos));
	infos->lst_tokens = tokenize_cmd(infos->curr_cmd, &syntax_error,
			&error_pos);
	if (!infos->lst_tokens || syntax_error < 0)
		return (parsing_error(syntax_error, error_pos));
	infos->lst_cmds = separate_simple_cmd(infos, NULL, 1);
	if (!infos->lst_cmds)
		return (parsing_error(0, NULL));
	return (0);
}

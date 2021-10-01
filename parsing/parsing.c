/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlichir <hlichir@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/07 14:43:01 by anadege           #+#    #+#             */
/*   Updated: 2021/09/30 22:58:06 by hlichir          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

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
	*new = NULL;
	*new = init_new_cmd(lst_tokens, lst_cmds);
	if (!*new)
	{
		free_cmd_list_from_extremity(lst_cmds, 0);
		return (-1);
	}
	*new_cmd = 0;
	add_back_cmd(lst_cmds, *new);
	return (0);
}

/*
** Function which browse the t_tokens linked list infos->lst_tokens
** and separate it inside a t_cmds structure depending on operators.
** Returns NULL if an errors occurs, the t_cmd structure lst_cmds otherwise.
*/
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
		if (lst_tokens->type != OPERATOR && new_cmd
			&& check_init_new_cmd(&new, lst_tokens, &lst_cmds, &new_cmd) == -1)
			return (NULL);
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
	infos->lst_cmds = separate_simple_cmd(infos);
	if (!infos->lst_cmds)
		return (parsing_error(0, NULL));
	return (0);
}

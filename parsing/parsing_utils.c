/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlichir <hlichir@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/07 14:43:01 by anadege           #+#    #+#             */
/*   Updated: 2021/10/21 15:06:35 by anadege          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

/*
** Free list of cmd from one of it's extremity. If end is equal to 1,
** start freeing struct from the tail. If end is equal to 0, start
** freeing fom the head.
*/
void	free_cmd_list_from_extremity(t_cmd **cmds, int end)
{
	t_cmd	*to_free;

	if (!cmds || !*cmds)
		return ;
	while (*cmds)
	{
		to_free = *cmds;
		if (end)
			*cmds = (*cmds)->prev;
		else
			*cmds = (*cmds)->next;
		if (to_free->fd_input > 1)
			if (close(to_free->fd_input) < 0)
				return_error(1, strerror(errno), 0, -1);
		if (to_free->fd_output > 1)
			if (close(to_free->fd_output) < 0)
				return_error(1, strerror(errno), 0, -1);
		free(to_free);
	}
	*cmds = NULL;
}

/*
** Function which returns the enum t_operator corresponding to the current
** token operator.
*/
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

/*
** Function to manipulate t_cmd structure by adding new element
** to the back of the linked list.
*/
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

/*
** Function to initialize a new element of t_cmd structure.
** The new elem previous element is set in this function, but
** new elem need to be added at the back of the cmd list
** by the function add_back_cmd.
** Return NULL if an error occurs, the new element otherwise.
*/
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
	new->next = NULL;
	new->prev = NULL;
	new->fd_input = 0;
	new->fd_output = 1;
	new->nb_tmp_file = 0;
	if (!*head_lst)
		return (new);
	prev = *head_lst;
	while (prev && prev->next)
		prev = prev->next;
	new->prev = prev;
	return (new);
}

/*
** Functions to display corresponding parsing error
** (mainly informations about syntax errors).
** Return 1 which will be the exit status.
** WARNING : Exit value may be modified.
*/
int	parsing_error(int syntax_error, char *error_pos)
{
	g_exit_status = 258;
	if (syntax_error <= -1 && syntax_error >= -5)
		ft_puterr("minishell : syntax error with ", 0);
	if (syntax_error == -1)
		print_error("unclosed quotes ", error_pos, 0, 1);
	else if (syntax_error == -2)
		print_error("consecutive operators found near ", NULL, *error_pos, 1);
	else if (syntax_error == -3)
		print_error("undefined special character ", NULL, *error_pos, 1);
	else if (syntax_error == -4)
		print_error("operator at the end ", error_pos, 0, 1);
	else if (syntax_error == -5)
		print_error("command starting with operator ", NULL, *error_pos, 1);
	else
		ft_puterr("minishell : parsing error", 1);
	return (1);
}

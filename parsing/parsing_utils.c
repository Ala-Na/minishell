/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlichir < hlichir@student.42.fr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/07 14:43:01 by anadege           #+#    #+#             */
/*   Updated: 2021/09/17 15:40:22 by hlichir          ###   ########.fr       */
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
		if (to_free->output)
			free(to_free->output);
		if (to_free->input)
			free(to_free->input);
		free(to_free);
	}
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
	new->input = NULL;
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

/*
** Functions to display corresponding parsing error
** (mainly informations about syntax errors).
** Return 1 which will be the exit status.
** WARNING : Exit value may be modified.
*/
int	parsing_error(int syntax_error, char *error_pos)
{
	if (syntax_error <= -1 && syntax_error >= -5)
		printf("minishell : syntax error with ");
	if (syntax_error == -1)
		printf("unclosed quotes %s\n", error_pos);
	else if (syntax_error == -2)
		printf("consecutive operators found near %c\n", *error_pos);
	else if (syntax_error == -3)
		printf("undefined special character %c\n", *error_pos);
	else if (syntax_error == -4)
		printf("operator at the end %s\n", error_pos);
	else if (syntax_error == -5)
		printf("command starting with operator %c\n", *error_pos);
	else
		printf("minishell : parsing error\n");
	return (1);
}

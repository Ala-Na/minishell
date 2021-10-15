/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   skip_redir.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlichir < hlichir@student.42.fr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/03 21:22:56 by anadege           #+#    #+#             */
/*   Updated: 2021/10/15 19:16:18 by hlichir          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

/*
** Function which returns the executable/builtin token.
** It skips redirections instructions and assignments.
** It fills exec_cmd with the cmd containing the exec_token.
** Returns NULL in case of error (or only assignments/redirections).
*/
t_token	*get_exec_token(t_infos *infos, t_cmd *head_cmd, t_cmd **exec_cmd)
{
	t_token	*curr_token;
	int		end;

	curr_token = NULL;
	*exec_cmd = NULL;
	end = 0;
	curr_token = get_next_token(infos, head_cmd, exec_cmd, curr_token);
	while (1)
	{
		if (curr_token->type != ASSIGNMENT)
			break ;
		end = check_if_end_pipeline(*exec_cmd, curr_token);
		if (end == 1)
			break ;
		curr_token = get_next_token(infos, head_cmd, exec_cmd, curr_token);
	}
	if (!curr_token || curr_token->type == ASSIGNMENT || end == -1)
		return ((t_token *)(return_null_error(1, "something went wrong", 0)));
	return (curr_token);
}

/*
** Function to check if present token is the last of a pipeline (single or 
** multiple t_cmd structures ending by a pipe or by the end).
** Returns 1 if it's the end, 0 otherwise. -1 is returned in cas of error.
*/
int	check_if_end_pipeline(t_cmd *cmd, t_token *token)
{
	if (!cmd || !token)
		return (return_error(1, "something went wrong", 0, -1));
	if (token == cmd->end && token->type == VARIABLE && token->next
		&& token->next->type == VARIABLE)
		return (2);
	if (token == cmd->end
		&& (cmd->next_operator == PIPE || (int)cmd->next_operator == -1))
		return (1);
	return (0);
}

/*
** Function to obtains next "non redirection instruction" token inside a 
** pipeline when the last token was a redirection instruction.
** Returns -1 in case of error, 0 otherwise.
*/
int	get_next_token_loop(t_cmd **cmd, t_token **token)
{
	if (!cmd || !token || !*cmd || !*token)
		return (return_error(1, "something went wrong", 0, -1));
	while (1)
	{
		if (check_if_end_pipeline(*cmd, *token) == 1)
		{
			*token = NULL;
			return (0);
		}
		else if (*token == (*cmd)->end)
		{
			*cmd = (*cmd)->next;
			*token = (*cmd)->start;
		}
		else if (*token && (*token)->linked_to_next != NULL)
			*token = (*token)->next;
		else
		{
			*token = (*token)->next;
			return (0);
		}
	}
	return (0);
}

/*
** Function to check if it's the first call made to get_next_token.
** In case it's the first call, it set prev_cmd pointer to head_cmd.
** Returns -1 in case of error, 0 if it was not the first call or that it was
** the first call but the cmd was empty, 1 if it was the first call and that
** the cmd didn't start by a redirection.
*/
int	check_if_first_call(t_cmd *head_cmd, t_cmd **prev_cmd, t_token **curr_token)
{
	*curr_token = NULL;
	if (!head_cmd)
		return (return_error(1, "something went wrong", 0, -1));
	if (!*prev_cmd)
	{
		*prev_cmd = head_cmd;
		if (!head_cmd->start)
			return (0);
		*curr_token = head_cmd->start;
		return (1);
	}
	return (0);
}

/*
** Function to call to get the next token inside a pipeline,
** by skipping redirections instructions token.
** Returns NULL in case of error or end of pipeline, the next token
** otherwise.
*/
t_token	*get_next_token(t_infos *infos, t_cmd *head_cmd,
		t_cmd **prev_cmd, t_token *prev_token)
{
	t_token	*curr_token;

	if (!infos || !head_cmd)
		return ((t_token *)return_null_error(1, "something went wrong", 0));
	if (check_if_first_call(head_cmd, prev_cmd, &curr_token) != 0)
		return (curr_token);
	else if (prev_token && prev_token != (*prev_cmd)->end)
		return (check_prev_token(prev_token, prev_cmd));
	else if (prev_token && check_if_end_pipeline(*prev_cmd, prev_token) == 1)
		return (NULL);
	else if (prev_token && check_if_end_pipeline(*prev_cmd, prev_token) == 2)
	{
		(*prev_cmd)->end = prev_token->next;
		return (prev_token->next);
	}
	*prev_cmd = (*prev_cmd)->next;
	if (!*prev_cmd)
		return (NULL);
	curr_token = (*prev_cmd)->start;
	if (get_next_token_loop(prev_cmd, &curr_token) == -1)
		return (NULL);
	return (curr_token);
}

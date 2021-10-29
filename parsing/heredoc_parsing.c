/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_parsing.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlichir <hlichir@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/18 18:50:05 by hlichir           #+#    #+#             */
/*   Updated: 2021/10/29 15:25:38 by anadege          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

/*
** Functions to handle the exception << $variable.
*/
char	*get_new_string_for_exception(char **cmd, int *i, int size, int tmp_i)
{
	int		j;
	char	*new;

	if (!cmd || !*cmd)
		return (return_null_error(1, "something went wrong", 0));
	j = 0;
	new = malloc(sizeof(*new) * (size + 1));
	if (!new)
		return (NULL);
	while (j < *i)
	{
		new[j] = (*cmd)[j];
		j++;
	}
	new[j++] = '\'';
	new[j++] = (*cmd)[(*i)++];
	while ((*cmd)[(*i)] && !ft_strchr(" \t\n\'\"$", (*cmd)[*i]))
		new[j++] = (*cmd)[(*i)++];
	new[j++] = '\'';
	tmp_i = *i;
	while (j < size)
		new[j++] = (*cmd)[tmp_i++];
	new[j] = 0;
	free(*cmd);
	return (new);
}

/*
** Subfunction to handle quotes & variables. For instance "hey$test hey"
**	will become "hey"$test" hey" -> the function isolate the variable to
**	avoid that il will get expanding during tokenization.
*/
char	*split_string_for_heredoc(char **cmd, int i, int size, char quote)
{
	int		j;
	char	*new;

	if (!cmd || !*cmd)
		return (return_null_error(1, "something went wrong", 0));
	j = 0;
	size = ft_strlen(*cmd) + 2;
	new = malloc(sizeof(*new) * (size + 1));
	if (!new)
		return (NULL);
	while (j < i)
	{
		new[j] = (*cmd)[j];
		j++;
	}
	new[j++] = quote;
	new[j++] = (*cmd)[i++];
	while ((*cmd)[i] && !ft_strchr(" \t\n\'\"$", (*cmd)[i]))
		new[j++] = (*cmd)[i++];
	new[j++] = quote;
	while (j < size)
		new[j++] = (*cmd)[i++];
	new[j] = 0;
	free(*cmd);
	return (new);
}

/*
**	Sub_function to navigate within quotes & modify the string if needed
**	(cf function above for further explanations).
*/
int	check_if_within_quotes(char **cmd, int *i)
{
	int	quote_char;

	quote_char = 0;
	if ((*cmd)[*i] && ft_strchr("\"\'", (*cmd)[*i]))
	{
		quote_char = (*cmd)[(*i)++];
		while ((*cmd)[*i] && (*cmd)[*i] != quote_char && (*cmd)[*i] != '$')
			(*i)++;
		if ((*cmd)[*i] && (*cmd)[*i] == '$')
		{
			*cmd = split_string_for_heredoc(cmd, *i, 0, quote_char);
			if (!(*cmd))
				return (-1);
		}
	}
	return (0);
}

/*
** Sub_function for checking if there is a variable exception after a "<<"
**	(in get_var_utils.c file).
*/
int	modify_cmd_for_heredoc(char **cmd, int *i, int *check)
{
	while ((*cmd)[*i] && !ft_strchr(" \t\n", (*cmd)[*i]))
	{
		if (check_if_within_quotes(cmd, i) < 0)
			return (-1);
		if ((*cmd)[*i] && (*cmd)[*i] == '$' && (*cmd)[*i + 1]
			&& !ft_strchr("\"\'", (*cmd)[*i + 1]))
		{
			*cmd = get_new_string_for_exception(cmd, i, ft_strlen(*cmd) + 2, 0);
			if (!(*cmd))
				return (-1);
			*check = 1;
			(*i)++;
		}
		if ((*cmd)[*i])
			(*i)++;
	}
	return (0);
}

/*
** Functions to handle the exception << $variable.
*/
int	check_for_heredoc_exception(t_infos *infos, int *new_size, int check, int i)
{
	char	*cmd;

	if (!infos || !infos->curr_cmd)
		return (return_error(1, "something went wrong", 0, -1));
	cmd = infos->curr_cmd;
	while (cmd && cmd[i])
	{
		if (cmd[i] == '<' && cmd[i + 1] && cmd[i + 1] == '<')
		{
			i = i + 2;
			while (cmd[i] && ft_strchr(" \t\n", cmd[i]))
				i++;
			if (modify_cmd_for_heredoc(&cmd, &i, &check) < 0)
				return (return_error(1, "memory allocation error", 0, -1));
		}
		if (cmd[i])
			i++;
	}
	if (check == 1)
	{
		infos->curr_cmd = cmd;
		*new_size = ft_strlen(cmd);
	}
	return (0);
}

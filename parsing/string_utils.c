/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   string_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlichir <hlichir@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/05 14:15:54 by hlichir           #+#    #+#             */
/*   Updated: 2021/10/11 22:50:16 by anadege          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

/*
** Function to get all tokens linked together.
*/
void	get_string_loop(t_token *elem, char **str, int fill_str, int i)
{
	t_token	*curr;
	int		j;

	j = 0;
	curr = elem;
	while (curr)
	{
		j = 0;
		while (j < curr->length)
		{
			if (fill_str)
			{	
				(*str)[i] = (curr->token)[j];
			}
			i++;
			j++;
		}
		if (!curr->linked_to_next)
			break ;
		curr = curr->next;
	}
	if (fill_str)
		(*str)[i] = 0;
	else
		*str = malloc(sizeof(**str) * (i + 1));
}

/*
** Create a string by taking into account the linked_to_next tokens.
*/
char	*ft_strdup_linked_string(t_token *token)
{
	char	*str;

	if (!token)
		return (return_null_error(1, "something went wrong", 0));
	str = NULL;
	get_string_loop(token, &str, 0, 0);
	if (!str)
		return (return_null_error(1, "memory allocation error", 0));
	get_string_loop(token, &str, 1, 0);
	return (str);
}

/*
** Functions to handle the exception << $variable.
*/
char	*get_new_string_for_exception(char **cmd, int i)
{
	int		j;
	int		new_size;
	char	*new;

	if (!cmd || !*cmd)
		return (return_null_error(1, "something went wrong", 0));
	j = 0;
	new_size = ft_strlen(*cmd) + 2;
	new = malloc(sizeof(*new) * (new_size + 1));
	if (!new)
		return (NULL);
	while (j < i)
	{
		new[j] = (*cmd)[j];
		j++;
	}
	new[j++] = '\'';
	while ((*cmd)[i] && !ft_strchr(" \t\n", (*cmd)[i]))
		new[j++] = (*cmd)[i++];
	new[j++] = '\'';
	while (j < new_size)
		new[j++] = (*cmd)[i++];
	new[j] = 0;
	free(*cmd);
	return (new);
}

/*
** Sub-function to print the error during the parsing if needed.
*/
void	print_error(char *str, char *s, char c, int new_line)
{
	ft_puterr(str, 0);
	if (s)
		ft_puterr(s, 0);
	else if (c)
		write(2, &c, 1);
	if (new_line)
		write(1, "\n", 1);
}

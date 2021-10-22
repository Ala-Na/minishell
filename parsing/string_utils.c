/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   string_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlichir <hlichir@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/05 14:15:54 by hlichir           #+#    #+#             */
/*   Updated: 2021/10/18 18:51:28 by hlichir          ###   ########.fr       */
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

/*
**	Sub-function to check if the var is empty & modify it.
*/
void	modify_var_if_empty(char **var, char **elem_name, int elem_size)
{
	if (*var && *var[0] == 0
		&& !ft_strncmp(*elem_name, "HOME", ft_max(4, elem_size)))
		*var = "''";
	else if (!*var || *var[0] == 0)
		*var = "\"\'";
}

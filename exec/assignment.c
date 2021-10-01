/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   assignment.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlichir <hlichir@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/13 16:06:44 by hlichir           #+#    #+#             */
/*   Updated: 2021/10/01 20:13:21 by hlichir          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

/*
** Function to extract the value of a variable assigned with '='
*/
char	*get_elem_value(char *str)
{
	int		i;
	int		j;
	char	*dest;

	i = 0;
	j = 0;
	if (!str)
		return (return_null_error(1, "something went wrong", 0));
	while (str[i] && str[i] != '=')
		i++;
	i++;
	dest = malloc(sizeof(char) * (ft_strlen(str + i) + 1));
	if (!dest)
		return (return_null_error(1, "memory allocation error", 0));
	while (str[i + j])
	{
		dest[j] = str[i + j];
		j++;
	}
	dest[j] = 0;
	return (dest);
}

/*
** Function to modify the value of an assigned variable
*/
int	modify_var_in_list(t_infos *infos, char *str, int *check)
{
	t_var	*current;
	char	*tmp_name;

	tmp_name = extract_name(str, ft_strlen(str));
	if (!tmp_name)
		return (-1);
	current = infos->lst_var;
	while (current)
	{
		if (!ft_strncmp(current->name, tmp_name, ft_strlen(tmp_name)))
		{
			free(current->value);
			current->value = get_elem_value(str);
			free(tmp_name);
			if (!current->value)
				return (-1);
			if (check)
				*check = 1;
			break ;
		}
		current = current->next;
	}
	if (check && *check == 0)
		free(tmp_name);
	return (0);
}

/*
** Function to add a new variable to the linked list of assigned variables.
*/
int	add_new_var_to_list(t_infos *infos, char *str)
{
	t_var	*new;
	t_var	*current;

	current = infos->lst_var;
	while (current && current->next)
		current = current->next;
	new = malloc(sizeof(t_var));
	if (!new)
		return (return_error(1, "memory allocation error", 0, -1));
	new->name = extract_name(str, ft_strlen(str));
	if (!new->name)
		return (-1);
	new->value = get_elem_value(str);
	if (!new->value)
	{
		free(new->name);
		return (-1);
	}
	new->next = NULL;
	if (current == NULL)
		infos->lst_var = new;
	else
		current->next = new;
	return (0);
}

/*
** Function to get all tokens linked together.
*/
void	get_string_loop(t_token *elem, char **str, int fill_str)
{
	t_token	*curr;
	int		i;
	int		j;

	i = 0;
	j = 0;
	curr = elem;
	while (curr)
	{
		j = 0;
		while (j < curr->length)
		{
			if (fill_str)
				(*str)[i] = curr->token[j];
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
** Function that handle the assignation of a variable. Called when needed :
** Token type = ASSIGNMENT.
*/
int	assign_variable_to_list(t_infos *infos, t_token *current_token)
{
	char	*str;
	int		i;
	int		check;

	i = 0;
	check = 0;
	get_string_loop(current_token, &str, 0);
	if (!str)
		return (return_error(1, "memory allocation error", 0, -1));
	get_string_loop(current_token, &str, 1);
	if (modify_var_in_list(infos, str, &check) < 0)
		return (-1);
	if (check == 0)
	{
		if (add_new_var_to_list(infos, str) < 0)
			return (-1);
	}
	free(str);
	return (0);
}

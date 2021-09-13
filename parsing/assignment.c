/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   assignment.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlichir <hlichir@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/13 16:06:44 by hlichir           #+#    #+#             */
/*   Updated: 2021/09/13 17:36:00 by hlichir          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

/*
** Function to free the linked list of variables if assignments were set!
*/
int	free_lst_var(t_infos *infos)
{
	t_var	*current;
	t_var	*tmp;

	current = infos->lst_var;
	while (current)
	{
		tmp = current;
		current = current->next;
		free(tmp->name);
		free(tmp->value);
		free(tmp);
	}
	infos->lst_var = NULL;
	return (0);
}

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
	while (str[i] && str[i] != '=')
		i++;
	i++;
	dest = malloc(sizeof(char) * (ft_strlen(str + i) + 1));
	if (!dest)
		return (NULL);
	while (str[i + j])
	{
		dest[j] = str[i + j];
		j++;
	}
	dest[j] = 0;
	return (dest);
}

/*
**	Function to modify the value of an assigned variable
*/
int	modify_var_in_list(t_infos *infos, char *str, int *check)
{
	t_var	*current;
	char	*tmp_name;

	tmp_name = get_elem_name(str);
	if (!tmp_name)
		return (0);
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
			*check = 1;
			break ;
		}
		current = current->next;
	}
	if (check == 0)
		free(tmp_name);
	return (0);
}

/*
**	Function to add a new variable to the linked list of assigned variables.
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
		return (-1);
	new->name = get_elem_name(str);
	new->value = get_elem_value(str);
	if (!new->name || !new->value)
		return (-1);
	new->next = NULL;
	if (current == NULL)
		infos->lst_var = new;
	else
		current->next = new;
	return (0);
}

/*
**	Function that handle the assignation of a variable. Called when needed :
**	Token type = ASSIGNMENT & no other command after that.
*/
int	assign_variable(t_infos *infos, t_cmd *current_cmd)
{
	char	*str;
	int		i;
	int		check;

	i = 0;
	check = 0;
	str = malloc(sizeof(char) * (current_cmd->start->length + 1));
	if (!str)
		return (-1);
	while (i < current_cmd->start->length)
	{
		str[i] = (current_cmd->start->token)[i];
		i++;
	}
	str[i] = 0;
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

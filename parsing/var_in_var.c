/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   var_in_var.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anadege <anadege@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/13 11:04:35 by anadege           #+#    #+#             */
/*   Updated: 2021/10/13 15:55:22 by anadege          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	add_var_symbol(char **new_cmd, char *var, int var_size, int *i)
{
	int	j;

	j = *i;
	if (var[0] == '$' && var_size == 1)
		(*new_cmd)[j++] = '\'';
	else
		(*new_cmd)[j++] = '$';
	*i = j;
}

void	var_in_var(char **new_cmd, int *i, int *k)
{
	int	j;

	j = *i;
	(*new_cmd)[j++] = '$';
	(*new_cmd)[j++] = '\'';
	(*new_cmd)[j++] = '$';
	(*new_cmd)[j++] = '\'';
	(*new_cmd)[j++] = '$';
	*i = j;
	*k += 1;
}

int	return_diff_size(char *var, int dbl, int i)
{
	int	nbr_var;
	int	size;

	size = (int)ft_strlen(var);
	if (size == 1 && var[0] == '$')
		return (2);
	nbr_var = 0;
	if (!dbl)
		nbr_var = check_var_in_var(var);
	size = size_var_if_var(var, nbr_var);
	if (dbl)
		return (size - i);
	return (size - i + 2);
}

int	size_var_if_var(char *var, int nbr_var)
{
	int	size;

	size = ft_strlen(var);
	if (nbr_var)
		size += (nbr_var * 4);
	return (size);
}

int	check_var_in_var(char *var)
{
	int	nbr_var;
	int	i;

	i = 0;
	nbr_var = 0;
	while (var && var[i])
	{
		if (var[i] == '$')
			nbr_var++;
		i++;
	}
	return (nbr_var);
}

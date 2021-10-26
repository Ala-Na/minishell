/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dtoa_ope_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elanna <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/27 14:53:06 by elanna            #+#    #+#             */
/*   Updated: 2021/06/22 15:12:10 by elanna           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*apply_dtwo_pten(unsigned int i)
{
	char			*to_add;
	char			tmp;
	unsigned int	y;
	unsigned int	z;
	char			rem;

	y = 1;
	to_add = malloc(sizeof(*to_add) * (i + 1));
	if (!to_add)
		return (NULL);
	to_add[0] = '5';
	to_add[i] = 0;
	while (y < i)
	{
		to_add[y++] = '0';
		z = 0;
		rem = 0;
		while (z <= (y - 1))
		{
			tmp = (to_add[z] + '0') / 2 + (rem * 5);
			rem = (to_add[z] - '0') % 2;
			to_add[z++] = tmp;
		}
	}
	return (to_add);
}

void	apply_ptwo_fill(char **to_add, int approx_size)
{
	char	tmp;
	char	rem;
	int		i;

	rem = 0;
	i = approx_size - 1;
	while (i >= 0)
	{
		tmp = ((((*to_add)[i] - '0') * 2) % 10) + rem;
		rem = (((*to_add)[i] - '0') * 2) - ((((*to_add)[i] - '0') * 2) % 10);
		rem /= 10;
		(*to_add)[i--] = tmp + '0';
	}
}

void	apply_ptwo_init(short exp, char **to_add)
{
	int	approx_size;
	int	curr_exp;
	int	i;

	i = 0;
	curr_exp = 1;
	approx_size = exp / 3 + 1;
	*to_add = malloc(sizeof(**to_add) * (approx_size + 1));
	if (!(*to_add))
		return ;
	while (i < approx_size)
		(*to_add)[i++] = '0';
	(*to_add)[i--] = 0;
	(*to_add)[i] = '2';
	while (curr_exp < exp)
	{
		apply_ptwo_fill(to_add, approx_size);
		curr_exp++;
	}
	*to_add = del_front_zero(*to_add, approx_size);
}

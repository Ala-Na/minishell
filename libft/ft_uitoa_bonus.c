/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_uitoa_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elanna <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/12 22:28:07 by elanna            #+#    #+#             */
/*   Updated: 2021/06/22 15:17:58 by elanna           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
** Function which turn an unsigned int into a string of
** it's ascii decimal representation.
*/

#include "libft.h"

static int	ft_det_size_uitoa(unsigned int n)
{
	int	size;

	if (n == 0)
		return (1);
	size = 0;
	while (n > 0)
	{
		size++;
		n /= 10;
	}
	return (size);
}

char	*ft_uitoa(unsigned int n)
{
	char	*arr;
	int		i;

	i = ft_det_size_uitoa(n);
	arr = malloc(sizeof(*arr) * (i + 1));
	if (!arr)
		return (0);
	arr[i] = 0;
	if (n == 0)
		arr[0] = '0';
	while (n > 0)
	{
		arr[--i] = '0' + (n % 10);
		n /= 10;
	}
	return (arr);
}

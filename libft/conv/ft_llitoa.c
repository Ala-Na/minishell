/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_llitoa_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elanna <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/12 22:23:43 by elanna            #+#    #+#             */
/*   Updated: 2021/06/22 15:14:13 by elanna           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
** Function which turn a long long into an ascii
** string as it's decimal representation.
*/

#include "libft.h"

static int	ft_det_size_llitoa(long long n)
{
	int					size;
	unsigned long long	nb;

	if (n == 0)
		return (1);
	size = 0;
	if (n < 0)
	{
		size++;
		nb = -n;
	}
	else
		nb = n;
	while (nb > 0)
	{
		size++;
		nb /= 10;
	}
	return (size);
}

char	*ft_llitoa(long long n)
{
	char				*arr;
	unsigned long long	nb;
	unsigned long long	i;

	i = ft_det_size_llitoa(n);
	arr = malloc(sizeof(*arr) * (i + 1));
	if (!arr)
		return (0);
	arr[i] = 0;
	nb = 0;
	if (n == 0)
		arr[0] = '0';
	else if (n < 0)
	{
		arr[0] = '-';
		nb = n * (-1);
	}
	else
		nb = n;
	while (nb > 0)
	{
		arr[--i] = '0' + (nb % 10);
		nb /= 10;
	}
	return (arr);
}

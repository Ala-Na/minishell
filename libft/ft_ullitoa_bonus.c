/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ullitoa_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elanna <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/12 22:22:23 by elanna            #+#    #+#             */
/*   Updated: 2021/06/22 15:16:38 by elanna           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
** Function which turn an unsigned long long into an ascii
** string of it's decimal representation.
*/

#include "libft.h"

static int	ft_det_size_ullitoa(unsigned long long n)
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

char	*ft_ullitoa(unsigned long long n)
{
	char	*arr;
	int		i;

	i = ft_det_size_ullitoa(n);
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

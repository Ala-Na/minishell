/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ullitobase_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elanna <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/12 22:19:50 by elanna            #+#    #+#             */
/*   Updated: 2021/06/22 15:16:24 by elanna           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
** Function which turn an unsigned long long into an ascii
** string according to a given base.
** Careful : This does not check if the base is valid (no repetitions).
*/

#include "libft.h"

static int	ft_det_size_ullitobase(unsigned long long n,
unsigned long long base_size)
{
	int	size;

	if (n == 0)
		return (1);
	size = 0;
	while (n > 0)
	{
		size++;
		n /= base_size;
	}
	return (size);
}

char	*ft_ullitobase(unsigned long long n, char *base)
{
	char				*arr;
	int					i;
	unsigned long long	base_size;

	i = 0;
	base_size = 0;
	while (base[i++] != '\0')
		base_size++;
	i = ft_det_size_ullitobase(n, base_size);
	arr = malloc(sizeof(*arr) * (i + 1));
	if (!arr)
		return (0);
	arr[i] = 0;
	if (n == 0)
		arr[0] = base[0];
	while (n > 0)
	{
		arr[--i] = base[n % base_size];
		n /= base_size;
	}
	return (arr);
}

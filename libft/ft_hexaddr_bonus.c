/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_hexaddr_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elanna <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/12 22:25:13 by elanna            #+#    #+#             */
/*   Updated: 2021/06/22 15:13:35 by elanna           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
** Function which give the address in hexadecimal format of an item pointed
** by addr.
*/

#include "libft.h"

static int	ft_det_size_hexaddr(size_t a_value)
{
	int	size;

	if (a_value == 0)
		return (1);
	size = 0;
	while (a_value > 0)
	{
		size++;
		a_value /= 16;
	}
	return (size);
}

char	*ft_hexaddr(void *addr)
{
	char	*arr;
	char	*full_arr;
	int		i;
	char	*base;
	size_t	a_value;

	base = "0123456789abcdef";
	a_value = (size_t)addr;
	i = ft_det_size_hexaddr(a_value);
	arr = malloc(sizeof(*arr) * (i + 1));
	if (!arr)
		return (0);
	arr[i] = 0;
	if (a_value == 0)
		arr[0] = base[0];
	while (a_value > 0)
	{
		arr[--i] = base[a_value % 16];
		a_value /= 16;
	}
	full_arr = ft_strjoin("0x", arr);
	free(arr);
	return (full_arr);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anadege <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/05 23:07:28 by anadege           #+#    #+#             */
/*   Updated: 2021/05/20 14:04:50 by anadege          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	unsigned char	*str;
	unsigned char	ch;
	size_t			i;

	i = -1;
	str = (unsigned char *)s;
	ch = (unsigned char)c;
	while (++i < n)
	{
		if (str[i] == ch)
			return ((void *)(s + i));
	}
	return (0);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anadege <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/05 23:46:04 by anadege           #+#    #+#             */
/*   Updated: 2021/05/24 11:55:17 by anadege          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	ft_sub_memmove(void *dst, const void *src, size_t n)
{
	const char	*s_tmp;
	char		*d_tmp;

	s_tmp = (const char *)src;
	d_tmp = (char *)dst;
	s_tmp += n;
	d_tmp += n;
	while (n != 0)
	{
		*--d_tmp = *--s_tmp;
		n--;
	}
}

void	*ft_memmove(void *dst, const void *src, size_t n)
{
	const char	*s_tmp;
	char		*d_tmp;

	s_tmp = (const char *)src;
	d_tmp = (char *)dst;
	if (!n || (!dst && !src))
		return (dst);
	if (d_tmp <= s_tmp)
	{
		while (n != 0)
		{
			*d_tmp++ = *s_tmp++;
			n--;
		}
	}
	else
	{
		ft_sub_memmove(dst, src, n);
	}
	return (dst);
}

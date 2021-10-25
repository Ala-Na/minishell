/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anadege <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/06 17:37:52 by anadege           #+#    #+#             */
/*   Updated: 2021/05/24 11:54:08 by anadege          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	char		*d_tmp;
	const char	*s_tmp;

	d_tmp = dst;
	s_tmp = src;
	if (!dst && !src)
		return (NULL);
	while (n != 0)
	{
		*d_tmp = *s_tmp;
		d_tmp++;
		s_tmp++;
		n--;
	}
	return (dst);
}

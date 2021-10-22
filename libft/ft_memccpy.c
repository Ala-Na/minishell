/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memccpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anadege <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/06 22:37:45 by anadege           #+#    #+#             */
/*   Updated: 2021/03/16 22:59:12 by elanna           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memccpy(void *dst, const void *src, int c, size_t n)
{
	char			*d_tmp;
	const char		*s_tmp;
	char			ch;
	size_t			i;

	i = 0;
	ch = (char)c;
	d_tmp = (char *)dst;
	s_tmp = (const char *)src;
	while (i < n)
	{
		*d_tmp = s_tmp[i];
		d_tmp++;
		if (s_tmp[i] == ch)
			return (dst + i + 1);
		i++;
	}
	return (0);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anadege <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/05 15:18:39 by anadege           #+#    #+#             */
/*   Updated: 2021/05/20 14:44:47 by anadege          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t size)
{
	size_t	s_len;
	size_t	d_len;
	size_t	i;

	i = 0;
	s_len = 0;
	d_len = 0;
	while (src[s_len])
		s_len++;
	while (dst[d_len])
		d_len++;
	if (size == 0)
		return (s_len);
	if (size <= d_len)
		return (size + s_len);
	i = 0;
	while (src[i] && i < (size - d_len - 1))
	{
		dst[d_len + i] = src[i];
		i += 1;
	}
	dst[d_len + i] = 0;
	return (d_len + s_len);
}

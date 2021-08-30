/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anadege <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/05 15:48:37 by anadege           #+#    #+#             */
/*   Updated: 2021/05/24 12:04:46 by anadege          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcpy(char *dst, const char *src, size_t size)
{
	size_t	i;
	size_t	s_len;

	i = 0;
	s_len = 0;
	if (!src || !dst)
		return (0);
	while (src[s_len])
		s_len++;
	if (src == 0 || size == 0)
		return (s_len);
	while (src[i] && i < size - 1)
	{
		dst[i] = src[i];
		i += 1;
	}
	dst[i] = '\0';
	return (s_len);
}

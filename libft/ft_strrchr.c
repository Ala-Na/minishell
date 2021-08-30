/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anadege <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/05 18:51:22 by anadege           #+#    #+#             */
/*   Updated: 2021/05/20 14:47:22 by anadege          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	size_t	i;

	i = 0;
	while (s[i])
		i++;
	if (c == '\0' && s[i] == '\0')
		return ((char *)s + i);
	while (i-- > 0)
		if (s[i] == (char)c)
			return ((char *)s + i);
	return (0);
}

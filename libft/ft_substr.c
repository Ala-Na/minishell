/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anadege <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/07 15:59:44 by anadege           #+#    #+#             */
/*   Updated: 2021/05/20 14:58:10 by anadege          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	*ft_suballoc(unsigned int start, size_t len, size_t size)
{
	char	*str;

	if (start > size)
	{
		str = malloc(sizeof(*str) * (1));
		if (!str)
			return (NULL);
	}
	else
	{
		if (size - start > len)
			size = len;
		else
			size = size - start;
		str = malloc(sizeof(*str) * (size + 1));
		if (!str)
			return (NULL);
	}
	return (str);
}

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*str;
	size_t	size;
	size_t	i;

	size = 0;
	if (!s)
		return (NULL);
	while (s[size])
		size++;
	str = ft_suballoc(start, len, size);
	if (!str)
		return (str);
	if (start > size)
	{
		str[0] = 0;
		return (str);
	}
	i = 0;
	while (s[start] && i < len)
	{
		str[i++] = s[start++];
	}
	str[i] = 0;
	return (str);
}

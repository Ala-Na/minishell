/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnjoin.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlichir < hlichir@student.42.fr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/07 16:16:47 by anadege           #+#    #+#             */
/*   Updated: 2021/09/17 11:11:22 by hlichir          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnjoin(char const *s1, char const *s2, int length)
{
	size_t	i;
	size_t	size;
	char	*str;

	i = -1;
	size = 0;
	if (!s1 && !s2)
		return (NULL);
	while (s1 && s1[size])
		size++;
	while (s2 && s2[++i] && i < (size_t)length)
		size++;
	str = malloc(sizeof(*str) * (size + 1));
	if (!str)
		return (NULL);
	i = 0;
	while (s1 && *s1)
		str[i++] = *s1++;
	while (s2 && *s2 && i < (size + 1))
		str[i++] = *s2++;
	str[size] = 0;
	return (str);
}

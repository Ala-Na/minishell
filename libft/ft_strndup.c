/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strndup.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anadege <anadege@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/15 16:19:55 by anadege           #+#    #+#             */
/*   Updated: 2021/09/15 21:02:21 by anadege          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strndup(const char *s, const int size)
{
	char	*dest;
	int		i;

	i = 0;
	dest = malloc(sizeof(*dest) * (size + 1));
	if (!dest)
		return (0);
	while (s[i] != 0 && i < size)
	{
		dest[i] = s[i];
		i++;
	}
	while (i <= size)
		dest[i++] = 0;
	return (dest);
}

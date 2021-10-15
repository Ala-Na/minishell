/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup_free.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlichir < hlichir@student.42.fr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/05 11:56:16 by elanna            #+#    #+#             */
/*   Updated: 2021/10/15 15:59:09 by hlichir          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup_free(char **s, int to_free)
{
	int		size;
	char	*dest;
	int		i;

	i = 0;
	size = 0;
	while ((*s)[size])
		size++;
	dest = malloc(sizeof(*dest) * (size + 1));
	if (!dest)
		return (0);
	while ((*s)[i] != 0)
	{
		dest[i] = (*s)[i];
		i++;
	}
	dest[i] = 0;
	if (to_free)
	{
		free(*s);
		*s = NULL;
	}
	return (dest);
}

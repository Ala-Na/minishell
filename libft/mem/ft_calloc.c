/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anadege <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/07 00:01:34 by anadege           #+#    #+#             */
/*   Updated: 2021/05/20 21:27:59 by elanna           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t nmemb, size_t size)
{
	void			*ptr;
	unsigned char	*res;
	size_t			total;

	total = nmemb * size;
	if (!(total))
		total = 1;
	ptr = malloc(total);
	if (!ptr)
		return (NULL);
	res = (unsigned char *)ptr;
	while (total > 0)
	{
		*res++ = '\0';
		total--;
	}
	return (ptr);
}

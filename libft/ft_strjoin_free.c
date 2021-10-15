/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin_free.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlichir < hlichir@student.42.fr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/27 11:42:23 by hlichir           #+#    #+#             */
/*   Updated: 2021/10/15 15:59:29 by anadege          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	check_and_free(char **s1, char **s2, int free_s1, int free_s2)
{
	if (free_s1)
	{
		free(*s1);
		*s1 = NULL;
	}
	if (free_s2)
	{
		free(*s2);
		*s2 = NULL;
	}
}

char	*ft_strjoin_free(char **s1, char **s2, int free_s1, int free_s2)
{
	char	*dest;
	int		i;
	int		j;

	i = 0;
	j = 0;
	dest = malloc(sizeof(*dest) * (ft_strlen(*s1) + ft_strlen(*s2) + 1));
	if (!dest)
	{
		check_and_free(s1, s2, free_s1, free_s2);
		return (NULL);
	}
	while ((*s1)[j])
		dest[i++] = (*s1)[j++];
	j = 0;
	while ((*s2)[j])
		dest[i++] = (*s2)[j++];
	dest[i] = '\0';
	check_and_free(s1, s2, free_s1, free_s2);
	return (dest);
}

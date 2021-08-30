/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anadege <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/07 16:42:48 by anadege           #+#    #+#             */
/*   Updated: 2021/05/20 14:50:44 by anadege          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_inside_set(char const c, char const *set)
{
	size_t	i;

	i = 0;
	while (set[i])
	{
		if (set[i] == c)
			return (1);
		i++;
	}
	return (0);
}

static size_t	ft_det_size(char const *s1, char const *set)
{
	size_t	occ;
	size_t	size;
	size_t	i;

	occ = 0;
	i = 0;
	while (s1[i] && ft_inside_set(s1[i++], set))
		occ++;
	if (s1[i] == 0)
		return (0);
	while (s1[i])
		i++;
	size = i;
	i--;
	while (ft_inside_set(s1[i--], set))
		occ++;
	return (size - occ);
}

static char	*ft_stralloc(char const *s1, char const *set, size_t *size)
{
	char	*s2;

	if (s1 == NULL)
		return (NULL);
	else if (set == NULL)
	{
		while (s1[*size])
			*size += 1;
		s2 = malloc(sizeof(*s2) * (*size + 1));
		if (!s2)
			return (NULL);
		return (s2);
	}
	*size = ft_det_size(s1, set);
	s2 = malloc(sizeof(*s2) * (*size + 1));
	if (!s2)
		return (NULL);
	return (s2);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	char	*s2;
	size_t	i;
	size_t	j;
	size_t	size;

	size = 0;
	s2 = ft_stralloc(s1, set, &size);
	i = 0;
	j = 0;
	if (s2)
	{
		while (set && ft_inside_set(s1[i], set))
			i++;
		while (j < size)
		{
			s2[j++] = s1[i++];
		}
		s2[size] = 0;
	}
	return (s2);
}

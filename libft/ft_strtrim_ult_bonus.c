/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim_ult_bonus.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elanna <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/17 14:50:05 by elanna            #+#    #+#             */
/*   Updated: 2021/06/22 15:15:51 by elanna           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	ft_det_size(char const *s1, char const *set)
{
	size_t	occ;
	size_t	i;
	size_t	j;

	occ = 0;
	i = 0;
	while (s1[i])
	{
		j = 0;
		while (set[j])
		{
			if (set[j] == s1[i])
			{
				occ++;
				break ;
			}
			j++;
		}
		i++;
	}
	return (i - occ);
}

static char	*ft_stralloc(char const *s1, char const *set)
{
	size_t	size;
	char	*s2;

	size = 0;
	if (s1 == NULL)
		return (NULL);
	else if (set == NULL)
	{
		while (s1[size])
			size++;
		s2 = malloc(sizeof(*s2) * (size + 1));
		if (!s2)
			return (NULL);
		return (s2);
	}
	size = ft_det_size(s1, set);
	s2 = malloc(sizeof(*s2) * (size + 1));
	if (!s2)
		return (NULL);
	return (s2);
}

static void	ft_move_iterator(char const *s1, char const *set, size_t *i)
{
	size_t	j;

	j = 0;
	while (set && s1[*i] && set[j])
	{
		if (s1[*i] == set[j++])
		{
			j = 0;
			*i += 1;
		}
	}
}

char	*ft_strtrim_ult(char const *s1, char const *set)
{
	char	*s2;
	size_t	i;
	size_t	k;

	i = 0;
	k = 0;
	s2 = ft_stralloc(s1, set);
	if (s2)
	{
		while (s1[i])
		{
			ft_move_iterator(s1, set, &i);
			if (s1[i])
				s2[k++] = s1[i++];
		}
		s2[k] = 0;
	}
	return (s2);
}

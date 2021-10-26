/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anadege <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/08 12:01:20 by anadege           #+#    #+#             */
/*   Updated: 2021/05/26 10:42:20 by anadege          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	**ft_split_init(char const *s, char c)
{
	int		i;
	int		occ;
	char	**arr;
	int		i_max;

	i = 0;
	occ = 0;
	i_max = 0;
	while (s && s[i_max])
		i_max++;
	while (s && s[i])
	{
		if (i == 0 && s[i] != c)
			occ++;
		else if (i - 1 >= 0 && s[i - 1] == c && s[i] != c)
			occ++;
		else if (i_max != 0 && i == i_max && s[i_max] == c)
			occ++;
		i++;
	}
	arr = malloc(sizeof(*arr) * (occ + 1));
	if (!arr)
		return (NULL);
	arr[occ] = NULL;
	return (arr);
}

static char	*ft_split_dup(char const *s, char c, int *start)
{
	size_t	str_size;
	char	*str;

	*start = 0;
	str_size = 0;
	while (s[str_size] && s[str_size] != c)
		str_size++;
	str = malloc(sizeof(*str) * (str_size + 1));
	if (!str)
		return (0);
	str_size = 0;
	while (s[str_size] && s[str_size] != c)
	{
		str[str_size] = s[str_size];
		str_size++;
	}
	str[str_size] = 0;
	return (str);
}

static void	ft_split_init_values(size_t *i, size_t *size, int *start)
{
	*i = -1;
	*size = 0;
	*start = 0;
}

static void	ft_split_free_arr(char ***arr, size_t size)
{
	while (--size > 0)
		free(*(arr[size--]));
	free(*arr);
}

char	**ft_split(char const *s, char c)
{
	size_t	size;
	size_t	i;
	int		start;
	char	**arr;

	arr = ft_split_init(s, c);
	if (!arr)
		return (NULL);
	ft_split_init_values(&i, &size, &start);
	while (s && s[++i])
	{
		if (i == 0 || s[i - 1] == c)
			start = 1;
		if (s[i] != c && start == 1)
		{
			arr[size++] = ft_split_dup(s + i, c, &start);
			if (!arr[size - 1])
			{
				ft_split_free_arr(&arr, size);
				return (0);
			}
		}
	}
	return (arr);
}

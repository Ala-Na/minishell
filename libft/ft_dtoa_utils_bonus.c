/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dtoa_utils_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elanna <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/12 17:47:28 by elanna            #+#    #+#             */
/*   Updated: 2021/06/22 15:13:19 by elanna           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*del_front_zero(char *to_add, int approx_size)
{
	int		nbr_zero;
	int		i;
	int		y;
	char	*tmp;

	i = 0;
	y = 0;
	nbr_zero = 0;
	while (to_add[i] == '0')
	{
		nbr_zero++;
		i++;
	}
	if (nbr_zero == 0)
		return (to_add);
	tmp = malloc(sizeof(*tmp) * (approx_size - nbr_zero + 1));
	if (!tmp)
		return (NULL);
	while (to_add[i] != 0)
		tmp[y++] = to_add[i++];
	tmp[y] = 0;
	free(to_add);
	return (tmp);
}

char	*add_chars_to_mall_str(char *mall_str, const char *cst,
char front_or_end)
{
	char	*tmp;

	if (front_or_end == 'f')
		tmp = ft_strjoin(cst, mall_str);
	else
		tmp = ft_strjoin(mall_str, cst);
	free(mall_str);
	return (tmp);
}

void	stock_fill(char **stock_part, char *to_add, int s_part, int s_add)
{
	int	ret;

	ret = 0;
	while (s_part >= 0 && s_add >= 0)
	{
		(*stock_part)[s_part] += to_add[s_add--] - '0' + ret;
		ret = 0;
		if ((*stock_part)[s_part--] > '9')
		{
			(*stock_part)[s_part + 1] -= 10;
			ret = 1;
		}
	}
	while (ret != 0 && s_part >= 0)
	{
		(*stock_part)[s_part] += 1;
		ret = 0;
		if ((*stock_part)[s_part--] > '9' && s_part != 0)
		{
			(*stock_part)[s_part + 1] -= 10;
			ret = 1;
		}
	}
	if (ret != 0 && s_part == -1)
		*stock_part = add_chars_to_mall_str(*stock_part, "1", 'f');
}

char	*stock_init(char *stock_part, char *to_add, char int_or_frac)
{
	int	size_part;
	int	size_add;

	if (stock_part == NULL)
		return (to_add);
	else if (to_add == NULL)
		return (NULL);
	size_part = ft_strlen(stock_part) - 1;
	size_add = ft_strlen(to_add) - 1;
	while (size_part < size_add)
	{
		stock_part = add_chars_to_mall_str(stock_part, "0", int_or_frac);
		size_part++;
	}
	if (stock_part == NULL)
	{
		free(to_add);
		return (NULL);
	}
	stock_fill(&stock_part, to_add, size_part, size_add);
	free(to_add);
	return (stock_part);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dtoa_rounding_bonus.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elanna <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/12 17:16:32 by elanna            #+#    #+#             */
/*   Updated: 2021/06/22 15:12:20 by elanna           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	bankers_or_usual_rounding(char **number, char **frac_part,
		unsigned int i)
{
	int	y;

	y = 0;
	if ((*frac_part)[y] >= '5' && (*frac_part)[y] <= '9')
	{
		if ((*frac_part)[y + 1] == 0 && ((*number)[i - 1] % 2) == 0)
			return ;
		(*number)[--i] += 1;
		while ((*number)[i] > '9')
		{
			if (i != 0)
				(*number)[i] = '0';
			if (i > 0 && (*number)[--i] == '.')
				--i;
			if ((*number)[i] >= '9' && i == 0)
			{
				(*number)[i] = '0';
				*number = add_chars_to_mall_str(*number, "1", 'f');
			}
			else
				(*number)[i] += 1;
		}
	}
}

void	do_rounding(char **number, char *frac_part,
unsigned i, unsigned size)
{
	while (i < size)
	{
		if (*frac_part)
			(*number)[i++] = *frac_part++;
		else
			(*number)[i++] = '0';
	}
	bankers_or_usual_rounding(number, &frac_part, i);
}

char	*get_round_number(char *int_part, char *frac_part, int precision)
{
	char			*number;
	unsigned int	size;
	unsigned int	i;

	if (precision == 0)
		size = ft_strlen(int_part);
	else
		size = ft_strlen(int_part) + precision + 1;
	number = malloc(sizeof(*number) * (size + 1));
	if (!number)
		return (NULL);
	number[size] = 0;
	i = 0;
	while (i < size && *int_part)
	{
		number[i++] = *int_part++;
	}
	number[i] = 0;
	if (i < size - 1)
		number[i++] = '.';
	do_rounding(&number, frac_part, i, size);
	return (number);
}

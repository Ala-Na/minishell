/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dtoa_frac_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elanna <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/12 17:37:08 by elanna            #+#    #+#             */
/*   Updated: 2021/06/22 15:12:01 by elanna           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

unsigned long long	convert_mant_to_frac(unsigned long long mant, short exp,
unsigned int *i)
{
	*i = 1;
	if (exp > 0)
		return (mant << (exp + 1));
	else if (exp == 0)
		return (mant << 1);
	*i = (unsigned int)(-exp);
	return (mant);
}

char	*get_frac_part(unsigned long long mant,
short exp)
{
	unsigned long long	frac_part;
	char				*to_add;
	unsigned int		i;
	char				*stock_frac;

	stock_frac = NULL;
	frac_part = convert_mant_to_frac(mant, exp, &i);
	if (frac_part == 0 || exp > 63)
		return (ft_strdup("0"));
	while (frac_part != 0)
	{
		if (((frac_part >> 63) & 1) == 0)
		{
			frac_part = frac_part << 1;
			i++;
			continue ;
		}
		to_add = apply_dtwo_pten(i);
		frac_part = frac_part << 1;
		stock_frac = stock_init(stock_frac, to_add, 'e');
		i++;
	}
	return (stock_frac);
}

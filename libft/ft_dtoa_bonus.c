/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dtoa_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elanna <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/12 16:55:13 by elanna            #+#    #+#             */
/*   Updated: 2021/06/22 15:11:39 by elanna           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*get_big_int(unsigned long long int_part, short exp)
{
	char	*to_add;
	short	i;
	char	*stock_big_int;

	i = exp - 52;
	stock_big_int = NULL;
	to_add = NULL;
	while (int_part != 0)
	{
		if ((int_part & 1) == 0)
		{
			int_part = int_part >> 1;
			i++;
			continue ;
		}
		apply_ptwo_init(i, &to_add);
		int_part = int_part >> 1;
		stock_big_int = stock_init(stock_big_int, to_add, 'f');
		i++;
	}
	return (stock_big_int);
}

char	*get_int_part(unsigned long long mant, short exp)
{
	unsigned long long	int_part;

	int_part = 0;
	if (exp == 0)
		int_part = 1;
	else if (exp > 0 && exp <= 63)
	{
		int_part = mant >> (63 - exp);
		int_part = ft_bintodec(int_part, 0);
	}
	else if (exp > 63)
	{
		int_part = mant >> 11;
		return (get_big_int(int_part, exp));
	}
	return (ft_ullitoa(int_part));
}

char	*get_dtoa_number(unsigned long long mant, short exp, int precision,
int show_exp)
{
	char	*number;
	char	*int_part;
	char	*frac_part;

	if (exp == -1023)
	{
		mant = mant << 12;
		int_part = ft_strdup("0");
	}
	else
	{
		mant = mant << 11;
		mant = mant | 0x8000000000000000;
		int_part = get_int_part(mant, exp);
	}
	frac_part = get_frac_part(mant, exp);
	if (show_exp == 0)
		number = get_round_number(int_part, frac_part, precision);
	else
		number = get_round_exp_number(int_part, frac_part, precision);
	free(int_part);
	free(frac_part);
	return (number);
}

char	*ft_dtoa(double dbl, int precision, int show_exp)
{
	short				sign;
	short				exp;
	unsigned long long	mant;
	t_dbl_union			dbl_rep;
	char				*number;

	dbl_rep.d = dbl;
	sign = dbl_rep.l >> 63;
	exp = ((dbl_rep.l << 1) >> 53) - 1023;
	mant = ((dbl_rep.l << 12) >> 12);
	if (exp == 1024 && mant == 0)
		number = ft_strdup("inf");
	else if (exp == 1024 && mant != 0)
		number = ft_strdup("nan");
	else
		number = get_dtoa_number(mant, exp, precision, show_exp);
	if (sign == 1)
		number = add_chars_to_mall_str(number, "-", 'f');
	return (number);
}

/*
**Briefs tests for dtoa 'f' format
**void	test(double dbl)
**{
**	char *str;
**	printf("printf : %.1000f\n", dbl);
**	str = ft_dtoa(dbl, 1000);
**	printf("mine   : %s\n", str);
**	free(str);
**	str = ft_dtoa(dbl, 6);
**	printf("mine   : %s\n", str);
**	free(str);
**	printf("printf : %f\n", dbl);
**	printf("printf : %.1f\n", dbl);
**	str = ft_dtoa(dbl, 1);
**	printf("mine   : %s\n", str);
**	free(str);
**	printf("\n");
**}
**
**int main()
**{
**	double nbr;
**	nbr = 0.0000000000000000000000000000000000000000000000000000000000001;
**	test(nbr);
**	test(19.99);
**	test(99.999);
**	test(0.25);
**	test(-0.25);
**	test(-42);
**	test(INFINITY);
**	test (-INFINITY);
**	test(NAN);
**	test(-NAN);
**	test(222222222222222222222022222222222222.20);
**	test(2);
**	test(0);
**	test(1);
**}
*/

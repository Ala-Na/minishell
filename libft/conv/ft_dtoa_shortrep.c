/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dtoa_shortrep_bonus.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elanna <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/12 16:09:43 by elanna            #+#    #+#             */
/*   Updated: 2021/06/22 15:12:54 by elanna           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*check_exp_for_format(int exp, char *int_part, char *frac_part,
int precision)
{
	char	*number;
	int		int_size;
	int		exp_cpy;

	int_size = ft_strlen(int_part);
	if (exp >= 0 && int_part[0] != '0')
		number = ft_strjoin(int_part, frac_part);
	else
		number = ft_strdup(frac_part);
	exp_cpy = exp_after_rounding(&number, exp, precision, int_size);
	if (exp_cpy < -4 || exp_cpy >= precision)
	{
		adjust_number(&number);
		do_exp_rounding(&number, &exp, precision - 1);
		number = add_exp(exp, number, 1);
	}
	else
	{
		adjust_precision(int_part, frac_part, &precision);
		free(number);
		number = get_round_number(int_part, frac_part, precision - int_size);
		if (ft_strchr(number, '.'))
			del_last_zero(&number, ft_strlen(number));
	}
	return (number);
}

char	*get_number_shortest_rep(char *int_part, char *frac_part, int precision)
{
	int		exp;
	char	*number;
	size_t	i;

	exp = 0;
	i = 0;
	if (int_part[0] != '0')
		exp = ft_strlen(int_part) - 1;
	else
	{
		while (i < ft_strlen(frac_part) && frac_part[i++] == '0')
		{
			exp--;
		}
		if (frac_part[i] != 0)
			exp--;
		else
			exp = 0;
	}
	number = check_exp_for_format(exp, int_part, frac_part, precision);
	return (number);
}

char	*get_dtoa_shortest_rep(unsigned long long mant, short exp,
int precision)
{
	char	*number;
	char	*int_part;
	char	*frac_part;

	if (precision == 0)
		precision = 1;
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
	number = get_number_shortest_rep(int_part, frac_part, precision);
	free(int_part);
	free(frac_part);
	return (number);
}

char	*ft_dtoa_shortest_rep(double dbl, int precision)
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
		number = get_dtoa_shortest_rep(mant, exp, precision);
	if (sign == 1)
		number = add_chars_to_mall_str(number, "-", 'f');
	return (number);
}

/*
**Briefs tests of 'f' 'e' 'g' formats
**void	test(double nbr)
**{
**	int precision = 11;
**	char *str_g = ft_dtoa_shortest_rep(nbr, precision);
**	char *str_f = ft_dtoa(nbr, precision, 0);
**	char *str_e = ft_dtoa(nbr, precision, 1);
**	printf("F : %s\nR : %.*f\n", str_f, precision, nbr);
**	printf("E : %s\nR : %.*e\n", str_e, precision, nbr);
**	printf("G : %s\nR : %.*g\n\n", str_g, precision, nbr);
**	free(str_g);
**	free(str_f);
**	free(str_e);
**}
**
**int main()
**{
**	test(999994.94);
**	test(100000.0);
**	double nbr;
**	nbr = 0.0000000000000000000000000000000000000000000000001;
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
**	test(0.0000000000000086);
**	test(0.000000000000000000000000000000000000000000000000000004);
**	test(2.54);
**	test(2.49);
**	test(0.0);
**	test(154.987456622358632);
**	test(425896315587899);
**	test(22222222228963214522222222222222222222.20);
**	test(100000000000);
**	test(0.56);
**	test(0.056);
**	test(0.5);
**}
*/

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dtoa_exp_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elanna <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/29 21:54:56 by elanna            #+#    #+#             */
/*   Updated: 2021/06/22 15:11:48 by elanna           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*add_exp(int exp, char *number, int shortest_rep)
{
	char	*str_exp;
	char	intro_exp[3];
	int		i;

	if (shortest_rep)
		del_last_zero(&number, ft_strlen(number));
	i = 0;
	intro_exp[i++] = 'e';
	if (exp >= 0)
		intro_exp[i++] = '+';
	else
	{
		intro_exp[i++] = '-';
		exp = -exp;
	}
	if (exp < 10)
		intro_exp[i++] = '0';
	intro_exp[i] = 0;
	str_exp = add_chars_to_mall_str(ft_itoa(exp), intro_exp, 'f');
	number = add_chars_to_mall_str(number, str_exp, 'e');
	free(str_exp);
	return (number);
}

void	fill_round_exp_number(char **number, int size,
int limit_size)
{
	int		i;
	int		y;
	char	*round_number;

	i = 0;
	y = 0;
	round_number = malloc(sizeof(*round_number) * (size + 1));
	if (!round_number)
	{
		free(*number);
		*number = NULL;
		return ;
	}
	round_number[i] = '0';
	if ((*number)[0] != 0)
		round_number[i] = (*number)[y++];
	if (size > 1)
		round_number[++i] = '.';
	while (++i < limit_size)
		round_number[i] = (*number)[y++];
	while (i < size)
		round_number[i++] = '0';
	round_number[size] = 0;
	free(*number);
	*number = round_number;
}

void	exp_rounding_operation(char **number, int *exp, int i)
{
	if ((*number)[i] >= '5' && (*number)[i] <= '9')
	{
		if ((*number)[i + 1] == 0 && (i > 0 && ((*number)[i - 1] % 2) == 0))
			return ;
		(*number)[--i] += 1;
		while (i >= 0 && (*number)[i] > '9')
		{
			if (i > 0)
			{
				(*number)[i--] = '0';
				(*number)[i] += 1;
			}
			else if (i == 0)
			{
				(*number)[i] = '0';
				*number = add_chars_to_mall_str(*number, "1", 'f');
				*exp += 1;
				break ;
			}
		}
	}
}

void	do_exp_rounding(char **number, int *exp, int precision)
{
	int	i;
	int	size;
	int	num_size;
	int	limit_size;

	size = precision + 1;
	i = size;
	if (precision != 0)
		size += 1;
	num_size = ft_strlen(*number) + 1;
	if (i > 0 && i < num_size)
	{
		exp_rounding_operation(number, exp, i);
	}
	limit_size = size;
	if (num_size < size)
		limit_size = num_size;
	fill_round_exp_number(number, size, limit_size);
}

char	*get_round_exp_number(char *int_part, char *frac_part, int precision)
{
	int		exp;
	char	*number;

	exp = 0;
	if (int_part[0] != '0')
	{
		exp = ft_strlen(int_part) - 1;
		number = ft_strjoin(int_part, frac_part);
	}
	else
	{
		while (*frac_part == '0')
		{
			exp--;
			frac_part++;
		}
		if (*frac_part != 0)
			exp--;
		else
			exp = 0;
		number = ft_strdup(frac_part);
	}
	do_exp_rounding(&number, &exp, precision);
	number = add_exp(exp, number, 0);
	return (number);
}

/*
**Briefs tests for 'e' format
**
**void test(double nbr)
**{
**	printf("dbl e : %.0e\n", nbr);
**	char *str = ft_dtoa_with_exp(nbr, 0, 1);
**	printf("mine :  %s\n\n", str);
**	free(str);
**	printf("dbl e : %.1e\n", nbr);
**	str = ft_dtoa_with_exp(nbr, 1, 1);
**	printf("mine :  %s\n\n", str);
**	free(str);
**	printf("dbl e : %.3e\n", nbr);
**	str = ft_dtoa_with_exp(nbr, 3, 1);
**	printf("mine :  %s\n\n", str);
**	free(str);
**	printf("dbl e : %.12e\n", nbr);
**	str = ft_dtoa_with_exp(nbr, 12, 1);
**	printf("mine :  %s\n\n", str);
**	free(str);
**
**}
**
**int	main()
**{
**	test(999.99999);
**	test(-INFINITY);
**	test(NAN);
**	test(0.0000000000000086);
**	test(0.000000000000000000000000000000000000000000000000000000000000004);
**	test(2.54);
**	test(2.49);
**	test(0.0);
**	test(154.987456622358632);
**	test(425896315587899);
**	test(22222222228963214522222222222222222222.20);
**}
*/

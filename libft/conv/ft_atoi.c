/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anadege <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/05 17:44:35 by anadege           #+#    #+#             */
/*   Updated: 2021/05/24 12:32:17 by anadege          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	return_value(long int res, long int sign)
{
	if (res < 0 && sign > 0)
		return (-1);
	else if (res < 0 && sign < 0)
		return (0);
	res *= sign;
	return ((int)res);
}

int	ft_atoi(const char *nptr)
{
	unsigned int	nbr;
	long int		res;
	long int		sign;

	nbr = 0;
	res = 0;
	sign = 1;
	while (*nptr == 32 || (*nptr >= 9 && *nptr <= 13))
		nptr++;
	if (*nptr == '-' || *nptr == '+')
	{
		if (*nptr == '-')
			sign = -1;
		nptr++;
	}
	while (*nptr >= '0' && *nptr <= '9')
	{
		nbr = *nptr - '0';
		res = res * 10 + nbr;
		nptr++;
	}
	return ((int)return_value(res, sign));
}

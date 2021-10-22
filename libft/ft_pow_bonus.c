/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pow_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elanna <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/12 22:29:32 by elanna            #+#    #+#             */
/*   Updated: 2021/06/22 15:14:30 by elanna           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
** Function which give the power of two numbers
** Careful : The result may be wrong if it's more than the
** unsigned long long maximal number.
*/

#include "libft.h"

unsigned long long	ft_pow(unsigned long long nb, int power)
{
	if (power == 0)
		return (1);
	else if (power > 1)
		return ((unsigned long long)nb * ft_pow(nb, power - 1));
	else if (power == 1)
		return ((unsigned long long)nb);
	return (0);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bintodec_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elanna <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/12 22:12:11 by elanna            #+#    #+#             */
/*   Updated: 2021/06/22 15:10:42 by elanna           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
** Function to turn an unsigned long long binary to decimal number.
** Start represent the first power of two which is applied.
** This function is used in ft_dtoa.
*/

#include "libft.h"

unsigned long long	ft_bintodec(unsigned long long bin, int start)
{
	unsigned long long	dec;
	int					i;
	int					rest;

	dec = 0;
	i = start;
	while (bin != 0)
	{
		rest = bin & 1;
		bin = bin >> 1;
		dec += (rest * ft_pow(2, i));
		i++;
	}
	return (dec);
}

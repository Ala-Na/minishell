/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_bin_rep_bonus.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elanna <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/12 22:13:58 by elanna            #+#    #+#             */
/*   Updated: 2021/06/22 15:14:43 by elanna           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
** Function printing the binary representation of any item
** Bits are grouped in bytes.
** Call function as :
** ft_print_bin_rep(sizeof(item), &item);
*/

#include "libft.h"

void	ft_print_bin_rep(size_t const size, void const *ptr)
{
	unsigned char	*byte;
	unsigned char	bit;
	int				i;
	int				j;

	byte = (unsigned char *)ptr;
	i = size - 1;
	while (i >= 0)
	{
		j = 7;
		while (j >= 0)
		{
			bit = (byte[i] >> j) & 1;
			ft_putnbr_fd(bit, 1);
			j--;
		}
		ft_putchar_fd(' ', 1);
		i--;
	}
	ft_putchar_fd(' ', 1);
}

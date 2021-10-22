/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anadege <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/08 21:29:38 by anadege           #+#    #+#             */
/*   Updated: 2021/03/16 17:52:24 by anadege          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putnbr_fd(int n, int fd)
{
	char			c;
	unsigned int	nb;

	if (n < 0)
	{
		c = '-';
		write(fd, &c, 1);
		nb = -n;
	}
	else
		nb = n;
	if (nb / 10 > 0)
		ft_putnbr_fd(nb / 10, fd);
	c = '0' + (nb % 10);
	write(fd, &c, 1);
}

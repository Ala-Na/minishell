/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putlenwstr_fd.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elanna <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/27 22:55:31 by elanna            #+#    #+#             */
/*   Updated: 2021/06/22 15:15:23 by elanna           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_putlenwstr_fd(wchar_t *w_str, int fd, size_t len)
{
	mbstate_t	ps;
	size_t		nbr_bytes;
	int			res;
	char		to_print;

	nbr_bytes = 0;
	res = 0;
	to_print = 0;
	ft_memset(&ps, 0, sizeof(ps));
	while (w_str && (int)nbr_bytes != -1 && (size_t)res < len)
	{
		nbr_bytes = ft_wcrtomb(&to_print, *w_str++, &ps);
		write(fd, &to_print, nbr_bytes);
		res++;
	}
	if ((int)nbr_bytes == -1)
		return (-1);
	return (res);
}

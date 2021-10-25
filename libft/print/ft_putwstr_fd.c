/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putwstr_fd_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elanna <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/27 21:48:05 by elanna            #+#    #+#             */
/*   Updated: 2021/06/22 15:15:37 by elanna           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_putwstr_fd(wchar_t *w_str, int fd)
{
	mbstate_t	ps;
	size_t		nbr_bytes;
	char		to_print[MB_CUR_MAX + 1];
	int			result;

	nbr_bytes = 0;
	to_print[0] = 0;
	ft_memset(&ps, 0, sizeof(ps));
	result = 0;
	while (w_str && *w_str)
	{
		nbr_bytes = ft_wcrtomb(&to_print[0], *w_str++, &ps);
		if (nbr_bytes == 0)
			return (-1);
		result += nbr_bytes;
		write(fd, &to_print, nbr_bytes);
	}
	return (result);
}

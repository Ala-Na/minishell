/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_wcrtomb_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elanna <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/27 20:45:14 by elanna            #+#    #+#             */
/*   Updated: 2021/06/22 15:16:53 by elanna           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_wcrtomb(char *s, wchar_t wc, mbstate_t *ps)
{
	int	i;

	i = 0;
	(void)ps;
	if (!s)
		return (1);
	if (s && (unsigned)wc < 0x80)
		s[i++] = wc;
	else if (s && (unsigned)wc < 0x800)
		s[i++] = ((wc >> 6) & 0x1f) | 0xc0;
	else if (s && (unsigned)wc < 0x10000)
		s[i++] = ((wc >> 12) & 0x0f) | 0xe0;
	else if (s && (unsigned)wc < 0x110000)
		s[i++] = ((wc >> 18) & 0x07) | 0xf0;
	else if (s)
		return (0);
	if (s && (unsigned)wc >= 0x10000)
		s[i++] = ((wc >> 12) & 0x3f) | 0x80;
	if (s && (unsigned)wc >= 0x800)
		s[i++] = ((wc >> 6) & 0x3f) | 0x80;
	if (s && (unsigned)wc >= 0x80)
		s[i++] = (wc & 0x3f) | 0x80;
	return (i);
}

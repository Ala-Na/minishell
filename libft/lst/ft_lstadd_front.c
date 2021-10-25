/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_front.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anadege <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/09 10:48:46 by anadege           #+#    #+#             */
/*   Updated: 2021/03/09 12:23:49 by anadege          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstadd_front(t_list **alst, t_list *new)
{
	if (new == NULL)
		return ;
	else if (*alst == NULL)
	{
		*alst = new;
		return ;
	}
	else
	{
		new->next = *alst;
		*alst = new;
	}
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anadege <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/09 14:20:30 by anadege           #+#    #+#             */
/*   Updated: 2021/05/20 13:57:16 by anadege          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstclear(t_list **lst, void (*del)(void *))
{
	t_list	*elem;
	t_list	*temp;

	elem = *lst;
	while (elem)
	{
		del(elem->content);
		temp = elem;
		elem = elem->next;
		free(temp);
	}
	*lst = NULL;
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dtoa_shortrep_utils_bonus.c                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elanna <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/04 17:36:49 by elanna            #+#    #+#             */
/*   Updated: 2021/06/22 15:13:05 by elanna           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	del_last_zero(char **number, int size)
{
	int		nbr_zero;
	int		i;
	char	*tmp;

	i = size - 1;
	nbr_zero = 0;
	while (i > 0 && (*number)[i] == '0')
	{
		nbr_zero++;
		i--;
	}
	if (i > 0 && (*number)[i] == '.')
		nbr_zero++;
	if (nbr_zero <= 0)
		return ;
	tmp = malloc(sizeof(*tmp) * (size - nbr_zero + 1));
	if (!tmp)
		return ;
	i = -1;
	while (++i < (size - nbr_zero))
		tmp[i] = (*number)[i];
	tmp[i] = 0;
	free(*number);
	*number = tmp;
}

static int	get_index_for_rounding_start(int precision, int int_size)
{
	if (int_size < precision)
		return (precision + 1 - int_size);
	else if (int_size == precision)
		return (precision);
	else
		return (precision + 1);
}

int	exp_after_rounding(char **number, int exp, int precision, int int_size)
{
	int	i;
	int	num_size;

	i = get_index_for_rounding_start(precision, int_size);
	num_size = ft_strlen(*number);
	if (i > 0 && i <= num_size)
	{
		if ((*number)[i] >= '5' && (*number)[i--] <= '9')
		{
			while (i >= 0 && (*number)[i] == '9')
			{
				if (i > 0)
					i--;
				else if (i == 0)
				{
					exp += 1;
					break ;
				}
			}
		}
	}
	return (exp);
}

void	adjust_precision(char *int_part, char *frac_part, int *precision)
{
	int	i;

	i = 0;
	if (int_part[0] == '0')
	{
		*precision += 1;
		while (frac_part[i++] == '0')
			*precision += 1;
	}
}

void	adjust_number(char **number)
{
	int		i;
	int		y;
	char	*tmp;

	i = 0;
	y = 0;
	while ((*number)[i] == '0')
		i++;
	tmp = malloc(sizeof(*tmp) * (ft_strlen(*number) - i + 1));
	if (!tmp)
		return ;
	while ((*number)[i] != 0)
		tmp[y++] = (*number)[i++];
	tmp[y] = 0;
	free(*number);
	*number = tmp;
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anadege <anadege@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/03 14:49:33 by anadege           #+#    #+#             */
/*   Updated: 2021/09/03 16:20:01 by anadege          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_tokentype	identify_token_type(char *token)
{
	if (!ft_strncmp(token, "|", 2))
		return (OPERATOR);
	else if ()
}

t_cmd	parse_curr_cmd(char *curr_cmd)
{
	t_cmd	cmd;
	char	*splited_cmd;

	return (cmd);
}

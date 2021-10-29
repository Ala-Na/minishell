/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_builtin.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlichir <hlichir@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/18 10:48:26 by anadege           #+#    #+#             */
/*   Updated: 2021/10/29 13:52:59 by hlichir          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	print_non_numeric_error(char **str_value)
{
	char	*error_msg;

	if (!str_value)
		return (return_error(1, "something went wrong", 0, -1));
	error_msg = "exit : ";
	*str_value = ft_strjoin_free(&error_msg, str_value, 0, 1);
	if (!str_value)
		return (return_error(1, "memory allocation error", 0, -1));
	error_msg = " : numeric argument required";
	*str_value = ft_strjoin_free(str_value, &error_msg, 1, 0);
	if (!str_value)
		return (return_error(1, "memory allocation error", 0, -1));
	return (return_error(255, 0, str_value, 255));
}

int	get_exit_value(t_token *token_value)
{
	int		i;
	char	*str_value;
	int		int_value;

	if (!token_value)
		return (return_error(1, "something went wrong", 0, -1));
	str_value = ft_strdup_linked_string(token_value);
	if (!str_value)
		return (-1);
	i = 0;
	while (str_value[i])
	{
		if (i == 0 && (str_value[i] == '-' || str_value[i] == '+'))
			i++;
		else if (!ft_isdigit(str_value[i]))
			return (print_non_numeric_error(&str_value));
		else
			i++;
	}
	int_value = ft_atoi(str_value);
	free(str_value);
	return (int_value);
}

int	exit_builtin(t_infos *infos, t_cmd *cmd, t_token *token)
{
	t_token	*curr;
	t_token	*next;
	int		value;

	if (!infos || !cmd)
		return (return_error(1, "something went wrong", 0, -1));
	ft_putstr("exit\n");
	curr = get_next_token(infos, cmd, &cmd, token);
	if (!curr && g_exit_status != 0)
		return (-1);
	next = get_next_token(infos, cmd, &cmd, curr);
	if (!curr)
		value = 0;
	else
		value = get_exit_value(curr);
	if (value != 255 && value != -1 && next)
		return (return_error(1, "exit : too many arguments", 0, -1));
	if (value == -1)
		return (-1);
	clean_exit(infos, 0);
	exit(value);
	return (return_error(1, "something went wrong", 0, -1));
}

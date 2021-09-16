/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlichir <hlichir@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/07 12:14:01 by hlichir           #+#    #+#             */
/*   Updated: 2021/09/15 15:56:14 by anadege          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

/*
** Functions to call when the built in echo is correctly called (4 letters = echo
** followed by a whitespace or '\0') in the string *str.
** WARNING : echo print a whitespace when a tab is meeted
** (generalized to blanks ?) by default.
*/

/*
** Function to check if option -n is activated (followed by whitespace or '\0')
** to modify the value of the argument *option which is a pointer to an int.
** Returns the position of the first character to display in the string *str.
*/
int	check_n_option(t_token *first)
{
	int	i;

	i = 1;
	if (!first || first->token[0] != '-')
		return (0);
	while (i < first->length)
	{
		if (first->token[i] != 'n')
			return (0);
		i++;
	}
	return (1);
}

/*
** Function which is launched when the command contains the built in ECHO.
** - Check if option -n is activated or not
** - Display the rest of the string str (without echo and option) while 
**   checking whitespaces.
** This function return an int 0 but could return a void.
*/
int	echo_builtin(t_cmd *cmd)
{
	int		option;
	int		i;
	t_token	*to_print;

	to_print = cmd->start;
	option = check_n_option(to_print);
	if (option)
		to_print = to_print->next;
	while (to_print)
	{
		i = 0;
		if (to_print->type == STRING && ++i)
			to_print->length -= 2;
		write(1, &to_print->token[i], to_print->length);
		if (to_print == cmd->end)
			break ;
		to_print = to_print->next;
		if (to_print)
			write(1, " ", 1);
	}
	if (option == 0)
		write(1, "\n", 1);
	return (0);
}

int	cmd_echo(t_infos *infos, t_cmd *cmd)
{
	int		str_size;
	char	*str_begin;

	if (!infos || !cmd
		|| ft_strncmp(cmd->start->token, "echo", cmd->start->length))
		return (-1);
	cmd->start = cmd->start->next;
	return (echo_builtin(cmd));
}

/* Main to test echo built in
int	main(void)
{
	char *str = "echo -n					la deh					oehie 		,oej,de";
	
	echo_builtin(str, ft_strlen(str));
	return (0);
}*/

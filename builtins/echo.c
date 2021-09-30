/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlichir <hlichir@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/07 12:14:01 by hlichir           #+#    #+#             */
/*   Updated: 2021/09/30 23:12:04 by hlichir          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

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
	while (i < first->length && first->token[i] == 'n')
		i++;
	if (i != first->length)
		return (0);
	return (1);
}

/*
** Split the echo_builtin in two -> tmp loop
*/
int	echo_builtin_loop(t_infos *infos, t_cmd *cmd, t_token *tmp, int i)
{
	char	*new;

	while (tmp)
	{
		if (tmp->type == STRING && ++i)
			tmp->length -= 2;
		write(1, &tmp->token[i], tmp->length);
		if (tmp == cmd->end)
			break ;
		tmp = tmp->next;
		if (tmp)
			write(1, " ", 1);
	}
	return (0);
}

void	skip_n_option(t_token **tmp)
{
	int	i;

	*tmp = (*tmp)->next;
	i = 1;
	while (*tmp)
	{
		if (!(*tmp) || (*tmp)->token[0] != '-')
			break ;
		while (i < (*tmp)->length && (*tmp)->token[i] == 'n')
			i++;
		if (i != (*tmp)->length)
			break ;
		*tmp = (*tmp)->next;
	}
}

/*
** Function which is launched when the command contains the built in ECHO.
** - Check if option -n is activated or not
** - Display the rest of the string str (without echo and option) while 
**   checking whitespaces.
** This function return an int 0 but could return a void.
*/
int	echo_builtin(t_infos *infos, t_cmd *cmd)
{
	int		n_option;
	int		i;
	t_token	*tmp;
	char	*new;

	i = 0;
	tmp = cmd->start;
	n_option = check_n_option(tmp);
	if (n_option)
		skip_n_option(&tmp);
	if (echo_builtin_loop(infos, cmd, tmp, i) < 0)
		return (-1);
	if (n_option == 0)
		write(1, "\n", 1);
	return (0);
}

/*
** Functions to call when the built in echo is correctly called (4 letters = echo
** followed by a whitespace or '\0') in the string *str.
** WARNING : echo print a whitespace when a tab is meeted
** (generalized to blanks ?) by default.
*/
int	cmd_echo(t_infos *infos, t_cmd *cmd)
{
	int		str_size;
	char	*str_begin;

	if (!infos || !cmd || !cmd->start
		|| ft_strncmp(cmd->start->token, "echo", cmd->start->length))
		return (return_error(1, "something went wrong", 0, -1));
	cmd->start = cmd->start->next;
	return (echo_builtin(infos, cmd));
}

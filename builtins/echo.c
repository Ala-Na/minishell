/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlichir < hlichir@student.42.fr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/07 12:14:01 by hlichir           #+#    #+#             */
/*   Updated: 2021/10/11 16:13:02 by anadege          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	return_n_option(char **str, int return_value)
{
	if (!str || !*str)
		return (return_error(1, "something went wrong", 0, -1));
	free(*str);
	return (return_value);
}

/*
** Function to check if option -n is activated (followed by whitespace or '\0')
** to modify the value of the argument *option which is a pointer to an int.
** Returns the position of the first character to display in the string *str.
*/
int	check_n_option(t_token *first)
{
	int		i;
	char	*str;

	i = 2;
	if (!first)
		return (0);
	str = ft_strdup_linked_string(first);
	if (!str)
		return (-1);
	if (str[0] != '-' || (str[1] && str[1] != 'n'))
		return (return_n_option(&str, 0));
	if (str[0] == '-' && (!str[1] || (str[1] && str[1] != 'n')))
		return (return_n_option(&str, 0));
	while (str[i] && str[i] == 'n')
		i++;
	if (!str[i])
		return (return_n_option(&str, 1));
	return (return_n_option(&str, 0));
}

/*
** Split the echo_builtin in two -> tmp loop
*/
int	echo_builtin_loop(t_infos *infos, t_cmd *head_cmd, t_cmd *cmd, t_token *tmp)
{
	char	*str;

	while (tmp)
	{
		str = ft_strdup_linked_string(tmp);
		if (!str)
			return (-1);
		write(head_cmd->fd_output, str, ft_strlen(str));
		tmp = get_next_token(infos, head_cmd, &cmd, tmp);
		if (tmp)
			write(head_cmd->fd_output, " ", 1);
		free(str);
	}
	return (0);
}

void	skip_n_option(t_infos *infos, t_cmd **cmd, t_token **tmp)
{
	char	*str;
	int		i;

	while (*tmp)
	{
		i = 1;
		if ((*tmp)->token[0] != '-' || ((*tmp)->token[1] \
			&& ft_strchr(" \t\n", (*tmp)->token[1])) \
			|| !(*tmp)->token[1])
			break ;
		str = ft_strdup_linked_string(*tmp);
		if (!str)
			return ;
		while (str[i] && str[i] == 'n')
			i++;
		if (str[i])
		{
			free(str);
			break ;
		}
		free(str);
		*tmp = get_next_token(infos, *cmd, cmd, *tmp);
	}
}

/*
** Function which is launched when the command contains the built in ECHO.
** - Check if option -n is activated or not
** - Display the rest of the string str (without echo and option) while 
**   checking whitespaces.
** This function return an int 0 but could return a void.
** Functions to call when the built in echo is correctly called (4 letters = echo
** followed by a whitespace or '\0') in the string *str.
*/
int	cmd_echo(t_infos *infos, t_cmd *head_cmd, t_cmd *builtin_cmd,
		t_token *builtin_token)
{
	int		n_option;
	t_token	*tmp;
	t_cmd	*moving_cmd;

	if (!infos || !head_cmd || !builtin_cmd || !builtin_token)
		return (return_error(1, "something went wrong", 0, -1));
	moving_cmd = builtin_cmd;
	tmp = get_next_token(infos, builtin_cmd, &moving_cmd, builtin_token);
	n_option = check_n_option(tmp);
	if (n_option)
		skip_n_option(infos, &moving_cmd, &tmp);
	if (echo_builtin_loop(infos, head_cmd, moving_cmd, tmp) < 0)
		return (-1);
	if (n_option == 0)
		write(head_cmd->fd_output, "\n", 1);
	return (0);
}

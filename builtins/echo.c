/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlichir < hlichir@student.42.fr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/07 12:14:01 by hlichir           #+#    #+#             */
/*   Updated: 2021/09/17 11:28:04 by hlichir          ###   ########.fr       */
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
** Split the echo_builtin in two -> tmp loop
*/
int	echo_builtin_loop(t_infos *infos, t_cmd *cmd, t_token *tmp, int i)
{
	while (tmp)
	{
		if (tmp->type == STRING && ++i)
			tmp->length -= 2;
		cmd->output = ft_strnjoin(cmd->output, &tmp->token[i], tmp->length);
		if (!cmd->output)
			return (error_exit_status("Malloc error", infos, "?=1"));
		if (tmp == cmd->end)
			break ;
		tmp = tmp->next;
		if (tmp)
		{
			cmd->output = ft_strjoin(cmd->output, " ");
			if (!cmd->output)
				return (error_exit_status("Malloc error", infos, "?=1"));
		}
	}
	return (0);
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
	int		option;
	int		i;
	t_token	*tmp;

	i = 0;
	tmp = cmd->start;
	option = check_n_option(tmp);
	if (option)
		tmp = tmp->next;
	cmd->output = ft_strdup("");
	if (echo_builtin_loop(infos, cmd, tmp, i) < 0)
		return (-1);
	if (option == 0)
		cmd->output = ft_strjoin(cmd->output, "\n");
	if (modify_var_in_list(infos, "?=0", NULL) < 0)
		return (error_exit_status("Memory allocation error", infos, "?=1"));
	printf("%s", cmd->output);
	return (0);
}

int	cmd_echo(t_infos *infos, t_cmd *cmd)
{
	int		str_size;
	char	*str_begin;

	if (!infos || !cmd
		|| ft_strncmp(cmd->start->token, "echo", cmd->start->length))
		return (error_exit_status("Error!", infos, "?=1"));
	cmd->start = cmd->start->next;
	return (echo_builtin(infos, cmd));
}

/* Main to test echo built in
int	main(void)
{
	char *str = "echo -n					la deh					oehie 		,oej,de";
	
	echo_builtin(str, ft_strlen(str));
	return (0);
}*/

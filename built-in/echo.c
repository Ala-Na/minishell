/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlichir <hlichir@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/07 12:14:01 by hlichir           #+#    #+#             */
/*   Updated: 2021/09/12 16:42:30 by anadege          ###   ########.fr       */
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
int	check_n_option(char *str, int str_length, int *option)
{
	int	i;

	i = 4;
	if (str_length <= i)
		return (4);
	while (str[i] && ft_iswhitespace(str[i]))
		i++;
	if (str_length < i + 2)
		return (i);
	if (str[i] && str[i] == '-' && str[i + 1] && str[i + 1] == 'n')
	{
		if (str[i + 2] == '\0' || ft_iswhitespace(str[i + 2]))
		{
			*option = 1;
			return (i + 2);
		}
	}
	return (i);
}

/*
** Function which is launched when the command contains the built in ECHO.
** - Check if option -n is activated or not
** - Display the rest of the string str (without echo and option) while 
**   checking whitespaces.
** This function return an int 0 but could return a void.
*/
int	echo_builtin(char *str, int str_length)
{
	int	option;
	int	i;

	option = 0;
	i = check_n_option(str, str_length, &option);
	while (str[i] && ft_iswhitespace(str[i]))
		i++;
	while (str[i] && i < str_length)
	{
		if (ft_iswhitespace(str[i]))
		{
			write(1, " ", 1);
			while (str[i] && i < str_length && ft_iswhitespace(str[i]))
				i++;
		}
		else
		{
			write(1, str + i, 1);
			i++;
		}
	}
	if (option == 0)
		write(1, "\n", 1);
	return (0);
}

/* Main to test echo built in
int	main(void)
{
	char *str = "echo -n					la deh					oehie 		,oej,de";
	
	echo_builtin(str, ft_strlen(str));
	return (0);
}*/

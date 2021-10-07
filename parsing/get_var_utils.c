/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_var_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlichir <hlichir@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/07 23:56:52 by hlichir           #+#    #+#             */
/*   Updated: 2021/10/08 00:42:24 by hlichir          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

/*
** Subfonction to expand string for variable in case of home (thanks norme)
*/
void	expand_variable_for_home(t_infos *infos, int i, int *size, char **var)
{
	if ((i == 0 || infos->curr_cmd[i - 1] == ' ')
		&& (!infos->curr_cmd[i + 1] || infos->curr_cmd[i + 1] == ' '))
		*size += get_var(infos, &infos->curr_cmd[i], var, 1);
}

/*
** Subfunction to add ignore & dbl for string parsing (function get_cmd_var)
*/
void	add_ignore_dbl(char cmd_char, int *ignore, int *dbl)
{
	if (cmd_char == '"' && *dbl == 0 && *ignore == 0)
		*dbl = 1;
	else if (cmd_char == '"' && *dbl == 1 && *ignore == 0)
		*dbl = 0;
	else if (cmd_char == '\'' && *ignore == 0 && *dbl == 0)
		*ignore = 1;
	else if (cmd_char == '\'' && *ignore == 1 && *dbl == 0)
		*ignore = 0;
}

/*
** Functions to handle the exception << $variable.
*/
int	check_for_redir_exception(t_infos *infos, int exception, int i)
{
	char	*cmd;

	cmd = infos->curr_cmd;
	while (cmd[i])
	{
		if (cmd[i] == '<' && cmd[i + 1] && cmd[i + 1] == '<')
		{
			i = i + 2;
			while (cmd[i] && ft_strchr(" \t\n", cmd[i]))
				i++;
			if (cmd[i] && cmd[i] == '$')
			{
				cmd = get_new_string_for_exception(&cmd, i);
				if (!cmd)
					return (return_error(1, "memory allocation error", 0, -1));
				exception = 1;
				i = i + 2;
			}
		}
		if (cmd[i])
			i++;
	}
	if (exception == 1)
		infos->curr_cmd = cmd;
	return (0);
}

/*
** Sub-function to modify string when adding variables.
*/
void	add_var_modify_string(char **new_cmd, char *var, int dbl, int i[2])
{
	int	var_size;
	int	k;

	var_size = ft_strlen(var);
	k = 0;
	if (dbl == 0 && var_size > 0)
	{
		if (var[0] == '$' && var_size == 1)
			(*new_cmd)[i[1]++] = '\'';
		else
			(*new_cmd)[i[1]++] = '$';
	}
	while (k < var_size)
	{
		(*new_cmd)[i[1]] = var[k++];
		i[1] += 1;
	}
	if (dbl == 0 && var_size > 0)
	{
		if (var[0] == '$' && var_size == 1)
			(*new_cmd)[i[1]++] = '\'';
		else
			(*new_cmd)[i[1]++] = '$';
	}
}

/*
** Sub_function for get_var.
*/
int	get_var_exception(t_infos *infos, char **var, char *cmd, int *i)
{
	*i = 0;
	if (cmd[*i] != '$' && cmd[*i] != '~')
	{
		*var = NULL;
		*i = -1;
		return (0);
	}
	if (cmd[(*i)++] == '~')
	{
		sub_get_var(var, "HOME", infos->env, infos->lst_var);
		if (!*var)
			*var = "~";
		(*i) = -1;
		return (ft_strlen(*var) - 1);
	}
	while (cmd[*i])
	{
		if (!ft_isalnum(cmd[*i]) && cmd[*i] != '_' && cmd[*i] != '?')
			break ;
		(*i)++;
	}
	return (-1);
}
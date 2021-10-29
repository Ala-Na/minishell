/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_var_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlichir < hlichir@student.42.fr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/07 23:56:52 by hlichir           #+#    #+#             */
/*   Updated: 2021/10/29 13:04:26 by hlichir          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

/*
** Subfonction to expand string for variable in case of home (thanks norme)
*/
void	expand_variable_for_home(t_infos *infos, int i, int *size, char **var)
{
	int	pos;

	if ((i == 0 || infos->curr_cmd[i - 1] == ' ')
		&& (!infos->curr_cmd[i + 1] || infos->curr_cmd[i + 1] == ' '))
	{
		pos = seek_elem_pos(infos->env, "HOME");
		if (pos >= 0 && (infos->env)[pos][ft_strlen("HOME")] == '=')
		{
			*var = get_env_elem(infos->env, "HOME", ft_strlen("HOME"));
			if (*var)
			{
				if (size)
					*size += ft_strlen(*var) - 1;
				return ;
			}
			else
				return_error(1, "memory allocation error", 0, -1);
		}
		if (size)
			*size += get_var(infos, i, var, 1);
		else
			get_var(infos, i, var, 1);
	}
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
** Sub-function to modify string when adding variables.
*/
void	add_var_modify_string(char **new_cmd, char *var, int dbl, int i[2])
{
	int	var_size;
	int	k;

	var_size = ft_strlen(var);
	k = 0;
	if (dbl == 0 && var_size > 0)
		add_var_symbol(new_cmd, var, var_size, &(i[1]));
	while (k < var_size)
	{
		if (var_size > 1 && dbl == 0 && var[k] == '$')
			var_in_var(new_cmd, &(i[1]), &k);
		else
			(*new_cmd)[i[1]++] = var[k++];
	}
	if (dbl == 0 && var_size > 0)
		add_var_symbol(new_cmd, var, var_size, &(i[1]));
}

/*
** Sub_function for get_var.
*/
int	get_var_exception(t_infos *infos, char **var, char *cmd, int *i)
{
	*i = 0;
	if (cmd && var && cmd[*i] != '$' && cmd[*i] != '~')
	{
		*var = NULL;
		*i = -1;
		return (0);
	}
	if (cmd && infos && var && cmd[(*i)++] == '~')
	{
		cmd = ft_strdup("~");
		if (!cmd)
			return (return_error(1, "memory allocation error", 0, -1));
		sub_get_var(var, &cmd, infos->env, infos->lst_var);
		(*i) = -1;
		return (ft_strlen(*var) - 1);
	}
	while (cmd && infos && var && cmd[*i])
	{
		if (!ft_isalnum(cmd[*i]) && cmd[*i] != '_' && cmd[*i] != '?')
			break ;
		(*i)++;
	}
	return (-1);
}

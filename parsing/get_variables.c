/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_variables.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlichir < hlichir@student.42.fr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/09 21:45:16 by anadege           #+#    #+#             */
/*   Updated: 2021/10/11 22:57:28 by anadege          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	sub_get_var(char **var, char *elem_name, char **env, t_var *var_lst)
{
	*var = get_env_elem(env, elem_name, ft_strlen(elem_name));
	if (!*var)
	{
		while (var_lst)
		{
			if (!ft_strncmp(var_lst->name, elem_name, ft_strlen(elem_name)))
			{
				*var = var_lst->value;
				return ;
			}
			var_lst = var_lst->next;
		}
	}
}

/*
** Function to get the env variable pointed by the beginning of cmd.
** Return the size difference between the variable and the size it takes inside
** the original cmd line (ex : for variable lol=1, the difference size returned 
** $lol of size 4 and it's value 1 of size 1 is -3).
** It also fill the pointer on string **var with the string value of the 
** env variable.
** Return -1 (size of single char $) and fill var with NULL if the variable isn't
** found or an error occurs.
*/
int	get_var(t_infos *infos, char *cmd, char **var, int dbl)
{
	int		i;
	int		res;
	char	*elem_name;

	res = get_var_exception(infos, var, cmd, &i);
	if (res != -1)
		return (res);
	if (i == 1 && ((cmd[1] != '\'' && cmd[1] != '"') || dbl == 1))
	{
		*var = "$";
		return (0);
	}
	if (i > 1)
		elem_name = ft_substr(cmd, 1, i - 1);
	if (i <= 1 || !elem_name)
	{
		*var = NULL;
		return (-1);
	}
	sub_get_var(var, elem_name, infos->env, infos->lst_var);
	free(elem_name);
	if (dbl == 1)
		return (ft_strlen(*var) - i);
	return (ft_strlen(*var) - i + 2);
}

/*
** Sub function of get_cmd 
*/
void	add_var(t_infos *infos, char **new_cmd, int i[2], int dbl)
{
	char	*var;

	get_var(infos, &infos->curr_cmd[i[0]], &var, dbl);
	add_var_modify_string(new_cmd, var, dbl, i);
	if (infos->curr_cmd[i[0]] == '~')
	{
		*i += 1;
		return ;
	}
	i[0] += 1;
	while (infos->curr_cmd[i[0]])
	{
		if (!ft_isalnum(infos->curr_cmd[i[0]]) && infos->curr_cmd[i[0]] != '_' \
			&& infos->curr_cmd[i[0]] != '?')
			return ;
		i[0] += 1;
	}
}

void	get_cmd_with_var(t_infos *infos, int new_size, int ignore, int dbl)
{
	int		i[2];
	char	*new_cmd;

	init_variables(&i[0], &i[1]);
	if (!infos || !infos->curr_cmd
		|| check_for_redir_exception(infos, &new_size, 0, 0) == -1)
		return ;
	new_cmd = malloc(sizeof(*new_cmd) * (new_size + 1));
	if (!new_cmd)
		return ;
	while (infos->curr_cmd[i[0]])
	{
		add_ignore_dbl(infos->curr_cmd[i[0]], &ignore, &dbl);
		if (infos->curr_cmd[i[0]] == '$' && ignore == 0)
			add_var(infos, &new_cmd, i, dbl);
		else if (infos->curr_cmd[i[0]] == '~' && ignore == 0
			&& (i[0] == 0 || infos->curr_cmd[i[0] - 1] == ' ')
			&& (!infos->curr_cmd[i[0] + 1] || infos->curr_cmd[i[0] + 1] == ' '))
			add_var(infos, &new_cmd, i, 1);
		else
			new_cmd[i[1]++] = infos->curr_cmd[i[0]++];
	}
	new_cmd[i[1]] = 0;
	free(infos->curr_cmd);
	infos->curr_cmd = new_cmd;
}

void	expand_variables(t_infos *infos, int dbl, int ignore, int new_size)
{
	int		i;
	char	*var;

	if (!infos || !infos->curr_cmd)
		return ;
	i = 0;
	while (infos->curr_cmd[i])
	{
		if (infos->curr_cmd[i] == '"' && dbl == 0 && ignore == 0)
			dbl = 1;
		else if (infos->curr_cmd[i] == '"' && dbl == 1 && ignore == 0)
			dbl = 0;
		else if (infos->curr_cmd[i] == '\'' && ignore == 0 && dbl == 0)
			ignore = 1;
		else if (infos->curr_cmd[i] == '\'' && ignore == 1 && dbl == 0)
			ignore = 0;
		else if (infos->curr_cmd[i] == '$' && ignore == 0)
			new_size += get_var(infos, &infos->curr_cmd[i], &var, dbl);
		else if (infos->curr_cmd[i] == '~' && ignore == 0)
			expand_variable_for_home(infos, i, &new_size, &var);
		i++;
	}
	new_size += i;
	get_cmd_with_var(infos, new_size, 0, 0);
}

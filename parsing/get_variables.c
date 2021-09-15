/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_variables.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anadege <anadege@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/09 21:45:16 by anadege           #+#    #+#             */
/*   Updated: 2021/09/10 15:02:39 by anadege          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

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
int	get_var(char *cmd, char **var, char **env)
{
	int		i;
	char	*env_elem;

	i = 0;
	if (cmd[i++] != '$')
	{
		*var = NULL;
		return (0);
	}
	while (cmd[i])
	{
		if (!ft_isalnum(cmd[i]) && cmd[i] != '_')
			break ;
		i++;
	}
	if (i > 1)
		env_elem = ft_substr(cmd, 1, i - 1);
	if (i <= 1 || !env_elem)
	{
		*var = NULL;
		return (-1);
	}
	*var = get_env_elem(env, env_elem);
	free(env_elem);
	return (ft_strlen(*var) - i);
}

/*
** Sub function of get_cmd 
*/
void	add_var(t_infos *infos, char **new_cmd, int *i, int *j)
{
	int		k;
	char	*var;
	int		var_size;

	k = 0;
	get_var(&infos->curr_cmd[i[0]], &var, infos->env);
	var_size = ft_strlen(var);
	while (k < var_size)
	{
		(*new_cmd)[*j] = var[k++];
		*j += 1;
	}
	*i += 1;
	while (infos->curr_cmd[*i])
	{
		if (!ft_isalnum(infos->curr_cmd[*i]) && infos->curr_cmd[*i] != '_')
			return ;
		*i += 1;
	}
}

void	get_cmd_with_var(t_infos *infos, int new_size)
{
	int		i[2];
	int		ignore;
	char	*new_cmd;
	int		var_size;

	i[0] = 0;
	i[1] = 0;
	ignore = 0;
	new_cmd = malloc(sizeof(*new_cmd) * (new_size + 1));
	if (!new_cmd)
		return ;
	while (infos->curr_cmd[i[0]])
	{
		if (infos->curr_cmd[i[0]] == '\'' && ignore == 0)
			ignore = 1;
		else if (infos->curr_cmd[i[0]] == '\'')
			ignore = 0;
		if (infos->curr_cmd[i[0]] == '$' && ignore == 0)
			add_var(infos, &new_cmd, &i[0], &i[1]);
		else
			new_cmd[i[1]++] = infos->curr_cmd[i[0]++];
	}
	new_cmd[i[1]] = 0;
	free(infos->curr_cmd);
	infos->curr_cmd = new_cmd;
}

void	expand_variables(t_infos *infos)
{
	int		i;
	char	*var;
	int		new_size;
	int		ignore;

	i = 0;
	new_size = 0;
	ignore = 0;
	while (infos->curr_cmd[i])
	{
		if (infos->curr_cmd[i] == '\'' && ignore == 0)
			ignore = 1;
		else if (infos->curr_cmd[i] == '\'' && ignore == 1)
			ignore = 0;
		else if (infos->curr_cmd[i] == '$')
			new_size += get_var(&infos->curr_cmd[i], &var, infos->env);
		i++;
	}
	new_size += i;
	get_cmd_with_var(infos, new_size);
}

/*
// Main pour tester remplacement de variables
int main(int argc, char **argv, char **env)
{
	t_infos	infos;

	save_env(&infos, env);
	infos.curr_cmd = ft_strdup("$'$PWD'=joli $HOME$lol\"$lol\"");
	printf("old cmd : %s\n", infos.curr_cmd);
	expand_variables(&infos);
	printf("new cmd : %s\n", infos.curr_cmd);
	free(infos.curr_cmd);
	int i = 0;
	while (infos.env[i])
		free(infos.env[i++]);
	free(infos.env);
	return (0);
}
*/

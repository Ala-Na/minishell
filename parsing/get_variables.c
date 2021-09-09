/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_variables.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anadege <anadege@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/09 21:45:16 by anadege           #+#    #+#             */
/*   Updated: 2021/09/09 23:43:07 by anadege          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

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

void	get_cmd_with_var(t_infos *infos, int new_size)
{
	int		i[3];
	int		ignore;
	char	*new_cmd;
	char	*var;
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
		{
			i[2] = 0;
			get_var(&infos->curr_cmd[i[0]], &var, infos->env);
			var_size = ft_strlen(var);
			while (i[2] < var_size)
				new_cmd[i[1]++] = var[i[2]++];
			while (infos->curr_cmd[++i[0]])
			{
				if (!ft_isalnum(infos->curr_cmd[i[0]]) && infos->curr_cmd[i[0]] != '_')
					break ;
			}
		}
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

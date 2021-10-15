/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlichir <hlichir@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/02 11:52:56 by anadege           #+#    #+#             */
/*   Updated: 2021/10/15 11:49:55 by anadege          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

/*
** The two following functions initialize the variable "SHLVL" in the
**	environement -> shows how many shells are launched.
*/
int	get_shell_nbr(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '=' && str[i + 1])
			return (ft_atoi(str + i + 1));
		i++;
	}
	return (0);
}

/*
** Function to modify SHLVL value to +1.
*/
int	add_new_shlvl(t_infos *infos, char *shlvl, char **env, int nb)
{
	t_token	*new_elem;
	char	*str;

	str = ft_itoa(get_shell_nbr(env[nb]) + 1);
	if (!str)
		return (-1);
	str = ft_strjoin_free(&shlvl, &str, 0, 1);
	if (!str)
		return (-1);
	new_elem = malloc(sizeof(*new_elem));
	if (!new_elem)
	{
		free(str);
		return (-1);
	}
	new_elem->type = ASSIGNMENT;
	new_elem->token = str;
	new_elem->length = ft_strlen(str);
	new_elem->linked_to_next = NULL;
	new_elem->prev = NULL;
	new_elem->next = NULL;
	nb = modify_existing_elem_to_env(infos, infos->env, new_elem, shlvl);
	free(str);
	free(new_elem);
	return (nb);
}

int	add_tilde_to_var_list(t_infos *infos)
{
	char	*home_path;

	home_path = get_env_elem(infos->env, "HOME", 4);
	if (home_path)
		home_path = ft_strjoin("~=", home_path);
	else
		home_path = ft_strdup("~=/home");
	if (add_new_var_to_list(infos, home_path) == -1)
	{
		free(home_path);
		return (-1);
	}
	free(home_path);
	return (0);
}

/*
** Function to initialize minishell
** Will fill the structure 'infos' and add the previous history from file
** Returns -1 in case of an error, 0 if not.
*/
int	init_minishell(t_infos *infos, char **env)
{	
	int	nbr;

	g_exit_status = -1;
	infos->prompt = NULL;
	infos->curr_cmd = NULL;
	infos->lst_tokens = NULL;
	infos->lst_cmds = NULL;
	infos->lst_var = NULL;
	if (add_new_var_to_list(infos, "?=0") == -1)
		return (-1);
	infos->fd_history = 0;
	infos->env = NULL;
	infos->fd_history = get_previous_history();
	if (infos->fd_history == -1)
		return (-1);
	if (save_env(infos, env) == -1 || infos->env == NULL)
		return (-1);
	nbr = seek_elem_pos(env, "SHLVL");
	if (nbr < 0 || add_new_shlvl(infos, "SHLVL=", env, nbr) == -1)
		return (-1);
	if (add_tilde_to_var_list(infos) == -1)
		return (-1);
	return (0);
}

void	init_variables(int *i1, int *i2, int value)
{
	*i1 = value;
	*i2 = value;
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlichir < hlichir@student.42.fr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/31 15:39:01 by anadege           #+#    #+#             */
/*   Updated: 2021/09/20 16:44:00 by anadege          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

/*
** Function which is useful to recuperate only the name of a variable
** from it's format "NAME=value".
** Returns NULL if an error occurs.
*/
char	*get_elem_name(char *elem, int size)
{
	char	*elem_name;
	int		i;

	i = 0;
	if (!elem)
		return (NULL);
	while (elem[i] != '=' && i < size)
		i++;
	elem_name = malloc(sizeof(*elem_name) * (i + 1));
	if (!elem_name)
	{
		ft_puterr("Memory allocation error\n", 0);
		g_exit_status = 1;
		return (NULL);
	}
	i = 0;
	while (elem[i] != '=' && i < size)
	{
		elem_name[i] = elem[i];
		i++;
	}
	elem_name[i] = 0;
	return (elem_name);
}

/*
** Function which returns environment's variable corresponding to the given 
** element (ex : For HOME, returns "/home/user42").
** Do the same as getenv function but for minishell environment where variables
** can be added.
** The argument char **env is infos->env.
** Returns NULL if the element is not found.
*/
char	*get_env_elem(char **env, char *elem)
{
	int		i;
	char	*elem_value;
	int		elem_size;

	i = 0;
	elem_size = ft_strlen(elem);
	while (env[i])
	{
		if (!ft_strncmp(env[i], elem, elem_size))
		{
			elem_value = env[i];
			elem_value += elem_size + 1;
			return (elem_value);
		}
		i++;
	}
	return (NULL);
}

/*
** Function to free the allocated memory for the array **env and for each
** of its element.
** last argument represents the last element of the array which was allocated.
** If last is equal to -1, every elements of the array is freed.
*/
void	free_env(char **env, int last)
{
	int	i;

	i = 0;
	if (last > 0)
	{
		while (i < last)
			free(env[i++]);
	}
	else if (last == -1)
	{
		while (env[i])
			free(env[i++]);
	}
	free(env);
}

/*
** Function which aim to save environment variables inside a structure
** containing the minishell's informations.
** Allocations are realised to free the array without complications.
** Return -1 if an error occurs, 0 otherwise.
*/
int	save_env(t_infos *infos, char **env)
{
	int		i;
	int		y;
	char	**tmp_env;

	i = 0;
	while (env[i])
		i++;
	tmp_env = malloc(sizeof(*tmp_env) * (i + 1));
	if (!tmp_env)
		return (error_exit_status("Malloc error", infos, "?=1"));
	i = 0;
	while (env[i])
	{
		y = 0;
		tmp_env[i] = ft_strdup(env[i]);
		if (!tmp_env[i])
		{
			free_env(tmp_env, i);
			return (error_exit_status("Malloc error", infos, "?=1"));
		}
		i++;
	}
	tmp_env[i] = NULL;
	infos->env = tmp_env;
	return (0);
}

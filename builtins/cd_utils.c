/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlichir <hlichir@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/05 13:05:41 by hlichir           #+#    #+#             */
/*   Updated: 2021/10/07 22:23:23 by anadege          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

/*
** Function to create the new string that will be put in the environment,
** as well as the token needed to change the env.
*/
int	create_tmp_new_elem(t_token **new_elem, char *name, char *value, char *str)
{
	str = ft_strjoin(name, "=");
	if (!str)
		return (return_error(1, "memory allocation error", 0, -1));
	str = ft_strjoin_free(&str, &value, 1, 0);
	if (!str)
		return (return_error(1, "memory allocation error", 0, -1));
	*new_elem = malloc(sizeof(t_token));
	if (!new_elem)
	{
		free(str);
		return (return_error(1, "memory allocation error", 0, -1));
	}
	(*new_elem)->type = ASSIGNMENT;
	(*new_elem)->token = ft_strdup_free(&str, 1);
	if (!(*new_elem)->token)
	{
		free(str);
		return (return_error(1, "memory allocation error", 0, -1));
	}
	(*new_elem)->length = ft_strlen((*new_elem)->token);
	(*new_elem)->linked_to_next = NULL;
	(*new_elem)->prev = NULL;
	(*new_elem)->next = NULL;
	return (0);
}

/*
**	Subfunction to save the old path name in a tmp_variable & to check
** if cd - was called.
*/
char	*check_oldpwd_cdpath(t_infos *infos, char **path, int *is_alloc)
{
	int			nb;

	if (!ft_strncmp(*path, "-", 2))
	{
		nb = seek_elem_pos(infos->env, "OLDPWD");
		if (nb < 0)
			return (return_null_error(1, "cd: OLDPWD not set", 0));
		if (*is_alloc)
			free(*path);
		*path = get_elem_value((infos->env)[nb]);
		if (!*path)
			return (NULL);
		*path = ft_strdup_free(path, 1);
		if (!(*path))
			return (return_null_error(1, "memory allocation error", 0));
		*is_alloc = 2;
	}
	else if (get_env_elem(infos->env, "CDPATH", ft_strlen("CDPATH")))
	{
		if (handle_cd_path(infos->env, path, is_alloc) < 0)
			return (return_null_error(1, "error", 0));
	}
	return (get_curr_dir(infos, 0));
}

/*
** Function to handle CDPATH.
*/
int	handle_cd_path(char **env, char **path, int *is_alloc)
{
	int			nb;
	char		*str;
	struct stat	buf;

	nb = seek_elem_pos(env, "CDPATH");
	if (nb < 0)
		return (-1);
	str = get_elem_value(env[nb]);
	if (!str)
		return (return_error(1, "memory allocation error", 0, -1));
	str = ft_strjoin_free(&str, path, 1, 0);
	if (!str)
		return (return_error(1, "memory allocation error", 0, -1));
	if (stat(str, &buf) != -1 && S_ISDIR(buf.st_mode))
	{
		if (*is_alloc)
			free(*path);
		*path = ft_strdup_free(&str, 1);
		if (!(path))
			return (return_error(1, "memory allocation error", 0, -1));
		*is_alloc = 2;
	}
	return (0);
}

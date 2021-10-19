/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlichir <hlichir@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/05 13:05:41 by hlichir           #+#    #+#             */
/*   Updated: 2021/10/18 21:55:43 by hlichir          ###   ########.fr       */
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
		free(new_elem);
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
			return (return_null_error(1, "OLDPWD not assigned", 0));
		*is_alloc = 2;
	}
	else if (ft_strncmp(*path, ".", 2) && ft_strncmp(*path, "..", 3) && \
		get_env_elem(infos->env, "CDPATH", ft_strlen("CDPATH")))
	{
		if (handle_cd_path(infos->env, path, is_alloc) < 0)
			return (return_null_error(1, NULL, 0));
	}
	return (get_curr_dir(infos, 0));
}

/*
**	Subfunction to see if one of the cdpath is valid. -
*/
int	check_if_valid_cdpath(char *cdpath, char **path, int *is_alloc)
{
	struct stat	buf;
	char		*str;

	str = ft_strdup(cdpath);
	if (!str)
		return (return_error(1, "memory allocation error", 0, -1));
	str = ft_strjoin_free(&str, path, 1, 0);
	if (!str)
		return (return_error(1, "memory allocation error", 0, -1));
	if (stat(str, &buf) != -1 && S_ISDIR(buf.st_mode))
	{
		if (!(stat(*path, &buf) != -1 && S_ISDIR(buf.st_mode))
			|| ((*path)[0] && (*path)[0] != '/'))
			*is_alloc = 2;
		if (*is_alloc)
			free(*path);
		*path = ft_strdup_free(&str, 1);
		if (!(*path))
			return (return_error(1, "memory allocation error", 0, -1));
		return (1);
	}
	if (str)
		free(str);
	return (0);
}

/*
** Function to handle CDPATH.
*/
int	handle_cd_path(char **env, char **path, int *is_alloc)
{
	int			nb;
	char		*str;
	char		**all_cdpath;

	nb = seek_elem_pos(env, "CDPATH");
	if (nb < 0)
		return (-1);
	str = get_elem_value(env[nb]);
	if (!str)
		return (-1);
	all_cdpath = ft_split(str, ':');
	free(str);
	if (!all_cdpath)
		return (return_error(1, "memory allocation error", 0, -1));
	nb = -1;
	while (all_cdpath[++nb])
		if (check_if_valid_cdpath(all_cdpath[nb], path, is_alloc) == 1)
			break ;
	nb = -1;
	while (all_cdpath[++nb])
		free(all_cdpath[nb]);
	free(all_cdpath);
	return (0);
}

/*
**	Subfunction to check if the current directory still exists.
*/
void	check_if_currdir_exist(t_infos *infos, char **tmp_path, char *old_path,
			char *new_path)
{
	char		buffer[1024];
	struct stat	buf;

	if (getcwd(buffer, 1024) == NULL && errno == ENOENT)
	{
		if (stat(old_path, &buf) == -1)
		{
			ft_puterr("cd: ", 0);
			ft_puterr(strerror(errno), 1);
			*tmp_path = ft_strjoin(old_path, "/");
			if (!*tmp_path)
				return ;
			*tmp_path = ft_strjoin_free(tmp_path, &new_path, 1, 0);
			return ;
		}
		else
			*tmp_path = ft_strdup(new_path);
	}
	else
		*tmp_path = get_curr_dir(infos, 0);
}

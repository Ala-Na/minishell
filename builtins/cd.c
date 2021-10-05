/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlichir <hlichir@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/30 16:59:11 by anadege           #+#    #+#             */
/*   Updated: 2021/10/05 13:21:40 by hlichir          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

/*
** Function to change the current directory.
** To use when the buil in cd is called.
** Use the function chdir.
** Return -1 and display corresponding error if an error
** occurs, 0 otherwise.
** Exit = 126 > command is found but not executable
** Exit = 1 Somehing went wrong (memory allocation error)
*/
int	change_directory(t_infos *infos, char *new_path, int is_alloc)
{
	char	*tmp_path;

	if (!infos || !new_path)
	{
		if (is_alloc && new_path)
			free(new_path);
		return (return_error(1, "something went wrong", 0, -1));
	}
	tmp_path = check_oldpwd_cdpath(infos->env, &new_path, &is_alloc);
	if (!tmp_path)
		return (return_error(1, "memory allocation error", 0, -1));
	if (chdir(new_path) == -1)
	{
		if (is_alloc)
			free(new_path);
		ft_puterr("cd: ", 0);
		ft_puterr(new_path, 0);
		ft_puterr(": ", 0);
		return (return_error(1, strerror(errno), 0, -1));
	}
	modify_pwd(infos, "OLDPWD", tmp_path, 0);
	modify_pwd(infos, "PWD", get_curr_dir(0), is_alloc);
	if (is_alloc)
		free(new_path);
	return (0);
}

/*
** Function to call when the first element of a t_cmd structure is "cd".
** Exit status = 1 : something went wrong (memory allocation ...)
** Exit status = 2 : Misuse of a Shell builtin
*/
int	cmd_change_directory(t_infos *infos, t_cmd *cmd)
{
	int		i;
	char	*home_path;
	t_token	*curr;

	i = -1;
	if (!infos || !cmd)
		return (return_error(1, "something went wrong", 0, -1));
	curr = cmd->start;
	move_to_next_token(&curr, 0);
	if (curr == cmd->end)
	{
		home_path = get_env_elem(infos->env, "HOME", ft_strlen("HOME"));
		if (!home_path)
			return (return_error(1, "cd: « HOME » not defined", 0, -1));
		return (change_directory(infos, home_path, 0));
	}
	curr = curr->next;
	move_to_next_token(&curr, 0);
	if (curr && curr->next && curr->next != cmd->end)
		return (return_error(1, "cd: too many arguments", 0, -1));
	home_path = ft_strdup_linked_string(curr);
	if (!home_path)
		return (return_error(1, "memory allocation error", 0, -1));
	return (change_directory(infos, home_path, 1));
}

/*
**	Subfunction to save the old path name in a tmp_variable & to check
** if cd - was called.
*/
char	*check_oldpwd_cdpath(char **env, char **path, int *is_alloc)
{
	int			nb;

	if (!ft_strncmp(*path, "-", 2))
	{
		nb = seek_elem_pos(env, "OLDPWD");
		if (nb < 0)
			return (return_null_error(1, "cd: OLDPWD not set", 0));
		if (*is_alloc)
			free(*path);
		*path = ft_strdup_free(get_elem_value(env[nb]), 1);
		if (!(*path))
			return (return_null_error(1, "memory allocation error", 0));
		*is_alloc = 2;
	}
	else if (get_env_elem(env, "CDPATH", ft_strlen("CDPATH")))
		if (handle_cd_path(env, path, is_alloc) < 0)
			return (return_null_error(1, "error", 0));
	return (get_curr_dir(0));
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
	str = ft_strjoin_free(get_elem_value(env[nb]), *path, 1, 0);
	if (!str)
		return (return_error(1, "memory allocation error", 0, -1));
	if (stat(str, &buf) != -1 && S_ISDIR(buf.st_mode))
	{
		{
			if (is_alloc)
				free(*path);
			*path = ft_strdup_free(str, 1);
			if (!(path))
				return (return_error(1, "memory allocation error", 0, -1));
			*is_alloc = 2;
		}
	}
	return (0);
}

/*
** Function to change either the variable PWD or OLDPWD depending on "name"
** Create a new token with name=new_pwd to change the environment
** is_old is equal to 2 when cd - is called -> the new pwd is displayed.
*/
int	modify_pwd(t_infos *infos, char *name, char *new_pwd, int is_old)
{
	t_token	*new_elem;
	char	*str;
	int		tmp;
	int		env_size;

	if (!new_pwd)
		return (return_error(1, "memory allocation error", 0, -1));
	if (create_tmp_new_elem(&new_elem, name, new_pwd, str) < 0)
		return (-1);
	env_size = 0;
	while ((infos->env)[env_size])
		env_size++;
	if (!get_env_elem(infos->env, name, ft_strlen(name)))
		add_not_existing_elem_to_env(&infos->env, new_elem, env_size);
	else
		modify_existing_elem_to_env(infos, infos->env, new_elem, name);
	free(new_elem->token);
	free(new_elem);
	if (is_old == 2)
	{
		ft_putstr(new_pwd);
		ft_putchar('\n');
	}
	return (0);
}

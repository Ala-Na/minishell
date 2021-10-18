/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlichir <hlichir@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/30 16:59:11 by anadege           #+#    #+#             */
/*   Updated: 2021/10/18 21:59:57 by hlichir          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

/*
** Function to change either the variable PWD.
** Create a new token with OLD=new_pwd to change the environment
** is_old is equal to 2 when cd - is called or if cdpath was used
** -> the new pwd is displayed
*/
int	modify_pwd(t_infos *infos, t_cmd *cmd, char *new_pwd, int is_old)
{
	t_token	*new_elem;
	char	*str;
	int		env_size;

	str = NULL;
	if (!new_pwd)
		return (return_error(1, "memory allocation error", 0, -1));
	if (create_tmp_new_elem(&new_elem, "OLD", new_pwd, str) < 0)
		return (-1);
	env_size = 0;
	while ((infos->env)[env_size])
		env_size++;
	if (!get_env_elem(infos->env, "OLD", ft_strlen("OLD")))
		add_not_existing_elem_to_env(&infos->env, new_elem, env_size);
	else
		modify_existing_elem_to_env(infos, infos->env, new_elem, "OLD");
	free(new_elem->token);
	free(new_elem);
	if (is_old == 2)
	{
		write(cmd->fd_output, new_pwd, ft_strlen(new_pwd));
		write(cmd->fd_output, "\n", 1);
	}
	return (0);
}

/*
** Function to change either the variable OLDPWD
** Create a new token with OLDPWD=new_pwd to change the environment
*/
int	modify_old_pwd(t_infos *infos, char *new_pwd)
{
	t_token	*new_elem;
	char	*str;
	int		env_size;

	str = NULL;
	if (!new_pwd)
		return (return_error(1, "memory allocation error", 0, -1));
	if (create_tmp_new_elem(&new_elem, "OLDPWD", new_pwd, str) < 0)
		return (-1);
	env_size = 0;
	while ((infos->env)[env_size])
		env_size++;
	if (!get_env_elem(infos->env, "OLDPWD", ft_strlen("OLDPWD")))
		add_not_existing_elem_to_env(&infos->env, new_elem, env_size);
	else
		modify_existing_elem_to_env(infos, infos->env, new_elem, "OLDPWD");
	free(new_elem->token);
	free(new_elem);
	return (0);
}

/*
** Sub function of change_directory
*/
int	call_chdir(t_infos *infos, char **new_path, int *is_alloc,
		char **old_path)
{
	if (!infos || !new_path || !*new_path)
	{
		if (is_alloc && *new_path)
			free(new_path);
		return (return_error(1, "something went wrong", 0, -1));
	}
	*old_path = check_oldpwd_cdpath(infos, new_path, is_alloc);
	if (!(*old_path))
	{
		if (*is_alloc)
			free(*new_path);
		return (return_error(1, strerror(errno), 0, -1));
	}
	if (chdir(*new_path) == -1)
	{
		ft_puterr("cd: ", 0);
		ft_puterr(*new_path, 0);
		ft_puterr(": ", 0);
		if (*is_alloc)
			free(*new_path);
		free(*old_path);
		return (return_error(1, strerror(errno), 0, -1));
	}
	return (0);
}

/*
** Function to change the current directory.
** To use when the buil in cd is called.
** Use the function chdir.
** Return -1 and display corresponding error if an error
** occurs, 0 otherwise.
** Exit = 126 > command is found but not executable
** Exit = 1 Something went wrong (memory allocation error)
*/
int	change_directory(t_infos *infos, t_cmd *cmd, char **new_path, int is_alloc)
{
	char	*old_path;
	char	*tmp_path;

	if (!infos || !new_path || !*new_path)
	{
		if (is_alloc && *new_path)
			free(new_path);
		return (return_error(1, "something went wrong", 0, -1));
	}
	if (call_chdir(infos, new_path, &is_alloc, &old_path) == -1)
		return (-1);
	modify_old_pwd(infos, old_path);
	tmp_path = NULL;
	check_if_currdir_exist(infos, &tmp_path, old_path, *new_path);
	free(old_path);
	if (!tmp_path)
		return (return_error(1, "memory allocation error", 0, -1));
	modify_pwd(infos, cmd, tmp_path, is_alloc);
	if (is_alloc)
		free(*new_path);
	free(tmp_path);
	return (0);
}

/*
** Function to call when the first element of a t_cmd structure is "cd".
** Exit status = 1 : something went wrong (memory allocation ...)
** Exit status = 2 : Misuse of a Shell builtin
*/
int	cmd_change_directory(t_infos *infos, t_cmd *cmd, t_cmd *head, t_token *tok)
{
	char	*home_path;
	t_token	*curr;
	t_token	*next;

	if (!infos || !cmd)
		return (return_error(1, "something went wrong", 0, -1));
	curr = get_next_token(infos, cmd, &cmd, tok);
	if (!curr && g_exit_status != 0)
		return (-1);
	if ((!curr && g_exit_status == 0))
	{
		home_path = get_env_elem(infos->env, "HOME", ft_strlen("HOME"));
		if (!home_path)
			return (return_error(1, "cd: « HOME » not defined", 0, -1));
		if (ft_strlen(home_path) == 0)
			return (0);
		return (change_directory(infos, head, &home_path, 0));
	}
	next = get_next_token(infos, cmd, &cmd, curr);
	if (curr && next)
		return (return_error(1, "cd: too many arguments", 0, -1));
	home_path = ft_strdup_linked_string(curr);
	if (!home_path)
		return (return_error(1, "memory allocation error", 0, -1));
	return (change_directory(infos, head, &home_path, 1));
}

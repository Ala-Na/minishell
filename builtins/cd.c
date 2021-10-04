/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlichir <hlichir@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/30 16:59:11 by anadege           #+#    #+#             */
/*   Updated: 2021/10/04 18:26:20 by hlichir          ###   ########.fr       */
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
int	change_directory(t_infos *infos, char *new_dir_path, int is_alloc)
{
	char	*str;

	if (!infos || !new_dir_path)
	{
		if (is_alloc && new_dir_path)
			free(new_dir_path);
		return (return_error(1, "something went wrong", 0, -1));
	}
	if (chdir(new_dir_path) == -1)
	{
		if (is_alloc)
			free(new_dir_path);
		str = strerror(errno);
		str = ft_strjoin("cd : ", str);
		if (!str)
			return (return_error(1, "memory allocation error", 0, -1));
		return (return_error(1, str, 1, -1));
	}
	if (is_alloc)
		free(new_dir_path);
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

/*char	*create_str_assignment(char *name, char *value)
{
	char	*str;

	str = ft_strjoin(name, "=");
	if (!str)
		return (return_null_error(1, "yymemory allocation error", 0));
	str = ft_strjoin_free(str, value, 1, 0);
	if (!str)
		return (return_null_error(1, "ymemory allocation error", 0));
	return (str);
}

void	create_tmp_new_elem(t_token **new_elem, char *str)
{
	*new_elem = malloc(sizeof(t_token));
	if (!new_elem)
		return ;
	(*new_elem)->type = ASSIGNMENT;
	(*new_elem)->token = str;
	(*new_elem)->length = ft_strlen(str);
	(*new_elem)->linked_to_next = NULL;
	(*new_elem)->prev = NULL;
	(*new_elem)->next = NULL;
}

int	modify_pwd(t_infos *infos, char **env, char *name, char *new_pwd)
{
	t_token	*new_elem;
	char	*str;
	int		nb;

	str = create_str_assignment(name, new_pwd);
	if (!str)
		return (return_error(1, "yomemory allocation error", 0, -1));
	create_tmp_new_elem(&new_elem, str);
	if (!new_elem)
	{
		free(str);
		return (-1);
	}
	do_assignment(infos, new_elem);
	free(str);
	free(new_elem);
	return (0);
}
*/
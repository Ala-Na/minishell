/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlichir < hlichir@student.42.fr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/12 21:48:31 by anadege           #+#    #+#             */
/*   Updated: 2021/10/14 13:55:27 by hlichir          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	simplify_prompt_curr_dir(t_infos *infos, char **prompt)
{
	char	*home;
	char	*tmp_home;
	char	*tmp_prompt;

	if (!infos || !prompt || !*prompt)
		return ;
	home = get_env_elem(infos->env, "HOME", 4);
	if (!home)
		return ;
	tmp_home = ft_strdup(home);
	if (!tmp_home)
		return ;
	else if (!strncmp(tmp_home, *prompt, ft_strlen(tmp_home)))
	{
		tmp_prompt = ft_strdup(*prompt + ft_strlen(tmp_home));
		if (tmp_prompt)
		{
			free(*prompt);
			*prompt = ft_strjoin("~", tmp_prompt);
			free(tmp_prompt);
		}
	}
	if (tmp_home)
		free(tmp_home);
}

int	loop_to_getcwd(char **res, char **buffer_dir, size_t *size_buffer_dir)
{
	*res = getcwd(*buffer_dir, *size_buffer_dir - 1);
	while (!(*res) && errno == ERANGE)
	{
		free(*buffer_dir);
		*size_buffer_dir *= 2;
		*buffer_dir = malloc(sizeof(**buffer_dir) * *size_buffer_dir);
		if (!(*buffer_dir))
			return (return_error(1, "memory allocation error", 0, -1));
		*res = getcwd(*buffer_dir, *size_buffer_dir - 1);
	}
	return (0);
}

char	*get_curr_dir(t_infos *infos, int prompt)
{
	char	*res;
	size_t	size_buffer_dir;
	char	*buffer_dir;

	if (!infos && !prompt)
		return (return_null_error(1, "something went wrong", 0));
	else if (!infos)
		return (NULL);
	size_buffer_dir = 512;
	buffer_dir = malloc(sizeof(*buffer_dir) * size_buffer_dir);
	if (!buffer_dir)
		return (NULL);
	if (loop_to_getcwd(&res, &buffer_dir, &size_buffer_dir) == -1)
		return (NULL);
	if (!res && errno == ENOENT)
	{
		free(buffer_dir);
		buffer_dir = get_str_pwd(infos);
	}
	if (prompt)
		simplify_prompt_curr_dir(infos, &buffer_dir);
	return (buffer_dir);
}

char	*get_prompt(t_infos *infos)
{
	char	*curr_dir;
	char	*tmp_msg;
	char	*msg;

	if (!infos)
		return (NULL);
	curr_dir = get_curr_dir(infos, 1);
	if (!curr_dir)
		return (NULL);
	msg = ft_strjoin(PROMPT_MSG, "\001\033[38;5;31m\002");
	if (!msg)
		return (NULL);
	tmp_msg = ft_strjoin(msg, curr_dir);
	free(curr_dir);
	free(msg);
	if (!tmp_msg)
		return (NULL);
	msg = ft_strjoin(tmp_msg, " \001\033[0m\002");
	free(tmp_msg);
	return (msg);
}

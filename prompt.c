/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anadege <anadege@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/12 21:48:31 by anadege           #+#    #+#             */
/*   Updated: 2021/09/24 23:05:24 by anadege          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	simplify_prompt_curr_dir(char **prompt)
{
	char	*home;
	char	*tmp_home;
	char	*tmp_prompt;

	home = getenv("HOME");
	if (!home)
		return ;
	tmp_home = ft_strdup(home);
	if (home && !strncmp(tmp_home, *prompt, ft_strlen(tmp_home)))
	{
		tmp_prompt = ft_strdup(*prompt + ft_strlen(tmp_home));
		free(*prompt);
		*prompt = ft_strjoin("~", tmp_prompt);
		free(tmp_prompt);
	}
	free(tmp_home);
}

char	*get_curr_dir(int prompt)
{
	char	*res;
	size_t	size_buffer_dir;
	char	*buffer_dir;
	char	*user;

	size_buffer_dir = 512;
	buffer_dir = malloc(sizeof(*buffer_dir) * size_buffer_dir);
	if (!buffer_dir)
		return (NULL);
	res = getcwd(buffer_dir, size_buffer_dir - 1);
	while (!res && errno == ERANGE)
	{
		free(buffer_dir);
		size_buffer_dir *= 2;
		buffer_dir = malloc(sizeof(*buffer_dir) * size_buffer_dir);
		if (!buffer_dir)
			return (NULL);
		res = getcwd(buffer_dir, size_buffer_dir - 1);
	}
	if (prompt)
		simplify_prompt_curr_dir(&buffer_dir);
	return (buffer_dir);
}

char	*get_prompt(void)
{
	char	*curr_dir;
	char	*tmp_msg;
	char	*msg;

	curr_dir = get_curr_dir(1);
	if (!curr_dir)
		return (NULL);
	msg = ft_strjoin(PROMPT_MSG, "\001\033[38;5;31m\002");
	tmp_msg = ft_strjoin(msg, curr_dir);
	free(curr_dir);
	free(msg);
	msg = ft_strjoin(tmp_msg, " \001\033[0m\002");
	free(tmp_msg);
	return (msg);
}

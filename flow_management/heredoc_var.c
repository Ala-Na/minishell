/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_var.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlichir <hlichir@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/16 16:44:57 by hlichir           #+#    #+#             */
/*   Updated: 2021/10/20 15:36:44 by anadege          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	get_new_content(t_infos *infos, char **new, char *old)
{
	int	i;
	int	size;

	i = 0;
	size = 0;
	while (old[i])
	{
		if (old[i] == '$' && old[i + 1] && !ft_strchr(" \t\n\'\"", old[i + 1]))
		{
			add_variable_to_new(infos, new, size, old + i + 1);
			size = size + get_new_var_size(infos, old + i + 1);
			while (old[i] && !ft_strchr(" \t\n\'\"", old[i]))
				i++;
		}
		else
			(*new)[size++] = old[i++];
	}
	(*new)[size] = '\0';
}

void	get_new_content_size(t_infos *infos, char **new, char *old)
{
	int	i;
	int	size;

	i = 0;
	size = 0;
	while (old[i])
	{
		if (old[i] == '$' && old[i + 1] && !ft_strchr(" \t\n\'\"", old[i + 1]))
		{
			size = size + get_new_var_size(infos, old + i + 1);
			while (old[i] && !ft_strchr(" \t\n\'\"", old[i]))
				i++;
		}
		else
		{
			size++;
			i++;
		}
	}
	*new = malloc(sizeof(**new) * (size + 1));
}

char	*extract_content_from_file(int fd)
{
	char	*content;
	char	*tmp_str;

	content = ft_strdup("");
	if (!content)
		return (return_null_error(1, "memory allocation error", 0));
	close(fd);
	fd = open("./tmp_file", O_RDWR);
	if (fd < 0)
		return (return_null_error(1, "error while opening file", 0));
	while (get_next_line(fd, &tmp_str) > 0)
	{
		content = ft_strjoin_free(&content, &tmp_str, 1, 1);
		if (!content)
		{
			close(fd);
			return (return_null_error(1, "memory allocation error", 0));
		}
		tmp_str = "\n";
		content = ft_strjoin_free(&content, &tmp_str, 1, 0);
		if (!content)
		{
			close(fd);
			return (return_null_error(1, "memory allocation error", 0));
		}
	}
	close(fd);
	return (content);
}

int	check_if_string(t_cmd *cmd_end_str)
{
	t_token	*token;
	int		i;

	token = cmd_end_str->start;
	while (token)
	{
		if (token->type == STRING)
		{
			i = 0;
			while (i < token->length && token->token[i] != '$')
				i++;
			if (i == token->length)
				return (1);
		}
		if (!(token->linked_to_next))
			break ;
		token = token->next;
	}
	return (0);
}

int	expand_variable_to_heredoc(t_infos *infos, int fd, t_cmd *cmd_end_str)
{
	char	*old_content;
	char	*new_content;

	(void)infos;
	if (check_if_string(cmd_end_str) == 1)
		return (0);
	old_content = extract_content_from_file(fd);
	get_new_content_size(infos, &new_content, old_content);
	if (!new_content)
		return (return_error(1, "memory allocation error", 0, -1));
	get_new_content(infos, &new_content, old_content);
	free(old_content);
	close(fd);
	fd = open("./tmp_file", O_RDWR);
	if (fd < 0)
		return (return_error(1, "error while opening file", 0, -1));
	ft_putstr_fd(new_content, fd);
	free(new_content);
	close(fd);
	return (0);
}

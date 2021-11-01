/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlichir <hlichir@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/16 17:46:32 by hlichir           #+#    #+#             */
/*   Updated: 2021/10/25 19:14:25 by hlichir          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*get_new_value(t_infos *infos, char *old)
{
	int		i;
	int		pos;
	char	*name;

	i = 0;
	while (old[i] && (ft_isalnum(old[i]) || old[i] == '_'))
		i++;
	name = malloc(sizeof(*name) * (i + 1));
	if (!name)
		return (return_null_error(1, "memory allocation error", 0));
	i = 0;
	while (old[i] && (ft_isalnum(old[i]) || old[i] == '_'))
	{
		name[i] = old[i];
		i++;
	}
	name[i] = '\0';
	pos = seek_elem_pos(infos->env, name);
	if (pos == -2)
		return (check_list_var(infos->lst_var, &name));
	free(name);
	if (pos == -1)
		return (NULL);
	return (extract_value((infos->env)[pos], ft_strlen((infos->env)[pos])));
}

void	add_variable_to_new(t_infos *infos, char **new, int size, char *start)
{
	int		i;
	char	*value;

	i = 0;
	value = get_new_value(infos, start);
	if (!value)
		return ;
	while (value[i])
		(*new)[size++] = value[i++];
	free(value);
}

char	*check_list_var(t_var *lstvar, char **name)
{
	t_var	*current;
	int		size;

	current = lstvar;
	while (current)
	{
		size = ft_max(ft_strlen(*name), ft_strlen(current->name));
		if (!ft_strncmp(*name, current->name, size))
		{
			free(*name);
			return (ft_strdup(current->value));
		}
		current = current->next;
	}
	free(*name);
	return (NULL);
}

int	get_new_var_size(t_infos *infos, char *start_var)
{
	char	*value;
	int		result;

	value = get_new_value(infos, start_var);
	if (!value)
		return (0);
	result = ft_strlen(value);
	free(value);
	return (result);
}

int	add_new_line_in_content(char **content, char **tmp_str, int fd)
{
	*content = ft_strjoin_free(content, tmp_str, 1, 1);
	if (!(*content))
	{
		close(fd);
		return (return_error(1, "memory allocation error", 0, -1));
	}
	*tmp_str = "\n";
	*content = ft_strjoin_free(content, tmp_str, 1, 0);
	if (!(*content))
	{
		close(fd);
		return (return_error(1, "memory allocation error", 0, -1));
	}
	return (0);
}

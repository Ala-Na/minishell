/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_as_args.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlichir <hlichir@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/25 21:57:20 by hlichir           #+#    #+#             */
/*   Updated: 2021/09/25 23:12:52 by hlichir          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

/*
** Comment to do
*/
int	add_tmp_file_to_args(char ***exec_args)
{
	char	*tmp_str;

	tmp_str = ft_strdup((*exec_args)[0]);
	free((*exec_args)[0]);
	free(*exec_args);
	*exec_args = malloc(sizeof(**exec_args) * 3);
	if (!(*exec_args))
	{
		free(tmp_str);
		return (-1);
	}
	(*exec_args)[0] = ft_strdup(tmp_str);
	free(tmp_str);
	if (!(*exec_args)[0])
		return (-1);
	(*exec_args)[1] = ft_strdup("tmp_file");
	if (!(*exec_args)[1])
		return (-1);
	(*exec_args)[2] = NULL;
	return (0);
}

/*
** Comment to do
*/
int	check_add_input(t_infos *infos, char ***exec_args, int nbr_args)
{
	int		 fd;

	if (nbr_args > 1)
	{
		if (infos->lst_cmds->input)
		{
			free(infos->lst_cmds->input);
			infos->lst_cmds->input = NULL;
		}
		return (0);
	}
	if (infos->lst_cmds->input)
	{
		fd = open("tmp_file", O_RDWR | O_TRUNC | O_CREAT, S_IRWXG | S_IRWXU);
		if (fd < 0)
			return (-1);
		ft_putstr_fd(infos->lst_cmds->input, fd);
		close(fd);
		if (add_tmp_file_to_args(exec_args) < 0)
			return (-1);
	}
	return (0);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anadege <anadege@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/23 14:58:07 by anadege           #+#    #+#             */
/*   Updated: 2021/08/30 23:47:04 by anadege          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(int argc, char **argv, char **env)
{
	char	*str;
	char	*prompt;
	int		history_fd;

	history_fd = get_previous_history();
	while (1)
	{
		prompt = get_prompt();
		if (!prompt)
			return (1);
		str = readline(prompt);
		write(history_fd, str, ft_strlen(str));
		write(history_fd, "\n", 1);
		add_history(str);
		if (!ft_strncmp(str, "exit", 5))
			break;
		if (str)
			free(str);
		if (prompt)
			free(prompt);
	}
	if (str)
		free(str);
	if (prompt)
		free(prompt);
	rl_clear_history();
	close(history_fd);
	(void)argc;
	(void)argv;
	return (0);
}

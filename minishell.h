/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anadege <anadege@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/23 15:55:23 by anadege           #+#    #+#             */
/*   Updated: 2021/08/31 17:28:45 by anadege          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "libft/libft.h"
# include <stdio.h>
# include <sys/wait.h>
# include <signal.h>
# include <unistd.h>
# include <stdlib.h>
# include <sys/types.h>
# include <dirent.h>
# include <string.h>
# include <sys/ioctl.h>
# include <stdlib.h>
# include <curses.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <errno.h>
# include <fcntl.h>

#define	PROMPT_MSG "\033[1;38;5;51mPrompt > \033[0m"

typedef struct s_infos
{
	char	**env;
} t_infos ;

void	simplify_prompt_curr_dir(char **prompt);
char	*get_prompt_curr_dir(void);
char	*get_prompt(void);

int		get_previous_history(void);
void	add_line_to_history(int history_fd, char *str);

int		change_directory(char *new_dir_path);

char	*get_env_elem(char **env, char *elem);
int		save_env(t_infos *infos, char **env);


#endif

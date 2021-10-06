/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlichir <hlichir@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/23 14:58:07 by anadege           #+#    #+#             */
<<<<<<< HEAD
/*   Updated: 2021/10/06 13:40:14 by anadege          ###   ########.fr       */
=======
/*   Updated: 2021/10/05 13:59:25 by hlichir          ###   ########.fr       */
>>>>>>> 737b8433d011791d8b39fd66ff30fbfd97d8bc4a
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

/*
** Function to free allocated memory to prepare the next loop.
** Set g_exit_status at -1 (initial state).
*/
void	clean_to_continue(t_infos *infos)
{
	char	*str;

	g_exit_status = -1;
	if (infos->curr_cmd)
		free(infos->curr_cmd);
	if (infos->prompt)
		free(infos->prompt);
	if (infos->lst_cmds)
		free_cmd_list_from_extremity(&infos->lst_cmds, 0);
	if (infos->lst_tokens)
		free_token_list_from_extremity(&infos->lst_tokens, 0);
	if (check_file("./tmp_file") == 0)
	{
		if (unlink("./tmp_file") < 0)
		{
			str = ft_strjoin("unlink : ", strerror(errno));
			return_error(1, str, 1, -1);
		}
	}
	infos->curr_cmd = NULL;
	infos->prompt = NULL;
	infos->lst_cmds = NULL;
	infos->lst_tokens = NULL;
}

/*
** First : Check if curr_cmd is only filled with blanks.
** If not, parsing is done. If parsing is correct, command is launched.
** The output is then printed.
*/
void	parse_and_execute(t_infos *infos)
{
	int		res;
	t_cmd	*final_cmd;

	if (!infos->curr_cmd || ft_isblanks(infos->curr_cmd) == 1)
		return ;
	res = parse_cmd(infos);
	if (res != 0)
		return ;
	launch_cmds(infos);
}

/*
** Minishell main loop. The loop is infinte.
** For each loop, prompt is displayed and the command line is
** recuperate throught readline. The presence of signal is controlled
** (if signal == ctrl-C, $? is modified in consequence).
** Then, EOF (ctrl-D, give a NULL readline return char *) is checked.
** The current command is added to history. Then, if the command was exit,
** minishell is exited by exiting the loop and returning to main.
** If not, the command is parsed and launched.
** Memory allocation between two loops is cleaned except if it must
** be saved (example : env must be saved).
** Returns 1 in case of error, 0 otherwise.
*/
int	minishell_loop(t_infos *infos)
{
	while (1)
	{
		infos->prompt = get_prompt(infos);
		if (!infos->prompt)
			return (return_error(1, "minshell : fatal error", 0, 1));
		infos->curr_cmd = readline(infos->prompt);
		if (check_for_signal(infos) < 0)
			return (return_error(1, "minshell : fatal error", 0, 1));
		else if (!infos->curr_cmd)
		{
			write(1, "exit\n", 5);
			break ;
		}
		add_line_to_history(infos->fd_history, infos->curr_cmd);
		if (!ft_strncmp(infos->curr_cmd, "exit", 5))
			break ;
		if (infos->curr_cmd[0] != 0)
			parse_and_execute(infos);
		if (modify_exit_value_variable(infos, g_exit_status) < 0)
			return (return_error(1, "minshell : fatal error", 0, 1));
		clean_to_continue(infos);
	}
	write(1, "exit\n", 5);
	return (0);
}

/*
** Main function of minishell programm.
** First, a structure t_infos is initialized.
** Then, the programm go to minishell_loop where most of
** the work is done.
** When minishell_loop is exited, all allocated memory left is freed.
** The return value depends of minishell_loop.
*/
int	main(int argc, char **argv, char **env)
{
	t_infos	infos;
	int		return_value;

	(void)argc;
	(void)argv;
	if (init_minishell(&infos, env) == -1)
		return (return_error(1, "minshell : fatal error", 0, 1));
	handle_signals();
	return_value = minishell_loop(&infos);
	clean_exit(&infos);
	return (return_value);
}

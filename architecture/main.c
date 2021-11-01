/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlichir < hlichir@student.42.fr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/23 14:58:07 by anadege           #+#    #+#             */
/*   Updated: 2021/11/01 15:26:49 by hlichir          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	g_exit_status = -1;

/*
** Function to free allocated memory to prepare the next loop.
** Set g_exit_status at -1 (initial state).
*/
void	clean_to_continue(t_infos *infos, int init_exit)
{
	if (init_exit && infos->mode == 0)
	{
		g_exit_status = -1;
		handle_signals(0);
	}
	if (infos->curr_cmd)
		free(infos->curr_cmd);
	if (infos->prompt)
		free(infos->prompt);
	if (infos->lst_cmds)
		free_cmd_list_from_extremity(&infos->lst_cmds, 0);
	if (infos->lst_tokens)
		free_token_list_from_extremity(&infos->lst_tokens, 0);
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

	if (!infos)
	{
		return_error(1, "something went wrong", 0, 0);
		return ;
	}
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
			return (return_error(1, "minishell : fatal error", 0, 1));
		infos->curr_cmd = readline(infos->prompt);
		if (check_for_signal(infos) < 0)
			return (return_error(1, "minishell : fatal error", 0, 1));
		else if (!infos->curr_cmd)
			break ;
		if (add_line_to_history(infos->fd_history, infos->curr_cmd, 0) < 0)
			return (return_error(1, "minishell : fatal error", 0, 1));
		if (!ft_strncmp(infos->curr_cmd, "exit", 5))
			break ;
		if (infos->curr_cmd[0] != 0)
			parse_and_execute(infos);
		if (modify_exit_value_variable(infos, g_exit_status) < 0)
			return (return_error(1, "minishell : fatal error", 0, 1));
		clean_to_continue(infos, 1);
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
	char	*str;
	int		return_value;
	int		mode;

	(void)argc;
	(void)argv;
	mode = check_mode();
	if (mode == -1 || init_minishell(&infos, env) == -1)
		return (return_error(1, "minishell : fatal error", 0, 1));
	handle_signals(0);
	if (mode == 0)
		return_value = minishell_loop(&infos);
	else
		return_value = non_interactive_minishell_loop(&infos);
	if (return_value == 0)
	{
		str = find_assignment(&infos, "?");
		if (!str)
			return (-1);
		return_value = ft_atoi(str);
	}
	if (clean_exit(&infos, 1) == -1)
		return (return_error(1, "minishell : fatal error", 0, 1));
	return (return_value);
}

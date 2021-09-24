/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anadege <anadege@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/23 15:55:23 by anadege           #+#    #+#             */
/*   Updated: 2021/09/24 14:31:24 by anadege          ###   ########.fr       */
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
# include <sys/stat.h>

# define PROMPT_MSG "\001\033[1;38;5;51m\002Prompt > \001\033[0m\002"

/*
** Use of one global variable to handle exit_status = 130 when ctrl+c is used
*/

int					g_exit_status;

/*
** Enum useful to check if the command line contains a built in.
*/
typedef enum e_builtin
{
	NONE,
	ECHO,
	CD,
	PWD,
	EXPORT,
	UNSET,
	ENV
}	t_builtin;

/*
** Enum useful to indicate the type of token.
*/
typedef enum e_tokentype
{
	IDENTIFIER,
	ASSIGNMENT,
	OPERATOR,
	STRING
}	t_tokentype;

/*
** TOKEN STRUCTURE
** Structure and doubly linked list to stock
** informations about tokens of a command line.
*/
typedef struct s_token
{
	char			*token;
	int				length;
	t_tokentype		type;
	struct s_token	*prev;
	struct s_token	*next;
}	t_token;

/*
** Enum to identify the operator following a simple command.
** LT (lesser than) = < LT_DBL = << GT (greater than) = > DT_DBL = >>
*/
typedef enum e_operator
{
	PIPE,
	LT,
	LT_DBL,
	GT,
	GT_DBL
}	t_operator;

/*
** SIMPLE COMMAND STRUCTURE
** Structure to identify and stock informations for each "simple" command
** (commands separated by operators).
*/
typedef struct s_cmd
{
	t_token			*start;
	t_token			*end;
	t_operator		next_operator;
	char			*input;
	char			*output;
	int				return_value;
	struct s_cmd	*prev;
	struct s_cmd	*next;
}	t_cmd;

/*
** SIMPLE LINKED LIST TO KEEP THE LIST OF ADDED VARIABLES
** When a variable is assigned without "export", the list is kept here.
*/
typedef struct s_var
{
	char			*name;
	char			*value;
	struct s_var	*next;
}	t_var;

/*
** MINISHELL INFORMATION STRUCTURE
*/
typedef struct s_infos
{
	char	*prompt;
	char	*curr_cmd;
	t_token	*lst_tokens;
	t_cmd	*lst_cmds;
	int		fd_history;
	char	**env;
	t_var	*lst_var;
}	t_infos;

/*
** FUNCTIONS INSIDE MAIN
*/
int			minishell_loop(t_infos *infos);
void		parse_and_execute(t_infos *infos);

/*
** PROMPT DISPLAY
** Set of function to display a "clean" prompt under the format :
** prompt_name > current_directory (with HOME replace by ~).
*/
void		simplify_prompt_curr_dir(char **prompt);
char		*get_curr_dir(int prompt);
char		*get_prompt(void);

/*
** HISTORY MANAGEMENT
** Set of function to recuperate the history of precedent calls of 
** minishell programm.
** History is stocked inside a file named minishell history.
** Each line of that file is added to readline when minishell is launched.
*/
int			get_previous_history(void);
void		add_line_to_history(int history_fd, char *str);

/*
** BUILT IN CD
** WARNING : Doesn't check if the path is correctly formated.
*/
int			change_directory(t_infos *infos, char *new_dir_path);
int			cmd_change_directory(t_infos *infos, t_cmd *cmd);

/*
** BUILT IN ECHO
** Receive the string "command" and it's size.
** Check for the option -n is made inside the built-in.
*/
int			echo_builtin(t_infos *infos, t_cmd *cmd);
int			echo_builtin_loop(t_infos *infos, t_cmd *cmd, t_token *tmp, int i);
int			check_n_option(t_token *first);
int			cmd_echo(t_infos *infos, t_cmd *cmd);

/*
** BUILT IN PWD
*/
int			show_current_dir(t_infos *infos, t_cmd *cmd);

/*
** BUILT IN ENV / EXPORT / UNSET
** Reminder : Call save_end at launch of minishell programm in order to
** stock environmentals variables.
** The function add_elem_to_env must be called when EXPORT is called IF
** the format is correct.
** The function show_env must be called when the built in ENV is called.
** The function delete_elem_from_env must be called when the built
** in UNSET is called.
*/
int			fill_env_with_deletion(char ***env, int elem_pos, int env_size);
int			delete_elem_from_env(char ***env, char *elem);
int			delete_elem_from_var_lst(t_var **var_lst, char *elem_name);
int			sub_unset_var(t_infos *infos, t_token *to_unset);
int			unset_var(t_infos *infos, t_cmd *cmd);
int			add_not_existing_elem_to_env(char ***env, t_token *new_elem,
				int env_size);
int			modify_existing_elem_to_env(t_infos *infos, char **env,
				t_token *new_elem, char *elem_name);
int			add_elem_to_env(t_infos *infos, t_cmd *cmd);
int			sub_add_elem_to_env(t_infos *infos, t_token *new_elem,
				int env_size, int *ptr_res);
char		*get_elem_name(char *elem, int size);
char		*get_env_elem(char **env, char *elem);
int			seek_elem_pos(char **env, char *elem_name);
int			show_env(t_infos *infos, t_cmd *cmd, int export);
int			show_env_for_export(t_infos *infos, t_cmd *cmd, char **env, int i);
void		free_env(char **env, int last);
int			save_env(t_infos *infos, char **env);

/*
** EXIT MANAGEMENT
** WARNING : Proper clean of all allocated memory to check before
** submitting project.
*/
int			set_g_status_to_error(int status);
int			error_exit_status(char *str, int str_is_alloc, t_infos *infos, char *new_status);
int			check_for_signal(t_infos *infos);
void		clean_to_continue(t_infos *infos);
int			clean_exit(t_infos *infos);
int			modify_exit_value_variable(t_infos *infos, int new_value);

/*
** MINISHELL INTIALIZATION
*/
int			init_minishell(t_infos *infos, char **env);

/*
** COMMAND LINE INTERPRETER
*/
t_builtin	check_builtin(char *first_elem_cmd_line);

/*
** TOKENIZER
*/
t_token		*tokenize_cmd(char *cmd, int *syntax_error, char **error_pos);
void		free_token_list_from_extremity(t_token *tokens, int end);
t_token		*init_new_token(t_token **tokens, char *cmd, int *syntax_error,
				char **error_pos);
int			browse_string(char *begin_token, char stop_char, int *syntax_error,
				char **error_pos);
int			browse_token(char *begin_token, int *syntax_error,
				char **error_pos);
t_tokentype	identify_token_type(char *token, int length);
int			check_operators_and_undefined_char(t_token *curr, t_token *prev,
				int *syntax_error, char **error_pos);
void		add_back_token(t_token **tokens, t_token *new);

/*
** PARSING
*/
int			parsing_error(int syntax_error, char *error_pos);
t_cmd		*separate_simple_cmd(t_infos *infos);
int			check_init_new_cmd(t_cmd **new, t_token *lst_tokens,
				t_cmd **lst_cmds, int *new_cmd);
t_cmd		*init_new_cmd(t_token *start, t_cmd **head_lst);
void		add_back_cmd(t_cmd **cmds, t_cmd *new);
t_operator	identify_operator(t_token *operator);
void		free_cmd_list_from_extremity(t_cmd *cmds, int end);
int			parse_cmd(t_infos *infos);

/*
** GET FILE FULL PATH
*/
char		*get_path(char *filepath, char **env);
char		*get_absolute_path(char *filepath, char **env, char in_home);
char		*get_absolute_path_from_path(char *filepath, char *env_var);
char		*reconstitute_absolute_path(char *env_var, char *filepath);
int			is_absolute_path(char *filepath);

/*
** CHECK FOR BUILTIN OR LAUNCH COMMAND
*/
int			launch_builtin(t_infos *infos, t_cmd *cmd, t_builtin builtin);
t_builtin	check_builtin(char *first_elem);

/*
** REPLACE VARIABLES
*/
void		expand_variables(t_infos *infos);
int			get_var(char *cmd, char **var, char **env, t_var *var_lst);
void		sub_get_var(char **var, char *elem_name,
				char **env, t_var *var_lst);
void		add_var(t_infos *infos, char **new_cmd, int *i, int *j);
void		get_cmd_with_var(t_infos *infos, int new_size);

/*
** SIGNALS HANDLER
*/
void		handle_signals(void);
void		sig_handler_function(int signum);

/*
** ASSIGNMENTS HANDLING
*/
int			do_assignment(t_infos *infos, t_token *token);
int			assign_variable_to_list(t_infos *infos, t_token *current_token);
int			add_new_var_to_list(t_infos *infos, char *str);
int			modify_var_in_list(t_infos *infos, char *str, int *check);
char		*get_elem_value(char *str);
int			free_lst_var(t_infos *infos);

/*
** LAUNCH
*/
int			launch_cmds(t_infos *infos);
int			check_if_pipes(t_infos *infos);
int			check_assignments(t_infos *infos, t_cmd *cmd);
int			is_only_assignments(t_cmd *cmd);
int			launch_simple_cmd(t_infos *infos);

/*
** SIMPLE COMMAND EXECUTION
*/
int			execute_simple_cmd(t_infos *infos);
char		*get_exec_path(t_infos *infos, t_cmd *cmd, char ***exec_env,
				t_token **exec_token);
t_token		*move_to_exec(t_infos *infos, t_cmd *cmd, char ***exec_env);
char		**get_exec_args(t_infos *infos, t_cmd *cmd, t_token *exec_token);
int			get_args_nbr(t_cmd *cmd, t_token *exec_token);

/*
** REDIRECTIONS
*/
int			check_redirections(t_infos *infos, t_cmd *cmd);
int			handle_multiple_redirections(t_infos *infos, t_cmd **cmd);
int			single_right_redirect(t_infos *infos, t_cmd *cmd);
int			double_right_redirect(t_infos *infos, t_cmd *cmd);
int			single_left_redirect(t_infos *infos, t_cmd *cmd, t_cmd *cmd_next);
int			double_left_redirect(t_infos *infos, t_cmd *cmd, t_cmd *cmd_next);
int			check_if_end(char **str, char *end, char c, int i);
int			extract_file(int fd, t_cmd *cmd);
char		*extract_name_in_string(t_cmd *cmd);

/*
** MANAGEMENT OF ENV FOR EXECUTION
*/
int			add_elem_to_exec_env(t_infos *infos, char ***exec_env,
				t_token *new_elem);
void		child_execution(t_infos *infos);
void		free_child_exec_var(t_infos *infos, char *exec_path,
				char **exec_env, char **exec_args);
int			get_exec_env_diff_size(t_infos *infos, t_cmd *cmd, int *modif);
int			copy_env(t_infos *infos, char **env, char ***cpy_env,
				int cpy_diff_size);

/*
** EXIT STATUS
*/
int			return_error(int exit_status, char *error_msg, int msg_is_alloc,
				int return_value);

#endif

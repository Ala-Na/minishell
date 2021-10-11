/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlichir < hlichir@student.42.fr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/23 15:55:23 by anadege           #+#    #+#             */
/*   Updated: 2021/10/11 22:54:09 by anadege          ###   ########.fr       */
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
	STRING,
	VARIABLE
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
	struct s_token	*linked_to_next;
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
	int				fd_input;
	int				fd_output;
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
void		clean_to_continue(t_infos *infos);

/*
** MINISHELL INTIALIZATION
*/
int			init_minishell(t_infos *infos, char **env);
void		init_variables(int *i1, int *i2);
int			add_new_shlvl(t_infos *infos, char *shlvl, char **env);
int			get_shell_nbr(char *str);

/*
** PROMPT DISPLAY
** Set of function to display a "clean" prompt under the format :
** prompt_name > current_directory (with HOME replace by ~).
*/
void		simplify_prompt_curr_dir(t_infos *infos, char **prompt);
char		*get_curr_dir(t_infos *infos, int prompt);
char		*get_prompt(t_infos *infos);

/*
** HISTORY MANAGEMENT
** Set of function to recuperate the history of precedent calls of 
** minishell programm.
** History is stocked inside a file named minishell history.
** Each line of that file is added to readline when minishell is launched.
*/
int			get_previous_history(void);
int			add_line_to_history(int history_fd, char *str);

/*
** HANDLING SIGNALS
** Set of functions
*/
void		handle_signals(void);
void		sig_handler_function(int signum);

/*
** BUILT IN CD
** WARNING : Doesn't check if the path is correctly formated.
*/
int			change_directory(t_infos *infos, char **new_path, int is_alloc);
int			cmd_change_directory(t_infos *infos, t_cmd *cmd, t_token *token);
int			modify_pwd(t_infos *infos, char *name, char *new_pwd, int is_old);

int			create_tmp_new_elem(t_token **new_elem, char *name, char *value, \
				char *str);
char		*check_oldpwd_cdpath(t_infos *infos, char **path, int *is_alloc);
int			handle_cd_path(char **env, char **path, int *is_alloc);

/*
** BUILT IN ECHO
** Receive the string "command" and it's size.
** Check for the option -n is made inside the built-in.
*/
int			cmd_echo(t_infos *infos, t_cmd *head_cmd,
				t_cmd *builtin_cmd, t_token *builtin_token);
int			echo_builtin_loop(t_infos *infos, t_cmd *head_cmd, t_cmd *cmd,
				t_token *token);
int			check_n_option(t_token *first);
void		skip_n_option(t_infos *infos, t_cmd **cmd, t_token **tmp);

/*
** BUILT IN PWD
*/
int			show_current_dir(t_infos *infos, t_cmd *cmd);

/*
** BUILT IN ENV
*/
int			show_env(t_infos *infos, t_cmd *cmd, t_token *builtin_token,
				int export);
int			show_env_for_export(t_infos *infos, t_cmd *cmd, char **env, int i);
int			show_env_loop(t_infos *infos, t_cmd *cmd, int fd, int export);
int			check_for_assignment(char *str);

void		free_env(char ***env, int last);
int			save_env(t_infos *infos, char **env);
char		*get_elem_name(t_token *elem);
char		*get_env_elem(char **env, char *elem, int elem_size);
void		get_elem_name_loop(t_token *elem, char **elem_name, int fill_str);

/*
** BUILT IN EXPORT
*/
int			add_elem_to_env(t_infos *infos, t_cmd *builtin_cmd,
				t_token *builtin_token, int env_size);
int			sub_add_elem_to_env(t_infos *infos, t_token *new_elem,
				int env_size, int *ptr_res);
int			add_not_existing_elem_to_env(char ***env, t_token *new_elem,
				int env_size);
int			modify_existing_elem_to_env(t_infos *infos, char **env,
				t_token *new_elem, char *elem_name);

int			seek_elem_pos(char **env, char *elem_name);
void		free_var(t_var **var);
int			check_validity_token(t_token **token, int is_export, int *res);
int			invalid_token(t_token **token, int is_export,
				int *res, char **to_free);

/*
** BUILT IN UNSET
*/
int			unset_var(t_infos *infos, t_cmd *head_cmd, t_token *builtin_token);
int			sub_unset_var(t_infos *infos, t_token *to_unset);
int			delete_elem_from_env(char ***env, char *elem);
int			delete_elem_from_var_lst(t_var **var_lst, char *elem_name);
int			fill_env_with_deletion(char ***env, int elem_pos, int env_size);

/*
** EXIT MANAGEMENT
** WARNING : Proper clean of all allocated memory to check before
** submitting project.
*/
int			check_for_signal(t_infos *infos);
int			modify_exit_value_variable(t_infos *infos, int new_value);

int			clean_exit(t_infos *infos);

int			return_error(int exit_status, char *error_msg, int msg_is_alloc,
				int return_value);
char		*return_null_error(int exit_status, char *error_msg, \
				int msg_is_alloc);
int			return_value(int exit_status);
int			return_signal(int signal_value);
void		return_pipeline(int last_child_status);

/*
** [ TO CLEAN BELOW ]
*/

/*
** COMMAND LINE INTERPRETER
*/
t_builtin	check_builtin(char *first_elem_cmd_line);

/*
** TOKENIZER
*/
t_token		*tokenize_cmd(char *cmd, int *syntax_error, char **error_pos);
void		free_token_list_from_extremity(t_token **tokens, int end);
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
void		strings_manipulation(t_token **tokens);

void		add_tokens_for_variables(t_token **tokens);
void		tokenize_variables(t_token **tokens, t_token **current, \
			t_token *new, int size);
int			set_parsing_error(char **error_pos, char *error, t_token **to_free);
int			check_variable_sign(char **cmd, int *i, int *check);

/*
** PARSING
*/
int			parsing_error(int syntax_error, char *error_pos);
t_cmd		*separate_simple_cmd(t_infos *infos, t_cmd *lst_cmds, int new_cmd);
void		token_identifier(t_token *lst_tokens, t_cmd **new, int *new_cmd);
int			check_init_new_cmd(t_cmd **new, t_token *lst_tokens,
				t_cmd **lst_cmds, int *new_cmd);
t_cmd		*init_new_cmd(t_token *start, t_cmd **head_lst);
void		add_back_cmd(t_cmd **cmds, t_cmd *new);
t_operator	identify_operator(t_token *operator);
void		free_cmd_list_from_extremity(t_cmd **cmds, int end);
int			parse_cmd(t_infos *infos);

/*
** STRING UTILS
*/
char		*ft_strdup_linked_string(t_token *token);
void		get_string_loop(t_token *elem, char **str, int fill_str, int i);

/*
** GET FILE FULL PATH
*/
char		*get_path(char *filepath, char **env);
char		*get_absolute_path(char *filepath, char **env, char in_home);
char		*get_absolute_path_from_path(char *filepath, char *env_var);
char		*reconstitute_absolute_path(char *env_var, char *filepath);
int			is_absolute_path(char *filepath);
int			check_path_for_exceptions(char *file);
int			print_file_type(char *file);

/*
** CHECK FOR BUILTIN OR LAUNCH COMMAND
*/
int			launch_builtin(t_infos *infos, t_cmd *cmd, t_builtin builtin);
t_builtin	check_builtin(char *first_elem);

/*
** REPLACE VARIABLES
*/
void		expand_variables(t_infos *infos, int dbl, int ignore, \
				int new_size);
int			get_var(t_infos *infos, char *cmd, char **var, int dbl);
void		sub_get_var(char **var, char *elem_name,
				char **env, t_var *var_lst);
void		add_var(t_infos *infos, char **new_cmd, int i[2], int dbl);
void		get_cmd_with_var(t_infos *infos, int new_size, int ignore, \
				int dbl);

void		expand_variable_for_home(t_infos *infos, int i, int *size, \
				char **var);
void		add_ignore_dbl(char cmd_char, int *ignore, int *dbl);
int			check_for_redir_exception(t_infos *infos, int *new_size,
				int exception, int i);
void		add_var_modify_string(char **new_cmd, char *var, int dbl, int i[2]);
int			get_var_exception(t_infos *infos, char **var, char *cmd, int *i);

char		*get_new_string_for_exception(char **cmd, int i);

/*
** ASSIGNMENTS HANDLING
*/
int			do_assignment(t_infos *infos, t_token *token);
int			assign_variable_to_list(t_infos *infos, t_token *current_token);

int			add_new_var_to_list(t_infos *infos, char *str);
int			add_name_value_to_var(t_var **new, char *str);
int			modify_var_in_list(t_infos *infos, char *str, int *check);
char		*get_elem_value(char *str);

char		*extract_name(char *elem, int size);
int			free_lst_var(t_infos *infos);

/*
** LAUNCH
*/
int			launch_cmds(t_infos *infos);
int			check_if_pipes(t_infos *infos);
int			check_assignments(t_infos *infos, t_cmd *head_cmd, t_cmd *cmd,
				t_token *first_non_redir);
int			is_only_assignments(t_infos *infos, t_cmd *cmd,
				t_token *first_non_redir);
int			init_launch_simple_cmd(t_infos *infos, t_cmd *cmd, int from_pipe);
int			launch_simple_cmd(t_infos *infos, t_cmd *cmd, t_token *exec_token,
				int from_pipe);
int			assignments_management(t_infos *infos, t_cmd *head_cmd, t_cmd *cmd, \
				t_token **exec_token);

/*
** SIMPLE COMMAND EXECUTION
*/
int			execute_simple_cmd(t_infos *infos);
char		*get_exec_path(t_infos *infos, t_cmd **cmd, char ***exec_env,
				t_token **exec_token);
t_token		*move_to_exec_and_fill_env(t_infos *infos, t_cmd **cmd,
				char ***exec_env);
int			return_free_args(char ***env, int i, int error_msg);
char		**get_exec_args(t_infos *infos, t_cmd *cmd, t_token *exec_token);
int			get_args_nbr(t_infos *infos, t_cmd *cmd, t_token *exec_token);
int			get_arg_loop(t_cmd **cmd, t_token **curr_token);
int			check_add_input(t_infos *infos, char ***exec_args, int nbr_args);
int			add_tmp_file_to_args(char ***exec_args);

/*
** REDIRECTIONS
*/

int			add_redirections(t_cmd *cmd, int is_not_builtin);
int			add_input(t_cmd **cmd, t_cmd *curr);
int			add_output(t_cmd **cmd, t_cmd *curr);
int			add_fd_to_cmd(t_cmd **cmd, int fd, int is_output, int is_tmpfile);
char		*extract_name_in_string(t_cmd *cmd, int *error);
int			file_error_input(char *filename, char **tmp);
int			check_file(char	*filename);
int			append_to_file(t_cmd *curr);
int			create_new_file(t_cmd *curr);
int			extract_input_from_stdin(t_cmd *curr, int fill_str);
int			create_tmp_file(char *end_str, char **str, int fill_str, int *fd);
int			fill_tmp_file(char **str, int fill_str, int *fd);
int			check_if_end(char **str, char *end, char c, int i);
int			get_fd(t_cmd *curr);
int			display_next_lt_dbl(t_cmd *cmd);

/*
** MANAGEMENT OF ENV FOR EXECUTION
*/
int			add_elem_to_exec_env(t_infos *infos, char ***exec_env,
				t_token *new_elem);
void		free_child_exec_var_and_exit(t_infos *infos, char **exec_path,
				char ***exec_env, char ***exec_args);
void		child_execution(t_infos *infos, t_cmd *exec_cmd);
int			get_exec_env_diff_size(t_infos *infos, t_cmd *cmd, int *modif);
int			copy_env(t_infos *infos, char **env, char ***cpy_env,
				int cpy_diff_size);
int			complete_exec_env_with_assignments(t_infos *infos,
				t_cmd *cmd, char ***exec_env);

/*
** PIPELINE
*/
int			launch_pipes_cmds(t_infos *infos, t_cmd *cmd, int nbr_pipes);
int			wait_for_pipeline_childs(int nbr_pipes, \
				pid_t **child_pids);
t_cmd		*get_next_cmd(t_cmd *cmd);

/*
** OBTAINING TOKENS
*/
t_token		*get_next_token(t_infos *infos, t_cmd *head_cmd,
				t_cmd **prev_cmd, t_token *prev_token);
t_token		*check_prev_token(t_token *prev_token, t_cmd **prev_cmd);
int			get_next_token_loop(t_cmd **cmd, t_token **token);
int			check_if_end_pipeline(t_cmd *cmd, t_token *token);
t_token		*get_exec_token(t_infos *infos, t_cmd *head_cmd, t_cmd **exec_cmd);

#endif

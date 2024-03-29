/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlichir < hlichir@student.42.fr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/23 15:55:23 by anadege           #+#    #+#             */
/*   Updated: 2021/11/01 16:09:49 by hlichir          ###   ########.fr       */
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

# define PROMPT_MSG "\001\033[1;38;5;51m\002Minishell > \001\033[0m\002"

# define WRITE_SIDE 1
# define READ_SIDE 0
# define FD_UNSET -1

/*
** Use of one global variable to handle exit_status = 130 when ctrl+c is used
*/
extern int					g_exit_status;

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
	ENV,
	EXIT
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
	int				nb_tmp_file;
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
	int		mode;
	char	*prompt;
	char	*curr_cmd;
	t_token	*lst_tokens;
	t_cmd	*lst_cmds;
	int		fd_history;
	int		pipe_read_side;
	int		pipe_write_side;
	char	**env;
	t_var	*lst_var;
}	t_infos;

/*
** FUNCTIONS INSIDE MAIN
*/
int			minishell_loop(t_infos *infos);
void		parse_and_execute(t_infos *infos);
void		clean_to_continue(t_infos *infos, int init_exit);

/*
** ALTERNATIVE NON INTERACTIVE MODE
*/
int			check_mode(void);
int			non_interactive_minishell_loop(t_infos *infos);
void		exit_non_interactive(int signum);

/*
** MINISHELL INTIALIZATION
*/
int			init_minishell(t_infos *infos, char **env);
void		init_variables(int *i1, int *i2, int value);
int			add_new_shlvl(t_infos *infos, char *shlvl, char **env, int nb);
int			get_shell_nbr(char *str);

/*
** PROMPT DISPLAY
** Set of function to display a "clean" prompt under the format :
** prompt_name > current_directory (with HOME replace by ~).
*/
void		simplify_prompt_curr_dir(t_infos *infos, char **prompt);
int			loop_to_getcwd(char **res, char **buffer_dir, \
				size_t *size_buffer_dir);
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
int			add_line_to_history(int history_fd, char *str, int exit);

/*
** HANDLING SIGNALS
*/
void		handle_signals(int is_child);
void		sig_handler_function(int signum);

/*
** HANDLING SIGNALS IN CHILD
*/
void		ignore_signals(t_infos *infos);
void		restore_signals(t_infos *infos);

/*
** BUILT IN CD
*/
int			change_directory(t_infos *infos, t_cmd *cmd, char **new_path,
				int is_alloc);
int			cmd_change_directory(t_infos *infos, t_cmd *cmd, t_cmd *head,
				t_token *token);
int			modify_pwd(t_infos *infos, t_cmd *cmd, char *new_pwd, int is_old);
int			modify_old_pwd(t_infos *infos, char *new_pwd);
int			call_chdir(t_infos *infos, char **new_path, int *is_alloc,
				char **old_path);

int			create_tmp_new_elem(t_token **new_elem, char *name, char *value, \
				char *str);
char		*check_oldpwd_cdpath(t_infos *infos, char **path, int *is_alloc);
int			handle_cd_path(char **env, char **path, int *is_alloc);
int			check_if_valid_cdpath(char *cdpath, char **path, int *is_alloc);
void		check_if_currdir_exist(t_infos *infos, char **tmp_path,
				char *old_path, char *new_path);

char		*get_correct_cdpath(char *cdpath);
int			go_to_home(t_infos *infos, t_cmd *cmd);

/*
** BUILT IN ECHO
*/
int			cmd_echo(t_infos *infos, t_cmd *head_cmd,
				t_cmd *builtin_cmd, t_token *builtin_token);
int			echo_builtin_loop(t_infos *infos, t_cmd *head_cmd, t_cmd *cmd,
				t_token *token);
int			check_n_option(t_token *first);
void		skip_n_option(t_infos *infos, t_cmd **cmd, t_token **tmp);
int			return_n_option(char **str, int return_value);

/*
** BUILT IN PWD
*/
int			show_current_dir(t_infos *infos, t_cmd *cmd);
char		*get_str_pwd(t_infos *infos);

/*
** BUILT IN ENV
*/
int			show_env(t_infos *infos, t_cmd *cmd, t_token *builtin_token,
				int export);
int			show_env_for_export(t_infos *infos, t_cmd *cmd, char **env, int i);
int			show_env_loop(t_infos *infos, t_cmd *cmd, int fd, int export);
int			check_for_assignment(char *str);
int			save_env(t_infos *infos, char **env);

void		free_env(char ***env, int last);
char		*get_elem_name(t_token *elem);
char		*get_env_elem(char **env, char *elem, int elem_size);
void		get_elem_name_loop(t_token *elem, char **elem_name, int fill_str);
void		set_value_for_get_env_elem(char *env_elem, int elem_size, \
				char **value);

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
int			return_valid_token(char **to_free);

/*
** BUILT IN UNSET
*/
int			unset_var(t_infos *infos, t_cmd *head_cmd, t_token *builtin_token);
int			sub_unset_var(t_infos *infos, t_token *to_unset);
int			delete_elem_from_env(char ***env, char *elem);
int			delete_elem_from_var_lst(t_var **var_lst, char *elem_name);
int			fill_env_with_deletion(char ***env, int elem_pos, int env_size);

/*
** BUILT IN EXIT 
*/
int			exit_builtin(t_infos *infos, t_cmd *cmd, t_token *token);
int			get_exit_value(t_token *token_value);
int			print_non_numeric_error(char **str_value);

/*
** EXIT MANAGEMENT
** WARNING : Proper clean of all allocated memory to check before
** submitting project.
*/
int			check_for_signal(t_infos *infos);
int			modify_exit_value_variable(t_infos *infos, int new_value);

int			clean_exit(t_infos *infos, int init_exit);

int			return_error(int exit_status, char *error_msg, char **alloc_msg,
				int return_value);
char		*return_null_error(int exit_status, char *error_msg, \
				char **alloc_msg);
int			return_value(int exit_status);
int			return_signal(int signal_value);
void		return_pipeline(int last_child_status);

/*
** TOKENIZER
*/
t_token		*tokenize_cmd(char *cmd, int *syntax_error, char **error_pos);
int			browse_string(char *begin_token, char stop_char, int *syntax_error,
				char **error_pos);
int			browse_token(char *begin_token, int *syntax_error,
				char **error_pos);
int			check_operators_and_undefined_char(t_token *curr, t_token *prev,
				int *syntax_error, char **error_pos);
t_token		*check_cmd_extremity_is_not_operator(t_token **tokens,
				int *syntax_error, char **error_pos);

void		add_back_token(t_token **tokens, t_token *new);
t_tokentype	identify_token_type(char *token, int length);
t_token		*init_new_token(t_token **tokens, char *cmd, int *syntax_error,
				char **error_pos);
void		free_token_list_from_extremity(t_token **tokens, int end);
void		strings_manipulation(t_token **tokens);

void		add_tokens_for_variables(t_token **tokens, t_token *new);
void		separate_var_for_tokenization(t_token **start, t_token **cur,
				t_token *new, int size);
void		tokenize_variables(t_token **tokens, t_token **current,
				t_token *new, int size);
int			set_parsing_error(char **error_pos, char *error, t_token **to_free);
void		change_token_as_string(t_token **string_token);

int			check_for_heredoc_exception(t_infos *infos, int *new_size,
				int check, int i);
int			modify_cmd_for_heredoc(char **cmd, int *i, int *check);
int			check_if_within_quotes(char **cmd, int *i);
char		*split_string_for_heredoc(char **cmd, int i, int size, char quote);
char		*get_new_string_for_exception(char **cmd, int *i, int size,
				int tmp_i);

/*
** PARSING
*/
int			parse_cmd(t_infos *infos);
int			init_empty_cmd(t_cmd **new, t_token **lst_tokens);
int			check_init_new_cmd(t_cmd **new, t_token *lst_tokens,
				t_cmd **lst_cmds, int *new_cmd);
void		token_identifier(t_token *lst_tokens, t_cmd **new, int *new_cmd);
t_cmd		*separate_simple_cmd(t_infos *infos, t_cmd *lst_cmds, int new_cmd);

int			parsing_error(int syntax_error, char *error_pos);
t_cmd		*init_new_cmd(t_token *start, t_cmd **head_lst);
void		add_back_cmd(t_cmd **cmds, t_cmd *new);
t_operator	identify_operator(t_token *operator);
void		free_cmd_list_from_extremity(t_cmd **cmds, int end);

/*
** VARIABLES AND STRINGS UTILITARY FUNCTIONS
*/
void		sub_get_var(char **var, char **elem_name,
				char **env, t_var *var_lst);
int			get_var(t_infos *infos, int start, char **var, int dbl);
void		add_var(t_infos *infos, char **new_cmd, int i[2], int dbl);
void		get_cmd_with_var(t_infos *infos, int new_size, int ignore, \
				int dbl);
void		expand_variables(t_infos *infos, int dbl, int ignore, \
				int new_size);

void		expand_variable_for_home(t_infos *infos, int i, int *size, \
				char **var);
void		add_ignore_dbl(char cmd_char, int *ignore, int *dbl);
void		add_var_modify_string(char **new_cmd, char *var, int dbl, int i[2]);
int			get_var_exception(t_infos *infos, char **var, char *cmd, int *i);

void		skip_empty_var(t_token **tokens);
void		skip_empty_var_in_middle(t_token **tokens, t_token **curr,
				t_token **next);
void		skip_empty_var_at_end(t_token **tokens, t_token **curr);
int			is_empty_var(char *var);
int			set_and_return_size_var(char **var, char *value, int size);

char		*ft_strdup_linked_string(t_token *token);
void		get_string_loop(t_token *elem, char **str, int fill_str, int i);
void		print_error(char *str, char *s, char c, int new_line);
void		modify_var_if_empty(char **var, char **elem_name, int elem_size);

int			return_diff_size(char *var, int dbl, int i);
int			size_var_if_var(char *var, int nbr_var);
int			check_var_in_var(char *var);
void		var_in_var(char **new_cmd, int *i, int *k);
void		add_var_symbol(char **new_cmd, char *var, int var_size, int *i);

/*
** GET FILE FULL PATH
*/
char		*get_path(t_infos *infos, char **filepath, char **env);
char		*get_absolute_path(char *filepath, char **env, char in_home);
char		*get_absolute_path_from_path(char *filepath, char *env_var);
char		*reconstitute_absolute_path(char *env_var, char *filepath);
int			is_absolute_path(char *filepath);

int			check_path_for_exceptions(t_infos *infos, char **file);
int			print_file_type(char *file);

/*
** CHECK FOR BUILTIN OR LAUNCH COMMAND
*/
int			launch_builtin(t_infos *infos, t_cmd *cmd, t_builtin builtin);
int			sub_launch_builtin(t_infos *infos, t_cmd *cmd,
				t_token *builtin_token, t_builtin builtin);
t_builtin	check_builtin(char *first_elem);

/*
** ASSIGNMENTS HANDLING
*/
int			assign_variable_to_list(t_infos *infos, t_token *current_token);
int			add_new_var_to_list(t_infos *infos, char *str);
int			add_name_value_to_var(t_var **new, char *str);
int			modify_var_in_list(t_infos *infos, char *str, int *check);
char		*get_elem_value(char *str);

char		*extract_name(char *elem, int size);
int			free_lst_var(t_infos *infos);
char		*extract_value(char *elem, int size);

int			check_assignments(t_infos *infos, t_cmd *head_cmd, t_cmd *cmd,
				t_token *first_non_redir);
int			is_only_assignments(t_infos *infos, t_cmd *cmd,
				t_token *first_non_redir);
int			do_assignment(t_infos *infos, t_token *token);
char		*find_assignment(t_infos *infos, char *var_name);

/*
** LAUNCH
*/
int			launch_cmds(t_infos *infos);
int			check_if_pipes(t_infos *infos);
int			init_launch_simple_cmd(t_infos *infos, t_cmd *cmd, int from_pipe);
int			launch_simple_cmd(t_infos *infos, t_cmd *cmd, t_token *exec_token,
				int from_pipe);
int			assignments_management(t_infos *infos, t_cmd *head_cmd, t_cmd *cmd, \
				t_token **exec_token);

/*
** SIMPLE COMMAND EXECUTION
*/
int			execute_simple_cmd(t_infos *infos);
void		child_execution(t_infos *infos, t_cmd *head_cmd, char *exec_path);
void		free_child_exec_var_and_exit(t_infos *infos, char **exec_path,
				char ***exec_env, char ***exec_args);

char		*get_exec_path(t_infos *infos, t_cmd **cmd, char ***exec_env,
				t_token **exec_token);
char		**get_exec_args(t_infos *infos, t_cmd *cmd, t_token *exec_token);
int			sub_get_args(t_infos *infos, t_cmd *exec_cmd, t_token *exec_token,
				char ***exec_args);

t_token		*move_to_exec_and_fill_env(t_infos *infos, t_cmd **cmd,
				char ***exec_env);
int			get_args_nbr(t_infos *infos, t_cmd *cmd, t_token *exec_token);

int			add_elem_to_exec_env(t_infos *infos, char ***exec_env,
				t_token *new_elem);
int			get_exec_env_diff_size(t_infos *infos, t_cmd *cmd, int *modif);
int			copy_env(t_infos *infos, char **env, char ***cpy_env,
				int cpy_diff_size);
int			complete_exec_env_with_assignments(t_infos *infos,
				t_cmd *cmd, char ***exec_env);

/*
** REDIRECTIONS
*/

int			add_redirections(t_infos *infos, t_cmd *cmd);
int			dup_redirections(t_infos *infos, t_cmd *cmd);
int			add_input(t_infos *infos, t_cmd **cmd, t_cmd *curr);
int			add_output(t_cmd **cmd, t_cmd *curr);
int			add_input_fd_to_cmd(t_cmd **cmd, int fd, int is_tmpfile);

int			append_to_file(t_cmd *curr, int fd);
int			create_new_file(t_cmd *curr);
int			add_output_fd_to_cmd(t_cmd **cmd, int fd);
int			return_and_display_open_error(char **filename, int free_filename);

int			extract_input_from_stdin(t_infos *infos, t_cmd *curr);
int			create_tmp_file(int nbr_tmp_file, char **tmp_file_name);
int			get_fd(t_infos *infos, t_cmd *curr);
int			display_next_lt_dbl(t_infos *infos, t_cmd *cmd);
int			fork_for_input(t_infos *infos, char *end_str, int fd);

char		*extract_name_in_string(t_cmd *cmd, int *error);
int			file_error_input(char *filename, char **tmp);
int			check_file(char	*filename);
int			check_end_or_fill_tmp_file(char **str, char *end, int fd);
char		*get_tmp_file_name(int nbr_tmp_file);

void		handle_signal_in_input(int signum, int *fd);
void		extract_child(t_infos *infos, int fd, char *end_str);
int			free_end_str_return(char **end_str, int result);
int			check_if_end(char **str, char *end_str, int fd);
int			check_input_signal(void);

int			expand_variable_to_heredoc(t_infos *infos, int fd,
				t_cmd *cmd_end_str, char *tmp_file_name);
int			check_if_string(t_cmd *cmd_end_str);
char		*extract_content_from_file(int fd, char *tmp_file_name);
void		get_new_content_size(t_infos *infos, char **new, char *old);
void		get_new_content(t_infos *infos, char **new, char *old);

int			get_new_var_size(t_infos *infos, char *start_var);
char		*get_new_value(t_infos *infos, char *old);
void		add_variable_to_new(t_infos *infos, char **new, int size,
				char *start_var);
char		*check_list_var(t_var *lstvar, char **name);
int			add_new_line_in_content(char **content, char **tmp_str, int fd);

/*
** PIPELINE MANAGEMENT
*/
int			launch_pipes_cmds(t_infos *infos, t_cmd *cmd, int nbr_pipes);
int			pipe_loop(t_infos *infos, t_cmd *cmd, int **child_pids, int i);
int			pipe_parent_fd_manipulation(t_cmd *cmd, int pipe_fd[2],
				int (*prev_fd)[2]);
void		pipe_child_execution(t_infos *infos, t_cmd *cmd, int pipe_fd[2],
				int prev_fd[2]);
int			last_close(int pipe_fd[2]);

int			wait_for_pipeline_childs(int nbr_pipes, \
				pid_t **child_pids);
t_cmd		*get_next_cmd(t_cmd *cmd);
void		close_and_duplicate_pipe_fd(int pipe_fd[2]);
int			free_child_pids(pid_t **child_pids);
void		close_pipe_fds(t_infos *infos);

/*
** TOKENS MANIPULATION
*/
t_token		*get_next_token(t_infos *infos, t_cmd *head_cmd,
				t_cmd **prev_cmd, t_token *prev_token);
int			check_if_first_call(t_cmd *head_cmd, t_cmd **prev_cmd,
				t_token **curr_token);
int			get_next_token_loop(t_cmd **cmd, t_token **token);
int			check_if_end_pipeline(t_cmd *cmd, t_token *token);
t_token		*get_exec_token(t_infos *infos, t_cmd *head_cmd,
				t_cmd **exec_cmd);

t_token		*check_prev_token(t_token *prev_token, t_cmd **prev_cmd);

#endif

# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: hlichir <hlichir@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/08/23 15:04:29 by anadege           #+#    #+#              #
#    Updated: 2021/10/21 16:35:39 by anadege          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell

CC = cc
CFLAGS = -Wall -Wextra -Werror -g -MMD
LIB_FLAGS = -L libft -lft -lreadline

SRCS_DIR = .
SRCS = 									\
		  $(SUB_SRCS_ARCHITECTURE)		\
		  $(SUB_SRCS_BUILTINS)			\
		  $(SUB_SRCS_EXIT)				\
		  $(SUB_SRCS_EXEC)				\
		  $(SUB_SRCS_PARSING)			\
		  $(SUB_SRCS_FLOW_MANAGEMENT)

SUB_SRCS_ARCHITECTURE = 				\
		  main.c						\
		  init.c						\
		  prompt.c						\
		  signals.c						\
		  history.c						\
		  check_mode.c

SUB_SRCS_BUILTINS =						\
		   cd.c							\
		   cd_utils.c					\
		   env.c						\
		   export.c						\
		   export_utils.c				\
		   unset.c						\
		   echo.c						\
		   env_utils.c					\
		   pwd.c						\
		   exit_builtin.c

SUB_SRCS_EXIT =							\
		   exit.c 						\
		   exit_status.c 				\
		   returns.c

SUB_SRCS_PARSING = 					\
		  parsing.c					\
		  tokenizer.c				\
		  get_variables.c			\
		  get_var_utils.c			\
		  tokenizer_utils.c			\
		  tokenize_var.c			\
		  parsing_utils.c			\
		  string_utils.c			\
		  var_in_var.c				\
		  empty_var.c			 	\
		  heredoc_parsing.c		

SUB_SRCS_EXEC =						\
		  assignment.c				\
		  check_assignments.c		\
		  assignment_utils.c		\
		  exec_cmd.c				\
		  seek_bin.c				\
		  launch_cmds.c				\
		  check_builtin.c			\
		  set_env_exec.c			\
		  get_cmd_args.c			\
		  exec_pipe.c				\
		  skip_redir.c				\
		  skip_redir_utils.c		\
		  exception_cmd.c			\
		  get_args_utils.c			\
		  exec_pipe_utils.c

SUB_SRCS_FLOW_MANAGEMENT =			\
		  redirections.c			\
		  file_utils.c				\
		  input_utils.c				\
		  output_utils.c			\
		  fork_utils.c				\
		  heredoc_var.c				\
		  heredoc_utils.c

OBJS = $(SRCS:%.c=$(OBJS_DIR)/%.o)
OBJS_DIR = .objs

DEPS = $(OBJS:%.o=%.d)

MAKE = make
MAKE_DIR = mkdir -p

all:		$(NAME) libft

$(NAME):	$(OBJS) libft
			$(CC) $(CFLAGS) $(OBJS) -o $(NAME) $(LIB_FLAGS)

-include $(DEPS)
$(OBJS_DIR)/%.o: %.c | $(OBJS_DIR)
			$(CC) $(CFLAGS) -c $< -o $@

$(OBJS_DIR):
			$(MAKE_DIR) $@

libft:
			$(MAKE) -C libft

clean:
			@$(MAKE) $@ -C libft
			@rm -rf $(OBJS_DIR)

fclean: 	clean
			@rm -f $(NAME)

re:			fclean all

.PHONY: all clean re

vpath %.c ./architecture ./builtins ./exec ./exit ./flow_management ./parsing
vpath %.h . ./libft
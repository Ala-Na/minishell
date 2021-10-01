# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: hlichir < hlichir@student.42.fr>           +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/08/23 15:04:29 by anadege           #+#    #+#              #
#    Updated: 2021/09/30 20:59:30 by anadege          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRCS	= ./main.c \
		  ./init.c \
		  ./prompt.c \
		  ./signals.c \
		  ./history/history.c \
		  ./builtins/cd.c \
		  ./builtins/env.c \
		  ./builtins/export.c \
		  ./builtins/unset.c \
		  ./builtins/unset_utils.c \
		  ./builtins/echo.c \
		  ./builtins/env_utils.c \
		  ./builtins/pwd.c \
		  ./exit/exit.c \
		  ./exit/exit_status.c \
		  ./exit/returns.c \
		  ./parsing/parsing.c \
		  ./parsing/tokenizer.c \
		  ./parsing/get_variables.c \
		  ./parsing/tokenizer_utils.c \
		  ./parsing/parsing_utils.c \
		  ./exec/assignment.c \
		  ./exec/exec_cmd.c \
		  ./exec/seek_bin.c \
		  ./exec/check_assignments.c \
		  ./exec/launch_cmds.c \
		  ./exec/check_builtin.c \
		  ./exec/set_env_exec.c \
		  ./exec/get_cmd_args.c \
		  ./exec/exec_pipe.c \
		  ./flow_management/redirections.c \
		  ./flow_management/file_utils.c \
		  ./flow_management/input_utils.c \
		  ./flow_management/output_utils.c \
		  ./exec/get_args_utils.c \
		  ./exec/exec_pipe_utils.c 

NAME = minishell

CC	= cc

CFLAGS	= -Wall -Wextra -Werror -g

OBJS	= ${SRCS:.c=.o}

LIB		= -L libft -lft -lreadline

%.o: %.c
			${CC} -g -o $@ -c $<

all:		${NAME}

${NAME}:	${OBJS}
			make -C libft
			${CC} ${CFLAGS} -o ${NAME} ${OBJS} ${LIB}

clean:
			@rm -f ${OBJS}

fclean: 	clean
			@rm -f ${NAME}

re:			fclean all

.PHONY: all clean re

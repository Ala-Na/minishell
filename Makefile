# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: anadege <anadege@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/08/23 15:04:29 by anadege           #+#    #+#              #
#    Updated: 2021/09/24 14:32:18 by anadege          ###   ########.fr        #
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
		  ./builtins/echo.c \
		  ./builtins/env_utils.c \
		  ./builtins/pwd.c \
		  ./exit/exit.c \
		  ./exit/exit_status.c \
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
		  ./flow_management/right_redirections.c \
		  ./flow_management/left_redirections.c \
		  ./flow_management/redirections.c 

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
			@rm -f ${OBJS}

clean:
			@rm -f ${OBJS}

fclean: 	clean
			@rm -f ${NAME}

re:			fclean all

.PHONY: all clean re

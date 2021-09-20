# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: hlichir <hlichir@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/08/23 15:04:29 by anadege           #+#    #+#              #
#    Updated: 2021/09/20 15:34:24 by anadege          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRCS	= ./main.c \
		  ./history/history.c \
		  ./prompt.c \
		  ./builtins/cd.c \
		  ./builtins/env.c \
		  ./builtins/export.c \
		  ./builtins/unset.c \
		  ./builtins/echo.c \
		  ./builtins/check_builtin.c \
		  ./builtins/env_utils.c \
		  ./builtins/pwd.c \
		  ./exit.c \
		  ./init.c \
		  ./parsing/parsing.c \
		  ./parsing/tokenizer.c \
		  ./parsing/get_variables.c \
		  ./parsing/tokenizer_utils.c \
		  ./parsing/parsing_utils.c \
		  ./parsing/assignment.c \
		  ./parsing/assignment_complementary.c \
		  ./exec/exec_cmd.c \
		  ./exec/seek_bin.c \
		  ./exec/set_env_exec.c \
		  ./signals.c

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


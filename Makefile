# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: hlichir <hlichir@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/08/23 15:04:29 by anadege           #+#    #+#              #
#    Updated: 2021/09/15 17:50:11 by anadege          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRCS	= ./main.c \
		  ./built-in/cd.c \
		  ./history.c \
		  ./prompt.c \
		  ./built-in/env.c \
		  ./built-in/export.c \
		  ./built-in/unset.c \
		  ./built-in/echo.c \
		  ./built-in/check_builtin.c \
		  ./built-in/env_utils.c \
		  ./built-in/pwd.c \
		  ./exit.c \
		  ./init.c \
		  ./parsing/parsing.c \
		  ./parsing/tokenizer.c \
		  ./parsing/get_variables.c \
		  ./parsing/tokenizer_utils.c \
		  ./parsing/parsing_utils.c \
		  ./parsing/assignment.c \
		  ./parsing/before_assignment.c \
		  ./exec/exec_cmd.c \
		  ./exec/seek_bin.c \
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


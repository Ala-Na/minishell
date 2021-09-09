# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: hlichir <hlichir@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/08/23 15:04:29 by anadege           #+#    #+#              #
#    Updated: 2021/09/09 17:32:15 by anadege          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRCS	= ./main.c \
		  ./built-in/cd.c \
		  ./history.c \
		  ./prompt.c \
		  ./built-in/env.c \
		  ./built-in/export.c \
		  ./built-in/unset.c \
		  ./exit.c \
		  ./init.c \
		  ./built-in/check_builtin.c \
		  ./parsing/parsing.c \
		  ./parsing/tokenizer.c \
		  ./parsing/tokenizer_utils.c \
		  ./built-in/echo.c \
		  ./exec/seek_bin.c

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


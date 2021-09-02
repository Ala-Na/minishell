# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: anadege <anadege@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/08/23 15:04:29 by anadege           #+#    #+#              #
#    Updated: 2021/09/02 12:03:09 by anadege          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRCS	= ./main.c \
		  ./cd.c \
		  ./history.c \
		  ./prompt.c \
		  ./env.c \
		  ./export.c \
		  ./unset.c \
		  ./exit.c \
		  ./init.c


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


# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: anadege <anadege@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/08/23 15:04:29 by anadege           #+#    #+#              #
#    Updated: 2021/08/30 17:26:44 by anadege          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRCS	= ./main.c \
		  ./cd.c \
		  ./history.c \
		  ./prompt.c

NAME = minishell

CC	= cc

CFLAGS	= -Wall -Wextra -Werror

OBJS	= ${SRCS:.c=.o}

LIB		= -L libft -lft -lreadline

%.o: %.c
			${CC} -o $@ -c $<

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


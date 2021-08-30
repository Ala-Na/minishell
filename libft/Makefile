# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: anadege <marvin@42.fr>                     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/05/26 11:25:33 by anadege           #+#    #+#              #
#    Updated: 2021/06/22 15:30:48 by elanna           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libft

CC = gcc

SRC = ./ft_atoi.c ./ft_bzero.c ./ft_calloc.c \
./ft_isalnum.c ./ft_isalpha.c ./ft_isascii.c \
./ft_isdigit.c ./ft_isprint.c ./ft_itoa.c \
./ft_memccpy.c ./ft_memchr.c ./ft_memcmp.c \
./ft_memcpy.c ./ft_memmove.c ./ft_memset.c \
./ft_putchar_fd.c ./ft_putendl_fd.c \
./ft_putnbr_fd.c ./ft_putstr_fd.c ./ft_split.c \
./ft_strchr.c ./ft_strdup.c ./ft_strjoin.c \
./ft_strlcat.c ./ft_strlcpy.c ./ft_strlen.c \
./ft_strmapi.c ./ft_strncmp.c ./ft_strnstr.c \
./ft_strrchr.c ./ft_strtrim.c ./ft_substr.c \
./ft_tolower.c  ./ft_toupper.c \
./ft_lstadd_back.c  ./ft_lstadd_front.c \
./ft_lstclear.c ./ft_lstdelone.c ./ft_lstiter.c \
./ft_lstlast.c ./ft_lstmap.c ./ft_lstnew.c \
./ft_lstsize.c ./ft_strtrim_ult_bonus.c \
./get_next_line_bonus.c ./get_next_line_utils_bonus.c \
./ft_bintodec_bonus.c ./ft_putchar_bonus.c \
./ft_pow_bonus.c .//ft_uitoa_bonus.c \
./ft_uitobase_bonus.c ./ft_hexaddr_bonus.c \
./ft_llitoa_bonus.c ./ft_ullitoa_bonus.c \
./ft_dtoa_exp_bonus.c ./ft_dtoa_frac_bonus.c \
./ft_dtoa_ope_bonus.c ./ft_dtoa_rounding_bonus.c \
./ft_dtoa_shortrep_bonus.c ./ft_ullitobase_bonus.c \
./ft_dtoa_shortrep_utils_bonus.c ./ft_print_bin_rep_bonus.c \
./ft_dtoa_utils_bonus.c ./ft_dtoa_bonus.c \
./ft_ishexa_bonus.c ./ft_putlenstr_fd_bonus.c \
./ft_putwstr_fd_bonus.c ./ft_wcrtomb_bonus.c \
./ft_putlenwstr_fd.c ./ft_isnumber.c ./ft_isprintable.c


HEADER = 		../includes

CFLAGS = 		-Wall -Wextra -Werror

OBJ = 			$(SRC:.c=.o)

%.o: %.c
				$(CC) $(CFLAGS) -c $< -o $(<:.c=.o) -I $(HEADER)

$(NAME).a :		$(OBJ)
				ar rcs $(NAME).a $(OBJ)

all :			$(NAME).a

clean :
				rm -f $(OBJ)

fclean :		clean
				rm -f $(NAME).a

re :			fclean all


.PHONY: $(NAME) bonus all clean fclean re


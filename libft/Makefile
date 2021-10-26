# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: hlichir <hlichir@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/05/26 11:25:33 by anadege           #+#    #+#              #
#    Updated: 2021/10/26 15:38:53 by anadege          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libft.a

CC = gcc
# -MMD flag allow to recompile if an header is modified
CFLAGS = -Wall -Wextra -Werror -MMD -I$(HEADER_DIR)

SRCS = 								\
		  $(SUB_SRCS_CHAR_UTILS)	\
		  $(SUB_SRCS_CONV)			\
		  $(SUB_SRCS_FILES_UTILS)	\
		  $(SUB_SRCS_IDS)			\
		  $(SUB_SRCS_LST)			\
		  $(SUB_SRCS_MATHS)			\
		  $(SUB_SRCS_MEM)			\
		  $(SUB_SRCS_PRINT)			\
		  $(SUB_SRCS_STR_UTILS)

SUB_SRCS_CHAR_UTILS =				\
		  ft_tolower.c				\
		  ft_toupper.c

SUB_SRCS_CONV =						\
		  ft_atoi.c					\
		  ft_dtoa.c					\
		  ft_dtoa_exp.c				\
		  ft_dtoa_frac.c			\
		  ft_dtoa_ope.c				\
		  ft_dtoa_rounding.c		\
		  ft_dtoa_shortrep.c		\
		  ft_dtoa_shortrep_utils.c	\
		  ft_dtoa_utils.c			\
		  ft_itoa.c					\
		  ft_hex_addr.c				\
		  ft_llitoa.c				\
		  ft_uitoa.c				\
		  ft_uitobase.c				\
		  ft_ullitoa.c				\
		  ft_ullitobase.c			\
		  ft_wcrtomb.c

SUB_SRCS_FILES_UTILS =				\
		  get_next_line.c			\
		  get_next_line_utils.c

SUB_SRCS_IDS =						\
		  ft_isalnum.c				\
		  ft_isalpha.c				\
		  ft_isascii.c				\
		  ft_isblank.c				\
		  ft_isblanks.c				\
		  ft_isdigit.c				\
		  ft_ishexa.c				\
		  ft_isnumber.c				\
		  ft_isprint.c				\
		  ft_isprintable.c			\
		  ft_iswhitespace.c

SUB_SRCS_LST =						\
		  ft_lstadd_back.c			\
		  ft_lstadd_front.c			\
		  ft_lstclear.c				\
		  ft_lstdelone.c			\
		  ft_lstiter.c				\
		  ft_lstlast.c				\
		  ft_lstmap.c				\
		  ft_lstnew.c				\
		  ft_lstsize.c

SUB_SRCS_MATHS =					\
		  ft_bintodec.c 			\
		  ft_max.c 					\
		  ft_pow.c

SUB_SRCS_MEM =						\
		  ft_bzero.c 				\
		  ft_calloc.c 				\
		  ft_memccpy.c 				\
		  ft_memcpy.c 				\
		  ft_memchr.c				\
		  ft_memcmp.c 				\
		  ft_memmove.c 				\
		  ft_memset.c

SUB_SRCS_STR_UTILS =				\
		  ft_atoi.c					\
		  ft_split.c				\
		  ft_strdup.c				\
		  ft_strdup_free.c			\
		  ft_strchr.c				\
		  ft_strjoin.c				\
		  ft_strjoin_free.c			\
		  ft_strlcat.c				\
		  ft_strlcpy.c				\
		  ft_strlen.c				\
		  ft_strmapi.c				\
		  ft_strncmp.c				\
		  ft_strndup.c				\
		  ft_strnjoin.c				\
		  ft_strnstr.c				\
		  ft_strrchr.c				\
		  ft_strtrim.c				\
		  ft_strtrim_ult.c			\
		  ft_substr.c

SUB_SRCS_PRINT =					\
		  ft_print_bin_rep.c		\
		  ft_putchar.c				\
		  ft_putchar_fd.c			\
		  ft_putendl_fd.c			\
		  ft_puterr.c				\
		  ft_putlenstr_fd.c			\
		  ft_putlenwstr_fd.c		\
		  ft_putnbr_fd.c			\
		  ft_putstr.c				\
		  ft_putstr_fd.c			\
		  ft_putwstr_fd.c

OBJS = 			$(SRCS:%.c=$(OBJS_DIR)/%.o)
OBJS_DIR = 		.objs

HEADER_DIR = .

# prerequisites / dependencies which will depends on
# corresponding .o files, and be remade if .o files are
# modified.
PREREQ =		$(OBJS:%.o=%.d)

MAKE_LIB = ar rcs
MAKE_DIR = mkdir -p
MAKE_RM = rm -f

# RULES

all :			$(NAME)

$(NAME) :		$(OBJS)
				@echo "\nAssembling $(NAME)"
				@$(MAKE_LIB) $(NAME) $(OBJS)
				@echo "Done !"

# include prerequisites which will be made (if needed)
# for following rules.
# '-' sign won't generate error if prereq doesn't exist.
-include $(PREREQ)

# rule to create objects inside objects directory.
# '|' symbol permits to make an order-only prerequisite
# (calling objs_dir rule if needed).
$(OBJS_DIR)/%.o: %.c | $(OBJS_DIR)
				@$(CC) $(CFLAGS) -c $< -o $@
				@echo -n "\rCreation of $(NAME) objects"

$(OBJS_DIR):
				@echo "Creation of $(NAME) $@ file"
				@$(MAKE_DIR) $@

clean :
				@echo "Deleting $(NAME) objects"
				@$(MAKE_RM) -r $(OBJS_DIR)

fclean :		clean
				@echo "Deleting $(NAME) executable"
				@$(MAKE_RM) $(NAME)

re :			fclean all


.PHONY: all clean fclean re

#VPATH

vpath %c ./char_utils ./conv ./files_utils ./ids ./lst ./maths ./mem ./print ./str_utils
vpath %h .

# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: dmlitvin <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/10/25 13:26:24 by dmlitvin          #+#    #+#              #
#    Updated: 2019/02/07 00:16:36 by dmlitvin         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME=libft.a

CC=clang

FLAGS=-c -Wall -Wextra -Werror

COMPRESS=ar rc

REMOVE=rm -rf

SRC=ft_atoi.c ft_bzero.c ft_is_whitespace.c ft_isalnum.c ft_isalpha.c \
ft_isascii.c ft_isdigit.c ft_isprint.c ft_itoa.c ft_list_size.c ft_lstadd.c \
ft_lstdel.c ft_lstdelone.c ft_lstiter.c ft_lstmap.c ft_lstnew.c ft_memalloc.c \
ft_memccpy.c ft_memchr.c ft_memcmp.c ft_memcpy.c ft_memdel.c ft_memmove.c \
ft_memset.c ft_putchar.c ft_putchar_fd.c ft_putendl.c ft_putendl_fd.c \
ft_putnbr.c ft_putnbr_fd.c ft_putstr.c ft_putstr_fd.c ft_strcat.c ft_strchr.c \
ft_strclr.c ft_strcmp.c ft_strcpy.c ft_strdel.c ft_strdup.c ft_strequ.c \
ft_striter.c ft_striteri.c ft_strjoin.c ft_strlcat.c ft_strlen.c ft_strmap.c \
ft_strmapi.c ft_strncat.c ft_strncmp.c ft_strncpy.c ft_strnequ.c ft_strnew.c \
ft_strnstr.c ft_strrchr.c ft_strsplit.c ft_strstr.c ft_strsub.c ft_strtrim.c \
ft_tolower.c ft_toupper.c ft_list_size.c ft_is_whitespace.c ft_itoa10.c \
get_next_line.c ft_printf.c ft_itoa_for_printf.c parsers.c print_cs.c \
print_float.c print_numeric.c ft_isnumeric.c ft_lstfind.c \
ft_cycle_move.c ft_reverse.c ft_lstadd_sorted.c \

SRO = $(SRC:.c=.o)

$(NAME): $(SRC) libft.h
	@$(CC) $(FLAGS) $(SRC)
	@$(COMPRESS) $(NAME) $(SRO)

all: $(NAME)

clean:
	@$(REMOVE) $(SRO)

fclean: clean
	@$(REMOVE) $(SRO) $(NAME)

re: fclean all

.PHONY: all clean fclean re

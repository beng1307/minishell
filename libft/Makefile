# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: bgretic <bgretic@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/04/26 12:32:52 by bgretic           #+#    #+#              #
#    Updated: 2024/09/12 15:37:55 by bgretic          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libft.a
CC = cc
CFLAGS = -Wall -Werror -Wextra -g
SRCS = ft_atoi.c ft_isalpha.c ft_memchr.c ft_memset.c ft_strlcpy.c ft_strrchr.c \
ft_bzero.c ft_isascii.c ft_memcmp.c ft_strchr.c ft_strlen.c ft_tolower.c \
ft_calloc.c ft_isdigit.c ft_memcpy.c ft_strdup.c ft_strncmp.c ft_toupper.c \
ft_isalnum.c ft_isprint.c ft_memmove.c ft_strlcat.c	ft_strnstr.c ft_substr.c \
ft_strjoin.c ft_strtrim.c ft_itoa.c ft_strmapi.c ft_striteri.c ft_putchar_fd.c \
ft_putstr_fd.c ft_putendl_fd.c ft_putnbr_fd.c ft_split.c ft_printf.c \
ft_printf/ft_print_cs.c ft_printf/ft_print_diu.c ft_printf/ft_print_xXp.c \
ft_lstadd_back.c ft_lstadd_front.c ft_lstclear.c ft_lstdelone.c ft_lstlast.c \
ft_lstnew.c ft_lstsize.c get_next_line.c ft_linelen.c ft_cmp.c\
free_that.c free_str_arr.c ft_realloc.c
OBJS = $(SRCS:.c=.o)
FROM = -I libft
LIB = ar rcs

all: $(NAME)

$(NAME): $(OBJS)
	@$(LIB) $(NAME) $(OBJS)

%.o: %.c
	@$(CC) $(CFLAGS) $(FROM) -o $@ -c $<

clean:
	@rm -f $(OBJS)

fclean:	clean
	@rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re

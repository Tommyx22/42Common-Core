# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: tolanini <tolanini@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/05/28 23:03:52 by tolanini          #+#    #+#              #
#    Updated: 2025/07/10 17:15:24 by tolanini         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libft.a

CC = cc
CFLAGS = -Wall -Wextra -Werror -I./

ARCHIVE = ar rc $(NAME)
RM = rm -f

SRCDIR = src/
SRC = $(SRCDIR)file_I_O/ft_putchar_fd.c $(SRCDIR)file_I_O/ft_putendl_fd.c $(SRCDIR)file_I_O/ft_putnbr_fd.c $(SRCDIR)file_I_O/ft_putstr_fd.c $(SRCDIR)file_I_O/ft_putnbr_un.c\
	  $(SRCDIR)ft_printf/ft_printf.c $(SRCDIR)ft_printf/ft_conv.c $(SRCDIR)ft_printf/ft_putbase_long.c $(SRCDIR)ft_printf/ft_putbase.c\
	  $(SRCDIR)get_next_line/get_next_line.c $(SRCDIR)get_next_line/get_next_line_utils.c \
	  $(SRCDIR)linked_list/ft_lstadd_back.c $(SRCDIR)linked_list/ft_lstadd_front.c $(SRCDIR)linked_list/ft_lstclear.c $(SRCDIR)linked_list/ft_lstdelone.c \
	  $(SRCDIR)linked_list/ft_lstiter.c $(SRCDIR)linked_list/ft_lstlast.c $(SRCDIR)linked_list/ft_lstmap.c $(SRCDIR)linked_list/ft_lstnew.c $(SRCDIR)linked_list/ft_lstsize.c \
	  $(SRCDIR)memory_management/ft_bzero.c $(SRCDIR)memory_management/ft_calloc.c $(SRCDIR)memory_management/ft_memchr.c $(SRCDIR)memory_management/ft_memcmp.c \
	  $(SRCDIR)memory_management/ft_memcpy.c $(SRCDIR)memory_management/ft_memmove.c $(SRCDIR)memory_management/ft_memset.c \
	  $(SRCDIR)string_manipulation/ft_atoi.c $(SRCDIR)string_manipulation/ft_isalnum.c $(SRCDIR)string_manipulation/ft_isalpha.c $(SRCDIR)string_manipulation/ft_isascii.c \
	  $(SRCDIR)string_manipulation/ft_isdigit.c $(SRCDIR)string_manipulation/ft_isprint.c $(SRCDIR)string_manipulation/ft_itoa.c $(SRCDIR)string_manipulation/ft_split.c \
	  $(SRCDIR)string_manipulation/ft_strchr.c $(SRCDIR)string_manipulation/ft_strdup.c $(SRCDIR)string_manipulation/ft_striteri.c $(SRCDIR)string_manipulation/ft_strjoin.c \
	  $(SRCDIR)string_manipulation/ft_strlcat.c $(SRCDIR)string_manipulation/ft_strlcpy.c $(SRCDIR)string_manipulation/ft_strlen.c $(SRCDIR)string_manipulation/ft_strmapi.c \
	  $(SRCDIR)string_manipulation/ft_strncmp.c $(SRCDIR)string_manipulation/ft_strnstr.c $(SRCDIR)string_manipulation/ft_strrchr.c $(SRCDIR)string_manipulation/ft_strtrim.c \
	  $(SRCDIR)string_manipulation/ft_substr.c $(SRCDIR)string_manipulation/ft_tolower.c $(SRCDIR)string_manipulation/ft_toupper.c $(SRCDIR)string_manipulation/ft_isavalidint.c \
	  $(SRCDIR)string_manipulation/ft_strcmp.c

OBJ = ${SRC:.c=.o}

all: $(NAME)

$(NAME): $(OBJ)
	@$(ARCHIVE) $(OBJ)
	@echo "Library created"

clean:
	@$(RM) $(OBJ)
	@echo "Objects deleted"

fclean: clean
	@$(RM) $(NAME)
	@echo "Library deleted"

re: fclean all

.PHONY: all clean fclean re

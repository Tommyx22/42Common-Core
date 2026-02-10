# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: tolanini <tolanini@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/07/08 18:46:54 by tolanini          #+#    #+#              #
#    Updated: 2026/02/10 14:16:56 by tolanini         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME    = cub3d
MLX     = libmlx_Linux.a
LIBFT   = libft.a

LFT_PATH    = ./libft/
MLX_PATH    = ./mlx_linux/
INCLUDES    = ./include
SRCDIR      = ./src/
OBJDIR      = objs/

SRC     = main.c \
          $(wildcard $(SRCDIR)*.c)
OBJ     = $(addprefix $(OBJDIR)/, $(notdir $(SRC:.c=.o)))

CC      = gcc
CFLAGS  = -Wall -Wextra -Werror -g
LDFLAGS = -no-pie
MLX_LIBS= -L$(MLX_PATH) -lmlx -L/usr/lib -lXext -lX11 -lm
LFT_LIBS= -L$(LFT_PATH) -lft
CFINC   = -I$(INCLUDES) -I$(MLX_PATH)
RM      = rm -f

all: $(NAME)

$(NAME): $(OBJ) $(LIBFT) $(MLX)
	@echo "Linking $(NAME)..."
	$(CC) $(CFLAGS) $(LDFLAGS) $(OBJ) $(LFT_LIBS) $(MLX_LIBS) -o $(NAME)
	@echo "$(NAME) successfully compiled!"

$(OBJDIR)/%.o: %.c
	@mkdir -p $(OBJDIR)
	@echo "Compiling $<..."
	$(CC) $(CFLAGS) $(CFINC) -c $< -o $@

$(OBJDIR)/%.o: $(SRCDIR)%.c
	@mkdir -p $(OBJDIR)
	@echo "Compiling $<..."
	$(CC) $(CFLAGS) $(CFINC) -c $< -o $@

$(MLX):
	@make -s -C $(MLX_PATH)

$(LIBFT):
	@make -s -C $(LFT_PATH)

clean:
	@echo "Removing object files..."
	$(RM) -r $(OBJDIR)
	@make clean -C $(LFT_PATH)

fclean: clean
	@echo "Removing $(NAME) and libraries..."
	$(RM) $(NAME)
	@make fclean -C $(LFT_PATH)

re: fclean all

.PHONY: all clean fclean re
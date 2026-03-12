# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: tolanini <tolanini@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/07/08 18:46:54 by tolanini          #+#    #+#              #
#    Updated: 2026/03/12 17:20:18 by tolanini         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME        = cub3D
LFT_PATH    = ./libft/
MLX_PATH    = ./mlx_linux/

LIBFT       = $(LFT_PATH)libft.a
MLX         = $(MLX_PATH)libmlx_Linux.a

INCLUDES    = ./include
SRCDIR      = ./src/
OBJDIR      = objs/
MAIN_SRC    = main.c

SRC_FILES   = bonus_utils.c \
              close.c \
              engine.c \
              engine_utils.c \
              keys.c \
              main_utils.c \
              player.c \
              ray_cast_utils.c \
              rendering_utils.c \
              texture.c \
              validating.c \
              validating_map.c \
              validating_map_utils.c \
              validating_utils.c \
              validating_utils_2.c \
              validating_utils_3.c

OBJ         = $(OBJDIR)main.o $(addprefix $(OBJDIR), $(SRC_FILES:.c=.o))

CC          = gcc
CFLAGS      = -Wall -Wextra -Werror -g
LDFLAGS     = -no-pie
MLX_LIBS    = -L$(MLX_PATH) -lmlx -L/usr/lib -lXext -lX11 -lm
LFT_LIBS    = -L$(LFT_PATH) -lft
CFINC       = -I$(INCLUDES) -I$(MLX_PATH)
RM          = rm -f

all: $(NAME)

$(NAME): $(OBJ) $(LIBFT) $(MLX)
	@echo "Linking $(NAME)..."
	$(CC) $(CFLAGS) $(LDFLAGS) $(OBJ) $(LFT_LIBS) $(MLX_LIBS) -o $(NAME)
	@echo "$(NAME) successfully compiled!"

$(OBJDIR)main.o: main.c
	@mkdir -p $(OBJDIR)
	@echo "Compiling $<..."
	$(CC) $(CFLAGS) $(CFINC) -c $< -o $@

$(OBJDIR)%.o: $(SRCDIR)%.c
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

# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: tolanini <tolanini@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/07/08 18:46:54 by tolanini          #+#    #+#              #
#    Updated: 2025/07/10 16:01:54 by tolanini         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME    = Cub3d.a
MLX     = libmlx_Linux.a
LIBFT   = libft.a

LFT_PATH    = ./libft/
MLX_PATH    = ./mlx_linux/
INCLUDES    = ./include
SRCDIR      = ./src/
OBJDIR      = objs/

# Main file is in root, others in src/
ROOT_SRC = main.c
SRC     = $(wildcard $(SRCDIR)*.c)
OBJ     = $(ROOT_SRC:%.c=$(OBJDIR)/%.o) $(SRC:$(SRCDIR)%.c=$(OBJDIR)/%.o)

CC      = cc
CFLAGS  = -Wall -Wextra -Werror
MLX_LIBS= -lm -lbsd -lmlx -lXext -lX11
CFINC   = -I$(INCLUDES)
RM      = rm -f

all: $(NAME)

$(NAME): $(OBJ) $(LIBFT) $(MLX)
	@echo "Generating $(NAME) executable..."
	$(CC) $(CFLAGS) -o $(NAME) $(OBJ) -L$(LFT_PATH) -L$(MLX_PATH) -lft $(MLX_LIBS) -g
	@clear
	@echo "$(NAME) created!"

# Rule for root source files
$(OBJDIR)/%.o: %.c
	@mkdir -p $(OBJDIR)
	@echo "Compiling $<..."
	@$(CC) $(CFLAGS) -g -c $(CFINC) $< -o $@

# Rule for src/ source files
$(OBJDIR)/%.o: $(SRCDIR)%.c
	@mkdir -p $(OBJDIR)
	@echo "Compiling $<..."
	@$(CC) $(CFLAGS) -g -c $(CFINC) $< -o $@

$(MLX):
	@make -C $(MLX_PATH)

$(LIBFT):
	@make -C $(LFT_PATH)

clean:
	@echo "Cleaning object files..."
	@$(RM) -rf $(OBJDIR)
	@clear
	@echo "Objects deleted"

fclean: clean
	@echo "Cleaning $(NAME) and libraries..."
	@$(RM) $(NAME)
	@make fclean -C $(LFT_PATH)
	@make clean -C $(MLX_PATH)
	@clear
	@echo "Library and $(NAME) deleted!"

re: fclean all
	@echo "Rebuilding everything..."

.PHONY: clean fclean all re
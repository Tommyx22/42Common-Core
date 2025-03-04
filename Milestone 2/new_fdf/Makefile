NAME 		= fdf.a
MLX 		= libmlx_Linux.a
LIBFT 		= libft.a

LFT_PATH 	= ./libft/
MLX_PATH 	= ./mlx_linux/
INCLUDES 	= ./include
SRCDIR 		= ./srcs/

SRC 		= $(SRCDIR)main.c

OBJ = objs/main.o

CF 			= -Wall -Wextra -Werror
CC 			= cc
MLX_CF 		= -lm -lbsd -lmlx -lXext -lX11
CFI 		= -I$(INCLUDES)
RM =rm -f

all: $(NAME)

$(NAME): $(OBJ) $(LIBFT) $(MLX)
	$(CC) $(CF) -o $(NAME) $(OBJ) -L $(LFT_PATH) -L $(MLX_PATH) -lft $(MLX_CF)

objs/%.o: $(SRCDIR)%.c
	@mkdir -p objs
	$(CC) $(CF) -g -c $(CFI) $< -o $@

$(MLX):
	@make -C $(MLX_PATH)

$(LIBFT):
	@make -C $(LFT_PATH)

clean:
	$(RM) -rf objs $(NAME)

fclean: clean
	@make fclean -C $(LFT_PATH)
	@make clean -C $(MLX_PATH)

re: fclean all

.PHONY: clean fclean all re

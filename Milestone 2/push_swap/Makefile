# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: tolanini <tolanini@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/02/25 23:20:38 by tolanini          #+#    #+#              #
#    Updated: 2025/03/26 15:29:12 by tolanini         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME    = push_swap
CHECKER = checker
LIBFT   = libft.a
LFT_PATH = ./libft/
INCLUDES = ./include/
SRCDIR   = ./src/
OBJDIR   = objs/
CHK_OBJDIR = chk_objs/

SRC      = $(SRCDIR)main.c $(SRCDIR)stacks_uti.c $(SRCDIR)position.c $(SRCDIR)cost.c $(SRCDIR)utility.c \
        $(SRCDIR)moves_both_rotation.c $(SRCDIR)moves_rotation.c $(SRCDIR)moves_swap_push.c \
        $(SRCDIR)sorting.c $(SRCDIR)find_rank.c $(SRCDIR)move_exe.c $(SRCDIR)ranking.c \
        $(SRCDIR)parsing.c
       
OBJ      = $(OBJDIR)main.o $(OBJDIR)stacks_uti.o $(OBJDIR)position.o $(OBJDIR)cost.o $(OBJDIR)utility.o \
        $(OBJDIR)moves_both_rotation.o $(OBJDIR)moves_rotation.o $(OBJDIR)moves_swap_push.o \
        $(OBJDIR)sorting.o $(OBJDIR)find_rank.o $(OBJDIR)move_exe.o $(OBJDIR)ranking.o \
        $(OBJDIR)parsing.o

CHK_SRC  = $(SRCDIR)bonus/checker.c $(SRCDIR)bonus/checker_uti.c $(SRCDIR)stacks_uti.c $(SRCDIR)position.c $(SRCDIR)cost.c $(SRCDIR)utility.c \
        $(SRCDIR)moves_both_rotation.c $(SRCDIR)moves_rotation.c $(SRCDIR)moves_swap_push.c \
        $(SRCDIR)sorting.c $(SRCDIR)find_rank.c $(SRCDIR)move_exe.c $(SRCDIR)ranking.c \
        $(SRCDIR)parsing.c

CHK_OBJ  = $(CHK_OBJDIR)checker.o $(CHK_OBJDIR)checker_uti.o $(CHK_OBJDIR)stacks_uti.o $(CHK_OBJDIR)position.o $(CHK_OBJDIR)cost.o $(CHK_OBJDIR)utility.o \
        $(CHK_OBJDIR)moves_both_rotation.o $(CHK_OBJDIR)moves_rotation.o $(CHK_OBJDIR)moves_swap_push.o \
        $(CHK_OBJDIR)sorting.o $(CHK_OBJDIR)find_rank.o $(CHK_OBJDIR)move_exe.o $(CHK_OBJDIR)ranking.o \
        $(CHK_OBJDIR)parsing.o

CF       = -Wall -Wextra -Werror
CC       = cc
CFI      = -I$(INCLUDES)
RM       = rm -f
ARCHIVE  = ar rc $(LIBFT)

all: $(NAME)

$(NAME): $(OBJ) $(LIBFT)
	@echo "Generating $(NAME) executable..."
	$(CC) $(CF) -o $(NAME) $(OBJ) -L$(LFT_PATH) -lft
	@echo "$(NAME) created!"

$(OBJDIR)%.o: $(SRCDIR)%.c
	@mkdir -p $(OBJDIR)
	@echo "Compiling $<..."
	$(CC) $(CF) -g -c $(CFI) $< -o $@
	@echo "$< compiled"

$(LIBFT):
	@make -C $(LFT_PATH)

bonus: $(CHECKER)

$(CHECKER): $(CHK_OBJ) $(LIBFT)
	@echo "Generating $(CHECKER) executable..."
	$(CC) $(CF) -o $(CHECKER) $(CHK_OBJ) -L$(LFT_PATH) -lft
	@echo "$(CHECKER) created!"

$(CHK_OBJDIR)%.o: $(SRCDIR)%.c
	@mkdir -p $(CHK_OBJDIR)
	@echo "Compiling $<..."
	$(CC) $(CF) -g -c $(CFI) $< -o $@
	@echo "$< compiled"

$(CHK_OBJDIR)%.o: $(SRCDIR)bonus/%.c
	@mkdir -p $(CHK_OBJDIR)
	@echo "Compiling $<..."
	$(CC) $(CF) -g -c $(CFI) $< -o $@
	@echo "$< compiled"

clean:
	@echo "Cleaning object files..."
	$(RM) -rf $(OBJDIR) $(CHK_OBJDIR)
	@echo "Objects deleted"

fclean: clean
	@echo "Cleaning $(NAME), $(CHECKER) and libraries..."
	$(RM) $(NAME) $(CHECKER)
	@make fclean -C $(LFT_PATH)
	@echo "Library, $(NAME), and $(CHECKER) deleted!"

re: fclean all
	@echo "Rebuilding everything..."

.PHONY: clean fclean all re bonus

# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: tolanini <tolanini@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/06/12 15:00:37 by tolanini          #+#    #+#              #
#    Updated: 2025/06/12 15:11:01 by tolanini         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME     = philo
INCLUDES = ./
SRCDIR   = ./src/
OBJDIR   = objs/
SRC      = main.c \
           $(SRCDIR)exec.c \
           $(SRCDIR)init.c \
           $(SRCDIR)parsing.c \
           $(SRCDIR)utils.c \
		   $(SRCDIR)exec_utils.c 
OBJ      = $(OBJDIR)main.o \
           $(OBJDIR)exec.o \
           $(OBJDIR)init.o \
           $(OBJDIR)parsing.o \
           $(OBJDIR)utils.o \
		   $(OBJDIR)exec_utils.o
CC       = cc
CFLAGS   = -Wall -Wextra -Werror -pthread
CFINC    = -I$(INCLUDES)
RM       = rm -f

all: $(NAME)

$(NAME): $(OBJDIR) $(OBJ)
	@echo "Generating $(NAME) executable..."
	$(CC) $(CFLAGS) $(CFINC) $(OBJ) -o $(NAME)
	@clear
	@echo "$(NAME) created!"

$(OBJDIR):
	@mkdir -p $(OBJDIR)

$(OBJDIR)main.o: main.c
	@echo "Compiling $<..."
	@$(CC) $(CFLAGS) -c $(CFINC) $< -o $@
	@echo "$< compiled"

$(OBJDIR)%.o: $(SRCDIR)%.c
	@echo "Compiling $<..."
	@$(CC) $(CFLAGS) -c $(CFINC) $< -o $@
	@echo "$< compiled"

clean:
	@echo "Cleaning object files..."
	@$(RM) -rf $(OBJDIR)
	@clear
	@echo "Objects deleted"

fclean: clean
	@echo "Cleaning $(NAME)..."
	@$(RM) $(NAME)
	@clear
	@echo "$(NAME) deleted!"

re: fclean all
	@echo "Rebuilding everything..."

.PHONY: clean fclean all re
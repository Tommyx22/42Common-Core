# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: tolanini <tolanini@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2026/05/20 15:12:23 by tolanini          #+#    #+#              #
#    Updated: 2026/05/22 17:47:22 by tolanini         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = ircserv
CPP = c++
CPPFLAGS = -Wall -Wextra -Werror -std=c++98

SRC = main.cpp \
	  Server.cpp \
	  User.cpp
OBJ = $(SRC:.cpp=.o)

all: $(NAME)

$(NAME): $(OBJ)
	@echo "Linking $(NAME)..."
	$(CPP) $(CPPFLAGS) -o $(NAME) $(OBJ)
	@echo "$(NAME) successfully compiled!"

%.o: %.cpp
	@echo "Compiling $<..."
	$(CPP) $(CPPFLAGS) -c $< -o $@

clean:
	@echo "Cleaning object files..."
	rm -f $(OBJ)

fclean: clean
	@echo "Removing executable $(NAME)..."
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
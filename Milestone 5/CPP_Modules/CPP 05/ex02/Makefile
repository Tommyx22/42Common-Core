# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: tolanini <tolanini@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2026/03/23 18:46:20 by tolanini          #+#    #+#              #
#    Updated: 2026/03/23 19:39:13 by tolanini         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = aform
CPP = c++
CPPFLAGS = -Wall -Wextra -Werror -std=c++98

SRC = main.cpp \
	Bureaucrat.cpp \
	AForm.cpp \
	PresidentialPardonForm.cpp \
	RobotomyRequestForm.cpp \
	ShrubberyCreationForm.cpp
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
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Cat.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tolanini <tolanini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/20 13:56:40 by tolanini          #+#    #+#             */
/*   Updated: 2026/01/20 15:23:37 by tolanini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Cat.hpp"

Cat::Cat() {
	this->type = "Cat";
	this->brain = new Brain();
	std::cout << "Cat default constructor called" << std::endl;
}

Cat::Cat(const Cat &copy) {
	std::cout << "cat copy constructor called" << std::endl;
	this->type  = copy.type;
	this->brain = new Brain(*copy.brain);
}

Cat &Cat::operator=(const Cat &copy) {
	std::cout << "Cat copy assignment operator called" << std::endl;
	if (this != &copy) {
		this->type = copy.type;
		delete this->brain;
		this->brain = new Brain(*copy.brain);
	}
	return *this;
}

Cat::~Cat() {
	delete this->brain;
	std::cout << "Cat destructor called" << std::endl;
}

void Cat::makeSound() const {
	std::cout << "Cat makes a sound: meow meow!" << std::endl;
}
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Dog.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tolanini <tolanini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/20 13:56:28 by tolanini          #+#    #+#             */
/*   Updated: 2026/01/20 15:23:29 by tolanini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Dog.hpp"

Dog::Dog() {
	this->type = "Dog";
	this->brain = new Brain();
	std::cout << "Dog default constructor called" << std::endl;
}

Dog::Dog(const Dog &copy) {
	std::cout << "Dog copy constructor called" << std::endl;
	this->type  = copy.type;
	this->brain = new Brain(*copy.brain);
}

Dog &Dog::operator=(const Dog &copy) {
	std::cout << "Dog copy assignment operator called" << std::endl;
	if (this != &copy) {
		this->type = copy.type;
		delete this->brain;
		this->brain = new Brain(*copy.brain);
	}
	return *this;
}

Dog::~Dog() {
	delete this->brain;
	std::cout << "Dog destructor called" << std::endl;
}

void Dog::makeSound() const {
	std::cout << "Dog makes a sound: woof woof!" << std::endl;
}
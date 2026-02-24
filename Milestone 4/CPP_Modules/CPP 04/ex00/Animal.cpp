/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Animal.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tolanini <tolanini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/20 13:56:58 by tolanini          #+#    #+#             */
/*   Updated: 2026/01/20 15:12:56 by tolanini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Animal.hpp"

Animal::Animal() : type("Animal") {
	std::cout << "Animal default constructor called" << std::endl;
}

Animal::Animal(const Animal &copy) {
	std::cout << "Animal copy constructor called" << std::endl;
	*this = copy;
}

Animal &Animal::operator=(const Animal &copy) {
	std::cout << "Animal copy assignment operator called" << std::endl;
	if (this != &copy) {
		this->type = copy.type;
	}
	return *this;
}

Animal::~Animal() {
	std::cout << "Animal destructor called" << std::endl;
}

void Animal::makeSound() const {
	std::cout << "Animal makes sound" << std::endl;
}

std::string Animal::getType() const {
	return this->type;
}
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   WrongCat.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tolanini <tolanini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/20 15:37:25 by tolanini          #+#    #+#             */
/*   Updated: 2026/01/20 15:51:04 by tolanini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "WrongCat.hpp"

WrongCat::WrongCat() {
	this->type = "WrongCat";
	std::cout << "WrongCat default constructor called" << std::endl;
}

WrongCat::WrongCat(const WrongCat &copy) {
	std::cout << "WrongCat copy constructor called" << std::endl;
	*this = copy;
}

WrongCat &WrongCat::operator=(const WrongCat &copy) {
	std::cout << "WrongCat copy assignment operator called" << std::endl;
	if (this != &copy) {
		this->type = copy.type;
	}
	return *this;
}

WrongCat::~WrongCat() {
	std::cout << "WrongCat destructor called" << std::endl;
}

void WrongCat::makeSound() const {
	std::cout << "WrongCat makes a sound: woof woof!" << std::endl;
}
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Serializer.cpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tolanini <tolanini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/14 13:48:40 by tolanini          #+#    #+#             */
/*   Updated: 2026/04/14 14:52:09 by tolanini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Serializer.hpp"

Serializer::Serializer() {
	std::cout << "Serializer default constructor called" << std::endl;
}

Serializer::Serializer(const Serializer& copy) {
	std::cout << "Serializer copy constructor called" << std::endl;
	*this = copy;
}

Serializer& Serializer::operator=(const Serializer& copy) {
	std::cout << "Serializer copy assignment operator called" << std::endl;
	if (this != &copy)
		*this = copy;
	return *this;
}

Serializer::~Serializer() {
	std::cout << "Serializer destructor called" << std::endl;
}

uintptr_t Serializer::serialize(Data *ptr) {
	return reinterpret_cast<uintptr_t>(ptr);
}

Data* Serializer::deserialize(uintptr_t raw) {
	return reinterpret_cast<Data*>(raw);
}
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Fixed.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tolanini <tolanini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/14 16:31:53 by tolanini          #+#    #+#             */
/*   Updated: 2026/01/14 17:04:02 by tolanini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Fixed.hpp"

Fixed::Fixed(const int number) {
	std::cout << "Int constructor called" << std::endl;
	fixedPointNumber = number << fractonalBits;
}

Fixed::Fixed(const float floater) {
	std::cout << "Float constructor called" << std::endl;
	fixedPointNumber = (int)roundf(floater * (1 << fractonalBits));	
}

Fixed::Fixed() : fixedPointNumber(0) {
	std::cout << "Default constructor called" << std::endl;
}

Fixed::Fixed(const Fixed &copy) {
	std::cout << "Copy constructor called" << std::endl;
	*this = copy;
}

Fixed &Fixed::operator=(const Fixed &copy) {
	std::cout << "Copy assignment operator called" << std::endl;
	if (this != &copy)
		this->fixedPointNumber = copy.fixedPointNumber;
	return *this;
}

Fixed::~Fixed() {
	std::cout << "Destructor called" << std::endl;
}

int Fixed::getRawBits( void ) const {
	std::cout << "getRawBits member function called" << std::endl;
	return this->fixedPointNumber;
}

void Fixed::setRawBits( int const raw ) {
	std::cout << "setRawBits member function called" << std::endl;
	this->fixedPointNumber = raw;
}

float Fixed::toFloat( void ) const {
	return ((float)fixedPointNumber / (1 << fractonalBits));
}

int Fixed::toInt( void ) const {
	return (fixedPointNumber >> fractonalBits);
}

std::ostream &operator<<(std::ostream &os, const Fixed &fixed) {
	os << fixed.toFloat();
	return os;
}
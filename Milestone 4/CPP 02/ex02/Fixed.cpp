/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Fixed.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tolanini <tolanini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/14 16:31:53 by tolanini          #+#    #+#             */
/*   Updated: 2026/01/15 16:01:56 by tolanini         ###   ########.fr       */
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

bool Fixed::operator>(const Fixed &copy) const {
	return (this->fixedPointNumber > copy.fixedPointNumber);
}

bool Fixed::operator<(const Fixed &copy) const {
	return (this->fixedPointNumber < copy.fixedPointNumber);
}

bool Fixed::operator>=(const Fixed &copy) const {
	return (this->fixedPointNumber >= copy.fixedPointNumber);
}

bool Fixed::operator<=(const Fixed &copy) const {
	return (this->fixedPointNumber <= copy.fixedPointNumber);
}

bool Fixed::operator==(const Fixed &copy) const {
	return (this->fixedPointNumber == copy.fixedPointNumber);
}

bool Fixed::operator!=(const Fixed &copy) const {
	return (this->fixedPointNumber != copy.fixedPointNumber);
}

Fixed Fixed::operator+(const Fixed &copy) const {
	Fixed result;
	result.fixedPointNumber = this->fixedPointNumber + copy.fixedPointNumber;
	return result;
}

Fixed Fixed::operator-(const Fixed &copy) const {
	Fixed result;
	result.fixedPointNumber = this->fixedPointNumber - copy.fixedPointNumber;
	return result;
}

Fixed Fixed::operator*(const Fixed &copy) const {
	Fixed result;
	result.fixedPointNumber = (this->fixedPointNumber * copy.fixedPointNumber) >> fractonalBits;
	return result;
}

Fixed Fixed::operator/(const Fixed &copy) const {
	Fixed result;
	result.fixedPointNumber = (this->fixedPointNumber << fractonalBits) / copy.fixedPointNumber;
	return result;
}

Fixed Fixed::operator++(int) {
	Fixed temp;
	this->fixedPointNumber++;
	return temp;
}

Fixed Fixed::operator--(int) {
	Fixed temp;
	this->fixedPointNumber--;
	return temp;
}

Fixed &Fixed::operator++() {
	this->fixedPointNumber++;
	return (*this);
}

Fixed &Fixed::operator--() {
	this->fixedPointNumber--;
	return (*this);
}

Fixed &Fixed::min(Fixed &a, Fixed &b) {
	if (a.getRawBits() <= b.getRawBits()) {
		return a;
	} else {
		return b;
	}
}

Fixed &Fixed::max(Fixed &a, Fixed &b) {
	if (a.getRawBits() >= b.getRawBits()) {
		return a;
	} else {
		return b;
	}
}

const Fixed &Fixed::min (const Fixed &a, const Fixed &b) {
	if (a.getRawBits() <= b.getRawBits()) {
		return a;
	} else {
		return b;
	}
}

const Fixed &Fixed::max(const Fixed &a, const Fixed &b) {
	if (a.getRawBits() >= b.getRawBits()) {
		return a;
	} else {
		return b;
	}
}

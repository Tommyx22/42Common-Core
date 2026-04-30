/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Span.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tolanini <tolanini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/28 14:29:09 by tolanini          #+#    #+#             */
/*   Updated: 2026/04/30 17:39:53 by tolanini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Span.hpp"

Span::Span() {
	std::cout << "Default constructor called" << std::endl;
}

Span::Span(unsigned int N) : N(N) {
	std::cout << "Constructor called" << std::endl;
}

Span::Span(const Span& copy) {
	std::cout << "Copy constructor called" << std::endl;
	*this = copy;
}

Span& Span::operator=(const Span& copy) {
	std::cout << "Copy assignment operator called" << std::endl;
	if (this != &copy) {
		*this = copy;
	}
	return *this;
}

Span::~Span() {
	std::cout << "Destructor called" << std::endl;
}

void Span::addNumber(int number) {
	if (v.size() >= N) {
		throw SpanFullException();
	}
	v.insert(std::lower_bound(v.begin(), v.end(), number), number);
}

int Span::longestSpan() const {
	if (v.size() < 2) {
		throw NotEnoughNumbersException();
	}
	return v.back() - v.front();
}

int Span::shortestSpan() const {
	if (v.size() < 2) {
		throw NotEnoughNumbersException();
	}
	int num = (v[1] - v[0]);
	unsigned int i = 0;
	unsigned int j = 0;
	while (i < (v.size() - 1)) {
		j = i + 1;
		while (j < v.size()) {
			if ((v[j] - v[i]) < num)
				num = v[j] - v[i];
			j++;
		}
		i++;
	}
	return num;
}

const char* Span::SpanFullException::what() const throw() {
	return "Container is full";
}

const char* Span::NotEnoughNumbersException::what() const throw() {
	return "Not enough numbers to find a span";
}
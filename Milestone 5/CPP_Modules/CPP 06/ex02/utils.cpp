/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tolanini <tolanini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/14 15:23:46 by tolanini          #+#    #+#             */
/*   Updated: 2026/04/14 15:56:24 by tolanini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.hpp"

Base *generate(void) {
	switch (std::rand() % 3) {
		case 0:
			std::cout << "Generated A" << std::endl;
			return new A();
		case 1:
			std::cout << "Generated B" << std::endl;
			return new B();
		case 2:
			std::cout << "Generated C" << std::endl;
			return new C();
		default:
			std::cout << "Generated A" << std::endl;
			return new A();
	}
}

void identify(Base* p) {
	if (dynamic_cast<A*>(p))
		std::cout << "Identified A" << std::endl;
	else if (dynamic_cast<B*>(p))
		std::cout << "Identified B" << std::endl;
	else if (dynamic_cast<C*>(p))
		std::cout << "Identified C" << std::endl;
	else 
		std::cout << "Unknown type" << std::endl;
}

void identify(Base& p) {
	try {
		(void)dynamic_cast<A&>(p);
		std::cout << "Identified A" << std::endl;
		return;
	} catch (...) {
	}
	try {
		(void)dynamic_cast<B&>(p);
		std::cout << "Identified B" << std::endl;
		return;
	} catch (...) {
	}
	try {
		(void)dynamic_cast<C&>(p);
		std::cout << "Identified C" << std::endl;
		return;
	} catch (...) {
	}
	std::cout << "Unknown type" << std::endl;
}
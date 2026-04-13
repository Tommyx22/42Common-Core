/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ScalarConverter.cpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tolanini <tolanini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/29 16:43:40 by tolanini          #+#    #+#             */
/*   Updated: 2026/03/29 16:43:40 by tolanini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ScalarConverter.hpp"

namespace {
	void getType(std::string str) {
		std::string pseudo[6] = {"nan", "nanf", "+inf", "-inf", "+inff", "-inff"};
		for (int i = 0; i < 6; i++) {
			if (str == pseudo[i])
				return "pseudo-literal";
		}
		if (str.length() == 1 && std::isprint(str[0]) && !std::isdigit(str[0]))
			return "char";
		else if (str.find('.') != std::string::npos) {
			if (str.back() == 'f')
				return "float";
			else
				return "double";
		}
		else
			return "int";
	}
}

ScalarConverter::ScalarConverter() {
	std::cout << "Default ScalarConverter constructor called" << std::endl;
}

ScalarConverter::ScalarConverter(const ScalarConverter &copy) {
	std::cout << "Copy ScalarConverter constructor called" << std::endl;
	*this = copy;
}

ScalarConverter &ScalarConverter::operator=(const ScalarConverter &copy) {
	std::cout << "Copy assignmen operator called" << std::endl;
	if (this != &copy)
		*this = copy;
	return *this;
}

ScalarConverter::~ScalarConverter() {
	std::cout << "ScalarConverter destructor called" << std::endl;
}


void ScalarConverter::convert(const std::string &str) {

}
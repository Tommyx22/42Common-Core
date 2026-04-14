/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ScalarConverter.cpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tolanini <tolanini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/29 16:43:40 by tolanini          #+#    #+#             */
/*   Updated: 2026/04/14 13:46:55 by tolanini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ScalarConverter.hpp"

namespace {
	int getType(std::string str) {
		std::string pseudo[6] = {"nan", "nanf", "+inf", "-inf", "+inff", "-inff"};
		for (int i = 0; i < 6; i++) {
			if (str == pseudo[i])
				return 1;
		}
		if (str.length() == 1 && std::isprint(str[0]) && !std::isdigit(str[0]))
			return 2;
		else if (str.find('.') != std::string::npos) {
			if (str[str.length() - 1] == 'f')
				return 3;
			else
				return 4;
		}
		else
			return 5;
		return -1;
	}

	void printImpossible() {
		std::cout << "char: impossible" << std::endl;
		std::cout << "int: impossible" << std::endl;
		std::cout << "float: impossible" << std::endl;
		std::cout << "double: impossible" << std::endl;
	}


	void charType(const std::string &str) {
		char value = str[0];
		std::cout << "char: '" << value << "'" << std::endl;
		std::cout << "int: " << static_cast<int>(value) << std::endl;
		std::cout << "float: " << std::fixed << std::setprecision(1) << static_cast<float>(value) << "f" << std::endl;
		std::cout << "double: " << std::fixed << std::setprecision(1) << static_cast<double>(value) << std::endl;
	}



	void intType(const std::string &str) {
		std::stringstream s(str);
		int value;

		s >> std::noskipws >> value;
		if (s.fail() || !s.eof()) {
			printImpossible();
			return;
		}
		std::cout << "char: ";
		if (value >= 32 && value <= 126)
			std::cout << "'" << static_cast<char>(value) << "'";
		else
			std::cout << "Non displayable";
		std::cout << std::endl;
		std::cout << "int: " << value << std::endl;
		std::cout << "float: " << std::fixed << std::setprecision(1) << static_cast<float>(value) << "f" << std::endl;
		std::cout << "double: " << std::fixed << std::setprecision(1) << static_cast<double>(value) << std::endl;
	}

	void floatType(const std::string &str) {
		std::stringstream s(str);
		float value;

		s >> std::noskipws >> value;
		if (s.fail() || !s.eof()) {
			printImpossible();
			return;
		}
		std::cout << "char: ";
		if (value >= 32 && value <= 126)
			std::cout << "'" << static_cast<char>(value) << "'";
		else
			std::cout << "Non displayable";
		std::cout << std::endl;
		std::cout << "int: " << static_cast<int>(value) << std::endl;
		std::cout << "float: " << std::fixed << std::setprecision(1) << value << "f" << std::endl;
		std::cout << "double: " << std::fixed << std::setprecision(1) << static_cast<double>(value) << std::endl;
	}

	void doubleType(const std::string &str) {
		std::stringstream s(str);
		double value;

		s >> std::noskipws >> value;
		if (s.fail() || !s.eof()) {
			printImpossible();
			return;
		}
		std::cout << "char: ";
		if (value >= 32 && value <= 126)
			std::cout << "'" << static_cast<char>(value) << "'";
		else
			std::cout << "Non displayable";
		std::cout << std::endl;
		std::cout << "int: " << static_cast<int>(value) << std::endl;
		std::cout << "float: " << std::fixed << std::setprecision(1) << static_cast<float>(value) << "f" << std::endl;
		std::cout << "double: " << std::fixed << std::setprecision(1) << value << std::endl;
	}


	void pseudoType(const std::string &str) {
		std::cout << "char: impossible" << std::endl;
		std::cout << "int: impossible" << std::endl;
		if (str == "nan" || str == "nanf") {
			std::cout << "float: nanf" << std::endl;
			std::cout << "double: nan" << std::endl;
		}
		else if (str[0] == '-') {
			std::cout << "float: -inff" << std::endl;
			std::cout << "double: -inf" << std::endl;
		}
		else {
			std::cout << "float: inff" << std::endl;
			std::cout << "double: inf" << std::endl;
		}
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
	std::cout << "Copy assignment operator called" << std::endl;
	if (this != &copy)
		*this = copy;
	return *this;
}

ScalarConverter::~ScalarConverter() {
	std::cout << "ScalarConverter destructor called" << std::endl;
}


void ScalarConverter::convert(const std::string &str) {
	int type = getType(str);
	switch (type) {
		case 1:
			pseudoType(str);
			break;
		case 2:
			charType(str);
			break;
		case 3:
			floatType(str);
			break;
		case 4:
			doubleType(str);
			break;
		case 5:
			intType(str);
			break;
		default:
			std::cout << "Error: Invalid input" << std::endl;
	}
}

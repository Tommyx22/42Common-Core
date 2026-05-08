/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RPN.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tolanini <tolanini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/08 17:38:30 by tolanini          #+#    #+#             */
/*   Updated: 2026/05/08 18:16:10 by tolanini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "RPN.hpp"

namespace {
	
	int operation(int a, int b, char op) {
		switch (op) {
			case '+':
				return a + b;
			case '-':
				return a - b;
			case '*':
				return a * b;
			case '/':
				return a / b;
			default:
				throw std::runtime_error("Error: invalid operator");
		}
	}
}

RPN::RPN() {}

RPN::RPN(const RPN &copy) {
	*this = copy;
}

RPN &RPN::operator=(const RPN &copy) {
	if (this == &copy)
		*this = copy;
	return *this;
}

RPN::~RPN() {}

int RPN::calculate(const std::string &expression) {
	std::stack<int> s;
	for (size_t i = 0; i < expression.length(); i++) {
		if (isspace(expression[i]))
			continue;
		if (isdigit(expression[i])) {
			s.push(expression[i] - '0');
		} else if (expression[i] == '+' || expression[i] == '-' || expression[i] == '*' || expression[i] == '/') {
			if (s.size() < 2)
				throw std::runtime_error("Error: not enough operands for operation");
			int b = s.top(); s.pop();
			int a = s.top(); s.pop();
			s.push(operation(a, b, expression[i]));
		} else {
			throw std::runtime_error("Error: invalid character in expression");
		}
	}
	if (s.size() != 1)
		throw std::runtime_error("Error: invalid expression");
	return s.top();
}
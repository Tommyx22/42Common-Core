/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tolanini <tolanini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/23 18:45:50 by tolanini          #+#    #+#             */
/*   Updated: 2026/03/23 19:51:43 by tolanini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Bureaucrat.hpp"

int main() {
	std::cout << "=== TEST 1: Valid Bureaucrat creation ===" << std::endl;
	Bureaucrat b0("Eve", 50);
	std::cout << "Created: " << b0 << std::endl;
	std::cout << std::endl;

	std::cout << "=== TEST 2: Invalid Bureaucrat creation (grade < 1) ===" << std::endl;
	try {
		Bureaucrat b_invalid("Frank", 0);
	}
	catch (Bureaucrat::GradeTooHighException &e) {
		std::cout << "Exception: " << e.what() << std::endl;
	}
	std::cout << std::endl;

	std::cout << "=== TEST 3: incrementGrade() ===" << std::endl;
	Bureaucrat b1("Alice", 50);
	std::cout << "Before: " << b1 << std::endl;
	b1.incrementGrade();
	std::cout << "After: " << b1 << std::endl;
	std::cout << std::endl;

	std::cout << "=== TEST 4: decrementGrade() ===" << std::endl;
	Bureaucrat b2("Bob", 50);
	std::cout << "Before: " << b2 << std::endl;
	b2.decrementGrade();
	std::cout << "After: " << b2 << std::endl;
	std::cout << std::endl;

	std::cout << "=== TEST 5: GradeTooHighException ===" << std::endl;
	Bureaucrat b3("Charlie", 1);
	std::cout << "Current: " << b3 << std::endl;
	try {
		b3.incrementGrade();
	}
	catch (Bureaucrat::GradeTooHighException &e) {
		std::cout << "Exception: " << e.what() << std::endl;
	}
	std::cout << std::endl;

	std::cout << "=== TEST 6: GradeTooLowException ===" << std::endl;
	Bureaucrat b4("Dave", 150);
	std::cout << "Current: " << b4 << std::endl;
	try {
		b4.decrementGrade();
	}
	catch (Bureaucrat::GradeTooLowException &e) {
		std::cout << "Exception: " << e.what() << std::endl;
	}
	std::cout << std::endl;

	return (0);
}
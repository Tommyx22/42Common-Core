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
#include "AForm.hpp"
#include "ShrubberyCreationForm.hpp"
#include "RobotomyRequestForm.hpp"
#include "PresidentialPardonForm.hpp"
#include "Intern.hpp"

int main() {
	std::cout << "INTERN TEST" << std::endl;
	Intern someRandomIntern;
	AForm* rrf;

	rrf = someRandomIntern.makeForm("presidential pardon", "Bender");
	std::cout << rrf->getName();
	if (rrf->getIsSigned() == 0)
		std::cout << " not signed" << std::endl;
	else
		std::cout << " signed" << std::endl;

	delete rrf;
	return (0);
}
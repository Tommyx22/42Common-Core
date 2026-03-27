/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Intern.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tolanini <tolanini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/27 16:35:07 by tolanini          #+#    #+#             */
/*   Updated: 2026/03/27 17:15:10 by tolanini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Intern.hpp"

namespace {
	typedef AForm *(*t_form_creator)(std::string const &);

	AForm *createShrubbery(std::string const &target) {
		return new ShrubberyCreationForm(target);
	}

	AForm *createRobotomy(std::string const &target) {
		return new RobotomyRequestForm(target);
	}

	AForm *createPardon(std::string const &target) {
		return new PresidentialPardonForm(target);
	}
}

Intern::Intern() {
	std::cout << "Intern default constructor called" << std::endl;
}

Intern::Intern(const Intern &copy) {
	std::cout << "Intern copy constructor called" << std::endl;
	*this = copy;
}

Intern &Intern::operator=(const Intern &copy) {
	std::cout << "Intern copy assignment operator called" << std::endl;
	if (this != &copy) {
		*this = copy;
	}
	return *this;
}

Intern::~Intern() {
	std::cout << "Intern destructor called" << std::endl;
}


AForm *Intern::makeForm(std::string formName, std::string target) {
	struct s_factory_entry {
		const char *name;
		t_form_creator creator;
	};

	static const s_factory_entry factories[3] = {
		{"shrubbery creation", &createShrubbery},
		{"robotomy request", &createRobotomy},
		{"presidential pardon", &createPardon}
	};

	for (int i = 0; i < 3; i++) {
		if (formName == factories[i].name) {
			std::cout << "Intern creates " << formName << std::endl;
			return factories[i].creator(target);
		}
	}
	std::cerr << "Error: form name not found" << std::endl;
	return NULL;
}
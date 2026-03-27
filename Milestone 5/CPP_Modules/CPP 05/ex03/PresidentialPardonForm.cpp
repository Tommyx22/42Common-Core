/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PresidentialPardonForm.cpp                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tolanini <tolanini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/26 23:06:17 by tolanini          #+#    #+#             */
/*   Updated: 2026/03/27 15:47:46 by tolanini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "PresidentialPardonForm.hpp"
#include "Bureaucrat.hpp"

PresidentialPardonForm::PresidentialPardonForm() : AForm("Default PresidentialPardonForm", 25, 5), target("default") {
	std::cout << "PresidentialPardonForm default constructor called" << std::endl;
}

PresidentialPardonForm::PresidentialPardonForm(const std::string &target) : AForm("PresidentialPardonForm", 25, 5), target(target) {
	std::cout << "PresidentialPardonForm constructor called" << std::endl;
}

PresidentialPardonForm::PresidentialPardonForm(const PresidentialPardonForm &copy) : AForm(copy), target(copy.target) {
	std::cout << "PresidentialPardonForm copy constructor called" << std::endl;
}

PresidentialPardonForm &PresidentialPardonForm::operator=(const PresidentialPardonForm &copy) {
	if (this != &copy) {
		*this = copy;
	}
	return *this;
}

PresidentialPardonForm::~PresidentialPardonForm() {
	std::cout << "PresidentialPardonForm destructor called" << std::endl;
}

std::string PresidentialPardonForm::getTarget() const {
	return this->target;
}

std::ostream &operator<<(std::ostream &out, const PresidentialPardonForm &ppf) {
	out << ppf.getName() << ", form grade sign " << ppf.getGradeSign() << ", form grade req " << ppf.getGradeReq() << ", is signed " << ppf.getIsSigned();
	return (out);
}

void PresidentialPardonForm::execute(const Bureaucrat &executor) const {
	if (executor.getGrade() > this->getGradeReq())
		throw AForm::GradeTooLowException();
	if(!this->getIsSigned())
		throw AForm::FormNotSignedException();
	std::cout << this->target << " has been pardoned by Zaphod Beeblebrox" << std::endl;
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ShrubberyCreationForm.cpp                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tolanini <tolanini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/26 23:06:04 by tolanini          #+#    #+#             */
/*   Updated: 2026/03/27 16:03:25 by tolanini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ShrubberyCreationForm.hpp"
ShrubberyCreationForm::ShrubberyCreationForm() : AForm("Default ShrubberyCreationForm", 145, 137), target("default") {
	std::cout << "ShrubberyCreationForm default constructor called" << std::endl;
}

ShrubberyCreationForm::ShrubberyCreationForm(const std::string &target) : AForm("ShrubberyCreationForm", 145, 137), target(target) {
	std::cout << "ShrubberyCreationForm constructor called" << std::endl;
}

ShrubberyCreationForm::ShrubberyCreationForm(const ShrubberyCreationForm &copy) : AForm(copy), target(copy.target) {
	std::cout << "ShrubberyCreationForm Copy constructor" << std::endl;
}

ShrubberyCreationForm &ShrubberyCreationForm::operator=(const ShrubberyCreationForm &copy) {
	if (this != &copy) {
		*this = copy;
	}
	return *this;
}

ShrubberyCreationForm::~ShrubberyCreationForm() {
	std::cout << "ShrubberyCreationForm destructor called" << std::endl;
}

std::string ShrubberyCreationForm::getTarget() const {
	return this->target;
}

std::ostream &operator<<(std::ostream &out, const ShrubberyCreationForm &scf) {
	out << scf.getName() << ", form grade sign " << scf.getGradeSign() << ", form grade req " << scf.getGradeReq() << ", is signed " << scf.getIsSigned();
	return (out);
}

void ShrubberyCreationForm::execute(const Bureaucrat &executor) const {
	if (executor.getGrade() > this->getGradeReq())
		throw AForm::GradeTooLowException();
	if(!this->getIsSigned())
		throw AForm::FormNotSignedException();
	std::ofstream file((this->target + "_shrubbery").c_str());
	if (!file.is_open()) {
		std::cerr << "Error: Could not create file " << this->target + "_shrubbery" << std::endl;
		return;
	}
	file << "       _-_" << std::endl;
	file << "    /~~   ~~\\" << std::endl;
	file << " /~~         ~~\\" << std::endl;
	file << "{               }" << std::endl;
	file << " \\  _-     -_  /" << std::endl;
	file << "   ~  \\\\ //  ~" << std::endl;
	file << "_- -   | | _- _" << std::endl;
	file << "  _ -  | |   -_" << std::endl;
	file << "      // \\\\" << std::endl;
	file.close();
	std::cout << "Shrubbery tree created in file " << this->target + "_shrubbery" << std::endl;
}
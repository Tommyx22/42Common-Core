/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RobotomyRequestForm.cpp                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tolanini <tolanini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/26 23:06:30 by tolanini          #+#    #+#             */
/*   Updated: 2026/03/27 16:20:54 by tolanini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "RobotomyRequestForm.hpp"
#include "Bureaucrat.hpp"

RobotomyRequestForm::RobotomyRequestForm() : AForm("Default Robotomy Request", 72, 45), target("default") {
	std::cout << "RobotomyRequestForm default constructor called" << std::endl;
}

RobotomyRequestForm::RobotomyRequestForm(const std::string &target) : AForm("RobotomyRequestForm", 72, 45), target(target) {
	std::cout << "RobotomyRequestForm constructor called" << std::endl;
}

RobotomyRequestForm::RobotomyRequestForm(const RobotomyRequestForm &copy) : AForm(copy), target(copy.target) {
	std::cout << "RobotomyRequestForm copy constructor called" << std::endl;
}

RobotomyRequestForm &RobotomyRequestForm::operator=(const RobotomyRequestForm &copy) {
	if (this != &copy) {
		*this = copy;
	}
	return *this;
}

RobotomyRequestForm::~RobotomyRequestForm() {
	std::cout << "RobotomyRequestForm destructor called" << std::endl;
}

std::string RobotomyRequestForm::getTarget() const {
	return this->target;
}

std::ostream &operator<<(std::ostream &out, const RobotomyRequestForm &rrf) {
	out << rrf.getName() << ", form grade sign " << rrf.getGradeSign() << ", form grade req " << rrf.getGradeReq() << ", is signed " << rrf.getIsSigned();
	return (out);
}

void RobotomyRequestForm::execute(const Bureaucrat &executor) const {
	if (executor.getGrade() > this->getGradeReq())
		throw AForm::GradeTooLowException();
	if(!this->getIsSigned())
		throw AForm::FormNotSignedException();
	std::cout << "Bzzzzzz... drilling noises..." << std::endl;
	srand(time(0));
	int num = rand() % 2;
	std::cout << num << " random number" << std::endl;
	if (num == 0)
		std::cout << this->target << " has been robotomized successfully!" << std::endl;
	else
		std::cout << "Failed to robotomize " << this->target << "." << std::endl;
}

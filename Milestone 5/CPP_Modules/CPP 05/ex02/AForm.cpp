/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   AForm.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tolanini <tolanini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/24 16:51:49 by tolanini          #+#    #+#             */
/*   Updated: 2026/03/24 16:51:49 by tolanini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "AForm.hpp"

AForm::AForm() : name("default"), gradeSign(1), gradeReq(1), isSigned(false) {
	std::cout << "Default constructor called" << std::endl;
}

AForm::AForm(const std::string name, const int gradeSign, const int gradeReq) : name(name), gradeSign(gradeSign), gradeReq(gradeReq), isSigned(false) {
	if (gradeSign < 1 || gradeReq < 1)
		throw GradeTooHighException();
	if (gradeSign > 150 || gradeReq > 150)
		throw GradeTooLowException();
	std::cout << this->name << " constructor called" << std::endl;
}

AForm::AForm(const AForm &copy) : name(copy.name), gradeSign(copy.gradeSign), gradeReq(copy.gradeReq), isSigned(copy.isSigned) {
	std::cout << "Copy constructor called" << std::endl;
}

AForm &AForm::operator=(const AForm &copy) {
	std::cout << "Copy assignment operator called" << std::endl;
	if (this != &copy)
		*this = copy;
	return (*this);
}

AForm::~AForm() {
	std::cout << this->name << " destructor called" << std::endl;
}

std::string AForm::getName() const {
	return (this->name);
}

int AForm::getGradeSign() const {
	return (this->gradeSign);
}

int AForm::getGradeReq() const {
	return (this->gradeReq);
}

bool AForm::getIsSigned() const {
	return (this->isSigned);
}

void AForm::beSigned(const Bureaucrat &bureaucrat) {
	if (bureaucrat.getGrade() > this->gradeSign)
		throw GradeTooLowException();
	this->isSigned = true;
}

const char *AForm::GradeTooHighException::what() const throw() {
	return ("Grade too high");
}

const char *AForm::GradeTooLowException::what() const throw() {
	return ("Grade too low");
}

const char *AForm::FormNotSignedException::what() const throw() {
	return ("Form not signed");
}

std::ostream &operator<<(std::ostream &out, const AForm &form) {
	out << form.getName() << ", form grade sign " << form.getGradeSign() << ", form grade req " << form.getGradeReq() << ", is signed " << form.getIsSigned();
	return (out);
}

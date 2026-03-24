/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Form.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tolanini <tolanini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/24 16:51:49 by tolanini          #+#    #+#             */
/*   Updated: 2026/03/24 16:51:49 by tolanini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Form.hpp"
#include "Bureaucrat.hpp"

Form::Form() : name("default"), gradeSign(150), gradeReq(150), isSigned(false) {
	std::cout << "Default constructor called" << std::endl;
}

Form::Form(const std::string name, const int gradeSign, const int gradeReq) : name(name), gradeSign(gradeSign), gradeReq(gradeReq), isSigned(false) {
	if (gradeSign < 1 || gradeReq < 1)
		throw GradeTooHighException();
	if (gradeSign > 150 || gradeReq > 150)
		throw GradeTooLowException();
	std::cout << "Constructor called" << std::endl;
}

Form::Form(const Form &copy) : name(copy.name), gradeSign(copy.gradeSign), gradeReq(copy.gradeReq), isSigned(copy.isSigned) {
	std::cout << "Copy constructor called" << std::endl;
}

Form &Form::operator=(const Form &copy) {
	std::cout << "Copy assignment operator called" << std::endl;
	if (this != &copy)
		this->isSigned = copy.isSigned;
	return (*this);
}

Form::~Form() {
	std::cout << "Form destructor called" << std::endl;
}

std::string Form::getName() const {
	return (this->name);
}

int Form::getGradeSign() const {
	return (this->gradeSign);
}

int Form::getGradeReq() const {
	return (this->gradeReq);
}

bool Form::getIsSigned() const {
	return (this->isSigned);
}

void Form::beSigned(const Bureaucrat &bureaucrat) {
	if (bureaucrat.getGrade() > this->gradeSign)
		throw GradeTooLowException();
	this->isSigned = true;
}

const char *Form::GradeTooHighException::what() const throw() {
	return ("Grade too high");
}

const char *Form::GradeTooLowException::what() const throw() {
	return ("Grade too low");
}


std::ostream &operator<<(std::ostream &out, const Form &form) {
	out << form.getName() << ", form grade sign " << form.getGradeSign() << ", form grade req " << form.getGradeReq() << ", is signed " << form.getIsSigned();
	return (out);
}

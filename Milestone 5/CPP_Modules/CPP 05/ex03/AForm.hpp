/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   AForm.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tolanini <tolanini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/24 16:57:53 by tolanini          #+#    #+#             */
/*   Updated: 2026/03/24 16:57:53 by tolanini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FORM_HPP
#define FORM_HPP

#include <string>
#include <iostream>
#include <exception>
#include "Bureaucrat.hpp"

class Bureaucrat;

class AForm {
	private:
		const std::string name;
		const int gradeSign;
		const int gradeReq;
		bool isSigned; 
	public:
		AForm();
		AForm(const std::string name, const int gradeSign, const int gradeReq);
		AForm(const AForm &copy);
		AForm &operator=(const AForm &copy);
		virtual ~AForm();

		std::string getName() const;
		int getGradeSign() const;
		int getGradeReq() const;
		bool getIsSigned() const;
		void beSigned(const Bureaucrat &bureaucrat);
		
		virtual void execute(Bureaucrat const &executor) const = 0;

		class GradeTooHighException : public std::exception {
			public:
				const char *what() const throw();
		};

		class GradeTooLowException : public std::exception {
			public:
				const char *what() const throw();
		};

		class FormNotSignedException : public std::exception {
			public:
				const char *what() const throw();
		};
};

std::ostream &operator<<(std::ostream &out, const AForm &form);

#endif
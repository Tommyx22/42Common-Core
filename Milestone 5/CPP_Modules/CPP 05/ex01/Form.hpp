/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Form.hpp                                           :+:      :+:    :+:   */
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

class Bureaucrat;

class Form {
	private:
		const std::string name;
		const int gradeSign;
		const int gradeReq;
		bool isSigned; 
	public:
		Form();
		Form(const std::string name, const int gradeSign, const int gradeReq);
		Form(const Form &copy);
		Form &operator=(const Form &copy);
		~Form();
		std::string getName() const;
		int getGradeSign() const;
		int getGradeReq() const;
		bool getIsSigned() const;
		void beSigned(const Bureaucrat &bureaucrat);

		class GradeTooHighException : public std::exception {
			public:
				const char *what() const throw();
		};

		class GradeTooLowException : public std::exception {
			public:
				const char *what() const throw();
		};
};

std::ostream &operator<<(std::ostream &out, const Form &form);

#endif
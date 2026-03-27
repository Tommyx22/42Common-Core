/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PresidentialPardonForm.hpp                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tolanini <tolanini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/26 23:06:21 by tolanini          #+#    #+#             */
/*   Updated: 2026/03/27 15:45:13 by tolanini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PRESIDENTIALPARDONFORM_HPP
#define PRESIDENTIALPARDONFORM_HPP

#include "AForm.hpp"

class Bureaucrat;

class PresidentialPardonForm : public AForm {
	private:
		std::string target;
	public:
		PresidentialPardonForm();
		PresidentialPardonForm(const std::string &target);
		PresidentialPardonForm(const PresidentialPardonForm &copy);
		PresidentialPardonForm &operator=(const PresidentialPardonForm &copy);
		~PresidentialPardonForm();

		std::string getTarget() const;
		void execute(const Bureaucrat &executor) const;
};

std::ostream &operator<<(std::ostream &out, const AForm &form);

#endif
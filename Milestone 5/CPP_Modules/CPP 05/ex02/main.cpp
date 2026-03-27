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

static void printTitle(const std::string &title) {
	std::cout << "\n==============================" << std::endl;
	std::cout << title << std::endl;
	std::cout << "==============================" << std::endl;
}

int main() {
	Bureaucrat chief("Chief", 1);
	Bureaucrat exec5("Exec5", 5);
	Bureaucrat signer25("Signer25", 25);
	Bureaucrat manager40("Manager40", 40);
	Bureaucrat signer70("Signer70", 70);
	Bureaucrat worker130("Worker130", 130);
	Bureaucrat low150("Low150", 150);

	printTitle("TEST 1: SHRUBBERY - EXECUTE UNSIGNED (FAIL)");
	{
		ShrubberyCreationForm form("garden_unsigned");
		worker130.executeForm(form);
	}

	printTitle("TEST 2: SHRUBBERY - LOW GRADE SIGN (FAIL)");
	{
		ShrubberyCreationForm form("garden_sign_fail");
		low150.signForm(form);
	}

	printTitle("TEST 3: SHRUBBERY - SIGN + EXECUTE (SUCCESS)");
	{
		ShrubberyCreationForm form("garden_ok");
		worker130.signForm(form);
		worker130.executeForm(form);
	}

	printTitle("TEST 4: ROBOTOMY - LOW EXEC GRADE (FAIL)");
	{
		RobotomyRequestForm form("Bender");
		signer70.signForm(form);
		worker130.executeForm(form);
	}

	printTitle("TEST 5: ROBOTOMY - EXECUTION (RANDOM)");
	{
		RobotomyRequestForm form("Marvin");
		signer70.signForm(form);
		manager40.executeForm(form);
	}

	printTitle("TEST 6: PRESIDENTIAL - LOW SIGN GRADE (FAIL)");
	{
		PresidentialPardonForm form("Arthur Dent");
		manager40.signForm(form);
	}

	printTitle("TEST 7: PRESIDENTIAL - LOW EXEC GRADE (FAIL)");
	{
		PresidentialPardonForm form("Ford Prefect");
		signer25.signForm(form);
		manager40.executeForm(form);
	}

	printTitle("TEST 8: PRESIDENTIAL - SIGN + EXECUTE (SUCCESS)");
	{
		PresidentialPardonForm form("Zaphod Beeblebrox");
		signer25.signForm(form);
		exec5.executeForm(form);
	}

	printTitle("TEST 9: ALL FORMS (SUCCESS)");
	{
		ShrubberyCreationForm shrub("final_tree");
		RobotomyRequestForm robot("HAL9000");
		PresidentialPardonForm pardon("Trillian");

		chief.signForm(shrub);
		chief.executeForm(shrub);

		chief.signForm(robot);
		chief.executeForm(robot);

		chief.signForm(pardon);
		chief.executeForm(pardon);
		std::cout << std::endl;
	}

	return (0);
}
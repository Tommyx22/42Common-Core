/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Contact.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tolanini <tolanini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/11 17:47:30 by tolanini          #+#    #+#             */
/*   Updated: 2025/11/11 17:56:37 by tolanini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Contact.hpp"

std::string prompt_non_empty(const std::string& prompt) {
	std::string input;
	while (true) {
		std::cout << prompt;
		if (!std::getline(std::cin, input))
			std::exit(0);
		if (!input.empty())
			return input;
		std::cout << "This field cannot be empty. Please try again." << std::endl;
	}
	return input;
}

void Contact::create_contact() {
	set_first_name(prompt_non_empty("Enter First Name: "));
	set_last_name(prompt_non_empty("Enter Last Name: "));
	set_nickname(prompt_non_empty("Enter Nickname: "));
	set_phone_number(prompt_non_empty("Enter Phone Number: "));
	set_secret(prompt_non_empty("Enter Darkest Secret: "));
}
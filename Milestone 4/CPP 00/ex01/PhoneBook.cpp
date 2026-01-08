/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PhoneBook.cpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tolanini <tolanini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/11 17:47:38 by tolanini          #+#    #+#             */
/*   Updated: 2026/01/08 14:31:45 by tolanini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "PhoneBook.hpp"

static std::string truncate_string(const std::string& str) {
	if (str.length() > 10)
		return str.substr(0, 9) + ".";
	return str;
}

void PhoneBook::add_contact(const Contact& c) {
	if (contact_count == MAX_CONTACTS) {
		for (int i = 1; i < MAX_CONTACTS; i++)
			contacts[i - 1] = contacts[i];
		contacts[MAX_CONTACTS - 1] = c;
		std::cout << "Phone book is full. Oldest contact overwritten." << std::endl;
	} else {
		contacts[contact_count] = c;
		contact_count++;
		std::cout << "Contact added successfully." << std::endl;
	}
}

void PhoneBook::search_contacts() {
	if (contact_count == 0) {
		std::cout << "Phone book is empty." << std::endl;
		return;
	}
	std::cout << std::setw(10) << "Index" << "|"
			  << std::setw(10) << "First Name" << "|"
			  << std::setw(10) << "Last Name" << "|"
			  << std::setw(10) << "Nickname" << std::endl;
	for (int i = 0; i < contact_count; i++) {
		std::cout << std::setw(10) << i + 1 << "|"
				  << std::setw(10) << truncate_string(contacts[i].get_first_name()) << "|"
				  << std::setw(10) << truncate_string(contacts[i].get_last_name()) << "|"
				  << std::setw(10) << truncate_string(contacts[i].get_nickname()) << std::endl;
	}
	int input;
	int index;
	while (true) {        
		std::cout << "Enter the index of the contact (1-" << contact_count << "): ";
		if (!(std::cin >> input)) {
			std::cout << "Invalid input. Please enter a number." << std::endl;
			std::cin.clear();
			std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			continue;
		}
		std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		if (input < 1 || input > contact_count) 
			std::cout << "Invalid index." << std::endl;
		else {
			index = input - 1;    
			break;
		}
	}
	std::cout << "\n--- Contact Details ---" << std::endl;
	std::cout << "Index: " << index + 1 << std::endl;
	std::cout << "First Name: " << contacts[index].get_first_name() << std::endl;
	std::cout << "Last Name: " << contacts[index].get_last_name() << std::endl;
	std::cout << "Nickname: " << contacts[index].get_nickname() << std::endl;
	std::cout << "Phone Number: " << contacts[index].get_phone_number() << std::endl;
	std::cout << "Darkest Secret: " << contacts[index].get_secret() << std::endl;
}
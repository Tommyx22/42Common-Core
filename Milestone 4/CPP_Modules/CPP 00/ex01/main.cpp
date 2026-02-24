/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tolanini <tolanini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/23 10:38:55 by tolanini          #+#    #+#             */
/*   Updated: 2025/11/11 17:56:17 by tolanini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "PhoneBook.hpp"



int main() {
	PhoneBook phone_book;
	std::string command;

	std::cout << "Enter a command (ADD, SEARCH, EXIT): " << std::endl;
	if (!std::getline(std::cin, command))
	{
		std::cout << "Error reading input." << std::endl;
		return 1;
	}
	while (command != "EXIT") {
		if (command == "ADD") 
		{
			Contact c;
			c.create_contact();
			phone_book.add_contact(c);
		}
		if (command == "SEARCH")
		{
			phone_book.search_contacts();
		}
		std::cout << "Enter a command (ADD, SEARCH, EXIT): " << std::endl;
		if (!std::getline(std::cin, command))
		{
			std::cout << "Error reading input." << std::endl;
			return 1;
		}
	}
	return 0;
}
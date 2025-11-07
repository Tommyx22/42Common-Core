/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tolanini <tolanini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/23 10:38:55 by tolanini          #+#    #+#             */
/*   Updated: 2025/11/07 18:12:22 by tolanini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include.hpp"

std::string add_contact()
{
    Contact new_contact;
    std::string input;

    std::cout << "Enter first name: ";
    std::getline(std::cin, input);
    if (input.empty()) return "First name cannot be empty.";
    new_contact.set_first_name(input);

    std::cout << "Enter last name: ";
    std::getline(std::cin, input);
    if (input.empty()) return "Last name cannot be empty.";
    new_contact.set_last_name(input);

    std::cout << "Enter nickname: ";
    std::getline(std::cin, input);
    if (input.empty()) return "Nickname cannot be empty.";
    new_contact.set_nickname(input);

    std::cout << "Enter phone number: ";
    std::getline(std::cin, input);
    if (input.empty()) return "Phone number cannot be empty.";
    new_contact.set_phone_number(input);

    std::cout << "Enter darkest secret: ";
    std::getline(std::cin, input);
    if (input.empty()) return "Darkest secret cannot be empty.";
    new_contact.set_secret(input);

    return "";
}

int main() {
    PhoneBook phone_book;
    std::string command;

    while (true) {
        std::cout << "Enter a command (ADD, SEARCH, EXIT): ";
        std::getline(std::cin, command);

        if (command == "ADD") {
            std::string error = phone_book.add_contact();
            if (!error.empty()) {
                std::cout << error << std::endl;
            }
        } else if (command == "SEARCH") {
            phone_book.search_contacts();
        } else if (command == "EXIT") {
            break;
        } else {
            std::cout << "Invalid command. Please try again." << std::endl;
        }
    }

    return 0;
}
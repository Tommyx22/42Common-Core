/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tolanini <tolanini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/08 17:22:01 by tolanini          #+#    #+#             */
/*   Updated: 2026/01/08 17:43:48 by tolanini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string>
#include <iostream>

int main() {
	std::string str = "HI THIS IS BRAIN";
	std::string* pointer = &str;
	std::string& reference = str;

	std::cout << "String address: " << &str << std::endl;
	std::cout << "Pointer address: " << pointer << std::endl;
	std::cout << "Reference address: " << &reference << std::endl;

	std::cout << "String value: " << str << std::endl;
	std::cout << "Pointer value: " << *pointer <<  std::endl;
	std::cout << "Reference value: " << reference << std::endl;
	return 0;
}
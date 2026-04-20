/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tolanini <tolanini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/20 02:15:31 by tolanini          #+#    #+#             */
/*   Updated: 2026/04/20 02:15:59 by tolanini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Array.hpp"

int main () {
	Array<int> intArray(5);
	Array<std::string> stringArray(3);

	for (unsigned int i = 0; i < intArray.size(); i++) {
		intArray[i] = i + 1;
	}

	stringArray[0] = "Hello";
	stringArray[1] = "World";
	stringArray[2] = "!";

	std::cout << "Integer Array: ";
	for (unsigned int i = 0; i < intArray.size(); i++) {
		std::cout << intArray[i] << " ";
	}
	std::cout << std::endl;

	std::cout << "String Array: ";
	for (unsigned int i = 0; i < stringArray.size(); i++) {
		std::cout << stringArray[i] << " ";
	}
	std::cout << std::endl;

	return 0;
}
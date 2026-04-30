/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tolanini <tolanini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/28 14:09:32 by tolanini          #+#    #+#             */
/*   Updated: 2026/04/28 14:25:29 by tolanini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "easyfind.hpp"

int main() {
	std::vector<int> v;
	v.push_back(1);
	v.push_back(2);
	v.push_back(3);
	
	try {
		std::cout << easyfind(v, 2) << std::endl;
		std::cout << easyfind(v, 4) << std::endl;
	} 
	catch (std::exception &e) {
		std::cout << "Value not found" << std::endl;
	}
}
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tolanini <tolanini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/28 14:09:32 by tolanini          #+#    #+#             */
/*   Updated: 2026/05/06 16:51:03 by tolanini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "PmergeMe.hpp"

int main(int argc, char **argv) {
	if (argc != 2) {
		std::cerr << "Error: invalid number of arguments" << std::endl;
		return 1;
	}
	try {
		PmergeMe pmergeMe;
		pmergeMe.process(argv[1]);
	} catch (const std::exception &e) {
		std::cerr << "Error: " << e.what() << std::endl;
		return 1;
	}
	return 0;
}
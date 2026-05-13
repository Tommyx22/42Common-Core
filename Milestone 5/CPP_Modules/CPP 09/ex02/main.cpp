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
	if (argc < 2) {
		std::cerr << "Error" << std::endl;
		return 1;
	}
	try {
		PmergeMe pmergeMe;
		pmergeMe.process(argc - 1, argv + 1);
	} catch (const std::exception &e) {
		std::cerr << "Error" << std::endl;
		return 1;
	}
	return 0;
}
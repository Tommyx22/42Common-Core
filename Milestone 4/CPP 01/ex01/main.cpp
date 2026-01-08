/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tolanini <tolanini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/08 16:19:23 by tolanini          #+#    #+#             */
/*   Updated: 2026/01/08 17:14:55 by tolanini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Zombie.hpp"

int main() {
	int	N = 0;
	std::string	name;
	std::cout << "Enter the number of zombies to create: ";
	std::cin >> N;
	std::cout << "Enter the name for the zombies: ";
	std::cin >> name;
	Zombie* horde = zombieHorde(N, name);
	if (horde == NULL) {
		std::cerr << "Failed to create zombie horde." << std::endl;
		return 1;
	}
	for (int i = 0; i < N; i++) {
		horde[i].announce();
	}
	delete[] horde;
	return 0;
}
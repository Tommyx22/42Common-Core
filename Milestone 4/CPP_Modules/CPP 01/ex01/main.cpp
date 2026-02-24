/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tolanini <tolanini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/08 16:19:23 by tolanini          #+#    #+#             */
/*   Updated: 2026/02/24 14:33:24 by tolanini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Zombie.hpp"

int main() {
	Zombie* horde = zombieHorde(12, "Horde");
	if (horde == NULL) {
		std::cerr << "Failed to create zombie horde." << std::endl;
		return 1;
	}
	for (int i = 0; i < 12; i++) {
		horde[i].announce();
	}
	delete[] horde;
	return 0;
}
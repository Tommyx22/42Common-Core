/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tolanini <tolanini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/15 16:23:43 by tolanini          #+#    #+#             */
/*   Updated: 2026/01/15 17:19:20 by tolanini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ScavTrap.hpp"

int main() {
	ScavTrap test("Bob");
	test.attack("Alice");
	test.takeDamage(5);
	test.beRepaired(3);
	test.guardGate();
	return 0;
}
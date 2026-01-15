/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tolanini <tolanini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/15 16:23:43 by tolanini          #+#    #+#             */
/*   Updated: 2026/01/15 17:27:36 by tolanini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "FragTrap.hpp"

int main() {
	FragTrap test("Bob");
	test.attack("Alice");
	test.takeDamage(5);
	test.beRepaired(3);
	test.highFivesGuys();
	return 0;
}
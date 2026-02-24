/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tolanini <tolanini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/08 16:19:23 by tolanini          #+#    #+#             */
/*   Updated: 2026/01/08 17:04:10 by tolanini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Zombie.hpp"

int main() {
	Zombie* heapZombie = newZombie("Heap Zombie");
	heapZombie->announce();
	delete heapZombie;
	randomChump("Stack Zombie");
	return 0;
}
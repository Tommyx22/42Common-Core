/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Zombie.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tolanini <tolanini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/08 16:19:47 by tolanini          #+#    #+#             */
/*   Updated: 2026/01/08 17:08:21 by tolanini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Zombie.hpp"

Zombie::~Zombie() {
	std::cout << get_name() << " is being destroyed" << std::endl;
}

void Zombie::announce() {
	std::cout << get_name() << ": BraiiiiiiinnnzzzZ..." << std::endl;
}

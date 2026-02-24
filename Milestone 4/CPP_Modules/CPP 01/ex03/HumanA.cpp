/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   HumanA.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tolanini <tolanini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/08 17:47:35 by tolanini          #+#    #+#             */
/*   Updated: 2026/01/08 18:29:49 by tolanini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "HumanA.hpp"

HumanA::HumanA(const std::string &name, Weapon &weapon) : name(name), weapon(weapon) {}

void HumanA::attack() {
	std::cout << name << " attacks with their " << weapon.getType() << std::endl;
}
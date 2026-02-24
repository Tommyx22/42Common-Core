/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   HumanB.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tolanini <tolanini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/08 17:47:40 by tolanini          #+#    #+#             */
/*   Updated: 2026/01/08 18:29:53 by tolanini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#ifndef HUMANB_HPP
#define HUMANB_HPP

#include "Weapon.hpp"
#include <string>
#include <iostream>

class HumanB {
	private:
		std::string name;
		Weapon *weapon;

	public:
		HumanB(const std::string &name);
		void setWeapon(Weapon &weapon);
		void attack() const;
};

#endif


/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ClapTrap.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tolanini <tolanini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/15 16:23:50 by tolanini          #+#    #+#             */
/*   Updated: 2026/01/15 16:58:53 by tolanini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ClapTrap.hpp"

ClapTrap::ClapTrap() : name("Default"), hitPoints(10), energyPoints(10), attackDamage(0) {
	std::cout << "Default ClapTrap constructor called" << std::endl;
}

ClapTrap::ClapTrap(std::string name) : name(name), hitPoints(10), energyPoints(10), attackDamage(0) {
	std::cout << name << " Claptrap constructor called" << std::endl;
}

ClapTrap::ClapTrap(const ClapTrap &copy) {
	std::cout << "ClapTrap copy constructor called" << std::endl;
	*this = copy;
}

ClapTrap &ClapTrap::operator=(const ClapTrap &copy) {
	std::cout << "ClapTrap copy assignment operator called" << std::endl;
	if (this != &copy) {
		this->name = copy.name;
		this->hitPoints = copy.hitPoints;
		this->energyPoints = copy.energyPoints;
		this->attackDamage = copy.attackDamage;
	}
	return *this;
}

ClapTrap::~ClapTrap() {
	std::cout << this->name << "ClapTrap destructor called" << std::endl;
}


void ClapTrap::attack(const std::string& target) {
	if (hitPoints == 0 || energyPoints == 0) {
		std::cout << "Invalid attack!" << std::endl;
		return ;
	}
	energyPoints--;
	std::cout << "ClapTrap " << this->name << " attacks " << target << ", causing " << this->attackDamage << " points of damage!" << std::endl;
}


void ClapTrap::takeDamage(unsigned int amount) {
	if (hitPoints == 0) {
		std::cout << "Invalid attack!" << std::endl;
		return ;
	}
	if (amount >= hitPoints) {
		hitPoints = 0;
	} else {
		hitPoints -= amount;
	}
	std::cout << "ClapTrap " << this->name << " lost " << amount << " of hitpoints!" << std::endl;
}


void ClapTrap::beRepaired(unsigned int amount) {
	if (hitPoints == 0 || energyPoints == 0) {
		std::cout << "Invalid repairing!" << std::endl;
		return ;
	}
	energyPoints--;
	if (hitPoints + amount >= hitPoints) {
		hitPoints = 10;
	} else {
		hitPoints += amount;
	}
	std::cout << "ClapTrap " << this->name << " healed for a total of " << amount << " hitpoints!" << std::endl;
}
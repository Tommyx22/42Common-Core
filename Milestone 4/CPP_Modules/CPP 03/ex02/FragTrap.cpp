/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   FragTrap.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tolanini <tolanini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/15 17:20:55 by tolanini          #+#    #+#             */
/*   Updated: 2026/01/15 17:27:00 by tolanini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "FragTrap.hpp"

FragTrap::FragTrap() : ClapTrap() {
	std::cout << "FragTrap default constructor called" << std::endl;
	this->name = "Default";
	this->hitPoints = 100;
	this->energyPoints = 100;
	this->attackDamage = 30;
}

FragTrap::FragTrap(std::string name) : ClapTrap() {
	std::cout << name << " FragTrap constructor called" << std::endl;
	this->name = name;
	this->hitPoints = 100;
	this->energyPoints = 100;
	this->attackDamage = 30;
}

FragTrap::FragTrap(const FragTrap &copy) : ClapTrap(copy) {
	std::cout << "FragTrap copy constructor called" << std::endl;
	*this = copy;
}

FragTrap &FragTrap::operator=(const FragTrap &copy) {
	std::cout << "FragTrap copy assignment operator called" << std::endl;
	if (this != &copy) {
		this->name = copy.name;
		this->hitPoints = copy.hitPoints;
		this->energyPoints = copy.energyPoints;
		this->attackDamage = copy.attackDamage;
	}
	return *this;
}

FragTrap::~FragTrap() {
	std::cout << this->name << " FragTrap destructor called" << std::endl;
}

void FragTrap::highFivesGuys() {
	std::cout << this->name << " FragTrap want to high five" << std::endl;
}
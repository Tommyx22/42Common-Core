/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tolanini <tolanini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/20 13:56:06 by tolanini          #+#    #+#             */
/*   Updated: 2026/01/20 16:17:16 by tolanini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Animal.hpp"
#include "Dog.hpp"
#include "Cat.hpp"
#include "WrongAnimal.hpp"
#include "WrongCat.hpp"
#include "Brain.hpp"

int main()
{
	const Animal* j = new Dog();
	const Animal* i = new Cat();
	delete j;//should not create a leak
	delete i;
	

	std::cout << "=== Polymorphism test ===" << std::endl;
	const Animal* animals[4];
	for (int i = 0; i < 4; ++i) {
		if (i < 2)
			animals[i] = new Dog();
		else
			animals[i] = new Cat();
	}
	for (int i = 0; i < 4; ++i)
		animals[i]->makeSound();
	for (int i = 0; i < 4; ++i)
		delete animals[i];

	std::cout << "\n=== Copy / Assignment test ===" << std::endl;
	Cat original;
	Cat copyConstructed = original; // copy constructor
	Cat assigned;
	assigned = original; // copy assignment operator

	return 0;
}

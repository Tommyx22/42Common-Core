/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tolanini <tolanini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/14 14:53:46 by tolanini          #+#    #+#             */
/*   Updated: 2026/04/14 15:56:21 by tolanini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Base.hpp"
#include "utils.hpp"

int main() {
	std::srand(std::time(0));

	Base* basePtr = generate();
	identify(basePtr);
	identify(*basePtr);

	delete basePtr;
	return 0;	
}

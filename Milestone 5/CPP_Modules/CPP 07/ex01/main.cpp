/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tolanini <tolanini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/20 01:32:46 by tolanini          #+#    #+#             */
/*   Updated: 2026/04/20 01:52:46 by tolanini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "iter.hpp"

template <typename T>
void print(const T &value) {
	std::cout << value << " ";
}

int main() {
	int values[] = {1, 2, 3, 4, 5};

	std::cout << "Print test: ";
	iter(values, 5, print<int>);
	std::cout << std::endl;

	return 0;
}
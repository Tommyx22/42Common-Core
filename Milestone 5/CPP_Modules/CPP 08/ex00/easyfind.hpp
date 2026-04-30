/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   easyfind.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tolanini <tolanini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/28 14:09:48 by tolanini          #+#    #+#             */
/*   Updated: 2026/04/28 14:26:34 by tolanini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EASYFIND_HPP
#define EASYFIND_HPP

#include <iostream>
#include <vector>
#include <algorithm>

template <typename T>
int easyfind(T &container, int value) {
	if (std::find(container.begin(), container.end(), value) == container.end())
		throw std::exception();
	return *std::find(container.begin(), container.end(), value); 
}

#endif
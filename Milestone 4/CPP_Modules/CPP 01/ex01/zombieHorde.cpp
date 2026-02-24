/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   zombieHorde.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tolanini <tolanini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/08 17:08:14 by tolanini          #+#    #+#             */
/*   Updated: 2026/02/24 14:34:09 by tolanini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Zombie.hpp"

Zombie*	zombieHorde( int N, std::string name ) {
	if (N <= 0)
		return NULL;
	Zombie* horde = new (std::nothrow) Zombie[N];
	if (!horde)
		return NULL;
	for (int i = 0; i < N; i++) {
		horde[i].set_name(name);
	}
	return horde;
}
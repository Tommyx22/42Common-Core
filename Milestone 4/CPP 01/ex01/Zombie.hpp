/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Zombie.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tolanini <tolanini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/08 16:19:37 by tolanini          #+#    #+#             */
/*   Updated: 2026/02/24 14:34:10 by tolanini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ZOMBIE_HPP
#define ZOMBIE_HPP

# include <string>
# include <iostream>
# include <new>

class Zombie {
	private: 
		
		std::string name;
	public:

		Zombie() : name("") {}
		~Zombie();
		
		inline std::string get_name() const { return name; }
		
		void set_name(const std::string &name) {
			this->name = name;
		}

		void announce ();
};
Zombie*	zombieHorde( int N, std::string name );

#endif
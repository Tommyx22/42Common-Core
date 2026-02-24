/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Zombie.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tolanini <tolanini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/08 16:19:37 by tolanini          #+#    #+#             */
/*   Updated: 2026/01/08 16:50:16 by tolanini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ZOMBIE_HPP
#define ZOMBIE_HPP

# include <string>
# include <iostream>

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

Zombie*	newZombie( std::string name );
void	randomChump( std::string name );

#endif
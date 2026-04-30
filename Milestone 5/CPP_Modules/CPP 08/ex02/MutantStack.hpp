/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   MutantStack.hpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tolanini <tolanini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/30 17:43:02 by tolanini          #+#    #+#             */
/*   Updated: 2026/04/30 18:06:20 by tolanini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MUTANTSTACK_HPP
#define MUTANTSTACK_HPP

#include <stack>
#include <iostream>

template<typename T>
class MutantStack : public std::stack<T> {
	public:

		MutantStack<T>()
		{
			std::cout << "Constructor called" << std::endl;
		}

		MutantStack<T>(MutantStack<T> const &copy) : std::stack<T>(copy)
		{
			std::cout << "Copy Constructor called" << std::endl;
		}

		~MutantStack<T>(void)
		{
			std::cout << "Destructor called" << std::endl;
		}

		MutantStack<T> &operator=(const MutantStack<T> &copy)
		{
			std::cout << "Copy assignment operator called" << std::endl;
			if (this != &copy)
				std::stack<T>::operator=(copy);
			return (*this);
		}
		
		typedef typename std::stack<T>::container_type::iterator iterator;
		iterator begin() {
			return this->c.begin();
		}

		iterator end() {
			return this->c.end();
		}
		
		typedef typename std::stack<T>::container_type::const_iterator const_iterator;
		const_iterator begin() const {
			return this->c.begin();
		}
		
		const_iterator end() const {
			return this->c.end();
		}

		typedef typename std::stack<T>::container_type::reverse_iterator reverse_iterator;
		reverse_iterator rbegin() {
			return this->c.rbegin();
		}

		reverse_iterator rend() {
			return this->c.rend();
		}
		
		typedef typename std::stack<T>::container_type::const_reverse_iterator const_reverse_iterator;
		const_reverse_iterator rbegin() const {
			return this->c.rbegin();
		}

		const_reverse_iterator rend() const {
			return this->c.rend();
		}
};
#endif
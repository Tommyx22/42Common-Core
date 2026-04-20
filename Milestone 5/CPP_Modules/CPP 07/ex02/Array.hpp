/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Array.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tolanini <tolanini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/20 01:59:59 by tolanini          #+#    #+#             */
/*   Updated: 2026/04/20 02:16:27 by tolanini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ARRAY_HPP
#define ARRAY_HPP

#include <iostream>

template <typename T>
class Array {
	private:
		T* _array;
		unsigned int _size;
	public:
		Array();
		Array(unsigned int n);
		Array(const Array& other);
		Array& operator=(const Array& other);
		~Array();
		T& operator[](unsigned int index);
		const T& operator[](unsigned int index) const;
		unsigned int size() const;
		class OutOfBoundsException : public std::exception {
			public:
				virtual const char* what() const throw();
		};
		
};

#include "Array.tpp"

#endif
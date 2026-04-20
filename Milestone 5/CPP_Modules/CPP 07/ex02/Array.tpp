/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Array.tpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tolanini <tolanini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/20 02:03:45 by tolanini          #+#    #+#             */
/*   Updated: 2026/04/20 02:18:47 by tolanini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ARRAY_TPP
#define ARRAY_TPP

#include "Array.hpp"

template <typename T>
Array<T>::Array() : _array(NULL), _size(0) {
	std::cout << "Default constructor called" << std::endl;
}

template <typename T>
Array<T>::Array(unsigned int n) : _array(new T[n]()), _size(n) {
	std::cout << "Constructor called" << std::endl;
}

template <typename T>
Array<T>::Array(const Array& other) : _array(new T[other._size]), _size(other._size) {
	std::cout << "Copy constructor called" << std::endl;
	for (unsigned int i = 0; i < _size; i++) {
		_array[i] = other._array[i];
	}
}

template <typename T>
Array<T>& Array<T>::operator=(const Array& other) {
	std::cout << "Copy assignment operator called" << std::endl;
	if (this != &other) {
		delete[] _array;
		_size = other._size;
		_array = new T[_size];
		for (unsigned int i = 0; i < _size; i++) {
			_array[i] = other._array[i];
		}
	}
	return *this;
}

template <typename T>
Array<T>::~Array() {
	std::cout << "Destructor called" << std::endl;
	delete[] _array;
}

template <typename T>
T& Array<T>::operator[](unsigned int index) {
	if (index >= _size) {
		throw OutOfBoundsException();
	}
	return _array[index];
}

template <typename T>
const T& Array<T>::operator[](unsigned int index) const {
	if (index >= _size) {
		throw OutOfBoundsException();
	}
	return _array[index];
}

template <typename T>
unsigned int Array<T>::size() const {
	return _size;
}

template <typename T>
const char* Array<T>::OutOfBoundsException::what() const throw() {
	return "Index out of bounds";
}

#endif
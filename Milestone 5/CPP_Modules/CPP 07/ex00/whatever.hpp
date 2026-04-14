/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   whatever.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tolanini <tolanini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/14 16:01:06 by tolanini          #+#    #+#             */
/*   Updated: 2026/04/14 16:06:54 by tolanini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef WHATEVER_HPP
#define WHATEVER_HPP

#include <iostream>
#include <string>


template <typename T>
void swap(T &a, T &b) {
	T temp = a;
	a = b;
	b = temp;
}

template <typename T>
T min(T a, T b) {
	if (a < b)
		return a;
	else
		return b;
}

template <typename T>
T max(T a, T b) {
	if (a > b)
		return a;
	else
		return b;
} 

#endif
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Span.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tolanini <tolanini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/28 14:29:24 by tolanini          #+#    #+#             */
/*   Updated: 2026/04/30 17:36:48 by tolanini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SPAN_HPP
#define SPAN_HPP

#include <iostream>
#include <vector>

class Span {
	private:
		unsigned int N;
		std::vector<int> v;
	public:
		Span();
		Span(unsigned int N);
		Span(const Span& other);
		Span& operator=(const Span& other);
		~Span();
		void addNumber(int number);
		int shortestSpan() const;
		int longestSpan() const;
		
		class SpanFullException : public std::exception {
			public:
				virtual const char* what() const throw();
		};

		class NotEnoughNumbersException : public std::exception {
			public:
				virtual const char* what() const throw();
		};
};

#endif
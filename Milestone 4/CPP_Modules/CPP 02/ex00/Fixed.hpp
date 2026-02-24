/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Fixed.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tolanini <tolanini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/14 14:45:24 by tolanini          #+#    #+#             */
/*   Updated: 2026/01/14 14:49:38 by tolanini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FIXED_HPP
#define FIXED_HPP

#include <iostream>

class Fixed {
	private:
		int fixedPointNumber;
		static const int fractonalBits = 8;
	public:
		Fixed();
		Fixed(const Fixed &copy);
		Fixed &operator=(const Fixed &copy);
		~Fixed();
		int getRawBits( void ) const;
		void setRawBits( int const raw );
};

#endif
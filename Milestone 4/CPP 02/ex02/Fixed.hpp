/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Fixed.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tolanini <tolanini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/14 16:31:59 by tolanini          #+#    #+#             */
/*   Updated: 2026/01/14 18:14:43 by tolanini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FIXED_HPP
#define FIXED_HPP

#include <iostream>
#include <cmath>

class Fixed {
	private:
		int fixedPointNumber;
		static const int fractonalBits = 8;
	public:
		Fixed();
		Fixed(const int number);
		Fixed(const float floater);
		Fixed(const Fixed &copy);
		Fixed &operator=(const Fixed &copy);
		~Fixed();
		int		getRawBits( void ) const;
		void	setRawBits( int const raw );
		float	toFloat( void ) const;
		int		toInt( void ) const;
		bool	operator>(const Fixed &copy) const;
		bool	operator<(const Fixed &copy) const;
		bool	operator>=(const Fixed &copy) const;
		bool	operator<=(const Fixed &copy) const;
		bool	operator==(const Fixed &copy) const;
		bool	operator!=(const Fixed &copy) const;
		Fixed	operator+(const Fixed &copy) const;
		Fixed	operator-(const Fixed &copy) const;
		Fixed	operator*(const Fixed &copy) const;
		Fixed	operator/(const Fixed &copy) const;
		Fixed	operator++(int);
		Fixed	operator--(int);
		Fixed	&operator++(void);
		Fixed	&operator--(void);
		static	Fixed &min(Fixed &a, Fixed &b);
		static	const Fixed &min (const Fixed &a, const Fixed &b); 
		static	Fixed &max(Fixed &a, Fixed &b);
		static	const Fixed &max(const Fixed &a, const Fixed &b);
};

std::ostream &operator<<(std::ostream &os, const Fixed &fixed);

#endif
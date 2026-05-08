/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RPN.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tolanini <tolanini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/08 17:38:35 by tolanini          #+#    #+#             */
/*   Updated: 2026/05/08 18:13:53 by tolanini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RPN_HPP
#define RPN_HPP

#include <iostream>
#include <stack>

class RPN {
	public:
		RPN();
		RPN(const RPN &copy);
		RPN &operator=(const RPN &copy);
		~RPN();
		static int calculate(const std::string &expression);
};

#endif
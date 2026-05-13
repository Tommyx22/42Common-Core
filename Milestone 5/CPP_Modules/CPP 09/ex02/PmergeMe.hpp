/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PmergeMe.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tolanini <tolanini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/08 18:25:38 by tolanini          #+#    #+#             */
/*   Updated: 2026/05/13 16:50:36 by tolanini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PMERGEME_HPP
#define PMERGEME_HPP

#include <iostream>
#include <vector>
#include <deque>
#include <ctime>
#include <cstdlib>
#include <sstream>
#include <iomanip>
#include <time.h>
#include <sys/time.h>

class PmergeMe {
	private:
		typedef std::vector<int> VectorType;
		typedef std::deque<int> DequeType;

		VectorType parseInput(int argc, char **argv);
		bool isValidPositiveInt(const std::string &str);

		template <typename Container>
		void mergeInsertSort(Container &container);

		template <typename Container>
		void fordJohnson(Container &container, int left, int right);

		template <typename Container>
		void binaryInsert(Container &container, int elem, int maxIdx);

		double getElapsedTime(struct timespec start, struct timespec end);
		
		template <typename Container>
		void displaySequence(const Container &container);

	public:
		PmergeMe();
		PmergeMe(const PmergeMe &other);
		PmergeMe &operator=(const PmergeMe &other);
		~PmergeMe();

		void process(int argc, char **argv);
};

#endif
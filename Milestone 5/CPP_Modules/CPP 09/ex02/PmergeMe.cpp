/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PmergeMe.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tolanini <tolanini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/08 18:25:34 by tolanini          #+#    #+#             */
/*   Updated: 2026/05/13 16:54:48 by tolanini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "PmergeMe.hpp"

PmergeMe::PmergeMe() {
}

PmergeMe::PmergeMe(const PmergeMe &other) {
	(void)other;
}

PmergeMe &PmergeMe::operator=(const PmergeMe &other) {
	(void)other;
	return *this;
}

PmergeMe::~PmergeMe() {
}

bool PmergeMe::isValidPositiveInt(const std::string &str) {
	if (str.empty())
		return false;
	for (size_t i = 0; i < str.length(); i++) {
		if (!std::isdigit(str[i]))
			return false;
	}
	long value = std::strtol(str.c_str(), NULL, 10);
	if (value <= 0 || value > 2147483647)
		return false;
	return true;
}

PmergeMe::VectorType PmergeMe::parseInput(int argc, char **argv) {
	VectorType result;
	for (int i = 0; i < argc; i++) {
		if (!isValidPositiveInt(argv[i])) {
			throw std::runtime_error("Invalid input");
		}
		result.push_back(std::atoi(argv[i]));
	}
	return result;
}

double PmergeMe::getElapsedTime(struct timespec start, struct timespec end) {
	double timeSort = static_cast<double>(end.tv_sec - start.tv_sec) * 1000000.0;
	timeSort += static_cast<double>(end.tv_nsec - start.tv_nsec) / 1000.0;
	return timeSort;
}

template <typename Container>
void PmergeMe::displaySequence(const Container &container) {
	for (size_t i = 0; i < container.size(); i++) {
		if (i > 0)
			std::cout << " ";
		std::cout << container[i];
	}
	std::cout << std::endl;
}

template <typename Container>
void PmergeMe::binaryInsert(Container &container, int elem, int maxIdx) {
	int left = 0;
	int right = maxIdx;
	while (left < right) {
		int mid = left + (right - left) / 2;
		if (container[mid] < elem)
			left = mid + 1;
		else
			right = mid;
	}
	container.insert(container.begin() + left, elem);
}

template <typename Container>
void PmergeMe::fordJohnson(Container &container, int left, int right) {
	if (right - left <= 1)
		return;
	
	VectorType larger;
	VectorType smaller;
	
	for (int i = left; i < right; i += 2) {
		if (i + 1 < right) {
			if (container[i] > container[i + 1]) {
				larger.push_back(container[i]);
				smaller.push_back(container[i + 1]);
			} else {
				larger.push_back(container[i + 1]);
				smaller.push_back(container[i]);
			}
		} else
			smaller.push_back(container[i]);
	}
	
	if (larger.size() > 1)
		fordJohnson(larger, 0, larger.size());
	
	container.erase(container.begin() + left, container.end());
	for (size_t i = 0; i < larger.size(); i++) {
		container.push_back(larger[i]);
	}
	
	for (size_t i = 0; i < smaller.size(); i++) {
		binaryInsert(container, smaller[i], container.size());
	}
}

template <typename Container>
void PmergeMe::mergeInsertSort(Container &container) {
	if (container.size() <= 1)
		return;
	fordJohnson(container, 0, container.size());
}

void PmergeMe::process(int argc, char **argv) {
	VectorType originalVec;
	
	try {
		originalVec = parseInput(argc, argv);
	} catch (const std::exception &e) {
		throw;
	}
	
	std::cout << "Before: ";
	displaySequence(originalVec);
	
	VectorType vecCopy = originalVec;
	struct timespec startVec, endVec;
	clock_gettime(CLOCK_MONOTONIC, &startVec);
	mergeInsertSort(vecCopy);
	clock_gettime(CLOCK_MONOTONIC, &endVec);
	double elapsedVec = getElapsedTime(startVec, endVec);
	
	DequeType deqCopy;
	for (size_t i = 0; i < originalVec.size(); i++) {
		deqCopy.push_back(originalVec[i]);
	}
	struct timespec startDeq, endDeq;
	clock_gettime(CLOCK_MONOTONIC, &startDeq);
	mergeInsertSort(deqCopy);
	clock_gettime(CLOCK_MONOTONIC, &endDeq);
	double elapsedDeq = getElapsedTime(startDeq, endDeq);
	
	std::cout << "After: ";
	displaySequence(vecCopy);
	
	std::cout << std::fixed << std::setprecision(5);
	std::cout << "Time to process a range of " << originalVec.size() 
		<< " elements with std::vector : " << elapsedVec << " us" << std::endl;
	std::cout << "Time to process a range of " << originalVec.size() 
		<< " elements with std::deque : " << elapsedDeq << " us" << std::endl;
}
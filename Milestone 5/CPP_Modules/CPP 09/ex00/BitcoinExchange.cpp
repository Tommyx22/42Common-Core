/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BitcoinExchange.cpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tolanini <tolanini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/06 16:40:55 by tolanini          #+#    #+#             */
/*   Updated: 2026/05/06 16:54:42 by tolanini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "BitcoinExchange.hpp"

namespace {

	void loadDatabase(std::map<std::string, float> &database) {
		std::ifstream file("data.csv");
		if (!file.is_open())
			throw BitcoinExchange::FileNotFoundException();
		
		std::string line;
		std::getline(file, line);
		while (std::getline(file, line)) {
			size_t commaPos = line.find(',');
			if (commaPos != std::string::npos) {
				std::string date = line.substr(0, commaPos);
				char *end;
				float value = static_cast<float>(std::strtod(line.substr(commaPos + 1).c_str(), &end));
				database[date] = value;
			}
		}
	}

	void trim(std::string &str) {
		str.erase(0, str.find_first_not_of(" \t\n\r\f\v"));
		str.erase(str.find_last_not_of(" \t\n\r\f\v") + 1);
	}

	bool valueCheck(float value) {
		if (value < 0){
			std::cout << "Error: not a positive number." << std::endl;
			return false;
		} else if (value > 1000) {
			std::cout << "Error: too large a number." << std::endl;
			return false;
		}
		return true;
	}

	bool isValidDate(const std::string &date) {
		if (date.length() != 10 || date[4] != '-' || date[7] != '-')
			return false;
		
		for (size_t i = 0; i < date.length(); ++i) {
			if (i == 4 || i == 7)
				continue;
			if (date[i] < '0' || date[i] > '9')
				return false;
		}

		int year = std::atoi(date.substr(0, 4).c_str());
		int month = std::atoi(date.substr(5, 2).c_str());
		int day = std::atoi(date.substr(8, 2).c_str());

		int maxDay;
		if (month == 2) {
			if (year % 4 == 0 && (year % 100 != 0 || year % 400 == 0))
				maxDay = 29;
			else
				maxDay = 28;
		} else if (month == 4 || month == 6 || month == 9 || month == 11)
			maxDay = 30;
		else
			maxDay = 31;

		if (year < 2009 || year > 2026)
			return false;
		if (month < 1 || month > 12)
			return false;
		if (day < 1 || day > maxDay)
			return false;

		return true;
	}
}

BitcoinExchange::BitcoinExchange() {
	loadDatabase(this->database);
}

BitcoinExchange::BitcoinExchange(const BitcoinExchange &copy) {
	*this = copy;
}

BitcoinExchange &BitcoinExchange::operator=(const BitcoinExchange &copy) {
	if (this == &copy)
		*this = copy;
	database = copy.database;
	return *this;
}

BitcoinExchange::~BitcoinExchange() {}

const char* BitcoinExchange::FileNotFoundException::what() const throw() {
	return "could not open file.";
}

void BitcoinExchange::calculate(const std::string &filename) const {
	std::ifstream file(filename.c_str());
	if (!file.is_open())
		throw FileNotFoundException();
	
	std::string line;
	std::getline(file, line);
	while (std::getline(file, line)) {
		trim(line);
		size_t pipePos = line.find('|');
		if (pipePos == std::string::npos) {
			std::cout << "Error: bad input => " << line << std::endl;
			continue;
		}
		else if (pipePos != std::string::npos) {
			std::string date = line.substr(0, pipePos);
			std::string valueStr = line.substr(pipePos + 1);
			trim(date);
			trim(valueStr);
			float value;
			char *end;
			value = static_cast<float>(std::strtod(valueStr.c_str(), &end));
			if (end == valueStr.c_str() || *end != '\0') {
				std::cout << "Error: bad input => " << valueStr << std::endl;
				continue;
			}
			if (!valueCheck(value))
				continue;
			if (!isValidDate(date)) {
				std::cout << "Error: bad input => " << date << std::endl;
				continue;
			}
			std::map<std::string, float>::const_iterator it = database.lower_bound(date);
			if (it != database.end() && it->first == date) {
				std::cout << date << " => " << value << " = " << value * it->second << std::endl;
			} else if (it != database.begin()) {
				--it;
				std::cout << date << " => " << value << " = " << value * it->second << std::endl;
			} else {
				std::cout << "Error: no data available for date => " << date << std::endl;
			}
		}
	}
}
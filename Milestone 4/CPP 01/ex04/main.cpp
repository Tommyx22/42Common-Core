/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tolanini <tolanini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/09 13:54:14 by tolanini          #+#    #+#             */
/*   Updated: 2026/01/09 15:01:57 by tolanini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include <fstream>
#include <string>

void stringManipulator(std::string filename, std::string s1, std::string s2) {
	std::ifstream file(filename.c_str());
	if (!file.is_open()) {
		std::cerr << "Could not open file " << filename << std::endl;
		return;
	}
	std::ofstream outputfile((filename + ".replace").c_str());
	if (!outputfile.is_open()) {
		std::cerr << "Error creating output file." << std::endl;
		return;
	}
	std::string line;
	size_t pos;
	while (std::getline(file, line)) {
		pos = 0;
		while ((pos = line.find(s1, pos)) != std::string::npos) {
			line.erase(pos, s1.length());
			line.insert(pos, s2);
			pos += s2.length();
		}
		outputfile << line << std::endl;
	}
	file.close();
	outputfile.close();
}

int main(int ac, char **av) {
	if (ac != 4) {
		std::cerr << "Invalid number of arguments." << std::endl;
		return 1;
	}
	stringManipulator(av[1], av[2], av[3]);
	return 0;
}
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tolanini <tolanini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/20 15:11:20 by tolanini          #+#    #+#             */
/*   Updated: 2026/05/20 16:02:32 by tolanini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Server.hpp"

static bool isValidPort(const char *arg, int &port)
{
	if (arg == NULL || *arg == '\0')
		return false;
	for (int i = 0; arg[i] != '\0'; ++i)
	{
		if (!std::isdigit(static_cast<unsigned char>(arg[i])))
			return false;
	}

	std::istringstream iss(arg);
	long parsed = 0;
	iss >> parsed;

	if (iss.fail() || !iss.eof())
		return false;
	if (parsed < 1024 || parsed > 65535)
		return false;
	port = static_cast<int>(parsed);
	return true;
}

static bool isValidPassword(const std::string &password)
{
	if (password.empty())
		return true;
	for (std::string::size_type i = 0; i < password.size(); ++i)
	{
		if (password[i] == ' ' || password[i] == '\t' || password[i] == '\r' || password[i] == '\n')
			return false;
	}
	return true;
}

int main(int ac, char **av) {
	if (ac != 3) {
		std::cerr << "Usage: " << av[0] << " <port> <password>" << std::endl;
		return (1);
	}
	int port = 0;
	if (!isValidPort(av[1], port)) {
		std::cerr << "Error: invalid port (must be numeric and between 1024 and 65535)." << std::endl;
		return (1);
	}
	std::string password(av[2]);
	if (!isValidPassword(password)) {
		std::cerr << "Error: invalid password (must be non-empty and without spaces)." << std::endl;
		return (1);
	}
	
	try {
		Server server(port, password);
		server.run();
	} catch (const std::exception &e) {
		std::cerr << "Error: " << e.what() << std::endl;
		return (1);
	}
	return (0);
}
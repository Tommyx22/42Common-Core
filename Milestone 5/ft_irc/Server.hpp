/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tolanini <tolanini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/20 15:24:00 by tolanini          #+#    #+#             */
/*   Updated: 2026/05/22 18:01:42 by tolanini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SERVER_HPP
#define SERVER_HPP

#include <sys/socket.h>
#include <netinet/in.h>
#include <sys/poll.h>
#include <arpa/inet.h>
#include <fcntl.h>
#include <unistd.h>
#include <cstring>
#include <string>
#include <vector>
#include <iostream>
#include <stdexcept>
#include "User.hpp"
#include <map>
#include <sstream>

class Server {
public:
	Server();
	Server(int port, const std::string &password);
	~Server();

	void run();

private:
	int _port;
	std::string _password;
	int _listen_fd;
	std::vector<struct pollfd> _poll_fds;
	//2 mappe momentanee per poter salvare gli user
	std::map<int, std::string> _client_buffers;
	std::map<int, User> _users;

	void initServer();
	void handleNewConnection();
	void handleClientMessage(size_t index);
	bool processCommand(int client_fd, std::string line, int index);
	void userRegistration(int client_fd);
	
};
#endif
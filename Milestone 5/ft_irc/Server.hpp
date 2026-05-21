/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tolanini <tolanini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/20 15:24:00 by tolanini          #+#    #+#             */
/*   Updated: 2026/05/20 18:04:11 by tolanini         ###   ########.fr       */
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

	void initServer();
	void handleNewConnection();
	void handleClientMessage(size_t index);
	
};
#endif
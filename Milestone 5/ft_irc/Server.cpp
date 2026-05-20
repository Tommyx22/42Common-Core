/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tolanini <tolanini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/20 15:40:00 by tolanini          #+#    #+#             */
/*   Updated: 2026/05/20 17:48:06 by tolanini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Server.hpp"

Server::Server() : _port(-1), _password(""), _listen_fd(-1) {}

Server::Server(int port, const std::string &password) : _port(port), _password(password), _listen_fd(-1) {
	initServer();
}

Server::~Server() {
	if (_listen_fd != -1) {
		close(_listen_fd);
	}
}

void Server::run() {
	struct pollfd listen_pollfd;
	listen_pollfd.fd = _listen_fd;
	listen_pollfd.events = POLLIN;
	listen_pollfd.revents = 0;
	_poll_fds.push_back(listen_pollfd);

	std::cout << "IRC Server is running on port " << _port << std::endl;

	while (true) {
		int poll_count = poll(&_poll_fds[0], _poll_fds.size(), -1);
		if (poll_count == -1) {
			throw std::runtime_error("Poll error");
		}
		
		for (size_t i = 0; i < _poll_fds.size(); ++i) {
			if (_poll_fds[i].revents & POLLIN) {
				if (_poll_fds[i].fd == _listen_fd) {
					handleNewConnection();
				} else {
					size_t current_size = _poll_fds.size();
					handleClientMessage(i);
					if (_poll_fds.size() < current_size)
						--i;
				}
			}
		}
	}
}

void Server::initServer() {
	_listen_fd = socket(AF_INET, SOCK_STREAM, 0);
	if (_listen_fd == -1) {
		throw std::runtime_error("Failed to create socket");
	}
	
	int opt = 1;
	if (setsockopt(_listen_fd, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt)) == -1) {
		throw std::runtime_error("Failed to set socket options");
	}

	if (fcntl(_listen_fd, F_SETFL, O_NONBLOCK) == -1) {
		throw std::runtime_error("Failed to set socket to non-blocking");
	}

	struct sockaddr_in address;
	std::memset(&address, 0, sizeof(address));
	
	address.sin_family = AF_INET;
	address.sin_port = htons(_port);
	address.sin_addr.s_addr = INADDR_ANY;

	if (bind(_listen_fd, (struct sockaddr *)&address, sizeof(address)) == -1) {
		throw std::runtime_error("Failed to bind socket to the port");
	}

	if (listen(_listen_fd, SOMAXCONN) == -1) {
		throw std::runtime_error("Failed to listen on socket");
	}
}

void Server::handleNewConnection() {
	struct sockaddr_in client_address;
	socklen_t client_len = sizeof(client_address);

	int client_fd = accept(_listen_fd, (struct sockaddr *)&client_address, &client_len);
	if (client_fd == -1) {
		std::cerr << "Failed to accept new connection" << std::endl;
		return;
	}
	
	fcntl(client_fd, F_SETFL, O_NONBLOCK);
	
	struct pollfd client_pollfd;
	client_pollfd.fd = client_fd;
	client_pollfd.events = POLLIN;
	client_pollfd.revents = 0;
	_poll_fds.push_back(client_pollfd);

	std::cout << "New client connected: " << inet_ntoa(client_address.sin_addr) << " on socket fd " << client_fd << std::endl;
}

void Server::handleClientMessage(size_t index) {
	int client_fd = _poll_fds[index].fd;
    char buffer[512];
    std::memset(buffer, 0, sizeof(buffer));
    
    int bytes_received = recv(client_fd, buffer, sizeof(buffer) - 1, 0);
    
    if (bytes_received <= 0) {
        std::cout << "Client on socket fd " << client_fd << " disconnected." << std::endl;
        close(client_fd);
        _poll_fds.erase(_poll_fds.begin() + index);
    } 
    else {
        std::cout << "Received from client " << client_fd << ": " << buffer;
        // Qui andrà la logica per accumulare nel buffer della classe Client e processare i comandi quando si riceve un \r\n
    }
}
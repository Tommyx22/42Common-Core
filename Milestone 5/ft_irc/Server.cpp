/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tolanini <tolanini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/20 15:40:00 by tolanini          #+#    #+#             */
/*   Updated: 2026/05/22 17:57:07 by tolanini         ###   ########.fr       */
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

	User newUser(client_fd, "", "", ""); 
    _users[client_fd] = newUser;
    _client_buffers[client_fd] = "";
}

void Server::handleClientMessage(size_t index) {
	int client_fd = _poll_fds[index].fd;
    char buffer[512];
    std::memset(buffer, 0, sizeof(buffer));
    
    int bytes_received = recv(client_fd, buffer, sizeof(buffer) - 1, 0);
    
    if (bytes_received <= 0) {
        std::cout << "Client on socket fd " << client_fd << " disconnected." << std::endl;
        close(client_fd);
		_users.erase(client_fd);
        _client_buffers.erase(client_fd);
        _poll_fds.erase(_poll_fds.begin() + index);
		return;
    } 

    _client_buffers[client_fd] += buffer;
    size_t pos;
	
    while ((pos = _client_buffers[client_fd].find('\n')) != std::string::npos) {

		std::string command_line = _client_buffers[client_fd].substr(0, pos);
		_client_buffers[client_fd].erase(0, pos + 1);

		if (!command_line.empty() && command_line[command_line.size() - 1] == '\r') {
			command_line.erase(command_line.size() - 1);
		}

		if (!processCommand(client_fd, command_line, index))
			return;
		

		userRegistration(client_fd);

		// STAMPA DI DEBUG
		std::cout << "====== DEBUG USER (fd: " << client_fd << ") ======" << std::endl;
        std::cout << "Raw Command: [" << command_line << "]" << std::endl;
        std::cout << "Stored Nickname: " << _users[client_fd].getNickname() << std::endl;
        std::cout << "Password inserita: " << _users[client_fd].getPassword() << std::endl;
		std::cout << "Username inserito: " << _users[client_fd].getUsername() << std::endl;
		std::cout << "Realname inserito: " << _users[client_fd].getRealname() << std::endl;
        std::cout << "Stato Autenticazione: " << (_users[client_fd].getHasProvidedPass() ? "SI" : "NO") << std::endl;
        std::cout << "========================================" << std::endl;
	}
}

bool Server::processCommand(int client_fd, std::string line, int index) {

	if (line.empty())
		return true;

	size_t space_pos = line.find(' ');
	std::string command;
	std::string args;

	if (space_pos != std::string::npos) {
		command = line.substr(0, space_pos);
		args = line.substr(space_pos + 1);
	} else {
		command = line;
	}

	if (command == "PASS") {

		if (_password.empty()) {
			std::cout << "[DEBUG] Il server non richiede password. Ignoro il PASS inviato." << std::endl;
            _users[client_fd].setHasProvidedPass(true);
            return true;
		}

		if (args.empty()) {
			std::cout << "[DEBUG] Nessuna password fornita per fd " << client_fd << std::endl;
			std::string error_msg = ":ft_irc.local 461 * PASS :Not enough parameters\r\n";
			send(client_fd, error_msg.c_str(), error_msg.length(), 0);

			close(client_fd);
			_users.erase(client_fd);
			_client_buffers.erase(client_fd);
			_poll_fds.erase(_poll_fds.begin() + index);
			return false;
		}

		_users[client_fd].setPassword(args);
		
		if (args == _password) {
			_users[client_fd].setHasProvidedPass(true);
			std::cout << "[DEBUG] Password corretta per fd " << client_fd << std::endl;
		} else {
			std::cout << "[DEBUG] Password REGISTRATA ERRATA per fd " << client_fd << std::endl;
			std::string error_msg = ":ft_irc.local 464 * :Password incorrect\r\n";
			send(client_fd, error_msg.c_str(), error_msg.length(), 0);

			close(client_fd);
			_users.erase(client_fd);
			_client_buffers.erase(client_fd);
			_poll_fds.erase(_poll_fds.begin() + index);
			return false;
		}
	} else if (command == "NICK") {
		
		if (!_password.empty() && !_users[client_fd].getHasProvidedPass()) {
			std::string error_msg = ":ft_irc.local 464 * :Password required before setting nickname\r\n";
			send(client_fd, error_msg.c_str(), error_msg.length(), 0);

			close(client_fd);
			_users.erase(client_fd);
			_client_buffers.erase(client_fd);
			_poll_fds.erase(_poll_fds.begin() + index);
			return false;
		}

		if (args.empty()) {
			std::string error_msg = ":ft_irc.local 431 * :No nickname given\r\n";
			send(client_fd, error_msg.c_str(), error_msg.length(), 0);
			return true;
		}
			_users[client_fd].setNickname(args);
	} else if (command == "USER") {

		if (!_password.empty() && !_users[client_fd].getHasProvidedPass()) {
			std::string error_msg = ":ft_irc.local 464 * :Password required before setting user information\r\n";
			send(client_fd, error_msg.c_str(), error_msg.length(), 0);

			close(client_fd);
			_users.erase(client_fd);
			_client_buffers.erase(client_fd);
			_poll_fds.erase(_poll_fds.begin() + index);
			return false;
		}

		if (args.empty()) {
			std::cout << "[DEBUG] Nessun argomento fornito per comando USER su fd " << client_fd << std::endl;
			std::string error_msg = ":ft_irc.local 461 * USER :Not enough parameters\r\n";
			send(client_fd, error_msg.c_str(), error_msg.length(), 0);
			return true;
		}
		
		size_t colon_pos = args.find(':');
		std::string realname = "";
		std::string remaining = args;

		if (colon_pos != std::string::npos) {
			realname = args.substr(colon_pos + 1);
			remaining = args.substr(0, colon_pos);
		}

		std::stringstream ss(remaining);
		std::string username;

		ss >> username;

		if (username.empty() || realname.empty()) {
			std::cout << "[DEBUG] Parametri insufficienti per comando USER su fd " << client_fd << std::endl;
			std::string error_msg = ":ft_irc.local 461 * USER :Not enough parameters\r\n";
			send(client_fd, error_msg.c_str(), error_msg.length(), 0);
			return true;
		}

		_users[client_fd].setUsername(username);
		_users[client_fd].setRealname(realname);
	} else {
		std::cout << "[DEBUG] Comando non ancora implementato" << std::endl;
	}

	return true;
}

void Server::userRegistration(int client_fd) {
	if (_users[client_fd].getIsRegistered() == false &&
		_users[client_fd].getHasProvidedPass() == true &&
		!_users[client_fd].getNickname().empty() &&
		!_users[client_fd].getUsername().empty() &&
		!_users[client_fd].getRealname().empty()) {

		_users[client_fd].setIsRegistered(true);

		std::string server_name = "ft_irc.local";
		std::string nick = _users[client_fd].getNickname();
		std::string user_ip = nick + "!" + _users[client_fd].getUsername() + "@127.0.0.1";

		std::string welcome_message;

		welcome_message += ":" + server_name + " 001 " + nick + " :Welcome to the Internet Relay Network " + user_ip + "\r\n";

        welcome_message += ":" + server_name + " 002 " + nick + " :Your host is " + server_name + ", running version 1.0\r\n";
        
        welcome_message += ":" + server_name + " 003 " + nick + " :This server was created Tue Jun 02 2026\r\n";
        
        welcome_message += ":" + server_name + " 004 " + nick + " " + server_name + " 1.0 o o\r\n";

		send(client_fd, welcome_message.c_str(), welcome_message.length(), 0);

		std::cout << "[SERVER] User " << nick << " successfully registered!" << std::endl;
	}
}

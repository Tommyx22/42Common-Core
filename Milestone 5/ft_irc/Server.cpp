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


	//codice momentaneo per poter salvare gli utenti
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
		_users.erase(client_fd);			// Rimuoviamo l'utente dalla mappa
        _client_buffers.erase(client_fd);	// Rimuoviamo il suo buffer
        _poll_fds.erase(_poll_fds.begin() + index);
		return;
    } 

    _client_buffers[client_fd] += buffer;
    size_t pos;
	
    while ((pos = _client_buffers[client_fd].find('\n')) != std::string::npos) {

		// Estraiamo la singola riga di comando (es. "NICK Pippo\r")
		std::string command_line = _client_buffers[client_fd].substr(0, pos);

		// Rimuoviamo la riga appena presa dal buffer residuo
		_client_buffers[client_fd].erase(0, pos + 1);

		// Puliamo i caratteri '\r' residui di Windows/IRC se presenti
		if (!command_line.empty() && command_line[command_line.size() - 1] == '\r') {
			command_line.erase(command_line.size() - 1);
		}
			
		// --- INIZIO LOGICA PARSING DI DEBUG ---
		// HexChat invia comandi del tipo: "NICK nome" o "PASS password"

		// vediamo se la password é corretta (per ora lo facciamo qui)
		if (command_line.find("PASS ") == 0) {
			std::string client_pass = command_line.substr(5);

			_users[client_fd].setPassword(client_pass);
			
			if (client_pass == _password) {
				_users[client_fd].setHasProvidedPass(true);
				std::cout << "[DEBUG] Password corretta per fd " << client_fd << std::endl;
			} else {
				// Se la password è errata, possiamo decidere di chiudere subito la connessione o semplicemente ignorare i comandi futuri
				// Per ora, stampiamo un messaggio di debug e ignoriamo i comandi
				std::cout << "[DEBUG] Password REGISTRATA ERRATA per fd " << client_fd << std::endl;
			}
		} else if (command_line.find("NICK ") == 0) {
			std::string nick = command_line.substr(5);
			_users[client_fd].setNickname(nick);
		} else if (command_line.find("USER ") == 0) {
			// Qui andrà il parsing del comando USER
			std::cout << "[DEBUG] Ricevuto comando USER: " << command_line << std::endl;
		}

		// STAMPA DI DEBUG
		std::cout << "====== DEBUG USER (fd: " << client_fd << ") ======" << std::endl;
        std::cout << "Raw Command: [" << command_line << "]" << std::endl;
        std::cout << "Stored Nickname: " << _users[client_fd].getNickname() << std::endl;
        std::cout << "Password inserita: " << _users[client_fd].getPassword() << std::endl;
		std::cout << "Username inserito: " << _users[client_fd].getUsername() << std::endl;
		std::cout << "Realname inserito: " << _users[client_fd].getRealname() << std::endl;
        std::cout << "Stato Autenticazione: " << (_users[client_fd].getHasProvidedPass() ? "SI" : "NO") << std::endl;
        std::cout << "========================================" << std::endl;
			
		// Se abbiamo sia Nickname che Password, possiamo mandargli il famoso codice 001
		// per sbloccare l'interfaccia grafica di HexChat!
		if (!_users[client_fd].getNickname().empty() && _users[client_fd].getHasProvidedPass() == true) {
			std::string welcome = ":my_server 001 " + _users[client_fd].getNickname() + " :Welcome to ft_irc!\r\n";
			send(client_fd, welcome.c_str(), welcome.length(), 0);
		}
	}
}
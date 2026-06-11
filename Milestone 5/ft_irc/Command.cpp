/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Command.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tolanini <tolanini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/11 16:19:19 by tolanini          #+#    #+#             */
/*   Updated: 2026/06/11 18:19:57 by tolanini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Server.hpp"


namespace {
	
	bool isValidNickname(const std::string& nick) {
		if (nick.empty() || nick.length() > 9)
			return false;
		
		char first = nick[0];
		if ((first >= '0' && first <= '9') || first == '-')
			return false;
		
		std::string allowed_special = "[]\\`^{}-_";
		for (size_t i = 0; i < nick.length(); ++i) {
			char c = nick[i];
			if (!((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z') || 
				(c >= '0' && c <= '9') || allowed_special.find(c) != std::string::npos)) {
				return false;
			}
		}
		return true;
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
		if (!pass(client_fd, args, index))
			return false;
	} else if (command == "NICK") {
		if (!nick(client_fd, args, index))
			return false;
	} else if (command == "USER") {
		if (!user(client_fd, args, index))
			return false;
	} else if (command == "PRIVMSG") {
		if (!privmsg(client_fd, args))
			return false;
	} else if (command == "JOIN") {
		if (!join(client_fd, args))
			return false;
	} else {
		std::cout << "[DEBUG] Comando non ancora implementato" << std::endl;
	}

	return true;
}

bool Server::pass(int client_fd, std::string &args, int index) {
	
	std::string nick = _users[client_fd].getNickname().empty() ? "*" : _users[client_fd].getNickname();

	if (_users[client_fd].getHasProvidedPass()) {
		std::string error_msg = ":ft_irc.local 462 " + nick + " :You may not reregister\r\n";
		send(client_fd, error_msg.c_str(), error_msg.length(), 0);
		return true;
	}

	if (_password.empty()) {
		std::cout << "[DEBUG] Il server non richiede password. Ignoro il PASS inviato." << std::endl;
		_users[client_fd].setHasProvidedPass(true);
		return true;
	}

	if (args.empty()) {
		std::cout << "[DEBUG] Nessuna password fornita per fd " << client_fd << std::endl;
		std::string error_msg = ":ft_irc.local 461 " + nick + " PASS :Not enough parameters\r\n";
		send(client_fd, error_msg.c_str(), error_msg.length(), 0);

		close(client_fd);
		_users.erase(client_fd);
		_client_buffers.erase(client_fd);
		_poll_fds.erase(_poll_fds.begin() + index);
		return false;
	}

	if (args[0] == ':')
		args = args.substr(1);
	

	if (args == _password) {
		_users[client_fd].setHasProvidedPass(true);
		_users[client_fd].setPassword(args);
		std::cout << "[DEBUG] Password corretta per fd " << client_fd << std::endl;
	} else {
		std::cout << "[DEBUG] Password REGISTRATA ERRATA per fd " << client_fd << std::endl;
		std::string error_msg = ":ft_irc.local 464 " + nick + " :Password incorrect\r\n";
		send(client_fd, error_msg.c_str(), error_msg.length(), 0);

		close(client_fd);
		_users.erase(client_fd);
		_client_buffers.erase(client_fd);
		_poll_fds.erase(_poll_fds.begin() + index);
		return false;
	}
	return true;
}

bool Server::nick(int client_fd, std::string &args, int index) {
	if (!_password.empty() && !_users[client_fd].getHasProvidedPass()) {
		std::string error_msg = ":ft_irc.local 464 * :Password required before setting nickname\r\n";
		send(client_fd, error_msg.c_str(), error_msg.length(), 0);

		close(client_fd);
		_users.erase(client_fd);
		_client_buffers.erase(client_fd);
		_poll_fds.erase(_poll_fds.begin() + index);
		return false;
	}

	std::string current_nick = _users[client_fd].getNickname().empty() ? "*" : _users[client_fd].getNickname();

	if (args.empty()) {
		std::string error_msg = ":ft_irc.local 431 " + current_nick + " :No nickname given\r\n";
		send(client_fd, error_msg.c_str(), error_msg.length(), 0);
		return true;
	}

	if (args[0] == ':')
		args = args.substr(1);

	if (!isValidNickname(args)) {
		std::string error_msg = ":ft_irc.local 432 " + current_nick + " " + args + " :Erroneous nickname\r\n";
		send(client_fd, error_msg.c_str(), error_msg.length(), 0);
		return true;
	}

	std::map<int, User>::iterator it;
    for (it = _users.begin(); it != _users.end(); ++it) {
        if (it->second.getNickname() == args && it->first != client_fd) {
            std::string error_msg = ":ft_irc.local 433 " + current_nick + " " + args + " :Nickname is already in use\r\n";
            send(client_fd, error_msg.c_str(), error_msg.length(), 0);
            return true;
        }
    }

	std::string old_nick = _users[client_fd].getNickname();
    _users[client_fd].setNickname(args);

	if (_users[client_fd].getIsRegistered() == true) {
		std::string msg = ":" + old_nick + "!" + _users[client_fd].getUsername() + "@127.0.0.1 NICK :" + args + "\r\n";
		send(client_fd, msg.c_str(), msg.length(), 0);
		std::cout << "[SERVER] " << old_nick << " ha cambiato nickname in " << args << std::endl;
	}
	return true;
}

bool Server::user(int client_fd, std::string &args, int index) {

	if (!_password.empty() && !_users[client_fd].getHasProvidedPass()) {
		std::string error_msg = ":ft_irc.local 464 * :Password required before setting user information\r\n";
		send(client_fd, error_msg.c_str(), error_msg.length(), 0);

		close(client_fd);
		_users.erase(client_fd);
		_client_buffers.erase(client_fd);
		_poll_fds.erase(_poll_fds.begin() + index);
		return false;
	}

	std::string current_nick = _users[client_fd].getNickname().empty() ? "*" : _users[client_fd].getNickname();

	if (_users[client_fd].getIsRegistered()) {
		std::string error_msg = ":ft_irc.local 462 " + current_nick + " :You may not reregister\r\n";
		send(client_fd, error_msg.c_str(), error_msg.length(), 0);
		return true;
	}

	if (args.empty()) {
		std::cout << "[DEBUG] Nessun argomento fornito per comando USER su fd " << client_fd << std::endl;
		std::string error_msg = ":ft_irc.local 461 " + current_nick + " USER :Not enough parameters\r\n";
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
	std::string unused_hostname;
	std::string unused_servername;

	ss >> username >> unused_hostname >> unused_servername;
	
	if (colon_pos == std::string::npos && !unused_servername.empty()) {
		realname = unused_servername; 
	}

	if (username.empty() || realname.empty()) {
		std::cout << "[DEBUG] Parametri insufficienti per comando USER su fd " << client_fd << std::endl;
		std::string error_msg = ":ft_irc.local 461 " + _users[client_fd].getNickname() + " USER :Not enough parameters\r\n";
		send(client_fd, error_msg.c_str(), error_msg.length(), 0);
		return true;
	}

	_users[client_fd].setUsername(username);
	_users[client_fd].setRealname(realname);
	return true;
}

bool Server::privmsg(int client_fd, std::string &args) {

	if (!_users[client_fd].getIsRegistered()) {
		std::string error_msg = ":ft_irc.local 451 * :You have not registered\r\n";
		send(client_fd, error_msg.c_str(), error_msg.length(), 0);
		return true;
	}

	// Controllo se il client è registrato
	if (args.empty()) {
		std::string error_msg = ":ft_irc.local 411 " + _users[client_fd].getNickname() + " :No recipient given (PRIVMSG)\r\n";
		send(client_fd, error_msg.c_str(), error_msg.length(), 0);
		return true;
	}

	// Separazione del target e del messaggio
	size_t space_pos = args.find(' ');
	if (space_pos == std::string::npos) {
		std::string error_msg = ":ft_irc.local 412 " + _users[client_fd].getNickname() + " :No text to send\r\n";
		send(client_fd, error_msg.c_str(), error_msg.length(), 0);
		return true;
	}

	std::string target = args.substr(0, space_pos);
	std::string message = args.substr(space_pos + 1);

	if (!target.empty() && target[0] == ':')
		target = target.substr(1);

	// Rimozione del prefisso ':' se presente
	if (!message.empty() && message[0] == ':')
		message = message.substr(1);
	// Controllo se il messaggio è vuoto dopo la rimozione del prefisso ':'
	if (message.empty()) {
		std::string error_msg = ":ft_irc.local 412 " + _users[client_fd].getNickname() + " :No text to send\r\n";
		send(client_fd, error_msg.c_str(), error_msg.length(), 0);
		return true;
	}

	if (target[0] != '#') {
		int target_fd = -1;
		
		std::map<int, User>::iterator it;
		for (it = _users.begin(); it != _users.end(); ++it) {
			if (it->second.getNickname() == target) {
				target_fd = it->first;
				break;
			}	
		}

		if (target_fd == -1) {
			std::string error_msg = ":ft_irc.local 401 " + _users[client_fd].getNickname() + " " + target + " :No such nick\r\n";
			send(client_fd, error_msg.c_str(), error_msg.length(), 0);
			return true;
		}

		if (target_fd == client_fd) {
			std::cout << "[DEBUG] " << _users[client_fd].getNickname() << " si è auto-inviato un messaggio. Eco bloccato." << std::endl;
			return true;
		}

		std::string sender_mask = _users[client_fd].getNickname() + "!" + _users[client_fd].getUsername() + "@127.0.0.1";
		std::string privmsg = ":" + sender_mask + " PRIVMSG " + target + " :" + message + "\r\n";

		send(target_fd, privmsg.c_str(), privmsg.length(), 0);
		std::cout << "[PRIVMSG] Da " << _users[client_fd].getNickname() << " a " << target << ": [" << message << "]" << std::endl;
	} else {
		
		std::map<std::string, Channel>::iterator it = _channels.find(target);
		if (it == _channels.end()) {
			std::string error_msg = ":ft_irc.local 401 " + _users[client_fd].getNickname() + " " + target + " :No such nick/channel\r\n";
			send(client_fd, error_msg.c_str(), error_msg.length(), 0);
			return true;
		}

		if (!it->second.hasClient(client_fd)) {
			std::string error_msg = ":ft_irc.local 442 " + _users[client_fd].getNickname() + " " + target + " :You're not on that channel\r\n";
			send(client_fd, error_msg.c_str(), error_msg.length(), 0);
			return true;
		}
	
		std::string sender_mask = _users[client_fd].getNickname() + "!" + _users[client_fd].getUsername() + "@127.0.0.1";
		std::string channel_msg = ":" + sender_mask + " PRIVMSG " + target + " :" + message + "\r\n";

		std::vector<int> const &members = it->second.getClientFds();
		for (size_t i = 0; i < members.size(); ++i) {
			int member_fd = members[i];
			if (member_fd != client_fd) {
				send(member_fd, channel_msg.c_str(), channel_msg.length(), 0);
			}
		}
		std::cout << "[CANALE] " << _users[client_fd].getNickname() << " su " << target << ": [" << message << "]" << std::endl;
	}
	return true;
}

bool Server::join(int client_fd, std::string &args) {

	if (!_users[client_fd].getIsRegistered()) {
		std::string error_msg = ":ft_irc.local 451 * :You have not registered\r\n";
		send(client_fd, error_msg.c_str(), error_msg.length(), 0);
		return true;
	}

	if (args.empty()) {
		std::string error_msg = ":ft_irc.local 461 " + _users[client_fd].getNickname() + " JOIN :Not enough parameters\r\n";
		send(client_fd, error_msg.c_str(), error_msg.length(), 0);
		return true;
	}

	std::stringstream ss(args);
	std::string channel_name;
	ss >> channel_name;

	if (channel_name.empty() || channel_name[0] != '#') {
		std::string error_msg = ":ft_irc.local 403 " + _users[client_fd].getNickname() + " " + channel_name + " :No such channel\r\n";
        send(client_fd, error_msg.c_str(), error_msg.length(), 0);
        return true;
	}

	std::map<std::string, Channel>::iterator it = _channels.find(channel_name);

	if (it == _channels.end()) {
		Channel new_channel(channel_name);
		new_channel.addClient(client_fd);
		new_channel.addOperator(client_fd);

		_channels[channel_name] = new_channel;

		it = _channels.find(channel_name);
		std::cout << "[CHANNEL] Creato nuovo canale: " << channel_name << " da " << _users[client_fd].getNickname() << std::endl;
	} else {
		if (!it->second.hasClient(client_fd)) {
			it->second.addClient(client_fd);
		} else {
			return true;
		}
	}

	std::string user_mask = _users[client_fd].getNickname() + "!" + _users[client_fd].getUsername() + "@127.0.0.1";

	std::string join_notification = ":" + user_mask + " JOIN :" + channel_name + "\r\n";
	std::vector<int> const &members = it->second.getClientFds();
	for (size_t i = 0; i < members.size(); ++i) {
		send(members[i], join_notification.c_str(), join_notification.length(), 0);
	}

	if (!it->second.getTopic().empty()) {
		std::string topic_msg = ":ft_irc.local 332 " + _users[client_fd].getNickname() + " " + channel_name + " :" + it->second.getTopic() + "\r\n";
		send(client_fd, topic_msg.c_str(), topic_msg.length(), 0);
	}

	std::string names_reply = ":ft_irc.local 353 " + _users[client_fd].getNickname() + " = " + channel_name + " :";
    
	for (size_t i = 0; i < members.size(); ++i) {
		int member_fd = members[i];
		if (it->second.isOperator(member_fd)) {
			names_reply += "@";
		}
		names_reply += _users[member_fd].getNickname();
        
		if (i < members.size() - 1) {
			names_reply += " ";
		}
	}
	names_reply += "\r\n";
	send(client_fd, names_reply.c_str(), names_reply.length(), 0);

	std::string end_names = ":ft_irc.local 366 " + _users[client_fd].getNickname() + " " + channel_name + " :End of /NAMES list\r\n";
	send(client_fd, end_names.c_str(), end_names.length(), 0);

	return true;
}
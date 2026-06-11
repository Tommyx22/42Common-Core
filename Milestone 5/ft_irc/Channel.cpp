/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Channel.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tolanini <tolanini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/11 17:30:51 by tolanini          #+#    #+#             */
/*   Updated: 2026/06/11 17:43:44 by tolanini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Channel.hpp"

Channel::Channel() : _name(""), _topic(""), _password("") {}

Channel::Channel(const std::string &name) : _name(name), _topic(""), _password("") {}

Channel::~Channel() {}

std::string const &Channel::getName() const {
	return _name;
}

std::string const &Channel::getTopic() const {
	return _topic;
}

std::vector<int> const &Channel::getClientFds() const {
	return _client_fds;
}

void Channel::setTopic(std::string const &topic) {
	_topic = topic;
}

void Channel::setKey(std::string const &key) {
	_password = key;
}

void Channel::addClient(int client_fd) {
	if (!hasClient(client_fd)) {
		_client_fds.push_back(client_fd);
	}
}

void Channel::removeClient(int client_fd) {
	_client_fds.erase(std::remove(_client_fds.begin(), _client_fds.end(), client_fd), _client_fds.end());
}

bool Channel::hasClient(int client_fd) const {
	return std::find(_client_fds.begin(), _client_fds.end(), client_fd) != _client_fds.end();
}

void Channel::addOperator(int client_fd) {
	if (!isOperator(client_fd)) {
		_operator_fds.push_back(client_fd);
	}
}

void Channel::removeOperator(int client_fd) {
	_operator_fds.erase(std::remove(_operator_fds.begin(), _operator_fds.end(), client_fd), _operator_fds.end());
}

bool Channel::isOperator(int client_fd) const {
	return std::find(_operator_fds.begin(), _operator_fds.end(), client_fd) != _operator_fds.end();
}

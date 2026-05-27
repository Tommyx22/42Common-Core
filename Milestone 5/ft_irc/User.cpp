/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   User.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tolanini <tolanini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/22 17:35:06 by tolanini          #+#    #+#             */
/*   Updated: 2026/05/22 17:39:04 by tolanini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "User.hpp"

User::User() : _fd(-1), _nickname(""), _username(""), _realname(""), _password(""), _isRegistered(false), _hasProvidedPass(false) {}

User::User(int fd, std::string nickname, std::string username, std::string realname) : _fd(fd), _nickname(nickname), _username(username), _realname(realname), _password(""), _isRegistered(false), _hasProvidedPass(false) {}
User::~User() {}

int User::getFd() const {
	return _fd;
}

void User::setNickname(const std::string &nickname) {
	_nickname = nickname;
}

std::string User::getNickname() const {
	return _nickname;
}

void User::setUsername(const std::string &username) {
	_username = username;
}

std::string User::getUsername() const {
	return _username;
}

void User::setRealname(const std::string &realname) {
	_realname = realname;
}

std::string User::getRealname() const {
	return _realname;
}

void User::setPassword(const std::string &password) {
	_password = password;
}

std::string User::getPassword() const {
	return _password;
}

void User::setHasProvidedPass(bool hasProvided) {
	_hasProvidedPass = hasProvided;
}

bool User::getHasProvidedPass() const {
	return _hasProvidedPass;
}

void User::setIsRegistered(bool isRegistered) {
	_isRegistered = isRegistered;
}

bool User::getIsRegistered() const {
	return _isRegistered;
}

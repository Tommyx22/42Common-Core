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

User::User() : _fd(-1), _nickname(""), _password("") {}

User::User(int fd, std::string nickname, std::string password) : _fd(fd), _nickname(nickname), _password(password) {}
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

void User::setPassword(const std::string &password) {
	_password = password;
}

std::string User::getPassword() const {
	return _password;
}

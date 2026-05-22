/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   User.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tolanini <tolanini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/22 17:35:07 by tolanini          #+#    #+#             */
/*   Updated: 2026/05/22 17:38:18 by tolanini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef USER_HPP
#define USER_HPP

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

class User {
	private:
		int _fd;
		std::string _nickname;
		std::string _password;

	public:
		User();
		User(int fd, std::string nickname, std::string password);
		~User();

		int getFd() const;
		void setNickname(const std::string &nickname);
		std::string getNickname() const;
		void setPassword(const std::string &password);
		std::string getPassword() const;

};

#endif
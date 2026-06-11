/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Channel.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tolanini <tolanini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/11 17:30:40 by tolanini          #+#    #+#             */
/*   Updated: 2026/06/11 17:44:28 by tolanini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CHANNEL_HPP
#define CHANNEL_HPP

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
#include <algorithm>

class Channel {
	private:
		std::string _name;
		std::string _topic;
		std::string _password;
		std::vector<int> _client_fds;
		std::vector<int> _operator_fds;

	public:
		Channel();
		Channel(const std::string &name);
		~Channel();

		std::string const &getName() const;
		std::string const &getTopic() const;
		std::vector<int> const &getClientFds() const;

		void setTopic(std::string const &topic);
		void setKey(std::string const &key);

		void addClient(int client_fd);
		void removeClient(int client_fd);
		bool hasClient(int client_fd) const;

		void addOperator(int client_fd);
		void removeOperator(int client_fd);
		bool isOperator(int client_fd) const;
};

#endif
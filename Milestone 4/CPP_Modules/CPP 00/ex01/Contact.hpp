/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Contact.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tolanini <tolanini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/23 10:42:16 by tolanini          #+#    #+#             */
/*   Updated: 2025/11/11 17:55:51 by tolanini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CONTACT_HPP
#define CONTACT_HPP

# include <iostream>
# include <string>
# include <iomanip>
# include <cstdlib>
# include <limits>

class Contact {
    private:
    
        std::string first_name;
        std::string last_name;
        std::string nickname;
        std::string phone_number;
        std::string secret;

    public:

        Contact() : first_name(""), last_name(""), nickname(""), phone_number(""), secret("") {}

        inline std::string get_first_name() const { return first_name; }
        inline std::string get_last_name() const { return last_name; }
        inline std::string get_nickname() const { return nickname; }
        inline std::string get_phone_number() const { return phone_number; }
        inline std::string get_secret() const { return secret; }

        void set_first_name(const std::string &first_name) {
        this->first_name = first_name; 
        }
        void set_last_name(const std::string &last_name) {
        this->last_name = last_name; 
        }
        void set_nickname(const std::string &nickname) {
        this->nickname = nickname; 
        }
        void set_phone_number(const std::string &phone_number) {
        this->phone_number = phone_number; 
        }
        void set_secret(const std::string &secret) {
        this->secret = secret; 
        }
        void create_contact();
};

#endif
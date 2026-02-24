/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PhoneBook.hpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tolanini <tolanini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/23 10:42:16 by tolanini          #+#    #+#             */
/*   Updated: 2025/11/11 17:46:44 by tolanini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHONEBOOK_HPP
#define PHONEBOOK_HPP

#include "Contact.hpp"

class PhoneBook {
    private:
    
        static const int MAX_CONTACTS = 8;
        Contact contacts[MAX_CONTACTS];
        int contact_count;
        
    public:

        PhoneBook() : contact_count(0) {}
        
        void add_contact(const Contact& c);
        void search_contacts();
        inline int get_contact_count() const { return contact_count; }
        inline int get_max_contacts() const { return MAX_CONTACTS; }
        
};

#endif
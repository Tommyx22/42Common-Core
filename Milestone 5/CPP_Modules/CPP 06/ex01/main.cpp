/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tolanini <tolanini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/14 13:47:16 by tolanini          #+#    #+#             */
/*   Updated: 2026/04/14 14:52:03 by tolanini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Serializer.hpp"

int main() {
	Data data;
	data.id = 42;
	data.name = "tolanini";

	uintptr_t raw = Serializer::serialize(&data);
	Data* deserializedData = Serializer::deserialize(raw);
	
	std::cout << "Original Data: id = " << data.id << ", name = " << data.name << std::endl;
	std::cout << "address (uintptr_t): " << raw << std::endl;
	std::cout << "Deserialized Data: id = " << deserializedData->id << ", name = " << deserializedData->name << std::endl;
	
	return 0;
}
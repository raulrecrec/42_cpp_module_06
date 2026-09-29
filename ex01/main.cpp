/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rexposit <rexposit@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/29 19:00:58 by rexposit          #+#    #+#             */
/*   Updated: 2026/09/29 19:40:03 by rexposit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Serializer.hpp"
#include <iostream>

int	main(void)
{
	Data	data;
	Data	*ptr;

	data.value = 42;
	ptr = &data;

	std::cout << "ptr: " << ptr << "\nvalue: " << data.value << std::endl;
	std::cout << "\nSerializing...\n" << std::endl;

	uintptr_t	raw;
	raw = Serializer::serialize(ptr);

	std::cout << "raw: " << raw << std::endl;
	std::cout << "\nDeserializing...\n" << std::endl;

	Data *new_ptr;

	new_ptr = Serializer::deserialize(raw);

	std::cout << "new_ptr: " << new_ptr << "\nvalue: " << new_ptr->value << std::endl;
	std::cout << "\nptr == new_ptr?" << std::endl;
	if (ptr == new_ptr)
		std::cout << "Yes" << std::endl;
	else
		std::cout << "No" << std::endl;
}
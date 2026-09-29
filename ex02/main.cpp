/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rexposit <rexposit@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/29 20:14:44 by rexposit          #+#    #+#             */
/*   Updated: 2026/09/29 20:48:06 by rexposit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Base.hpp"
#include <cstdlib>
#include <ctime>
#include <iostream>

int	main(void)
{
	srand(time(NULL));

	std::cout << "Generating random object...\n" << std::endl;

	Base	*ptr;

	ptr = generate();

	std::cout << "Identifying by pointer..." << std::endl;
	identify(ptr);

	std::cout << "\nIdentifying by reference..." << std::endl;
	identify(*ptr);

	std::cout << "\nDeleting object..." << std::endl;
	delete ptr;

	return (0);
}
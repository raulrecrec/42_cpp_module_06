/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Base.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rexposit <rexposit@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/29 20:14:38 by rexposit          #+#    #+#             */
/*   Updated: 2026/09/29 20:53:46 by rexposit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Base.hpp"
#include <cstdlib>
#include <iostream>
#include <typeinfo>

Base::~Base()
{
}

Base	*generate(void)
{
	int	random_value;

	random_value = rand() % 3;

	Base	*ptr = NULL;

	switch (random_value)
	{
		case 0:
			ptr = new A;
			break;
		case 1:
			ptr = new B;
			break;
		case 2:
			ptr = new C;
			break;
	}

	return (ptr);
}

void	identify(Base *p)
{
	std::cout << "Type of the object pointed by p:" << std::endl;

	if (dynamic_cast<A *>(p))
		std::cout << "A" << std::endl;
	else if (dynamic_cast<B *>(p))
		std::cout << "B" << std::endl;
	else if (dynamic_cast<C *>(p))
		std::cout << "C" << std::endl;
	else
		std::cout << "Type is not A, B or C" << std::endl;
}

void	identify(Base &p)
{
	std::cout << "Type of the object referenced by p:" << std::endl;

	try
	{
		dynamic_cast<A &>(p);
		std::cout << "A" << std::endl;
		return ;
	}
	catch (const std::bad_cast &e)
	{
	}
	
	try
	{
		dynamic_cast<B &>(p);
		std::cout << "B" << std::endl;
		return ;
	}
	catch (const std::bad_cast &e)
	{
	}

	try
	{
		dynamic_cast<C &>(p);
		std::cout << "C" << std::endl;
		return ;
	}
	catch (const std::bad_cast &e)
	{
	}

	std::cout << "Type is not A, B or C" << std::endl;
}
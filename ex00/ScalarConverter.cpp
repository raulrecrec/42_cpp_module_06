/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ScalarConverter.cpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rexposit <rexposit@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/29 12:06:08 by rexposit          #+#    #+#             */
/*   Updated: 2026/07/30 00:09:10 by rexposit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ScalarConverter.hpp"
#include <cctype>
#include <cfloat>
#include <iostream>
#include <climits>
#include <cstdlib>
#include <cerrno>
#include <iomanip>
#include <cmath>

bool ScalarConverter::isChar(const std::string &literal)
{
	if (literal.length() != 1)
		return (false);

	if (std::isdigit(literal[0]))
		return (false);

	return (true);
}

bool ScalarConverter::isInt(const std::string &literal)
{
	if (literal.empty())
		return (false);

	size_t i = 0;
	if (literal[0] == '+' || literal[0] == '-')
	{
		i = 1;
		if (i == literal.length())
			return (false);
	}

	while (i < literal.length())
	{
		if (!std::isdigit(literal[i]))
			return (false);
		i++;
	}

	long	value = std::strtol(literal.c_str(), NULL, 10);
	if (value > INT_MAX || value < INT_MIN)
		return (false);

	return (true);
}

bool ScalarConverter::isFloat(const std::string &literal)
{
	if (literal.empty() || literal[literal.length() - 1] != 'f')
		return (false);

	if (literal == "nanf" || literal == "+inff" || literal == "-inff")
		return (true);

	size_t i = 0;
	if (literal[0] == '+' || literal[0] == '-')
	{
		i = 1;
		if (i == literal.length())
			return (false);
	}

	int	dot_count = 0;
	int	digit_count = 0;
	while (i < literal.length() - 1)
	{
		if (literal[i] == '.')
			dot_count++;
		else if (std::isdigit(literal[i]))
			digit_count++;
		else
			return (false);

		if (dot_count > 1)
			return (false);
		i++;
	}

	if (dot_count != 1 || digit_count == 0)
		return (false);

	errno = 0;
	double	value = std::strtod(literal.c_str(), NULL);
	if (errno == ERANGE)
		return (false);
	if (value > FLT_MAX || value < -FLT_MAX)
		return (false);

	return (true);
}

bool ScalarConverter::isDouble(const std::string &literal)
{
	if (literal.empty())
		return (false);

	if (literal == "nan" || literal == "+inf" || literal == "-inf")
		return (true);

	size_t i = 0;
	if (literal[0] == '+' || literal[0] == '-')
	{
		i = 1;
		if (i == literal.length())
			return (false);
	}

	int	dot_count = 0;
	int	digit_count = 0;
	while (i < literal.length())
	{
		if (literal[i] == '.')
			dot_count++;
		else if (std::isdigit(literal[i]))
			digit_count++;
		else
			return (false);

		if (dot_count > 1)
			return (false);
		i++;
	}

	errno = 0;
	std::strtod(literal.c_str(), NULL);
	if (errno == ERANGE)
		return (false);
	
	if (dot_count == 1 && digit_count > 0)
		return (true);

	return (false);
}

ScalarConverter::Type	ScalarConverter::detectType(const std::string &literal)
{
	if (isChar(literal))
		return (CHAR);
	else if (isInt(literal))
		return (INT);
	else if (isFloat(literal))
		return (FLOAT);
	else if (isDouble(literal))
		return (DOUBLE);
	else
		return (INVALID);
}

char ScalarConverter::toChar(const std::string &literal)
{
	return (literal[0]);
}

int ScalarConverter::toInt(const std::string &literal)
{
	return (static_cast<int>(std::strtol(literal.c_str(), NULL, 10)));
}

float ScalarConverter::toFloat(const std::string &literal)
{
	return (static_cast<float>(std::strtod(literal.c_str(), NULL)));
}

double ScalarConverter::toDouble(const std::string &literal)
{
	return (std::strtod(literal.c_str(), NULL));
}

void	ScalarConverter::printFromChar(char literal)
{
	if (std::isprint(literal))
		std::cout << "char: '" << literal << "'" << std::endl;
	else
		std::cout << "char: Non displayable" << std::endl;

	std::cout << std::fixed << std::setprecision(1);

	std::cout << "int: " << static_cast<int>(literal) << std::endl;
	std::cout << "float: " << static_cast<float>(literal) << "f" << std::endl;
	std::cout << "double: " << static_cast<double>(literal) << std::endl;
}

void	ScalarConverter::printFromInt(int literal)
{
	if (literal >= 0 && literal <= 127)
	{
		char c = static_cast<char>(literal);
		if (std::isprint(c))
			std::cout << "char: '" << c << "'" << std::endl;
		else
			std::cout << "char: Non displayable" << std::endl;
	}
	else
		std::cout << "char: impossible" << std::endl;

	std::cout << std::fixed << std::setprecision(1);

	std::cout << "int: " << literal << std::endl;
	std::cout << "float: " << static_cast<float>(literal) << "f" << std::endl;
	std::cout << "double: " << static_cast<double>(literal) << std::endl;
}

void	ScalarConverter::printFromFloat(float literal)
{
	if (std::isnan(literal) || std::isinf(literal))
	{
		std::cout << "char: impossible" << std::endl;
		std::cout << "int: impossible" << std::endl;
	}
	else 
	{
		if (literal >= 0 && literal <= 127)
		{
			char c = static_cast<char>(literal);
			if (std::isprint(c))
				std::cout << "char: '" << c << "'" << std::endl;
			else
				std::cout << "char: Non displayable" << std::endl;
		}
		else
			std::cout << "char: impossible" << std::endl;

		if (static_cast<double>(literal) >= INT_MIN && static_cast<double>(literal) <= INT_MAX)
			std::cout << "int: " << static_cast<int>(literal) << std::endl;
		else
			std::cout << "int: impossible" << std::endl;
	}
	
	std::cout << std::fixed << std::setprecision(1);
	std::cout << "float: " << literal << "f" << std::endl;
	std::cout << "double: " << static_cast<double>(literal) << std::endl;
}

void	ScalarConverter::printFromDouble(double literal)
{
	if (std::isnan(literal) || std::isinf(literal))
	{
		std::cout << "char: impossible" << std::endl;
		std::cout << "int: impossible" << std::endl;
	}
	else
	{
		if (literal >= 0 && literal <= 127)
		{
			char c = static_cast<char>(literal);
			if (std::isprint(c))
				std::cout << "char: '" << c << "'" << std::endl;
			else
				std::cout << "char: Non displayable" << std::endl;
		}
		else
			std::cout << "char: impossible" << std::endl;

		if (literal >= INT_MIN && literal <= INT_MAX)
			std::cout << "int: " << static_cast<int>(literal) << std::endl;
		else
			std::cout << "int: impossible" << std::endl;
	}

	if (std::isnan(literal))
	{
		std::cout << "float: nanf" << std::endl;
		std::cout << "double: nan" << std::endl;
	}
	else if (std::isinf(literal))
	{
		if (literal < 0)
		{
			std::cout << "float: -inff" << std::endl;
			std::cout << "double: -inf" << std::endl;
		}
		else
		{
			std::cout << "float: +inff" << std::endl;
			std::cout << "double: +inf" << std::endl;
		}
	}
	else
	{
		std::cout << std::fixed << std::setprecision(1);

		if (literal >= -FLT_MAX && literal <= FLT_MAX)
			std::cout << "float: " << static_cast<float>(literal) << "f" << std::endl;
		else
			std::cout << "float: impossible" << std::endl;

		std::cout << "double: " << literal << std::endl;
	}
}

void	ScalarConverter::printImpossible()
{
	std::cout << "char: impossible" << std::endl;
	std::cout << "int: impossible" << std::endl;
	std::cout << "float: impossible" << std::endl;
	std::cout << "double: impossible" << std::endl;
}

void ScalarConverter::convert(const std::string &literal)
{
	switch (detectType(literal))
	{
		case CHAR:
			printFromChar(toChar(literal));
			break;
		case INT:
			printFromInt(toInt(literal));
			break;
		case FLOAT:
			printFromFloat(toFloat(literal));
			break;
		case DOUBLE:
			printFromDouble(toDouble(literal));
			break;
		case INVALID:
			printImpossible();
			break;
	}
}


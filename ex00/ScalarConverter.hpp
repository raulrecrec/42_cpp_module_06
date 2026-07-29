/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ScalarConverter.hpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rexposit <rexposit@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/29 12:06:11 by rexposit          #+#    #+#             */
/*   Updated: 2026/07/29 23:01:38 by rexposit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SCALARCONVERTER_HPP
# define SCALARCONVERTER_HPP

#include <string>

class	ScalarConverter
{
	private:
		ScalarConverter();
		ScalarConverter(const ScalarConverter &other);
		ScalarConverter	&operator=(const ScalarConverter &other);
		~ScalarConverter();

		static bool	isChar(const std::string &literal);
		static bool	isInt(const std::string &literal);
		static bool	isFloat(const std::string &literal);
		static bool	isDouble(const std::string &literal);

		enum	Type
		{
			CHAR,
			INT,
			FLOAT,
			DOUBLE,
			INVALID
		};


		static char		toChar(const std::string &literal);
		static int		toInt(const std::string &literal);
		static float	toFloat(const std::string &literal);
		static double	toDouble(const std::string &literal);
		static void		printFromChar(char literal);
		static void		printFromInt(int literal);
		static void		printFromFloat(float literal);
		static void		printFromDouble(double literal);
		static void		printImpossible();
		static Type		detectType(const std::string &literal);

	public:
		static void convert(const std::string &literal);
};

#endif

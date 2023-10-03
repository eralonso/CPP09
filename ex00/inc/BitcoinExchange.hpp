/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BitcoinExchange.hpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eralonso <eralonso@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/30 11:44:44 by eralonso          #+#    #+#             */
/*   Updated: 2023/10/03 10:45:35 by eralonso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <map>
#include <iostream>
#include <sstream>
#include <fstream>
#include <string>
#include <float.h>

#define DATA_BASE_PATH "./data.csv"

#define DATA_BASE_HEADER "date,exchange_rate"
#define INPUT_FILE_HEADER "date | value"

#define DATA_BASE_DELIMITER ','
#define INPUT_FILE_DELIMITER '|'

#define DATA_BASE_VALUE_LIMIT FLT_MAX
#define INPUT_FILE_VALUE_LIMIT 1000.0f

class BitcoinExchange
{
	private:
		BitcoinExchange( void );
		BitcoinExchange( const BitcoinExchange& bte );
		~BitcoinExchange( void );
		BitcoinExchange&						operator=( const BitcoinExchange& bte );
		static void								checkFile( std::string file, std::string headerExpected, std::ifstream& in );
		static std::pair< std::string, float >	checkLine( std::string& line, char delimiter, \
														std::string& valueLimit );
		static bool								checkDate( std::string& date );
		static bool								checkValue( std::string& date, std::string& valueLimit, std::string& error );
		static bool								isInt( std::string& num );
		static bool								isPositiveFloat( std::string& num, std::string& error );
		static size_t							countChar( std::string str, char c, size_t n );
		static std::string						beforeDot( std::string& num );
		static std::string						floatToString( float num );
		static void								processFile( std::ifstream& in, char delimiter, std::string valueLimit, \
														std::map< std::string, float >& dataBase, bool isDB );
	public:
		static void	exchange( std::string file );
};

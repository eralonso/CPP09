/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BitcoinExchange.hpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eralonso <eralonso@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/30 11:44:44 by eralonso          #+#    #+#             */
/*   Updated: 2023/09/30 19:23:30 by eralonso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <map>
#include <iostream>
#include <sstream>
#include <fstream>
#include <string>

#define DATA_BASE_PATH "./data.csv"

#define DATA_BASE_HEADER "date,exchange_rate"
#define INPUT_FILE_HEADER "date | value"

#define DATA_BASE_DELIMITER ','
#define INPUT_FILE_DELIMITER '|'

class BitcoinExchange
{
	private:
		BitcoinExchange( void );
		BitcoinExchange( const BitcoinExchange& bte );
		~BitcoinExchange( void );
		BitcoinExchange&	operator=( const BitcoinExchange& bte );
		static void			checkLine( std::string& line, char delimiter );
		static bool			checkDateSyntax( std::string& date );
		static bool			isInt( std::string& num );
		static size_t		countChar( std::string str, char c, size_t n );
	public:
		static void	exchange( std::string file );
		static void	readFile( std::string file, std::string header, char delimiter, std::map< std::string, float >& info );
};
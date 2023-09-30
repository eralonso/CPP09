/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BitcoinExchange.cpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eralonso <eralonso@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/30 11:53:10 by eralonso          #+#    #+#             */
/*   Updated: 2023/09/30 19:27:22 by eralonso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "BitcoinExchange.hpp"

BitcoinExchange::BitcoinExchange( void ) {}

BitcoinExchange::BitcoinExchange( const BitcoinExchange& bte )
{
	( void ) bte;
}

BitcoinExchange::~BitcoinExchange( void ) {}

BitcoinExchange&	BitcoinExchange::operator=( const BitcoinExchange& bte )
{
	( void ) bte;
	return ( *this );
}

void	BitcoinExchange::exchange( std::string file )
{
	std::map< std::string, float >	dataBaseInfo;
	std::map< std::string, float >	inputFileInfo;

	readFile( DATA_BASE_PATH, DATA_BASE_HEADER, DATA_BASE_DELIMITER, dataBaseInfo );
	readFile( file, INPUT_FILE_HEADER, INPUT_FILE_DELIMITER, inputFileInfo );
}

void	BitcoinExchange::readFile( std::string file, std::string header, char delimiter, std::map< std::string, float >& info )
{
	std::ifstream	input;
	std::string		storage;

	input.open( file );
	if ( input.is_open() == false )
		throw std::runtime_error( "Error Could not open file\n" );
	std::getline( input, storage );
	if ( storage != header )
		throw std::runtime_error( "Error: Invalid data header -> " + header );
	while ( std::getline( input, storage ) )
	{
		try
		{
			checkLine( storage, delimiter );
		}
		catch( const std::exception& e )
		{
			std::cerr << e.what() << std::endl;
		}
		std::cout << storage << std::endl;
	}
	( void ) info;
}

void	BitcoinExchange::checkLine( std::string& line, char delimiter )
{
	size_t				firstDel;
	std::string			extract;
	std::stringstream	tmpstream( line );

	firstDel = line.find_first_of( delimiter );
	if ( firstDel == std::string::npos || firstDel != line.find_last_of( delimiter ) )
		throw std::runtime_error( "Error: bad input => " + line );
	std::getline( tmpstream, extract, delimiter );
	if ( extract.length() == 0 )
		throw std::runtime_error( "Error: bad input => " + line );
	if ( checkDateSyntax( extract ) == true )
		throw std::runtime_error( "Error: bad input => " + line );
}

bool	BitcoinExchange::checkDateSyntax( std::string& date )
{
	std::stringstream	tmpstream( date );
	std::string			value;
	unsigned int		dashCount;
	size_t				len;
	const size_t		lengths[ 3 ] = { 4, 2, 2 };

	len = date.length() - 1;
	while ( len >= 0 && date[ len ] == ' ' )
		date.erase( date.begin() + len );
	if ( countChar( date, '-', std::string::npos ) != 2 )
		return ( false );
	value = "42";
	for ( int i = 0; i != 2 && value.length() > 0; i++ )
	{
		std::getline( tmpstream, value , '-' );
		if ( value.length() != lengths[ i ] || !isInt( value ) )
			return ( false );
	}
	return ( true );
}

size_t	BitcoinExchange::countChar( std::string str, char c, size_t n )
{
	size_t	count;

	for ( count = 0; str.find( c ) < n; count++ )
		str = str.find( c ) + 1;
	return ( count );
}

bool	BitcoinExchange::isInt( std::string& num )
{
	for ( std::string::iterator it = num.begin(); it != num.end(); it++ )
	{
		if  ( !std::isdigit( *it ) )
			return ( false );
	}
	return ( true );
}

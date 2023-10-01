/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BitcoinExchange.cpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eralonso <eralonso@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/30 11:53:10 by eralonso          #+#    #+#             */
/*   Updated: 2023/10/01 14:49:12 by eralonso         ###   ########.fr       */
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

	processFile( DATA_BASE_PATH, DATA_BASE_HEADER, DATA_BASE_DELIMITER, floatToString( DATA_BASE_VALUE_LIMIT ), dataBaseInfo );
	processFile( file, INPUT_FILE_HEADER, INPUT_FILE_DELIMITER, floatToString( INPUT_FILE_VALUE_LIMIT ), inputFileInfo );
	dataBaseInfo.clear();
	inputFileInfo.clear();
}

void	BitcoinExchange::processFile( std::string file, std::string header, char delimiter, std::string valueLimit, std::map< std::string, float >& info )
{
	std::ifstream					input;
	std::string						storage;
	std::pair< std::string, float >	elem;

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
			elem = checkLine( storage, delimiter, valueLimit );
			if ( info.count( elem.first ) > 0 )
				throw std::runtime_error( "Error: Duplicate date => " + storage );
			info.insert( elem );
		}
		catch( const std::exception& e )
		{
			std::cerr << e.what() << std::endl;
		}
		// std::cout << storage << std::endl;
	}
	( void ) info;
	input.close();
}

std::pair< std::string, float >	BitcoinExchange::checkLine( std::string& line, char delimiter, std::string& valueLimit )
{
	size_t				firstDel;
	std::string			extract[ 2 ];
	std::stringstream	tmpstream( line );
	std::string			error = "bad input => [ ";

	firstDel = line.find_first_of( delimiter );
	if ( firstDel == std::string::npos || firstDel != line.find_last_of( delimiter ) )
		throw std::runtime_error( "Error: " + error + line + " ]" );
	std::getline( tmpstream, extract[ 0 ], delimiter );
	if ( extract[ 0 ].length() == 0 )
		throw std::runtime_error( "Error: " + error + line + " ]" );
	if ( checkDateSyntax( extract[ 0 ] ) == false )
		throw std::runtime_error( "Error: " + error + line + " ]" );
	std::getline( tmpstream, extract[ 1 ], delimiter );
	if ( extract[ 1 ].length() == 0 )
		throw std::runtime_error( "Error: " + error + line + " ]" );
	if ( checkValue( extract[ 1 ], valueLimit, error ) == false )
		throw std::runtime_error( "Error: " + error + line + " ]" );
	// std::cout << "date:" << extract[ 0 ] << ":" << " value:" << std::atof( extract[ 1 ].c_str() ) << ":" << std::endl;
	return ( std::pair< std::string, float >( extract[ 0 ], std::atof( extract[ 1 ].c_str() ) ) );
}

bool	BitcoinExchange::checkDateSyntax( std::string& date )
{
	std::stringstream	tmpstream;
	std::string			value;
	const size_t		lengths[ 3 ] = { 4, 2, 2 };

	if ( *(date.end() - 1) == ' ' )
		date.erase( date.end() - 1 );
	if ( date.length() == 0 || countChar( date, '-', std::string::npos ) != 2 )
		return ( false );
	tmpstream << date;
	value = "42";
	for ( int i = 0; i < 3; i++ )
	{
		std::getline( tmpstream, value , '-' );
		if ( value.length() != lengths[ i ] || !isInt( value ) )
			return ( false );
	}
	return ( true );
}

bool	BitcoinExchange::checkValue( std::string& value, std::string& valueLimit, std::string& error )
{
	size_t		i;
	std::string	beforeDotValue;
	std::string	beforeDotValueLimit;

	if ( *value.begin() == ' ' )
		value.erase( value.begin() );
	if ( value.length() == 0 )
		return ( false );
	for ( i = 0; i < value.length() && value[ i ] == '0'; i++ )
		;
	value.erase( 0, i );
	if ( !isPositiveFloat( value, error ) )
		return ( false );
	beforeDotValue = beforeDot( value );
	beforeDotValueLimit = beforeDot( valueLimit );
	if ( beforeDotValue.length() > beforeDotValueLimit.length() \
		|| ( beforeDotValue.length() == beforeDotValueLimit.length() \
			&& beforeDotValueLimit.compare( beforeDotValue ) < 0 ) )
	{
		error = "too large number => [ ";
		return ( false );
	}
	return ( true );
}

size_t	BitcoinExchange::countChar( std::string str, char c, size_t n )
{
	size_t	count;

	for ( count = 0; str.find( c ) < n; count++ )
		str.erase( 0, str.find( c ) + 1 );
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

bool	BitcoinExchange::isPositiveFloat( std::string& num, std::string& error )
{
	std::string::iterator	it;

	if ( countChar( num, '.', std::string::npos ) > 1 )
	{
		error = "not a number => [ ";
		return ( false );
	}
	if ( *num.begin() == '+' )
		num.erase( 0, 1 );
	it = num.begin() + ( *num.begin() == '-' ? 1 : 0);
	for ( ; it != num.end(); it++ )
	{
		if  ( !std::isdigit( *it ) && *it != '.' )
		{
			error = "not a number => [ ";
			return ( false );
		}
	}
	if ( *num.begin() == '-' )
	{
		error = "not a positive number => [ ";
		return ( false );
	}
	return ( true );
}

std::string	BitcoinExchange::beforeDot( std::string& num )
{
	std::string	res;

	res = num;
	if ( num.find( '.' ) != std::string::npos )
		res = num.substr( 0, num.find( '.' ) );
	return ( res );
}

std::string	BitcoinExchange::floatToString( float num )
{
	std::stringstream	ss;

	ss << std::fixed << num;
	return ( ss.str() );
}
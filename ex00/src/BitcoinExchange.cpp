/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BitcoinExchange.cpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eralonso <eralonso@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/30 11:53:10 by eralonso          #+#    #+#             */
/*   Updated: 2023/10/03 16:29:42 by eralonso         ###   ########.fr       */
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
	std::ifstream					dataFile;
	std::ifstream					inputFile;

	checkFile( DATA_BASE_PATH, DATA_BASE_HEADER, dataFile );
	try
	{
		processFile( dataFile, DATA_BASE_DELIMITER, floatToString( DATA_BASE_VALUE_LIMIT ), dataBaseInfo, true );
		checkFile( file, INPUT_FILE_HEADER, inputFile );
		processFile( inputFile, INPUT_FILE_DELIMITER, floatToString( INPUT_FILE_VALUE_LIMIT ), dataBaseInfo, false );
	}
	catch( const std::exception& e )
	{
		dataFile.close();
		std::cerr << e.what() << std::endl;
		return ;
	}
	inputFile.close();
	dataFile.close();
}

void	BitcoinExchange::checkFile( std::string file, std::string headerExpected, std::ifstream& in )
{
	std::string	headerFile;

	in.open( file );
	if ( in.is_open() == false )
		throw std::runtime_error( "Error: Could not open file\n" );
	std::getline( in, headerFile );
	if ( headerExpected != headerFile )
	{
		in.close();
		throw std::runtime_error( "Error: Invalid data header => " + headerExpected );
	}
}

void	BitcoinExchange::processFile( std::ifstream& in, char delimiter, std::string valueLimit, std::map< std::string, float >& dataBase, bool isDB )
{
	std::pair< std::string, float >	elem;
	float							value;
	std::string						storage;

	while ( std::getline( in, storage ) )
	{
		try
		{
			elem = checkLine( storage, delimiter, valueLimit );
			if ( isDB == true )
			{
				if ( dataBase.count( elem.first ) > 0 )
					throw std::runtime_error( "Error: Duplicate date => " + storage );
				dataBase.insert( elem );
			}
			else
			{
				if ( dataBase.find( elem.first ) != dataBase.end() )
					value = dataBase[ elem.first ];
				else
				{
					dataBase.insert( elem );
					if ( dataBase.find( elem.first ) == dataBase.begin() )
						throw std::runtime_error( "Error: Date not found and no lowest date availabe on Data Base => [ " + storage + " ]" );
					value = (*(--dataBase.find( elem.first ))).second;
					dataBase.erase( elem.first );
				}
				std::cout << std::fixed << std::setprecision( 2 ) << elem.first << " => " << elem.second << " = " << elem.second * value << std::endl;
			}
		}
		catch( const std::exception& e )
		{
			std::cerr << e.what() << std::endl;
		}
	}
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
	if ( checkDate( extract[ 0 ] ) == false )
		throw std::runtime_error( "Error: " + error + line + " ]" );
	std::getline( tmpstream, extract[ 1 ], delimiter );
	if ( extract[ 1 ].length() == 0 )
		throw std::runtime_error( "Error: " + error + line + " ]" );
	if ( checkValue( extract[ 1 ], valueLimit, error ) == false )
		throw std::runtime_error( "Error: " + error + line + " ]" );
	return ( std::pair< std::string, float >( extract[ 0 ], std::atof( extract[ 1 ].c_str() ) ) );
}

bool	BitcoinExchange::checkDate( std::string& date )
{
	std::stringstream	tmpstream;
	std::string			value;
	size_t				components;
	const size_t		lengths[ 3 ] = { 4, 2, 2 };
	const size_t		ranges[ 3 ][ 2 ] = { { 0, 9999 }, { 1, 12 }, { 1, 31 } };

	if ( *(date.end() - 1) == ' ' )
		date.erase( date.end() - 1 );
	if ( date.length() == 0 || countChar( date, '-', std::string::npos ) != 2 )
		return ( false );
	tmpstream << date;
	value = "42";
	for ( int i = 0; i < 3; i++ )
	{
		std::getline( tmpstream, value , '-' );
		components = std::atoi( value.c_str() );
		if ( value.length() != lengths[ i ] || !isInt( value ) \
			|| components < ranges[ i ][ 0 ] || components > ranges[ i ][ 1 ] )
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

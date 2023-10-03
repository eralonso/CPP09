/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PmergeMe.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eralonso <eralonso@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/03 16:30:58 by eralonso          #+#    #+#             */
/*   Updated: 2023/10/03 19:35:46 by eralonso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "PmergeMe.hpp"

PmergeMe::PmergeMe( void ) {}

PmergeMe::PmergeMe( const PmergeMe& pmm )
{
	( void ) pmm;
}

PmergeMe::~PmergeMe( void ) {}

PmergeMe&	PmergeMe::operator=( const PmergeMe& pmm )
{
	( void ) pmm;
	return ( *this );
}

void	PmergeMe::mergeInsertionSort( char **nums )
{
	std::vector< int >	vec;
	std::list< int >	lst;
	time_t				vecTime[ 2 ];
	time_t				lstTime[ 2 ];

	checkNumbers( nums, vec, lst );
	printNumbers( "Before", vec );
	time( &vecTime[ 0 ] );
	time( &vecTime[ 1 ] );
	time( &lstTime[ 0 ] );
	time( &lstTime[ 1 ] );
	printNumbers( "After", vec );
	printTime( vec.size(), "vector", difftime( vecTime[ 1 ], vecTime[ 0 ] ) );
	printTime( lst.size(), "list", difftime( lstTime[ 1 ], lstTime[ 0 ] ) );
}

void	PmergeMe::checkNumbers( char **nums, std::vector< int >& container1, std::list< int >& container2 )
{
	std::string	error;

	error = "Error: ";
	for ( int i = 0; nums[ i ] != NULL; i++ )
	{
		if ( !isPositiveNum( nums[ i ], error ) )
			throw std::logic_error( error + std::string( nums[ i ] ) );
		if ( !isInteger( nums[ i ], error ) )
			throw std::logic_error( error + std::string( nums[ i ] ) );
		container1.push_back( std::atoi( nums[ i ] ) );
		container2.push_back( std::atoi( nums[ i ] ) );
	}
}

bool	PmergeMe::isInteger( std::string num, std::string& error )
{
	size_t		len;
	std::string	integerMax;

	if ( num[ 0 ] == '+' )
		num.erase( 0, 1 );
	len = num.length();
	if ( len == 0 )
	{
		error = "Error: empty string is not a valid number: ";
		return ( false );
	}
	integerMax = integerToString( INT_MAX );
	if ( len > integerMax.length() \
		|| ( len == integerMax.length() \
			&& integerMax.compare( num ) < 0 ) )
	{
		error = "Error: Not an integer -> [ overflow ]: ";
		return ( false );
	}
	return ( true );
}

bool	PmergeMe::isPositiveNum( std::string num, std::string& error )
{
	size_t	i;
	bool	negative;

	negative = num[ 0 ] == '-' ? true : false;
	i = num[ 0 ] == '-' || num[ 0 ] == '+' ? 1 : 0;
	for ( ; i < num.length(); i++ )
	{
		if ( std::isdigit( num[ i ] ) == false )
		{
			error = "Error: Not a number: ";
			return ( false );
		}
	}
	if ( negative == true )
	{
		error = "Error Not a positive number: ";
		return ( false );
	}
	return ( true );
}

void	PmergeMe::printNumbers( std::string status, std::vector< int > vec )
{
	std::cout << status << ":\t";
	for ( std::vector< int >::iterator it = vec.begin(); it != vec.end(); it++ )
	{
		std::cout << *it;
		if ( it + 1 != vec.end() )
			std::cout << " ";
	}
	std::cout << std::endl;
}

void	PmergeMe::printTime( int range, std::string container, double timeDiff )
{
	std::cout << std::fixed;
	std::cout << "Time to process a range of " << range;
	std::cout << " elements with std::" << container;
	std::cout << " : " << timeDiff << " us" << std::endl;
}

std::string     PmergeMe::integerToString( int num )
{
        std::stringstream       ss;

        ss << num;
        return ( ss.str() );
}
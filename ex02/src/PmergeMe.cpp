/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PmergeMe.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eralonso <eralonso@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/03 16:30:58 by eralonso          #+#    #+#             */
/*   Updated: 2023/10/04 18:37:50 by eralonso         ###   ########.fr       */
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

#include <unistd.h>

void	PmergeMe::mergeInsertionSort( char **nums )
{
	std::vector< int >	vec;
	std::deque< int >	dque;
	std::clock_t		vecTime[ 2 ];
	// time_t				dqueTime[ 2 ];

	checkNumbers( nums, vec, dque );
	printNumbers( "Before", vec );
	vecTime[ 0 ] = std::clock();
	sortVector( vec, 0, vec.size() - 1 );
	// usleep(10000000);
	vecTime[ 1 ] = std::clock();
	// time( &dqueTime[ 0 ] );
	// // sortDeque( dque, 0, dque.size() + 1 );
	// time( &dqueTime[ 1 ] );
	printNumbers( "After", vec );
	printTime( vec.size(), "vector", ( vecTime[ 1 ] - vecTime[ 0 ] ) / CLOCKS_PER_SEC * 1000 );
	// // printTime( dque.size(), "deque", difftime( dqueTime[ 1 ], dqueTime[ 0 ] ) );
}

void	PmergeMe::sortInsertionVector( std::vector< int >& vec, unsigned int start, unsigned int end )
{
	unsigned int	j;
	int				tmp;

	for ( unsigned int i = start; i < end; i++ )
	{
		j = i + 1;
		tmp = vec[ j ];
		for ( ; j > start && vec[ j - 1 ] > tmp ; j-- )
			vec[ j ] = vec[ j - 1 ];
		vec[ j ] = tmp;
	}
}

void	PmergeMe::sortMergeVector( std::vector< int >& vec, unsigned int start, unsigned int mid, unsigned int end )
{
	unsigned int		limits[ 2 ];
	unsigned int		idx[ 2 ];
	std::vector< int >	sides[ 2 ];

	limits[ LEFT ] = ( mid - start ) + 1;
	limits[ RIGHT ] = end - mid;
	sides[ LEFT ].insert( sides[ LEFT ].begin(), vec.begin() + start, vec.begin() + mid + 1 );
	sides[ RIGHT ].insert( sides[ RIGHT ].begin(), vec.begin() + mid + 1, vec.begin() + end + 1 );
	idx[ LEFT ] = 0;
	idx[ RIGHT ] = 0;
	for ( unsigned int i = start; i < ( end - start ) + 1; i++ )
	{
		if ( idx[ LEFT ] == limits[ LEFT ] )
			vec[ i ] = sides[ RIGHT ][ idx[ RIGHT ]++ ];
		else if ( idx[ RIGHT ] == limits[ RIGHT ] )
			vec[ i ] = sides[ LEFT ][ idx[ LEFT ]++ ];
		else if ( sides[ LEFT ][ idx[ LEFT ] ] < sides[ RIGHT ][ idx[ RIGHT ] ] )
			vec[ i ] = sides[ LEFT ][ idx[ LEFT ]++ ];
		else
			vec[ i ] = sides[ RIGHT ][ idx[ RIGHT ]++ ];
	}
}

void	PmergeMe::sortVector( std::vector< int >& vec, unsigned int start, unsigned int end )
{
	int	mid;

	if ( end - start > PmergeMe::_size )
	{
		mid = ( start + end ) / 2;
		sortVector( vec, start, mid );
		sortVector( vec, mid + 1, end );
		sortMergeVector( vec, start, mid, end );
	}
	else
		sortInsertionVector( vec, start, end );
}

void	PmergeMe::checkNumbers( char **nums, std::vector< int >& container1, std::deque< int >& container2 )
{
	std::string	error;

	error = "Error: ";
	for ( int i = 0; nums[ i ] != NULL; i++ )
	{
		if ( !isPositiveNum( nums[ i ], error ) )
			throw std::invalid_argument( error + std::string( nums[ i ] ) );
		if ( !isInteger( nums[ i ], error ) )
			throw std::invalid_argument( error + std::string( nums[ i ] ) );
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
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PmergeMe.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eralonso <eralonso@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/03 16:30:58 by eralonso          #+#    #+#             */
/*   Updated: 2023/10/05 13:45:34 by eralonso         ###   ########.fr       */
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

// Vector Insertion sort algortihm
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

// Vector Merge sort algortihm
void	PmergeMe::sortMergeVector( std::vector< int >& vec, unsigned int start, unsigned int mid, unsigned int end )
{
	unsigned int		limits[ 2 ];
	unsigned int		idx[ 2 ];
	std::vector< int >	sides[ 2 ];
	limits[ LEFT ] = mid - start + 1;
	limits[ RIGHT ] = end - mid;

	sides[ LEFT ].insert( sides[ LEFT ].begin(), vec.begin() + start, vec.begin() + mid + 1 );
	sides[ RIGHT ].insert( sides[ RIGHT ].begin(), vec.begin() + mid + 1, vec.begin() + end + 1 );
	idx[ LEFT ] = 0;
	idx[ RIGHT ] = 0;
	for ( unsigned int i = start; i - start < end - start + 1; i++ )
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

// Vector Merge-Insertion sort algortihm
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

// Deque insertion sort algortihm
void	PmergeMe::sortInsertionDeque( std::deque< int >& dque, unsigned int start, unsigned int end )
{
	unsigned int	j;
	int				tmp;

	for ( unsigned int i = start; i < end; i++ )
	{
		j = i + 1;
		tmp = dque[ j ];
		for ( ; j > start && dque[ j - 1 ] > tmp ; j-- )
			dque[ j ] = dque[ j - 1 ];
		dque[ j ] = tmp;
	}
}

// Deque Merge sort algortihm
void	PmergeMe::sortMergeDeque( std::deque< int >& dque, unsigned int start, unsigned int mid, unsigned int end )
{
	unsigned int		limits[ 2 ];
	unsigned int		idx[ 2 ];
	std::deque< int >	sides[ 2 ];
	limits[ LEFT ] = mid - start + 1;
	limits[ RIGHT ] = end - mid;

	sides[ LEFT ].insert( sides[ LEFT ].begin(), dque.begin() + start, dque.begin() + mid + 1 );
	sides[ RIGHT ].insert( sides[ RIGHT ].begin(), dque.begin() + mid + 1, dque.begin() + end + 1 );
	idx[ LEFT ] = 0;
	idx[ RIGHT ] = 0;
	for ( unsigned int i = start; i - start < end - start + 1; i++ )
	{
		if ( idx[ LEFT ] == limits[ LEFT ] )
			dque[ i ] = sides[ RIGHT ][ idx[ RIGHT ]++ ];
		else if ( idx[ RIGHT ] == limits[ RIGHT ] )
			dque[ i ] = sides[ LEFT ][ idx[ LEFT ]++ ];
		else if ( sides[ LEFT ][ idx[ LEFT ] ] < sides[ RIGHT ][ idx[ RIGHT ] ] )
			dque[ i ] = sides[ LEFT ][ idx[ LEFT ]++ ];
		else
			dque[ i ] = sides[ RIGHT ][ idx[ RIGHT ]++ ];
	}
}

// Deque Merge-Insertion sort algortihm
void	PmergeMe::sortDeque( std::deque< int >& dque, unsigned int start, unsigned int end )
{
	int	mid;

	if ( end - start > PmergeMe::_size )
	{
		mid = ( start + end ) / 2;
		sortDeque( dque, start, mid );
		sortDeque( dque, mid + 1, end );
		sortMergeDeque( dque, start, mid, end );
	}
	else
		sortInsertionDeque( dque, start, end );
}

// Main function
void	PmergeMe::mergeInsertionSort( char **nums )
{
	std::vector< int >	vec;
	std::deque< int >	dque;
	std::clock_t		vecTime[ 2 ];
	std::clock_t		dqueTime[ 2 ];

	checkNumbers( nums, vec, dque );
	printNumbers( "Before", vec );
	vecTime[ 0 ] = std::clock();
	sortVector( vec, 0, vec.size() - 1 );
	vecTime[ 1 ] = std::clock();
	dqueTime[ 0 ] = std::clock();
	sortDeque( dque, 0, dque.size() - 1 );
	dqueTime[ 1 ] = std::clock();
	printNumbers( "\n\nAfter", vec );
	printTime( vec.size(), "vector", ( static_cast< double >( vecTime[ 1 ] - vecTime[ 0 ] ) / CLOCKS_PER_SEC ) * 1000000 );
	printTime( dque.size(), "deque", ( static_cast< double >( dqueTime[ 1 ] - dqueTime[ 0 ] ) / CLOCKS_PER_SEC ) * 1000000 );
	if ( PmergeMe::isSorted< std::vector< int > >( vec.begin(), vec.end() ) == false )
		throw std::runtime_error( "\033[1;91mVector Is not sorted\033[1;97m" );
	std::cout << "\033[1;92mVector Is sorted\033[1;97m" << std::endl;
	if ( PmergeMe::isSorted< std::deque< int > >( dque.begin(), dque.end() ) == false )
		throw std::runtime_error( "\033[1;91mDeque Is not sorted\033[1;97m" );
	std::cout << "\033[1;92mDeque Is sorted\033[1;97m" << std::endl;
}

// Sorting check Util
template < typename T >
bool	PmergeMe::isSorted( typename T::iterator begin, typename T::iterator end )
{
	typename T::value_type	last;

	for ( typename T::iterator it = begin; it != end; it++ )
	{
		if ( it != begin &&  *it < last )
			return ( false );
		last = *it;
	}
	return ( true );
}

// Numbers checking
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
		if ( std::find< std::vector< int >::iterator, int >( container1.begin(), container1.end(), std::atoi( nums[ i ] ) ) != container1.end() )
			throw std::invalid_argument( "Error: Duplicate number is invalid => " + std::string( nums[ i ] ) );
		container1.push_back( std::atoi( nums[ i ] ) );
		container2.push_back( std::atoi( nums[ i ] ) );
	}
}

// Utils
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
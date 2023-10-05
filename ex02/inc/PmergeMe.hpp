/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PmergeMe.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eralonso <eralonso@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/03 14:21:07 by eralonso          #+#    #+#             */
/*   Updated: 2023/10/05 13:28:01 by eralonso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <iostream>
#include <sstream>
#include <deque>
#include <vector>
#include <algorithm>

#define LEFT 0
#define RIGHT 1

class PmergeMe
{
	private:
		static const unsigned int	_size = 5;
		PmergeMe( void );
		PmergeMe( const PmergeMe& pmm );
		~PmergeMe( void );
		PmergeMe&			operator=( const PmergeMe& pmm );
		template < typename T >
		static bool			isSorted( typename T::iterator begin, typename T::iterator end );
		static void			sortInsertionVector( std::vector< int >& vec, unsigned int start, unsigned int end );
		static void			sortMergeVector( std::vector< int >& vec, unsigned int start, unsigned int mid, unsigned int end );
		static void			sortVector( std::vector< int >& vec, unsigned int start, unsigned int end );
		static void			sortInsertionDeque( std::deque< int >& dque, unsigned int start, unsigned int end );
		static void			sortMergeDeque( std::deque< int >& dque, unsigned int start, unsigned int mid, unsigned int end );
		static void			sortDeque( std::deque< int >& dque, unsigned int start, unsigned int end );
		static std::string	integerToString( int num );
		static void			checkNumbers( char **nums, std::vector< int >& container1, std::deque< int >& container2 );
		static bool			isInteger( std::string num, std::string& error );
		static bool			isPositiveNum( std::string num, std::string& error );
		static void			printNumbers( std::string status, std::vector< int > vec );
		static void			printTime( int range, std::string container, double timeDiff );
	public:
		static void	mergeInsertionSort( char **nums );
};
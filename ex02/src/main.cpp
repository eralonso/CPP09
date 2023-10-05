/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eralonso <eralonso@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/26 11:33:48 by eralonso          #+#    #+#             */
/*   Updated: 2023/10/05 13:27:04 by eralonso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include "PmergeMe.hpp"

int main( int ac, char **argv )
{
	int	exitStatus;

	exitStatus = 0;
	if ( ac < 2 )
	{
		std::cerr << "Too few numbers to sort" << std::endl;
		return ( 1 );
	}
	try
	{
		PmergeMe::mergeInsertionSort( &argv[ 1 ] );
	}
	catch ( const std::exception& e )
	{
		std::cerr << e.what() << std::endl;
		if ( strstr( e.what(), "Is not sorted" ) != NULL )
			exitStatus = 1;
	}
	return ( exitStatus );
}
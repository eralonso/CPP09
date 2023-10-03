/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eralonso <eralonso@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/26 11:33:48 by eralonso          #+#    #+#             */
/*   Updated: 2023/10/03 13:01:43 by eralonso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include "RPN.hpp"

int main( int ac, char **argv )
{
	if ( ac != 2 )
	{
		std::cerr << "Invalid number of arguments" << std::endl;
		return ( 1 );
	}
	try
	{
		RPN::calculate( argv[ 1 ] );
	}
	catch ( const std::exception& e )
	{
		std::cerr << e.what() << std::endl;
		return ( 1 );
	}
	return ( 0 );
}
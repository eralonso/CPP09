/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eralonso <eralonso@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/26 11:33:48 by eralonso          #+#    #+#             */
/*   Updated: 2023/09/30 18:37:25 by eralonso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include "BitcoinExchange.hpp"

int main( int ac, char **av )
{
	std::string	file;

	if ( ac < 2 )
	{
		std::cerr << "Too few arguments, needed at least one input file" << std::endl;
		return ( 1 );
	}
	for ( int i = 1; i < ac; i++ )
	{
		file = av[ i ];
		std::transform( file.begin(), file.end(), file.begin(), toupper );
		std::cout << "[ " << file << " ]\n" << std::endl;
		try
		{
			BitcoinExchange::exchange( av[ i ] );
		}
		catch ( const std::exception& e )
		{
			std::cerr << e.what() << std::endl;
		}
		std::cout << "\n\n" << std::endl;
		file.clear();
	}
	return ( 0 );
}
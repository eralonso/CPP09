/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pueba.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eralonso <eralonso@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/30 18:38:28 by eralonso          #+#    #+#             */
/*   Updated: 2023/09/30 18:41:27 by eralonso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include <sstream>
#include <string>

int	main( void )
{
	std::string			a = "hola";
	std::string			tmp;
	std::stringstream	b( a );

	std::getline( b, a, 'h' );
	std::cout << "tmp:" << tmp << ":" << std::endl;
	std::cout << "tmp length:" << tmp.length() << ":" << std::endl;
	return ( 0 );
}

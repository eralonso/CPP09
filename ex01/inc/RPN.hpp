/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RPN.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eralonso <eralonso@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/02 19:30:33 by eralonso          #+#    #+#             */
/*   Updated: 2023/10/05 13:28:20 by eralonso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <iostream>
#include <string>
#include <sstream>
#include <stack>

#define ALLOWED_OPERATIONS_SIZE 4

class RPN
{
	private:
		RPN( void );
		RPN( const RPN& rpn );
		~RPN( void );
		RPN&		operator=( const RPN& rpn );
		static void	checkRes( std::stack< int >& storage );
		static bool	isOperation( char c, std::stack< int >& storage );
		static void	doAddition( std::stack< int >& storage );
		static void	doSubstraction( std::stack< int >& storage );
		static void	doMultiplication( std::stack< int >& storage );
		static void	doDivision( std::stack< int >& storage );
	public:
		static void	calculate( std::string operation );
};
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RPN.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eralonso <eralonso@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/02 19:30:33 by eralonso          #+#    #+#             */
/*   Updated: 2023/10/02 19:42:07 by eralonso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <iostream>
#include <string>
#include <stack>

class RPN
{
	private:
		std::stack< int >	_stk;
	public:
		RPN( void );
		RPN( const RPN& rpn );
		~RPN( void );
		RPN&	operator=( const RPN& rpn );
				
};
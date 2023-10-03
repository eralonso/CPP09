/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RPN.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eralonso <eralonso@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/03 10:46:35 by eralonso          #+#    #+#             */
/*   Updated: 2023/10/03 14:15:58 by eralonso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "RPN.hpp"

RPN::RPN( void ) {}

RPN::RPN( const RPN& rpn )
{
	( void ) rpn;
}

RPN::~RPN( void ) {}

RPN&	RPN::operator=( const RPN& rpn )
{
	( void ) rpn;
	return ( *this );
}

void	RPN::calculate( std::string str )
{
	std::stack< int >	storage;
	std::stringstream	values( str );
	std::string			components;

	while ( values >> components )
	{
		if ( components.length() != 1 )
			throw std::logic_error( "Error: Too long parameter provided \"" + components + "\"" );
		if ( std::isdigit( *( components.begin() ) ) )
			storage.push( std::atoi( components.c_str() ) );
		else if ( isOperation( *( components.begin() ), storage ) == false )
			throw std::logic_error( "Error: Not a valid operation" );
	}
	checkRes( storage );
	std::cout << storage.top() << std::endl;
	storage.pop();
}

void	RPN::checkRes( std::stack< int >& storage )
{
	if ( storage.empty() == true )
		throw std::logic_error( "Error: No numbers provided" );
	if ( storage.size() > 1 )
		throw std::logic_error( "Error: Too many numbers in stack" );
}

bool	RPN::isOperation( char c, std::stack< int >& storage )
{
	unsigned int	i;
	char			allowedOperations[ ALLOWED_OPERATIONS_SIZE ] = { '+', '-', '*', '/' };
	void			( *doOperation[ ALLOWED_OPERATIONS_SIZE ] )( std::stack< int >& storage ) = { \
															&RPN::doAddition, &RPN::doSubstraction, \
															&RPN::doMultiplication, &RPN::doDivision };

	i = 0;
	while ( i < ALLOWED_OPERATIONS_SIZE && allowedOperations[ i ] != c )
		i++;
	if ( i ==  ALLOWED_OPERATIONS_SIZE )
		return ( false );
	if ( storage.size() < 2 )
		throw std::logic_error( "Error: Too few numbers to do an operation, at least two" );
	doOperation[ i ]( storage );
	return ( true );
}

void	RPN::doAddition( std::stack< int >& storage )
{
	double	res;

	res = storage.top();
	storage.pop();
	res = static_cast< double >( storage.top() ) + res;
	storage.pop();
	if ( res > INT_MAX )
		throw  std::overflow_error( "Error: Integer overflow" );
	if ( res < INT_MIN )
		throw  std::underflow_error( "Error: Integer underflow" );
	storage.push( res );
}

void	RPN::doSubstraction( std::stack< int >& storage )
{
	double	res;

	res = storage.top();
	storage.pop();
	res = static_cast< double >( storage.top() ) - res;
	storage.pop();
	if ( res > INT_MAX )
		throw  std::overflow_error( "Error: Integer overflow" );
	if ( res < INT_MIN )
		throw  std::underflow_error( "Error: Integer underflow" );
	storage.push( res );
}

void	RPN::doMultiplication( std::stack< int >& storage )
{
	double	res;

	res = storage.top();
	storage.pop();
	res = static_cast< double >( storage.top() ) * res;
	storage.pop();
	if ( res > INT_MAX )
		throw  std::overflow_error( "Error: Integer overflow" );
	if ( res < INT_MIN )
		throw  std::underflow_error( "Error: Integer underflow" );
	storage.push( res );
}

void	RPN::doDivision( std::stack< int >& storage )
{
	double	res;

	res = storage.top();
	storage.pop();
	if ( res == 0 )
		throw std::logic_error( "Error: Invalid division by zero" );
	res = static_cast< double >( storage.top() ) / res;
	storage.pop();
	if ( res > INT_MAX )
		throw  std::overflow_error( "Error: Integer overflow" );
	if ( res < INT_MIN )
		throw  std::underflow_error( "Error: Integer underflow" );
	storage.push( res );
}

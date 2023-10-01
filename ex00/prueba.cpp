#include <iostream>
#include <sstream>
#include <float.h>
#include <string>

int	main( void )
{
	std::stringstream	ss;

	ss << std::fixed << FLT_MAX;
	std::cout << ss.str() << std::endl;
	return ( 0 );
}


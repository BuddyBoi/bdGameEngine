#include "Include.hpp"

int main( )
{
	if ( Threads::bSetup() )
		while ( !Globals::bForceExit )
			Sleep( 1000 );

	return 0;
}
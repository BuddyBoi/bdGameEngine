#pragma once 
#include "Include.hpp"

namespace Globals
{
	bool bForceExit = false;
	float fTime = 0.0f;
	float fTick = 0.0f;

	int iThreadDefExit = 1027;
}

bool bCreateThread( void *pFuncAddress )
{
	if ( !pFuncAddress )
		return false;

	if ( HANDLE hThread = CreateThread( 0, 0, (LPTHREAD_START_ROUTINE) pFuncAddress, 0, 0, 0 ) )
	{
		CloseHandle( hThread );
		return true;
	}

	return false;
}
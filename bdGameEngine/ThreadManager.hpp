#pragma once
#include "Include.hpp"

class cThread
{
	int iIndex = 0;
	void *pFuncAddress = nullptr;
	int64_t iFuncAddress = 0;
	std::string sTag = "NONE";
	DWORD dwThreadId = 0;
	bool bCreated = false;
public:
	std::string GetTag()
	{
		return sTag;
	}
	bool Suspend( )
	{
		if ( HANDLE h = OpenThread( PROCESS_VM_READ, false, dwThreadId ) )
		{
			SuspendThread( h );
			CloseHandle( h );
			return true;
		}

		return false;
	}
	bool Resume( )
	{
		if ( HANDLE h = OpenThread( PROCESS_VM_READ, false, dwThreadId ) )
		{
			ResumeThread( h );
			CloseHandle( h );
			return true;
		}

		return false;
	}
	bool Destroy( )
	{
		if ( HANDLE h = OpenThread( PROCESS_VM_READ, false, dwThreadId ) )
		{
			TerminateThread( h, Globals::iThreadDefExit );
			CloseHandle( h );
			return true;
		}

		return false;
	}
	cThread( void *ptr, std::string tag = "NONE" ) : sTag( tag ), pFuncAddress( ptr )
	{
		if ( HANDLE h = CreateThread( 0, 0, (LPTHREAD_START_ROUTINE) pFuncAddress, 0, 0, &dwThreadId ) )
		{
			bCreated = true;
			CloseHandle( h );
		}
	}
};

class cThreadManager
{
	int iLock = 0;
	std::vector<cThread> vecThreads { };
public:
	cThreadManager( int lock ) : iLock( lock )
	{ }
	bool Create( void* pFuncAddress, std::string sTag = "NONE" )
	{
		if ( !pFuncAddress )
			return false;

		cThread curThread( pFuncAddress, sTag );
		vecThreads.push_back( curThread );
	}
	std::vector<cThread *> GetThreadList( )
	{
		std::vector<cThread *> vecRet { };
		if ( !vecThreads.size( ) )
			return vecRet;

		for ( cThread x : vecThreads )
		{
			cThread *curThread = reinterpret_cast<cThread *>(&x);
			vecRet.push_back( curThread );
		}

		return vecRet;
	}
	cThread *GetThreadByTag( std::string sTag )
	{
		for ( cThread *x : GetThreadList( ) )
		{
			if ( x->GetTag( ) == sTag )
				return x;
		}
	}
};
cThreadManager ThreadManager( 1 );
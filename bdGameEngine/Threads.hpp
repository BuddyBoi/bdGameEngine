#pragma once 
#include "Include.hpp"
#include "Game.hpp"

namespace Threads
{
	void GameLoop( )
	{
		//fill object list
		ObjectManager.Add( 1, { 10.0f, 10.0f }, "PLAYER" );
		ObjectManager.Add( 2, { 250.0f, 250.0f }, "ENEMY 1" );
		ObjectManager.Add( 3, { 650.0f, 650.0f }, "ENEMY 2" );

		//get localplayer
		cObject *playerLocal = ObjectManager.GetObjectByIndex( 1 );
		playerLocal->MoveAbs( 500, 500 );

		while ( !Globals::bForceExit )
		{
			//controls
			{
				if ( GetAsyncKeyState( VK_RIGHT ) )
				{
					playerLocal->MoveRel( 1, 0 );
				}
				if ( GetAsyncKeyState( VK_LEFT ) )
				{
					playerLocal->MoveRel( -1, 0 );
				}
				if ( GetAsyncKeyState( VK_UP ) )
				{
					playerLocal->MoveRel( 0, -1 );
				}
				if ( GetAsyncKeyState( VK_DOWN ) )
				{
					playerLocal->MoveRel( 0, 1 );
				}
			}

			//hitbox register
			cObject *playerNearest = ObjectManager.GetObjectNearest( playerLocal );
			bool bCollidingWithNearest = false;

			if ( playerNearest )
			{
				bCollidingWithNearest = playerNearest->CheckCollider( playerLocal );
			}

			if ( GetAsyncKeyState( VK_RETURN ) && bCollidingWithNearest )
			{
				playerLocal->RunAttack( playerNearest );
			}

			Globals::fTick++;
			Sleep( 1 );
		}
	}

	void Render( )
	{
		if ( !RenderManager.Initialize( ) )
		{
			printf( "ERROR - FAILED TO INIT RENDERER\n" );
			return;
		}

		while ( !Globals::bForceExit )
		{
			Sleep( 1 );
			RenderManager.BeginScene( );
			{
				RenderManager.DrawString( 1, 1, "Test", COL_RED );
				Game::DrawObjectsList( );
			}
			RenderManager.EndScene( );
			Sleep( 1 );
		}

		RenderManager.Uninitialize( );
	}

	void Main( )
	{
		while ( !Globals::bForceExit )
		{
			Sleep( 1 );
		}
	}

	bool bSetup( )
	{
		if ( !bCreateThread( Main )
			|| !bCreateThread( Render )
			|| !bCreateThread( GameLoop )
			)
			return false;

		return true;
	}
}
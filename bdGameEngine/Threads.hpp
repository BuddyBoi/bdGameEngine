#pragma once 
#include "Include.hpp"
#include "Game.hpp"

namespace Threads
{
	void GameLoop( )
	{
		Game::CreateObjectList( );
		Game::Player = Game::GetPlayer( );
		Game::Player->MoveAbs( 500, 500 );

		while ( !Globals::bForceExit )
		{
			Game::EnemyClosest = ObjectManager.GetObjectNearest( Game::Player );
			Game::IsPlayerCollidingWithNearestEnemy = Game::Player->CheckCollider( Game::EnemyClosest );
			Game::RunKeyBindings( );
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
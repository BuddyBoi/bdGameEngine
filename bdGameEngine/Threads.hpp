#pragma once 
#include "Include.hpp"
#include "Game.hpp"
#include "EventManager.hpp"

namespace Threads
{
	void GameLoop( )
	{
		Game::CreateObjectList( );
		Game::Player = Game::GetPlayer( );
		Game::Player->MoveAbs( 500, 500 );

		//base game loop
		while ( !Globals::bForceExit )
		{
			printf( "LOOP\n" );

			Game::EnemyClosest = ObjectManager.GetObjectNearest( Game::Player );
			Game::IsPlayerCollidingWithNearestEnemy = Game::Player->CheckCollider( Game::EnemyClosest );
			
			//movement
			{
				if ( Game::bMovingUp )
				{
					Game::Player->vPosition.y--;
					Game::Player->fAngle = 0.0f;
				}					
				if ( Game::bMovingDown )
				{
					Game::Player->vPosition.y++;
					Game::Player->fAngle = 180.0f;
				}
				if ( Game::bMovingRight )
				{					
					Game::Player->vPosition.x++;
					Game::Player->fAngle = 90.0f;
				}
				if ( Game::bMovingLeft )
				{
					Game::Player->vPosition.x--;
					Game::Player->fAngle = 270.0f;					
				}
				if ( Game::bAttacking )
					//Game::ShootBullet( { 500.0f, 500.0f }, Game::Player->fAngle );

				Game::bMovingDown = false;
				Game::bMovingLeft = false;
				Game::bMovingUp = false;
				Game::bMovingRight = false;
				Game::bAttacking = false;
				Game::bAttacking = false;
			}

			//move bullets
			{
				for ( cObject *bullet : ObjectManager.GetObjectsList( 4 ) )
				{
					if ( bullet->fAngle == 90.0f )
						bullet->MoveRel( 1, 0 );
					if ( bullet->fAngle == 180.0f )
						bullet->MoveRel( 0, 1 );
					if ( bullet->fAngle == 270.0f )
						bullet->MoveRel( -1, 0 );
					if ( bullet->fAngle == 0.0f )
						bullet->MoveRel( 0, -1 );
				}				
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

		//rendering loop
		while ( !Globals::bForceExit )
		{
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
		//windows abstraction layer
		while ( !Globals::bForceExit )
		{
			Game::RunInputManager( );
			Sleep( 1 );
		}
	}

	bool bSetup( )
	{
		if ( !ThreadManager.Create( Main )
			|| !ThreadManager.Create( Render )
			|| !ThreadManager.Create( GameLoop )
			)
			return false;

		return true;
	}
}
#pragma once
#include "Include.hpp"

namespace Game
{
	cObject *Player = nullptr;
	cObject *EnemyClosest = nullptr;

	bool IsPlayerCollidingWithNearestEnemy = false;

	cObject *GetPlayer( )
	{
		return ObjectManager.GetObjectByIndex(1);
	}
	void CreateObjectList( )
	{
		//create static objects - modify after adding EntityList
		ObjectManager.Add( 1, { 10.0f, 10.0f }, "PLAYER" );
		ObjectManager.Add( 2, { 250.0f, 250.0f }, "NPC_ENEMY" );
		ObjectManager.Add( 3, { 650.0f, 650.0f }, "NPC_ENEMY_BOSS" );
	}
	void RunKeyBindings( )
	{
		if ( GetAsyncKeyState( VK_RIGHT ) )
		{
			Game::Player->MoveRel( 1, 0 );
		}
		if ( GetAsyncKeyState( VK_LEFT ) )
		{
			Game::Player->MoveRel( -1, 0 );
		}
		if ( GetAsyncKeyState( VK_UP ) )
		{
			Game::Player->MoveRel( 0, -1 );
		}
		if ( GetAsyncKeyState( VK_DOWN ) )
		{
			Game::Player->MoveRel( 0, 1 );
		}
		if ( GetAsyncKeyState( VK_RETURN ) )
		{
			if ( IsPlayerCollidingWithNearestEnemy )
			{
				Player->RunAttack( EnemyClosest );
			}
		}
	}
	void DrawObjectsList( )
	{
		RenderManager.DrawCircle( 250, 250, 30, COL_RED );

		if ( !ObjectManager.GetObjectListSize( ) )
			return;

		std::vector<cObject *> vecObjects { };
		vecObjects = ObjectManager.GetObjectsList( );

		for ( int i = 0; i != vecObjects.size( ); i++ )
		{
			if ( !vecObjects[i] )
				continue;

			cObject *object = vecObjects[i];
			if ( !object->fSize
				|| !object->fHealth )
				continue;

			RenderManager.DrawString( object->vPosition.x, object->vPosition.y - 15, std::to_string( object->GetHealth( ) ), COL_BLUE );
			RenderManager.DrawRect( object->vPosition.x, object->vPosition.y, object->fSize, object->fSize, COL_RED );
		}
	}
}
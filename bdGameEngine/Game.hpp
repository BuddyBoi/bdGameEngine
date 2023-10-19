#pragma once
#include "Include.hpp"

namespace Game
{
	cObject *Player = nullptr;
	cObject *EnemyClosest = nullptr;
	bool IsPlayerCollidingWithNearestEnemy = false;
	
	bool bMovingUp = false;
	bool bMovingRight = false;
	bool bMovingDown = false;
	bool bMovingLeft = false;
	bool bAttacking = false;

	cObject *GetPlayer( )
	{
		return ObjectManager.GetObjectByIndex( 1 );
	}
	void CreateObjectList( )
	{
		//create static objects - modify after adding EntityList
		ObjectManager.Add( 1, { 10.0f, 10.0f }, 0.0f, "PLAYER" );
		ObjectManager.Add( 2, { 250.0f, 250.0f }, 0.0f, "NPC_ENEMY" );
		ObjectManager.Add( 3, { 650.0f, 650.0f }, 0.0f, "NPC_ENEMY_BOSS" );
	}
	void ShootBullet( Vector2D vecStartPosition, float fInputAngle )
	{
		ObjectManager.Add( 4, vecStartPosition, fInputAngle, "BULLET" );
	}
	void DrawObjectsList( )
	{
		RenderManager.DrawCircle( 250, 250, 30, COL_RED );
		if ( !ObjectManager.GetObjectListSize( ) )
			return;

		for ( cObject *object : ObjectManager.GetObjectsList( ) )
		{
			if ( !object )
				continue;

			if ( !object->fSize
				|| !object->fHealth )
				continue;

			switch ( object->iItemId )
			{
				//characters
				case 1:
				case 2:
				case 3:
				{
					RenderManager.DrawRect( object->vPosition.x, object->vPosition.y, object->fSize, object->fSize, COL_RED );
					RenderManager.DrawString( object->vPosition.x, object->vPosition.y - 15, object->GetTag( ), COL_BLUE );
					break;
				}

				//bullets
				case 4:
				{
					RenderManager.DrawCircle( object->vPosition.x, object->vPosition.y, object->fSize, COL_GREEN );
					break;
				}
				default:
					continue;
			}
		}
	}
	void RunPlayerControls( )
	{

	}
	void RunInputManager( )
	{
		//basic controls
		if ( GetAsyncKeyState( VK_UP ) )
			bMovingUp = true;
		if ( GetAsyncKeyState( VK_RIGHT ) )
			bMovingRight = true;
		if ( GetAsyncKeyState( VK_DOWN ) )
			bMovingDown = true;
		if ( GetAsyncKeyState( VK_LEFT ) )
			bMovingLeft = true;
		if ( GetAsyncKeyState( VK_RETURN ) )
			bAttacking = true;
	}
}
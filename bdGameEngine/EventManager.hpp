#pragma once
#include "Include.hpp"

class cEvent
{
	bool bTimedEvent = false;
	float fTime = 0.0f;
public:

};

class cEventLog
{
	std::vector<std::string> vecLog { };
public:

};

//jesus christ dude what is wrong with you
void RunCollisionCheck( )
{
	if ( !Game::Player
		|| !ObjectManager.GetObjectListSize( ) )
		return;

	std::vector<cObject *> vecCurrentObjects = ObjectManager.GetObjectsList( );
	for ( cObject *obj : vecCurrentObjects )
	{
		if ( !obj )
			continue;
		if ( !obj->GetHealth( )
			|| !obj->fSize
			|| (!obj->vPosition.x && !obj->vPosition.y)
			)
			continue;

		bool bIsLocalPlayer = (obj == Game::Player);

		for ( cObject *objTwo : vecCurrentObjects )
		{
			if ( !objTwo )
				continue;
			if ( objTwo == obj )
				continue;
			if ( !objTwo->GetHealth( )
				|| !objTwo->fSize
				|| (!objTwo->vPosition.x && !objTwo->vPosition.y)
				)
				continue;

			if ( objTwo->CheckCollider( obj ) )
			{
				printf( "Entity: %s is colliding with entity: %s\n", objTwo->GetTag( ).c_str( ), obj->GetTag( ).c_str( ) );
			}
		}
	}
}
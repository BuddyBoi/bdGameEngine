#pragma once
#include "Include.hpp"

namespace Game
{
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

			RenderManager.DrawString( object->vPosition.x, object->vPosition.y - 15, std::to_string(object->GetHealth() ), COL_BLUE );
			RenderManager.DrawRect( object->vPosition.x, object->vPosition.y, object->fSize, object->fSize, COL_RED );
			printf( "DRAWN %i\n", i );
		}
	}
}
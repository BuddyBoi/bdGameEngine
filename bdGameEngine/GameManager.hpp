#pragma once 
#include "Include.hpp"

class Sprite
{
public:
	Vector2D vPosition { };
	Vector2D vSize { };

	Sprite( float fX, float fY, float fW, float fH ) : vPosition { fX, fY }, vSize( fW, fH ) //def pos and size
	{ }
	Sprite( float fX, float fY, float fSize ) : vPosition { fX, fY }, vSize( fSize, fSize ) //def pos with equal size
	{ }
	Sprite( )
	{ }
};

//ObjectList
enum E_OBJECT_TYPE
{
	OTYPE_INVALID = 0,
	OTYPE_ENTITY = 1, //Players, Characters, Items, Etc
	OTYPE_STATIC = 2, //Walls, Blockades, Boundaries, Terrain, Decorations, Etc
	OTYPE_MAX = 3,
};

//EntityList
enum E_ENTITY_TYPE
{
	ETYPE_INVALID = 0,
	ETYPE_PLAYER = 1,
	ETYPE_CHARACTER = 2,
	ETYPE_ITEM = 3,
	ETYPE_CONTAINER = 4,
	ETYPE_MAX = 5,
};

class cObject
{
public:
	int iIndex = 0; //specific reference id		
	int iItemId = 0; //item type
	Vector2D vPosition { 0.0f, 0.0f };
	float fAngle = 0.0f; //UP = 0, RIGHT = 90, DOWN = 180, LEFT = 270
	float fSize = 25.0f;
	std::string sTag = "NONE";

	//temp player vars
	float fHealth = 100.0f;
	float fDamage = 25.0f;	
	void MoveRel( float x, float y )
	{
		vPosition.x = vPosition.x + x;
		vPosition.y = vPosition.y + y;
	}
	void MoveAbs( float x, float y )
	{
		vPosition.x = x;
		vPosition.y = y;
	}
	void RunAttack( cObject *enemy )
	{
		if ( !enemy )
			return;

		enemy->fHealth -= this->fDamage;		
	}
	bool CheckCollider( cObject *oTarget )
	{
		if ( !oTarget )
			return false;

		return Util::bIsRectColliding( { vPosition.x, vPosition.y, fSize, fSize }, { oTarget->vPosition.x, oTarget->vPosition.y, oTarget->fSize, oTarget->fSize } );
	}
	std::string GetTag( )
	{
		return this->sTag;
	}
	float GetHealth( )
	{
		return this->fHealth;
	}
	cObject( int index, int item, Vector2D pos, std::string tag = "NONE" ) : iIndex( index ), iItemId( item ), vPosition( pos ), sTag( tag )
	{ }
	cObject( int index, int item, Vector2D pos, float angle, std::string tag = "NONE" ) : iIndex( index ), iItemId( item ), vPosition( pos ), fAngle( angle ), sTag( tag )
	{ }
	cObject( )
	{ }
};

class cObjectManager
{
	int iLock = 0;
	std::vector<cObject> vecObjects { };
public:
	cObjectManager( int lock )
	{
		iLock = lock;
	}
	int GetObjectListSize( )
	{
		return vecObjects.size( );
	}
	std::vector<cObject *> GetObjectsList( int iFilter = 0 )
	{
		std::vector<cObject *> vecReturn { };
		if ( !vecObjects.size( ) )
			return vecReturn;

		for ( int i = 0; i != vecObjects.size( ); i++ )
		{
			cObject *curObject = reinterpret_cast<cObject *>(&vecObjects[i]);
			if ( !curObject )
				continue;

			if ( iFilter )
			{
				if ( curObject->iItemId != iFilter )
					continue;
			}

			vecReturn.push_back( curObject );
		}

		return vecReturn;
	}
	bool Add( int item, Vector2D pos, float angle, std::string tag )
	{
		cObject obj( vecObjects.size( ) + 1, item, pos, angle, tag );
		vecObjects.push_back( obj );
		return true;
	}
	void DbgPrintObjects( )
	{
		for ( cObject x : vecObjects )
		{
			printf( "Object: ID:%i, ITEM:%i, POS_X:%f, POS_Y:%f, TAG:%s\n", x.iIndex, x.iItemId, x.vPosition.x, x.vPosition.y, x.sTag.c_str( ) );
		}
	}
	cObject *GetObjectByTag( std::string sTag )
	{
		for ( int i = 0; i != vecObjects.size( ); i++ )
		{
			if( vecObjects[i].GetTag() == sTag )
				return reinterpret_cast<cObject *>(&vecObjects[i]);
		}
	}
	cObject *GetObjectByIndex( int iIndex )
	{
		return reinterpret_cast<cObject *>(&vecObjects[iIndex - 1]);
	}
	cObject *GetObjectNearest( cObject *oTarget, int iFilterType = 0 )
	{
		/* iFilterType:
		0 = None
		1 = Characters
		2 = Static objects (Walls, Terrain, Blockades, Etc)
		3 = Items
		*/

		if ( !GetObjectListSize( ) )
			return nullptr;

		cObject *oNearest = nullptr;
		float fDistance = 1000.0f;

		for ( int i = 0; i != vecObjects.size( ); i++ )
		{
			cObject *curObject = reinterpret_cast<cObject *>(&vecObjects[i]);
			if ( !curObject )
				continue;

			if ( curObject->iItemId == 4 )
				continue;

			if ( curObject->iIndex == oTarget->iIndex
				|| !curObject->fSize
				|| !curObject->fHealth )
				continue;

			if ( float fDist = oTarget->vPosition.Distance( curObject->vPosition ) )
			{
				if ( fDist < fDistance )
				{
					//printf( "DISTANCE_CHECK - INDEX: %i - DISTANCE: %f\n", i, fDist );
					fDistance = fDist;
					oNearest = curObject;
				}
			}
		}

		if ( fDistance == 1000.0f )
			return 0;

		return oNearest;
	}
};
static cObjectManager ObjectManager( 1 );
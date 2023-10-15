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

class cObject
{
public:
	int iIndex = 0; //specific reference id		
	int iItemId = 0; //item type
	Vector2D vPosition { 0.0f, 0.0f };
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

		const float fDelay = 50.0f;
		static float fLastAttack = 0.0f;

		if ( Globals::fTick < (fLastAttack + fDelay) )
		{
			printf( "ATTACK AWAIT DELAY\n" );
			return;
		}

		//set attack
		enemy->fHealth -= this->fDamage;
		fLastAttack = Globals::fTick;
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
	std::vector<cObject *> GetObjectsList( )
	{
		std::vector<cObject *> vecReturn { };
		if ( !vecObjects.size( ) )
			return vecReturn;

		for ( int i = 0; i != vecObjects.size( ); i++ )
		{
			cObject *curObject = reinterpret_cast<cObject *>(&vecObjects[i]);
			if ( !curObject )
				continue;

			vecReturn.push_back( curObject );
		}

		return vecReturn;
	}
	bool Add( int item, Vector2D pos, std::string tag = "NONE" )
	{
		cObject obj( vecObjects.size( ) + 1, item, pos, tag );
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
		for ( cObject x : vecObjects )
		{
			if ( x.sTag == sTag )
				return reinterpret_cast<cObject *>(&x);
		}
	}
	cObject *GetObjectByIndex( int iIndex )
	{
		return reinterpret_cast<cObject *>(&vecObjects[iIndex - 1]);
	}
	cObject *GetObjectNearest( cObject *oTarget )
	{
		if ( !GetObjectListSize( ) )
			return nullptr;

		cObject *oNearest = nullptr;
		float fDistance = 1000.0f;

		for ( int i = 0; i != vecObjects.size( ); i++ )
		{
			cObject *curObject = reinterpret_cast<cObject *>(&vecObjects[i]);
			if ( !curObject )
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
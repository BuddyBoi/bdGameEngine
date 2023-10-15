#pragma once
#define _CRT_SECURE_NO_WARNINGS
#define _USE_MATH_DEFINES
#define CUSTOMFVF (D3DFVF_XYZRHW | D3DFVF_DIFFUSE)

#include <d3d9.h>
#include <d3dx9.h>
#include <Windows.h>
#include <Psapi.h>
#include <stdio.h>

#include <iostream>
#include <thread>
#include <string>
#include <vector>
#include <cmath>
#include <vector>
#include <map>

#pragma comment(lib,"d3d9.lib")
#pragma comment(lib,"d3dx9.lib")
#pragma comment(lib, "dwmapi.lib")

static DWORD COL_WHITE = D3DCOLOR_XRGB( 255, 255, 255 );
static DWORD COL_RED = D3DCOLOR_XRGB( 255, 0, 0 );
static DWORD COL_GREEN = D3DCOLOR_XRGB( 0, 255, 0 );
static DWORD COL_BLUE = D3DCOLOR_XRGB( 0, 0, 255 );
static DWORD COL_BLACK = D3DCOLOR_XRGB( 0, 0, 0 );

struct CUSTOMVERTEX
{
	FLOAT x, y, z, rhw;    // from the D3DFVF_XYZRHW flag
	DWORD color;          // from the D3DFVF_DIFFUSE flag
};

class Vector2D
{
public:
	float x = 0.0f;
	float y = 0.0f;
	float Distance( const Vector2D &other ) const
	{
		float dx = x - other.x;
		float dy = y - other.y;
		return std::sqrt( dx * dx + dy * dy );
	}
	Vector2D( float fX, float fY ) : x( fX ), y( fY )
	{ }
	Vector2D( )
	{ }
};

struct Rect
{
	float x;
	float y;
	float width;
	float height;
};

#include "Globals.hpp"
#include "Util.hpp"
#include "ThreadManager.hpp"
#include "Renderer.hpp"
#include "GameManager.hpp"
#include "Threads.hpp"
#pragma once
#include "Include.hpp"

LRESULT CALLBACK wndCallback( HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam )
{
	PAINTSTRUCT ps { };
	HDC hdc { };
	switch ( message )
	{
		case WM_SETFOCUS:
			printf( "WM_SETFOCUS\n" );
			break;

		case WM_PAINT:
			printf( "WM_PAINT\n" );
			break;

		case WM_DESTROY:
			printf( "WM_DESTROY\n" );
			break;

			PostQuitMessage( 0 );
			return 0;
	}

	return DefWindowProc( hWnd, message, wParam, lParam );
}

class cRenderer
{
	int iTag = 0;

	//window
	HWND hWindow = nullptr;
	std::string sWindowTitle = "Title";
	std::string sWindowClass = "Class";
	int iWindowX = 1280;
	int iWindowY = 720;

	LPDIRECT3DVERTEXBUFFER9 dVertexBuffer = NULL;
	IDirect3D9Ex *dObject = nullptr;
	IDirect3DDevice9 *dDevice = nullptr;
	D3DPRESENT_PARAMETERS dParams = { };
	ID3DXFont *pFont = NULL;

	bool bCreateWindow( )
	{
		static WNDCLASSEXA wclassWindow { };
		static HINSTANCE wiWindow { };

		// Register window class
		wclassWindow.cbSize = sizeof( WNDCLASSEX );
		wclassWindow.style = 0;
		wclassWindow.lpfnWndProc = wndCallback;
		wclassWindow.cbClsExtra = 0;
		wclassWindow.cbWndExtra = 0;
		wclassWindow.hInstance = wiWindow;
		wclassWindow.hIcon = LoadIcon( NULL, IDI_APPLICATION );
		wclassWindow.hCursor = LoadCursor( NULL, IDC_ARROW );
		wclassWindow.hbrBackground = (HBRUSH) GetStockObject( WHITE_BRUSH );
		wclassWindow.lpszMenuName = NULL;
		wclassWindow.lpszClassName = (LPCSTR) sWindowClass.c_str( );
		wclassWindow.hIconSm = LoadIcon( NULL, IDI_APPLICATION );
		RegisterClassExA( &wclassWindow );

		// Create window
		hWindow = CreateWindowExA(
			0,
			(LPCSTR) sWindowClass.c_str( ),
			(LPCSTR) sWindowTitle.c_str( ),
			WS_OVERLAPPEDWINDOW,
			1,
			1,
			iWindowX,
			iWindowY,
			NULL,
			NULL,
			wiWindow,
			NULL );

		if ( !hWindow )
		{
			printf( "Error - bCreateWindow - Failed to CreateWindowExA\n" );
			return false;
		}

		ShowWindow( hWindow, SW_SHOWDEFAULT );
		UpdateWindow( hWindow );
		return true;
	}
	bool bUninitD3D()
	{
		if ( pFont )
		{
			pFont->Release( );
			pFont = NULL;
		}

		dDevice->Release( );
		dObject->Release( );
		return true;
	}
	bool bInitD3D()
	{
		HRESULT hrDirectD3Create = Direct3DCreate9Ex( D3D_SDK_VERSION, &dObject );
		ZeroMemory( &dParams, sizeof( dParams ) );
		dParams.BackBufferWidth = iWindowX;
		dParams.BackBufferHeight = iWindowY;
		dParams.BackBufferFormat = D3DFMT_A8R8G8B8;
		dParams.MultiSampleQuality = D3DMULTISAMPLE_NONE;
		dParams.AutoDepthStencilFormat = D3DFMT_D16;
		dParams.SwapEffect = D3DSWAPEFFECT_DISCARD;
		dParams.EnableAutoDepthStencil = TRUE;
		dParams.hDeviceWindow = hWindow;
		dParams.FullScreen_RefreshRateInHz = 0;
		dParams.Windowed = TRUE;

		if ( !dObject )
		{
			printf( "Error - bInitD3D - Failed to init d3d\n" );
			return false;
		}

		HRESULT hrCreateDevice = dObject->CreateDevice( D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, hWindow, D3DCREATE_SOFTWARE_VERTEXPROCESSING, &dParams, &dDevice );
		if ( !dDevice )
		{
			printf( "Error - Failed to create device\n" );
			return false;
		}

		HRESULT hrCreateFontA = D3DXCreateFontA( dDevice, 12, 0, FW_NORMAL, 1, false, DEFAULT_CHARSET, OUT_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH | FF_DONTCARE, "Arial", &pFont );
		if ( !pFont )
		{
			printf( "Error - Failed to create font\n" );
			return false;
		}

		return true;
	}
	bool bSetWindowFlags( )
	{
		return true;
	}
	bool bUpdateWindowFlags( )
	{
		SetWindowLong( hWindow, GWL_EXSTYLE, WS_EX_LAYERED | WS_EX_TRANSPARENT | WS_EX_TOOLWINDOW );
		UpdateWindow( hWindow );
		return true;
	}
public:
	cRenderer( int tag )
	{
		iTag = tag;
	}
	HWND GetHandle( )
	{
		return this->hWindow;
	}
	void DrawRectFilled( float x, float y, float width, float height, DWORD color )
	{
		CUSTOMVERTEX vertices[] =
		{
			{ x, y, 0.0f, 1.0f, color },
			{ x + width, y, 0.0f, 1.0f, color },
			{ x, y + height, 0.0f, 1.0f, color },
			{ x + width, y + height, 0.0f, 1.0f, color }
		};

		dDevice->SetFVF( CUSTOMFVF );
		dDevice->DrawPrimitiveUP( D3DPT_TRIANGLESTRIP, 2, vertices, sizeof( CUSTOMVERTEX ) );
	}
	void DrawRect( float x, float y, float width, float height, DWORD color )
	{
		CUSTOMVERTEX vertices[] =
		{
			{ x, y, 0.0f, 1.0f, color },
			{ x + width, y, 0.0f, 1.0f, color },
			{ x + width, y + height, 0.0f, 1.0f, color },
			{ x, y + height, 0.0f, 1.0f, color },
			{ x, y, 0.0f, 1.0f, color } // Close the loop
		};

		dDevice->SetFVF( CUSTOMFVF );
		dDevice->DrawPrimitiveUP( D3DPT_LINESTRIP, 4, vertices, sizeof( CUSTOMVERTEX ) );
	}
	void DrawLine( float x1, float y1, float x2, float y2, DWORD color )
	{
		CUSTOMVERTEX vertices[] =
		{
			{ x1, y1, 0.0f, 1.0f, color },
			{ x2, y2, 0.0f, 1.0f, color }
		};

		dDevice->SetFVF( CUSTOMFVF );
		dDevice->DrawPrimitiveUP( D3DPT_LINELIST, 1, vertices, sizeof( CUSTOMVERTEX ) );
	}
	void DrawCircle( float xCenter, float yCenter, float radius, DWORD color, int segments = 36 )
	{
		CUSTOMVERTEX *vertices = new CUSTOMVERTEX[segments + 1];

		float anglePerSegment = (2.0f * 3.1415) / static_cast<float>(segments);
		for ( int i = 0; i < segments; ++i )
		{
			float x = xCenter + radius * cosf( i * anglePerSegment );
			float y = yCenter + radius * sinf( i * anglePerSegment );
			vertices[i] = { x, y, 0.0f, 1.0f, color };
		}
		vertices[segments] = vertices[0];

		dDevice->SetFVF( CUSTOMFVF );
		dDevice->DrawPrimitiveUP( D3DPT_LINESTRIP, segments, vertices, sizeof( CUSTOMVERTEX ) );

		delete[] vertices;
	}
	void DrawString( int x, int y, const std::string &text, DWORD color )
	{
		RECT rect;
		SetRect( &rect, x, y, 0, 0 );
		pFont->DrawTextA( NULL, text.c_str( ), -1, &rect, DT_NOCLIP, color );
	}
	bool BeginScene( )
	{
		//if ( !bUpdateWindowFlags( ) )
			//return false;

		dDevice->Clear( 0, NULL, D3DCLEAR_TARGET, D3DCOLOR_XRGB( 255, 255, 255 ), 0.0f, 0 );
		dDevice->BeginScene( );
		return true;
	}
	bool EndScene( )
	{
		dDevice->EndScene( );
		dDevice->Present( NULL, NULL, NULL, NULL );
		return true;
	}
	bool Uninitialize( )
	{
		this->EndScene( );
		return this->bUninitD3D( );
	}
	bool Initialize( )
	{
		if ( !this->bCreateWindow( ) )
		{
			printf( "ERROR - FAILED TO CREATE WINDOW\n" );
			return false;
		}

		if ( !this->bInitD3D( ) )
		{
			printf( "ERROR - FAILED TO CREATE D3 OBJECT\n" );
			return false;
		}

		return true;
	}
};
cRenderer RenderManager( 1 );
#include "DirectXinitializer.h"

//#define _CRTDBG_MAP_ALLOC
//#include <cstdlib>
//#include <crtdbg.h>
//#define new new( _NORMAL_BLOCK, __FILE__, __LINE__) //this lets me double-click a memory leak to take me to the line it occured
//_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
//_CrtSetBreakAlloc(-1L);
DxInit MrDx;

int WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPTSTR lpCmdLine,	int nCmdShow );						   
LRESULT CALLBACK WndProc(HWND hWnd,	UINT message, WPARAM wparam, LPARAM lparam );		
int WINAPI wWinMain( HINSTANCE hInstance, HINSTANCE, LPTSTR, int )
{
	srand(unsigned int(time(0)));

	MrDx.CreateMyWindow(hInstance, (WNDPROC)WndProc);
	MrDx.Initalize();

    MSG msg; ZeroMemory( &msg, sizeof( msg ) );

	while (msg.message != WM_QUIT && MrDx.Run())
    {	
	    if ( PeekMessage( &msg, NULL, 0, 0, PM_REMOVE ) )
        { 
            TranslateMessage( &msg );
            DispatchMessage( &msg ); 
        }
    }

	MrDx.Release();
	return 0; 
}
LRESULT CALLBACK WndProc( HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam )
{
    if(GetAsyncKeyState(VK_ESCAPE))
		message = WM_DESTROY;
    switch ( message )
    {
        case ( WM_DESTROY ): { PostQuitMessage( 0 ); }
        break;
		case (WM_SIZE):
		{
			MrDx.Resize();
		}
		 break;
		case (WM_KEYDOWN) :
		{
			if (wParam == VK_TAB)
			{
				MrDx.Is_FullScreen = true;
				MrDx.Resize();
			}
		}
		break;
    }
    return DefWindowProc( hWnd, message, wParam, lParam );
}

#include "DirectXinitializer.h"


int WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPTSTR lpCmdLine,	int nCmdShow );						   
LRESULT CALLBACK WndProc(HWND hWnd,	UINT message, WPARAM wparam, LPARAM lparam );		
int WINAPI wWinMain( HINSTANCE hInstance, HINSTANCE, LPTSTR, int )
{
	srand(unsigned int(time(0)));
	DxInit MrDx;

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
		case (WM_SIZE) :
		{

		}
		break;
    }
    return DefWindowProc( hWnd, message, wParam, lParam );
}

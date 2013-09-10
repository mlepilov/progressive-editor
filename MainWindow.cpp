//Workspace: Progressive Editor
//File Name: MainWindow.cpp
#include <windows.h>
#include "cWin32Wrapper.h"
#include "cMainWindow.h"
#include "resource.h"
//---------------------------------------------------------------------------
INT WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nShowCmd)
{
	MSG Msg;

	RECT dimensions;
	dimensions.top		= 0;
	dimensions.left		= 0;
	dimensions.bottom	= 300;
	dimensions.right	= 600;

	MainWindow *mWindow = new MainWindow(NULL, "PROGEDIT", "Progressive Editor", WS_VISIBLE | WS_OVERLAPPED | WS_SYSMENU | WS_CAPTION | WS_MINIMIZEBOX, &dimensions, (HMENU)MAKEINTRESOURCE(IDR_MAINMENU), hInstance);
	mWindow->Create();
	mWindow->Show();
	mWindow->BuildGUI();

	while(GetMessage(&Msg, NULL, 0, 0))
	{
		TranslateMessage(&Msg);
		DispatchMessage(&Msg);
	}

	return 0;
}
//---------------------------------------------------------------------------
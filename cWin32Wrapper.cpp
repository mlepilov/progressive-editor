//Workspace: GUI Trigger Editor
//File Name: cWin32Wrapper.cpp
#include "cWin32Wrapper.h"
//---------------------------------------------------------------------------
// Static Win32WrapperClass message loop
LRESULT CALLBACK Win32WrapperClass::stWinProc (HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {
// This does two things:
// 1.) If the window is being created, it calls SetWindowLong on the window to store the 
// pointer to the window.
// 2.) Otherwise, it gets the pointer to the window and calls that instance's WinProc
	Win32WrapperClass* pWnd;

	if (uMsg == WM_NCCREATE) {
		// Set the pointer
		SetWindowLong(hWnd, GWL_USERDATA, (long)((LPCREATESTRUCT(lParam))->lpCreateParams));
	}

	// Get the pointer
	pWnd = (Win32WrapperClass *)GetWindowLong(hWnd, GWL_USERDATA);

	// If we got it, call the windows message handler, otherwise call the default
	if (pWnd)	return pWnd->WinProc(hWnd, uMsg, wParam, lParam);
	else		return DefWindowProc(hWnd, uMsg, wParam, lParam);
}
//---------------------------------------------------------------------------
BOOL Win32WrapperClass::Create() {
	WNDCLASSEX WndCls;
	WndCls.cbSize        = sizeof(WNDCLASSEX);
	WndCls.style         = 0;
	WndCls.lpfnWndProc   = stWinProc;
	WndCls.cbClsExtra    = 0;
	WndCls.cbWndExtra    = 0;
	WndCls.hIcon         = LoadIcon(NULL, IDI_APPLICATION);
	WndCls.hCursor       = LoadCursor(NULL, IDC_ARROW);
	WndCls.hbrBackground = (HBRUSH)(COLOR_BACKGROUND);
	WndCls.lpszMenuName  = (LPSTR)m_pMenuName;
	WndCls.lpszClassName = m_pClassName;
	WndCls.hInstance     = m_hInstance;
	WndCls.hIconSm       = LoadIcon(NULL, IDI_APPLICATION);

	RegisterClassEx(&WndCls);

	// Send the this pointer as the window creation parameter
	m_hWnd = CreateWindowEx(m_dwExStyles,
							m_pClassName,m_pWindowTitle,
							m_dwStyles,
							m_pRect->left,
							m_pRect->top,
							m_pRect->right-m_pRect->left,
							m_pRect->bottom-m_pRect->top,
							NULL,NULL,
							m_hInstance,
							(void *)this);
	return (m_hWnd != NULL);
}
//---------------------------------------------------------------------------
BOOL Win32WrapperClass::Show() {
	ShowWindow(m_hWnd,SW_SHOW);
	UpdateWindow(m_hWnd);

	return true;
}
//---------------------------------------------------------------------------
Win32WrapperClass::Win32WrapperClass()
{
}
//---------------------------------------------------------------------------
Win32WrapperClass::Win32WrapperClass(DWORD dwExStyles, char *ClassName, char *WindowTitle, DWORD dwStyles, RECT *rect, HINSTANCE hInstance) {
	m_pClassName	= ClassName;
	m_pWindowTitle	= WindowTitle;
	m_pRect			= rect;
	m_hInstance		= hInstance;
	m_dwStyles		= dwStyles;
	m_dwExStyles	= dwExStyles;

	RECT desktopRect;
	GetWindowRect(GetDesktopWindow(),&desktopRect);

	int wWidth	=	m_pRect->right	-	m_pRect->left;
	int wHeight	=	m_pRect->bottom	-	m_pRect->top;

	m_pRect->left	=	((desktopRect.right		-	desktopRect.left)	-	wWidth)		/2;
	m_pRect->right	=	((desktopRect.right		-	desktopRect.left)	+	wWidth)		/2;
	m_pRect->top	=	((desktopRect.bottom	-	desktopRect.top)	-	wHeight)	/2;
	m_pRect->bottom	=	((desktopRect.bottom	-	desktopRect.top)	+	wHeight)	/2;
}
//---------------------------------------------------------------------------
Win32WrapperClass::~Win32WrapperClass () {
	// Destroy the render window
    if(m_hWnd) DestroyWindow(m_hWnd);
    m_hWnd = NULL;
}
//---------------------------------------------------------------------------
// Unique Win32WrapperClass message loop
LRESULT CALLBACK Win32WrapperClass::WinProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {
	switch(uMsg)
    {
		case WM_DESTROY:
			PostQuitMessage(NULL);
			break;

		default:
			return DefWindowProc(hWnd, uMsg, wParam, lParam);
    }

    return 0;
}
//---------------------------------------------------------------------------
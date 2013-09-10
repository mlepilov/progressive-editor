//Workspace: Progressive Editor
//File Name: cWin32Wrapper.h
#ifndef _CWIN32WRAPPER_H_
#define _CWIN32WRAPPER_H_

#include <windows.h>
//---------------------------------------------------------------------------
class Win32WrapperClass
{
public:
	Win32WrapperClass();
	Win32WrapperClass(DWORD dwExStyles, char *ClassName, char *WindowTitle, DWORD dwStyles, RECT *rect, HINSTANCE hInstance);
	virtual ~Win32WrapperClass();

	BOOL Create();
	BOOL Show();
	
	static LRESULT CALLBACK stWinProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
	virtual LRESULT CALLBACK WinProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

protected:
	HWND					m_hWnd;
	HINSTANCE				m_hInstance;
	HMENU					m_pMenuName;

	DWORD					m_dwStyles;
	DWORD					m_dwExStyles;
	RECT					*m_pRect;
	char					*m_pClassName;
	char					*m_pWindowTitle;
};
//---------------------------------------------------------------------------
#endif //ifndef _CWIN32WRAPPER_H_
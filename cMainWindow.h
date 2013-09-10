//Workspace: Progressive Editor
//File Name: cMainWindow.h
#ifndef _CMAINWINDOW_H_
#define _CMAINWINDOW_H_

#include <windows.h>
#include "cWin32Wrapper.h"
#include "ClassMap.h"
#include "LocalFileFunctions.h"
#include "lib/lmpqapi/LMPQAPI.h"
//---------------------------------------------------------------------------
class MainWindow:public Win32WrapperClass {
public:
	MainWindow(DWORD dwExStyles, char *ClassName, char *WindowTitle, DWORD dwStyles, RECT *rect, HMENU MenuName, HINSTANCE hInstance);
	void BuildGUI();
	virtual ~MainWindow();

	void AnnexEditMessage(char* Message);

	LRESULT CALLBACK WinProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

protected:
	HWND m_hBtnDetect;
	HWND m_hBtnRepair;
	HWND m_hEditMain;
	HWND m_hLblProtection;
	HWND m_hBtnInflate;
	HWND m_hBtnSwitches;
	HWND m_hBtnLocations;
	HWND m_hBtnUnits;
	HWND m_hBtnComments;
	HWND m_hBtnISOM;
	HWND m_hBtnTILE;
	HFONT m_hDefFont;

	MapClass* Map;
	bool Opened;
	LOCALFILEDATA LocalFileData;
};
//---------------------------------------------------------------------------
#endif //ifndef _CMAINWINDOW_H_
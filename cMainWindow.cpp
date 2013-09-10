//Workspace: Progressive Editor
//File Name: cMainWindow.cpp
#include "cMainWindow.h"
#include "ClassMap.h"
#include "resource.h"
#include "LocalFileFunctions.h"
//---------------------------------------------------------------------------
MainWindow::MainWindow(DWORD dwExStyles, char* ClassName, char* WindowTitle,
					   DWORD dwStyles, RECT *rect, HMENU MenuName, HINSTANCE hInstance) {
	m_pClassName	= ClassName;
	m_pWindowTitle	= WindowTitle;
	m_pRect			= rect;
	m_hInstance		= hInstance;
	m_dwStyles		= dwStyles;
	m_dwExStyles	= dwExStyles;
	m_pMenuName		= MenuName;

	RECT desktopRect;
	GetWindowRect(GetDesktopWindow(),&desktopRect);

	int wWidth	=	m_pRect->right	-	m_pRect->left;
	int wHeight	=	m_pRect->bottom	-	m_pRect->top;

	m_pRect->left	=	((desktopRect.right		-	desktopRect.left)	-	wWidth)		/2;
	m_pRect->right	=	((desktopRect.right		-	desktopRect.left)	+	wWidth)		/2;
	m_pRect->top	=	((desktopRect.bottom	-	desktopRect.top)	-	wHeight)	/2;
	m_pRect->bottom	=	((desktopRect.bottom	-	desktopRect.top)	+	wHeight)	/2;

	m_hDefFont = (HFONT)GetStockObject(DEFAULT_GUI_FONT);
}
//---------------------------------------------------------------------------
void MainWindow::BuildGUI()
{
	// Creating the "Detect" and "Repair" buttons
	m_hBtnDetect = CreateWindow("BUTTON", "Detect", WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON,
		20, 10, 100, 25, m_hWnd, (HMENU)IDB_DETECT, m_hInstance, NULL);
	SendMessage(m_hBtnDetect, WM_SETFONT, (WPARAM)m_hDefFont, NULL);
	m_hBtnRepair = CreateWindow("BUTTON", "Repair", WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON,
		20, 40, 100, 25, m_hWnd, (HMENU)IDB_REPAIR, m_hInstance, NULL);
	SendMessage(m_hBtnRepair, WM_SETFONT, (WPARAM)m_hDefFont, NULL);

	// Creating the main edit box
	m_hEditMain = CreateWindowEx(WS_EX_CLIENTEDGE, "EDIT", "", WS_VISIBLE | WS_CHILD | WS_VSCROLL | ES_MULTILINE | ES_READONLY,
		130, 10, 280, 220, m_hWnd, (HMENU)IDE_MAIN, m_hInstance, NULL);
	SendMessage(m_hEditMain, WM_SETFONT, (WPARAM)m_hDefFont, NULL);

	// Creating the protection static box
	m_hLblProtection = CreateWindowEx(WS_EX_CLIENTEDGE, "STATIC", "-Map Not Opened-", WS_VISIBLE | WS_CHILD,
		420, 10, 120, 20, m_hWnd, (HMENU)IDS_PROT, m_hInstance, NULL);
	SendMessage(m_hLblProtection, WM_SETFONT, (WPARAM)m_hDefFont, NULL);

	// Creating the "Inflate Strings", "Use Old Switches", "Use Old Locations", and
	// "Use Old Units" checkboxes
	m_hBtnInflate = CreateWindow("BUTTON", "Inflate Strings", WS_VISIBLE | WS_CHILD | BS_AUTOCHECKBOX,
		420, 40, 150, 25, m_hWnd, (HMENU)IDB_1024S, m_hInstance, NULL);
	SendMessage(m_hBtnInflate, WM_SETFONT, (WPARAM)m_hDefFont, NULL);
	m_hBtnSwitches = CreateWindow("BUTTON", "Use Old Switch Names", WS_VISIBLE | WS_CHILD | BS_AUTOCHECKBOX,
		420, 65, 150, 25, m_hWnd, (HMENU)IDB_OLDSWI, m_hInstance, NULL);
	SendMessage(m_hBtnSwitches, WM_SETFONT, (WPARAM)m_hDefFont, NULL);
	m_hBtnLocations = CreateWindow("BUTTON", "Use Old Location Names", WS_VISIBLE | WS_CHILD | BS_AUTOCHECKBOX,
		420, 90, 150, 25, m_hWnd, (HMENU)IDB_OLDLOC, m_hInstance, NULL);
	SendMessage(m_hBtnLocations, WM_SETFONT, (WPARAM)m_hDefFont, NULL);
	m_hBtnUnits = CreateWindow("BUTTON", "Use Old Unit Names", WS_VISIBLE | WS_CHILD | BS_AUTOCHECKBOX,
		420, 115, 150, 25, m_hWnd, (HMENU)IDB_OLDUNI, m_hInstance, NULL);
	SendMessage(m_hBtnUnits, WM_SETFONT, (WPARAM)m_hDefFont, NULL);
	m_hBtnComments = CreateWindow("BUTTON", "Delete Comments", WS_VISIBLE | WS_CHILD | BS_AUTOCHECKBOX,
		420, 140, 150, 25, m_hWnd, (HMENU)IDB_COMMENTS, m_hInstance, NULL);
	SendMessage(m_hBtnComments, WM_SETFONT, (WPARAM)m_hDefFont, NULL);
	m_hBtnISOM = CreateWindow("BUTTON", "Use Old ISOM", WS_VISIBLE | WS_CHILD | BS_AUTOCHECKBOX,
		420, 165, 150, 25, m_hWnd, (HMENU)IDB_ISOM, m_hInstance, NULL);
	SendMessage(m_hBtnISOM, WM_SETFONT, (WPARAM)m_hDefFont, NULL);
	m_hBtnTILE = CreateWindow("BUTTON", "Use Old TILE", WS_VISIBLE | WS_CHILD | BS_AUTOCHECKBOX,
		420, 190, 150, 25, m_hWnd, (HMENU)IDB_TILE, m_hInstance, NULL);
	SendMessage(m_hBtnTILE, WM_SETFONT, (WPARAM)m_hDefFont, NULL);

	// Disabling various controls on startup
	EnableWindow(m_hBtnDetect, FALSE);
	EnableWindow(m_hBtnRepair, FALSE);
	EnableWindow(m_hBtnInflate, FALSE);
	EnableWindow(m_hBtnSwitches, FALSE);
	EnableWindow(m_hBtnLocations, FALSE);
	EnableWindow(m_hBtnUnits, FALSE);
	EnableWindow(m_hBtnComments, FALSE);
	EnableWindow(m_hBtnISOM, FALSE);
	EnableWindow(m_hBtnTILE, FALSE);
}
//---------------------------------------------------------------------------
MainWindow::~MainWindow() {
	if ( m_hWnd ) DestroyWindow( m_hWnd );
	m_hWnd = NULL;
}
//---------------------------------------------------------------------------
void MainWindow::AnnexEditMessage(char* Message)
{
	int len = GetWindowTextLength(m_hEditMain);
	SendMessage(m_hEditMain, EM_SETSEL, (WPARAM)len, (LPARAM)len);
	SendMessage(m_hEditMain, EM_REPLACESEL, (WPARAM)FALSE, (LPARAM)Message);
}
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
LRESULT CALLBACK MainWindow::WinProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {
	switch(uMsg)
	{
		case WM_CREATE:
		{
			HMENU TempMenu = GetMenu(hWnd);
			EnableMenuItem(TempMenu, ID_FILE_SAVEMAP, MF_GRAYED);
			EnableMenuItem(TempMenu, ID_FILE_SAVEMAPAS, MF_GRAYED);
			EnableMenuItem(TempMenu, ID_FILE_CLOSEMAP, MF_GRAYED);
			Map = NULL;

			char Init = GetLocalFileData(&LocalFileData);
			if(Init == -1)
			{
				MessageBox(hWnd, "Error reading VCOD.bin. The program must now exit.", "Error",
					MB_ICONERROR);
				SendMessage(hWnd, WM_CLOSE, NULL, NULL);
			}

			if(!MpqInitialize())	// Has to be done to use lmpqapi
			{
				MessageBox(hWnd, "Error initializing lmpqapi. The program must now exit.\r\n\r\nMake sure that both Storm.dll and StarEdit.exe are in the directory.\r\nIf StarEdit is open, close it, and try again.",
					"Error", MB_ICONERROR);	// If MpqInitialize fails, stop the program from running
				SendMessage(hWnd, WM_CLOSE, NULL, NULL);
			}
			break;
		}

		case WM_COMMAND:
			switch(LOWORD(wParam))
			{
				case ID_FILE_OPENMAP:
				{
					char szFileName[MAX_PATH] = "";
					OPENFILENAME ofn;
					ZeroMemory(&ofn, sizeof(ofn));

					ofn.lStructSize = sizeof(ofn);
					ofn.hwndOwner = m_hWnd;
					ofn.lpstrFilter =
						"Compressed Scenario Files (*.scm, *.scx)\0*.scm;*.scx\0Raw Scenario Files (*.chk)\0*.chk\0\0";
					ofn.lpstrFile = szFileName;
					ofn.nMaxFile = MAX_PATH;
					ofn.lpstrDefExt = "chk";
					ofn.Flags = OFN_EXPLORER | OFN_FILEMUSTEXIST;
					if(GetOpenFileName(&ofn))
					{
						if(Map)
						{
							SendMessage(hWnd, WM_COMMAND, ID_FILE_CLOSEMAP, NULL);
						}

						Map = new MapClass(szFileName, &m_hEditMain, &LocalFileData);
						// If the DIM, VER, and STR sections are present...
						if(Map->Scan(Map->GetCurrentMap()))
						{
							Map->Read(Map->GetCurrentMap());

							HMENU TempMenu = GetMenu(hWnd);
							EnableMenuItem(TempMenu, ID_FILE_SAVEMAP, MF_ENABLED);
							EnableMenuItem(TempMenu, ID_FILE_SAVEMAPAS, MF_ENABLED);
							EnableMenuItem(TempMenu, ID_FILE_CLOSEMAP, MF_ENABLED);

							EnableWindow(m_hBtnDetect, TRUE);
			
							AnnexEditMessage("I/O: Opened Map.\r\n");
							char* TempString = (char*)malloc(22 + strlen(szFileName));
							strcpy(TempString, "Progressive Editor - ");
							strcat(TempString, szFileName);
							SetWindowText(hWnd, TempString);
							free(TempString);
						}
						// If they're not...
						else
						{
							SendMessage(hWnd, WM_COMMAND, ID_FILE_CLOSEMAP, NULL);
							AnnexEditMessage("I/O: Could not open map (DIM, STR, or VER not present).\r\n");
						}
					}
					break;
				}

				case ID_FILE_SAVEMAP:
				{
					// Saving
					Map->Save(NULL, NULL);

					// Displaying output in editbox
					char* MapPath = (char*)malloc(MAX_PATH);
					MapPath = Map->GetMapPath();
					int StrLen = strlen(MapPath);
					char* TempString = (char*)malloc(StrLen + 16);
					strcpy(TempString, "I/O: Saved Map: ");
					strcat(TempString, MapPath);
					StrLen = strlen(TempString);
					TempString = (char*)realloc(TempString, StrLen + 2);
					strcpy(TempString + StrLen, "\r\n\0");
					AnnexEditMessage(TempString);
					break;
				}

				case ID_FILE_SAVEMAPAS:
				{
					// Getting filename
					char szFileName[MAX_PATH] = "";
					OPENFILENAME ofn;
					ZeroMemory(&ofn, sizeof(ofn));

					ofn.lStructSize = sizeof(ofn);
					ofn.hwndOwner = m_hWnd;
					ofn.lpstrFilter =
						"Compressed StarCraft Map (*.scm)\0*.scm\0Compressed BroodWar Map (*.scx)\0*.scx\0Raw Scenario Files (*.chk)\0*.chk\0\0";
					ofn.lpstrFile = szFileName;
					ofn.nMaxFile = MAX_PATH;
					ofn.lpstrDefExt = "chk";
					ofn.Flags = OFN_EXPLORER | OFN_PATHMUSTEXIST | OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT;
					if(GetSaveFileName(&ofn))
						Map->Save(szFileName, ofn.nFilterIndex);	// Saving

					// Displaying output in editbox
					char* MapPath = (char*)malloc(MAX_PATH);
					MapPath = Map->GetMapPath();
					int StrLen = strlen(MapPath);
					char* TempString = (char*)malloc(StrLen + 16);
					strcpy(TempString, "I/O: Saved Map: ");
					strcat(TempString, MapPath);
					StrLen = strlen(TempString);
					TempString = (char*)realloc(TempString, StrLen + 2);
					strcpy(TempString + StrLen, "\r\n\0");
					AnnexEditMessage(TempString);

					// Updating the window main window caption
					TempString = (char*)realloc(TempString, 22 + strlen(MapPath));
					strcpy(TempString, "Progressive Editor - ");
					strcat(TempString, MapPath);
					SetWindowText(hWnd, TempString);
					break;
				}

				case ID_FILE_CLOSEMAP:
				{
					delete Map;
					Map = NULL;

					HMENU TempMenu = GetMenu(hWnd);
					EnableMenuItem(TempMenu, ID_FILE_SAVEMAP, MF_GRAYED);
					EnableMenuItem(TempMenu, ID_FILE_SAVEMAPAS, MF_GRAYED);
					EnableMenuItem(TempMenu, ID_FILE_CLOSEMAP, MF_GRAYED);

					EnableWindow(m_hBtnDetect, FALSE);
					EnableWindow(m_hBtnRepair, FALSE);

					EnableWindow(m_hBtnInflate, FALSE);
					EnableWindow(m_hBtnSwitches, FALSE);
					EnableWindow(m_hBtnLocations, FALSE);
					EnableWindow(m_hBtnUnits, FALSE);
					EnableWindow(m_hBtnComments, FALSE);
					EnableWindow(m_hBtnISOM, FALSE);
					EnableWindow(m_hBtnTILE, FALSE);

					SetWindowText(m_hLblProtection, "-Map Not Opened-");

					AnnexEditMessage("I/O: Closed Map.\r\n");
					SetWindowText(hWnd, "Progressive Editor");
					break;
				}

				case ID_FILE_EXIT:
					if(Opened)
						delete Map;
					PostQuitMessage(WM_QUIT);
					break;

				case IDB_DETECT:
					if(Map)
					{
						BYTE Checkboxes;
						Checkboxes = Map->Detect();

						EnableWindow(m_hBtnRepair, TRUE);
						EnableWindow(m_hBtnDetect, FALSE);

						EnableWindow(m_hBtnInflate, TRUE);
						EnableWindow(m_hBtnSwitches, TRUE);
						EnableWindow(m_hBtnLocations, TRUE);
						EnableWindow(m_hBtnUnits, TRUE);
						EnableWindow(m_hBtnComments, TRUE);
						EnableWindow(m_hBtnISOM, TRUE);
						EnableWindow(m_hBtnTILE, TRUE);

						if((Checkboxes & 0x01) > 0)
						{
							SendMessage(m_hBtnInflate, BM_SETCHECK, BST_UNCHECKED, NULL);
							EnableWindow(m_hBtnInflate, FALSE);
						}
						if((Checkboxes & 0x02) > 0)
						{
							SendMessage(m_hBtnSwitches, BM_SETCHECK, BST_UNCHECKED, NULL);
							EnableWindow(m_hBtnSwitches, FALSE);
						}
						if((Checkboxes & 0x04) > 0)
						{
							SendMessage(m_hBtnComments, BM_SETCHECK, BST_UNCHECKED, NULL);
							EnableWindow(m_hBtnComments, FALSE);
						}
						if((Checkboxes & 0x08) > 0)
						{
							SendMessage(m_hBtnISOM, BM_SETCHECK, BST_UNCHECKED, NULL);
							EnableWindow(m_hBtnISOM, FALSE);
						}
						if((Checkboxes & 0x10) > 0)
						{
							SendMessage(m_hBtnTILE, BM_SETCHECK, BST_UNCHECKED, NULL);
							EnableWindow(m_hBtnTILE, FALSE);
						}
					}
					break;

				case IDB_REPAIR:
					if(Map)
					{
						BYTE Checkboxes = 0;

						if(SendMessage(m_hBtnInflate, BM_GETCHECK, NULL, NULL) == BST_CHECKED)
							Checkboxes = Checkboxes | 0x01;
						if(SendMessage(m_hBtnSwitches, BM_GETCHECK, NULL, NULL) == BST_CHECKED)
							Checkboxes = Checkboxes | 0x02;
						if(SendMessage(m_hBtnLocations, BM_GETCHECK, NULL, NULL) == BST_CHECKED)
							Checkboxes = Checkboxes | 0x04;
						if(SendMessage(m_hBtnUnits, BM_GETCHECK, NULL, NULL) == BST_CHECKED)
							Checkboxes = Checkboxes | 0x08;
						if(SendMessage(m_hBtnComments, BM_GETCHECK, NULL, NULL) == BST_CHECKED)
							Checkboxes = Checkboxes | 0x10;
						if(SendMessage(m_hBtnISOM, BM_GETCHECK, NULL, NULL) == BST_CHECKED)
							Checkboxes = Checkboxes | 0x20;
						if(SendMessage(m_hBtnTILE, BM_GETCHECK, NULL, NULL) == BST_CHECKED)
							Checkboxes = Checkboxes | 0x40;

						EnableWindow(m_hBtnRepair, FALSE);

						EnableWindow(m_hBtnInflate, FALSE);
						SendMessage(m_hBtnInflate, BM_SETCHECK, BST_UNCHECKED, NULL);
						EnableWindow(m_hBtnSwitches, FALSE);
						SendMessage(m_hBtnSwitches, BM_SETCHECK, BST_UNCHECKED, NULL);
						EnableWindow(m_hBtnLocations, FALSE);
						SendMessage(m_hBtnLocations, BM_SETCHECK, BST_UNCHECKED, NULL);
						EnableWindow(m_hBtnUnits, FALSE);
						SendMessage(m_hBtnUnits, BM_SETCHECK, BST_UNCHECKED, NULL);
						EnableWindow(m_hBtnComments, FALSE);
						SendMessage(m_hBtnComments, BM_SETCHECK, BST_UNCHECKED, NULL);
						EnableWindow(m_hBtnISOM, FALSE);
						SendMessage(m_hBtnISOM, BM_SETCHECK, BST_UNCHECKED, NULL);
						EnableWindow(m_hBtnTILE, FALSE);
						SendMessage(m_hBtnTILE, BM_SETCHECK, BST_UNCHECKED, NULL);

						if(Map->Repair(Checkboxes))
						{
							AnnexEditMessage("REPAIR: Repair Successful.\r\n");
						}
						else
						{
							AnnexEditMessage("REPAIR: Repair Failed.\r\n");
							SendMessage(hWnd, WM_COMMAND, ID_FILE_CLOSEMAP, NULL);
						}
					}
					break;

			}
			break;

		case WM_CLOSE:
			if(Map)
				delete Map;
			break;

		case WM_DESTROY:
			PostQuitMessage(WM_QUIT);
			return 0;

	}
	return DefWindowProc(hWnd, uMsg, wParam, lParam);
}
//---------------------------------------------------------------------------
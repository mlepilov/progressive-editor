//Workspace: Progressive Editor
//File Name: LocalFileFunctions.cpp
#include "LocalFileFunctions.h"
#include <windows.h>
//---------------------------------------------------------------------------
char GetLocalFileData(LOCALFILEDATA* m_pLocalFileData)
{
	HANDLE TempHandle;
	DWORD TempNumOfBytesRead;

	TempHandle = CreateFile((LPCTSTR)"VCOD.bin", GENERIC_READ, FILE_SHARE_READ,
		NULL, OPEN_EXISTING, NULL, NULL);

	if(TempHandle == INVALID_HANDLE_VALUE)
		return -1;

	if(GetFileSize(TempHandle, NULL) == 1040)
		ReadFile(TempHandle, m_pLocalFileData->VCODbin, GetFileSize(TempHandle, NULL),
			&TempNumOfBytesRead, NULL);
	else
		return -1;

	CloseHandle(TempHandle);

	return 1;
}
//---------------------------------------------------------------------------
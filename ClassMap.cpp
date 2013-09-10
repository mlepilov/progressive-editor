//Workspace: Progressive Editor
//File Name: ClassMap.cpp
#include "ClassMap.h"
#include "LocalFileFunctions.h"
//---------------------------------------------------------------------------
//--MapClass Methods--
//---------------------------------------------------------------------------
MapClass::MapClass(LPSTR FileName, HWND* EditBox, LOCALFILEDATA* LocalFileData)
{
	CurrentMap = NULL;
	HANDLE TempHandle;
	DWORD TempSize = 0xFFFFFFFF;

	if(SFileOpenArchive((LPCSTR)FileName, 0, 0, &CurrentArchive))
	{
		if(SFileOpenFileEx(CurrentArchive, "staredit\\scenario.chk", 0, &TempHandle))
		{
			DWORD TempNumOfBytesRW;
			CurrentMapSize = SFileGetFileSize(TempHandle, NULL);
			char* TempDataArray = (char*)malloc(CurrentMapSize);
			SFileReadFile(TempHandle, TempDataArray, CurrentMapSize, &TempNumOfBytesRW, NULL);
			SFileCloseFile(TempHandle);

			CreateDirectory("\\staredit", NULL);
			TempHandle = CreateFile("\\staredit\\scenario.chk", GENERIC_WRITE, FILE_SHARE_WRITE,
				NULL, CREATE_ALWAYS, NULL, NULL);
			WriteFile(TempHandle, TempDataArray, CurrentMapSize, &TempNumOfBytesRW, NULL);
			free(TempDataArray);
			CloseHandle(TempHandle);

			TempHandle = CreateFile("\\staredit\\scenario.chk", GENERIC_READ, FILE_SHARE_READ,
				NULL, OPEN_EXISTING, NULL, NULL);
		}
		else
			TempHandle = INVALID_HANDLE_VALUE;
	}
	else
	{
		TempHandle = CreateFile((LPCTSTR)FileName, GENERIC_READ, FILE_SHARE_READ,
			NULL, OPEN_EXISTING, NULL, NULL);
		CurrentArchive = NULL;
	}

	if(TempHandle != INVALID_HANDLE_VALUE)
	{
		CurrentMap = TempHandle;
		memcpy(CurrentMapPath, FileName, MAX_PATH);
		TempSize = GetFileSize(CurrentMap, NULL);
		FilesInArchive = 1;
	}
	else
		CurrentMap = NULL;

	if(TempSize != 0xFFFFFFFF)
	{
		CurrentMapSize = TempSize;
	}

	m_pEditBox = EditBox;
	m_pLocalFileData = LocalFileData;
	FillMemory(&SectionInfo, sizeof(SECTIONINFORMATION), 0);
}
//---------------------------------------------------------------------------
MapClass::~MapClass()
{
	if(CurrentMap)
		CloseHandle(CurrentMap);

	if(CurrentArchive != NULL)
	{
		DeleteFile("\\staredit\\scenario.chk");
		RemoveDirectory("\\staredit");
	}
}
//---------------------------------------------------------------------------
void MapClass::AnnexEditMessage(char* Message)
{
	int len = GetWindowTextLength(*m_pEditBox);
	SendMessage(*m_pEditBox, EM_SETSEL, (WPARAM)len, (LPARAM)len);
	SendMessage(*m_pEditBox, EM_REPLACESEL, (WPARAM)FALSE, (LPARAM)Message);
}
//---------------------------------------------------------------------------
char MapClass::Scan(HANDLE Map)
{
	DWORD CurrentPosition = 0;
	DWORD CurrentOffset = 0;
	DWORD CurrentSectionLength;
	LPSTR CurrentSection = (LPSTR)malloc(5);
	CurrentSection[4] = 0;

	DWORD BytesRead;

	// MTXM, TILE, and MASK aren't present here. SC reads each duplicate section,
	// and this can mix data from 2 or more duplicates of the above sections. They
	// are read before any other section in MapClass::Open
	while(CurrentMapSize > CurrentPosition)
	{
		ReadFile(Map, CurrentSection, 4, &BytesRead, NULL);
		ReadFile(Map, &CurrentSectionLength, sizeof(CurrentSectionLength), &BytesRead, NULL);
		CurrentOffset = SetFilePointer(Map, 0, NULL, FILE_CURRENT);

		if(!strcmp(CurrentSection, "TYPE"))
		{
			SectionInfo.preTYPE = true;
			SectionInfo.slTYPE = CurrentSectionLength;
			SectionInfo.offsetTYPE = CurrentOffset;
		}
		else if(!strcmp(CurrentSection, "VER "))
		{
			SectionInfo.preVER = true;
			SectionInfo.slVER = CurrentSectionLength;
			SectionInfo.offsetVER = CurrentOffset;

			short TempShort;

			ReadFile(Map, &TempShort, sizeof(TempShort), &BytesRead, NULL);

			sVer.SetData(TempShort);

			SetFilePointer(Map, CurrentOffset, NULL, FILE_BEGIN);

			if(TempShort == 205)
			{
				BWUsed = 2;
			}
			else if(TempShort == 63)
			{
				BWUsed = 1;
			}
			else
			{
				BWUsed = 0;
			}
		}
		else if(!strcmp(CurrentSection, "IVER"))
		{
			SectionInfo.preIVER = true;
			SectionInfo.slIVER = CurrentSectionLength;
			SectionInfo.offsetIVER = CurrentOffset;
		}
		else if(!strcmp(CurrentSection, "IVE2"))
		{
			SectionInfo.preIVE2 = true;
			SectionInfo.slIVE2 = CurrentSectionLength;
			SectionInfo.offsetIVE2 = CurrentOffset;
		}
		else if(!strcmp(CurrentSection, "VCOD"))
		{
			SectionInfo.preVCOD = true;
			SectionInfo.slVCOD = CurrentSectionLength;
			SectionInfo.offsetVCOD = CurrentOffset;
		}
		else if(!strcmp(CurrentSection, "IOWN"))
		{
			SectionInfo.preIOWN = true;
			SectionInfo.slIOWN = CurrentSectionLength;
			SectionInfo.offsetIOWN = CurrentOffset;
		}
		else if(!strcmp(CurrentSection, "OWNR"))
		{
			SectionInfo.preOWNR = true;
			SectionInfo.slOWNR = CurrentSectionLength;
			SectionInfo.offsetOWNR = CurrentOffset;
		}
		else if(!strcmp(CurrentSection, "ERA "))
		{
			SectionInfo.preERA = true;
			SectionInfo.slERA = CurrentSectionLength;
			SectionInfo.offsetERA = CurrentOffset;
		}
		else if(!strcmp(CurrentSection, "DIM "))
		{
			// This section is read here and not in MapClass::Read because
			// it is needed to read dimensioned sections (MTXM, TILE, MASK)
			// prior to actually reading them.
			SectionInfo.preDIM = true;
			SectionInfo.slDIM = CurrentSectionLength;
			SectionInfo.offsetDIM = CurrentOffset;

			short TempWidth;
			short TempHeight;

			ReadFile(Map, &TempWidth, sizeof(TempWidth), &BytesRead, NULL);
			ReadFile(Map, &TempHeight, sizeof(TempHeight), &BytesRead, NULL);

			sDim.SetData(TempWidth, 0);
			sDim.SetData(TempHeight, 1);

			SetFilePointer(Map, CurrentOffset, NULL, FILE_BEGIN);
		}
		else if(!strcmp(CurrentSection, "SIDE"))
		{
			SectionInfo.preSIDE = true;
			SectionInfo.slSIDE = CurrentSectionLength;
			SectionInfo.offsetSIDE = CurrentOffset;
		}
		else if(!strcmp(CurrentSection, "PUNI"))
		{
			SectionInfo.prePUNI = true;
			SectionInfo.slPUNI = CurrentSectionLength;
			SectionInfo.offsetPUNI = CurrentOffset;
		}
		else if(!strcmp(CurrentSection, "UNIT"))
		{
			SectionInfo.preUNIT = true;
			SectionInfo.slUNIT = CurrentSectionLength;
			SectionInfo.offsetUNIT = CurrentOffset;
		}
		else if(!strcmp(CurrentSection, "ISOM"))
		{
			SectionInfo.preISOM = true;
			SectionInfo.slISOM = CurrentSectionLength;
			SectionInfo.offsetISOM = CurrentOffset;
		}
		else if(!strcmp(CurrentSection, "DD2 "))
		{
			SectionInfo.preDD2 = true;
			SectionInfo.slDD2 = CurrentSectionLength;
			SectionInfo.offsetDD2 = CurrentOffset;
		}
		else if(!strcmp(CurrentSection, "THG2"))
		{
			SectionInfo.preTHG2 = true;
			SectionInfo.slTHG2 = CurrentSectionLength;
			SectionInfo.offsetTHG2 = CurrentOffset;
		}
		else if(!strcmp(CurrentSection, "STR "))
		{
			// SC reads the last instance of STR that doesn't have a
			// sectionlength of 0
			if(CurrentSectionLength != 0)
			{
				SectionInfo.preSTR = true;
				SectionInfo.slSTR = CurrentSectionLength;
				SectionInfo.offsetSTR = CurrentOffset;
			}
		}
		else if(!strcmp(CurrentSection, "UPRP"))
		{
			SectionInfo.preUPRP = true;
			SectionInfo.slUPRP = CurrentSectionLength;
			SectionInfo.offsetUPRP = CurrentOffset;
		}
		else if(!strcmp(CurrentSection, "UPUS"))
		{
			SectionInfo.preUPUS = true;
			SectionInfo.slUPUS = CurrentSectionLength;
			SectionInfo.offsetUPUS = CurrentOffset;
		}
		else if(!strcmp(CurrentSection, "MRGN"))
		{
			SectionInfo.preMRGN = true;
			SectionInfo.slMRGN = CurrentSectionLength;
			SectionInfo.offsetMRGN = CurrentOffset;
		}
		else if(!strcmp(CurrentSection, "TRIG"))
		{
			// SC reads the last instance of TRIG that has at least
			// one "valid" trigger... same goes for MBRF below
			char TempCharArray[28];

			for(DWORD i = 0; i < CurrentSectionLength / 2400; i++)
			{
				SetFilePointer(Map, 2372, NULL, FILE_CURRENT);
				ReadFile(Map, &TempCharArray, 28, &BytesRead, NULL);

				if(SectionInfo.offsetTRIG == CurrentOffset &&
					SectionInfo.preTRIG == true)
					break;	// If it's already been determined that this is
							// a valid section, break the loop.
				for(char i2 = 0; i2 < 28; i2++)
				{
					if(TempCharArray[i2] != 0)
					{
						SectionInfo.preTRIG = true;
						SectionInfo.slTRIG = CurrentSectionLength;
						SectionInfo.offsetTRIG = CurrentOffset;
						break;
					}
				}
			}

			SetFilePointer(Map, CurrentOffset, NULL, FILE_BEGIN);
		}
		else if(!strcmp(CurrentSection, "MBRF"))
		{
			SectionInfo.preMBRF = true;
			SectionInfo.slMBRF = CurrentSectionLength;
			SectionInfo.offsetMBRF = CurrentOffset;
		}
		else if(!strcmp(CurrentSection, "SPRP"))
		{
			SectionInfo.preSPRP = true;
			SectionInfo.slSPRP = CurrentSectionLength;
			SectionInfo.offsetSPRP = CurrentOffset;
		}
		else if(!strcmp(CurrentSection, "FORC"))
		{
			SectionInfo.preFORC = true;
			SectionInfo.slFORC = CurrentSectionLength;
			SectionInfo.offsetFORC = CurrentOffset;
		}
		else if(!strcmp(CurrentSection, "WAV "))
		{
			SectionInfo.preWAV = true;
			SectionInfo.slWAV = CurrentSectionLength;
			SectionInfo.offsetWAV = CurrentOffset;
		}
		else if(!strcmp(CurrentSection, "SWNM"))
		{
			SectionInfo.preSWNM = true;
			SectionInfo.slSWNM = CurrentSectionLength;
			SectionInfo.offsetSWNM = CurrentOffset;
		}
		else if(!strcmp(CurrentSection, "COLR"))
		{
			SectionInfo.preCOLR = true;
			SectionInfo.slCOLR = CurrentSectionLength;
			SectionInfo.offsetCOLR = CurrentOffset;
		}
		else if(!strcmp(CurrentSection, "UPGR"))
		{
			SectionInfo.preUPGR = true;
			SectionInfo.slUPGR = CurrentSectionLength;
			SectionInfo.offsetUPGR = CurrentOffset;
		}
		else if(!strcmp(CurrentSection, "PTEC"))
		{
			SectionInfo.prePTEC = true;
			SectionInfo.slPTEC = CurrentSectionLength;
			SectionInfo.offsetPTEC = CurrentOffset;
		}
		else if(!strcmp(CurrentSection, "UNIS"))
		{
			SectionInfo.preUNIS = true;
			SectionInfo.slUNIS = CurrentSectionLength;
			SectionInfo.offsetUNIS = CurrentOffset;
		}
		else if(!strcmp(CurrentSection, "UPGS"))
		{
			SectionInfo.preUPGS = true;
			SectionInfo.slUPGS = CurrentSectionLength;
			SectionInfo.offsetUPGS = CurrentOffset;
		}
		else if(!strcmp(CurrentSection, "TECS"))
		{
			SectionInfo.preTECS = true;
			SectionInfo.slTECS = CurrentSectionLength;
			SectionInfo.offsetTECS = CurrentOffset;
		}
		else if(!strcmp(CurrentSection, "PUPx"))
		{
			SectionInfo.prePUPx = true;
			SectionInfo.slPUPx = CurrentSectionLength;
			SectionInfo.offsetPUPx = CurrentOffset;
		}
		else if(!strcmp(CurrentSection, "PTEx"))
		{
			SectionInfo.prePTEx = true;
			SectionInfo.slPTEx = CurrentSectionLength;
			SectionInfo.offsetPTEx = CurrentOffset;
		}
		else if(!strcmp(CurrentSection, "UNIx"))
		{
			SectionInfo.preUNIx = true;
			SectionInfo.slUNIx = CurrentSectionLength;
			SectionInfo.offsetUNIx = CurrentOffset;
		}
		else if(!strcmp(CurrentSection, "UPGx"))
		{
			SectionInfo.preUPGx = true;
			SectionInfo.slUPGx = CurrentSectionLength;
			SectionInfo.offsetUPGx = CurrentOffset;
		}
		else if(!strcmp(CurrentSection, "TECx"))
		{
			SectionInfo.preTECx = true;
			SectionInfo.slTECx = CurrentSectionLength;
			SectionInfo.offsetTECx = CurrentOffset;
		}

		SetFilePointer(Map, CurrentSectionLength, NULL, FILE_CURRENT);
		CurrentPosition = CurrentPosition + CurrentSectionLength + 8;
	}

	free(CurrentSection);
	if(SectionInfo.preDIM == false || SectionInfo.preVER == false ||
		SectionInfo.preSTR == false)
		return 0;
	return 1;
}
//---------------------------------------------------------------------------
HANDLE MapClass::GetCurrentArchive()
{
	return CurrentArchive;
}
//---------------------------------------------------------------------------
short MapClass::GetFilesInArchive()
{
	return FilesInArchive;
}
//---------------------------------------------------------------------------
HANDLE MapClass::GetCurrentMap()
{
	return CurrentMap;
}
//---------------------------------------------------------------------------
SECTIONINFORMATION MapClass::GetSectionInfo()
{
	return SectionInfo;
}
//---------------------------------------------------------------------------
char* MapClass::GetMapPath()
{
	return CurrentMapPath;
}
//---------------------------------------------------------------------------
//Workspace: Progressive Editor
//File Name: ReadFunctions.cpp
#include <windows.h>
#include "ClassMap.h"
//---------------------------------------------------------------------------
void MapClass::Read(HANDLE Map)
{
	DWORD TempNumOfBytesRead;

	// The 4 declarations below are all for the mini-dimention chain
	DWORD CurrentPosition = 0;
	DWORD CurrentSectionLength;
	LPSTR CurrentSection = (LPSTR)malloc(5);
	CurrentSection[4] = 0;

	//START MINI-DIM CHAIN
	SetFilePointer(Map, 0, NULL, FILE_BEGIN);
	// This is needed to read the MTXM, TILE, and MASK sections the way SC does
	DWORD TempLength;
	// The following size functions are used to set the maximum length of the tile arrays
	// to write to.
	sMtxm.Size(sDim.GetData(1), sDim.GetData(0));
	sTile.Size(sDim.GetData(1), sDim.GetData(0));
	sMask.Size(sDim.GetData(1), sDim.GetData(0));
	while(CurrentMapSize > CurrentPosition)
	{
		ReadFile(Map, CurrentSection, 4, &TempNumOfBytesRead, NULL);
		ReadFile(Map, &CurrentSectionLength, sizeof(CurrentSectionLength), &TempNumOfBytesRead, NULL);
		if(!strcmp(CurrentSection, "MTXM"))
		{
			SectionInfo.preMTXM = true;
			SectionInfo.slMTXM = sDim.GetData(0) * sDim.GetData(1) * sizeof(short);

			if(CurrentSectionLength < sDim.GetData(0) * sDim.GetData(1) * sizeof(short))
			{
				TempLength = CurrentSectionLength;
			}
			else
			{
				TempLength = sDim.GetData(0) * sDim.GetData(1) * sizeof(short);
			}

			long MoveBack = 0 - TempLength;

			short* TempShortArray = (short*)malloc(TempLength);

			ReadFile(Map, TempShortArray, TempLength, &TempNumOfBytesRead, NULL);
			SetFilePointer(Map, MoveBack, NULL, FILE_CURRENT);

			sMtxm.CopyData(TempShortArray, TempLength);

			free(TempShortArray);
		}
		if(!strcmp(CurrentSection, "TILE"))
		{
			SectionInfo.preTILE = true;
			SectionInfo.slTILE = sDim.GetData(0) * sDim.GetData(1) * sizeof(short);

			if(CurrentSectionLength < sDim.GetData(0) * sDim.GetData(1) * sizeof(short))
			{
				TempLength = CurrentSectionLength;
			}
			else
			{
				TempLength = sDim.GetData(0) * sDim.GetData(1) * sizeof(short);
			}

			long MoveBack = 0 - TempLength;
			
			short* TempShortArray = (short*)malloc(TempLength);

			ReadFile(Map, TempShortArray, TempLength, &TempNumOfBytesRead, NULL);
			SetFilePointer(Map, MoveBack, NULL, FILE_CURRENT);

			sTile.CopyData(TempShortArray, TempLength);

			free(TempShortArray);
		}
		if(!strcmp(CurrentSection, "MASK"))
		{
			SectionInfo.preMASK = true;
			SectionInfo.slMASK = sDim.GetData(0) * sDim.GetData(1);

			if(CurrentSectionLength < (unsigned long)sDim.GetData(0) * sDim.GetData(1))
			{
				TempLength = CurrentSectionLength;
			}
			else
			{
				TempLength = sDim.GetData(0) * sDim.GetData(1);
			}

			long MoveBack = 0 - TempLength;

			char* TempChrArray = (char*)malloc(TempLength);

			ReadFile(Map, TempChrArray, TempLength, &TempNumOfBytesRead, NULL);
			SetFilePointer(Map, MoveBack, NULL, FILE_CURRENT);

			sMask.CopyData(TempChrArray, TempLength);

			free(TempChrArray);
		}
		SetFilePointer(Map, CurrentSectionLength, NULL, FILE_CURRENT);
		CurrentPosition = CurrentPosition + CurrentSectionLength + 8;
	}
	free(CurrentSection);
	//END MINI-DIM CHAIN


	//START NORMAL READ
	// Offset-based reading for the rest of the sections.
	// The strings section is still read the way SC does: the largest section instance.
	// See MapClass::Scan, STR section passage
	if(true == SectionInfo.preTYPE)
	{
		if(4 == SectionInfo.slTYPE)
		{
			LPSTR TempString;
			TempString = (LPSTR)malloc(5);

			SetFilePointer(Map, SectionInfo.offsetTYPE, NULL, FILE_BEGIN);
			ReadFile(Map, TempString, 4, &TempNumOfBytesRead, NULL);

			sType.SetData(TempString);

			free(TempString);
		}
	}
	if(0 == BWUsed)
	{
		if(true == SectionInfo.preIVER)
		{
			if(2 == SectionInfo.slIVER)
			{
				short TempShort;

				SetFilePointer(Map, SectionInfo.offsetIVER, NULL, FILE_BEGIN);
				ReadFile(Map, &TempShort, sizeof(TempShort), &TempNumOfBytesRead, NULL);

				sIver.SetData(TempShort);
			}
		}
	}
	if(0 != BWUsed)
	{
		if(true == SectionInfo.preIVE2)
		{
			if(2 == SectionInfo.slIVE2)
			{
				short TempShort;

				SetFilePointer(Map, SectionInfo.offsetIVE2, NULL, FILE_BEGIN);
				ReadFile(Map, &TempShort, sizeof(TempShort), &TempNumOfBytesRead, NULL);

				sIve2.SetData(TempShort);
			}
		}
	}
	if(true == SectionInfo.preVCOD)
	{
		char TempChrArray[1040];

		SetFilePointer(Map, SectionInfo.offsetVCOD, NULL, FILE_BEGIN);
		ReadFile(Map, TempChrArray, 1040, &TempNumOfBytesRead, NULL);

		sVcod.SetData(TempChrArray);
	}
	if(true == SectionInfo.preIOWN)
	{
		if(12 == SectionInfo.slIOWN)
		{
			char TempChrArray[12];

			SetFilePointer(Map, SectionInfo.offsetIOWN, NULL, FILE_BEGIN);
			ReadFile(Map, TempChrArray, 12, &TempNumOfBytesRead, NULL);

			sIown.CopyData(TempChrArray);
		}
	}
	if(true == SectionInfo.preOWNR)
	{
		char TempChrArray[12];

		SetFilePointer(Map, SectionInfo.offsetOWNR, NULL, FILE_BEGIN);
		ReadFile(Map, TempChrArray, 12, &TempNumOfBytesRead, NULL);

		sOwnr.CopyData(TempChrArray);
	}
	if(true == SectionInfo.preERA)
	{
		short TempShort;

		SetFilePointer(Map, SectionInfo.offsetERA, NULL, FILE_BEGIN);
		ReadFile(Map, &TempShort, sizeof(TempShort), &TempNumOfBytesRead, NULL);

		sEra.SetData(TempShort);
	}
	if(true == SectionInfo.preSIDE)
	{
		char TempChrArray[12];

		SetFilePointer(Map, SectionInfo.offsetSIDE, NULL, FILE_BEGIN);
		ReadFile(Map, TempChrArray, 12, &TempNumOfBytesRead, NULL);

		sSide.CopyData(TempChrArray);
	}
	if(true == SectionInfo.prePUNI)
	{
		char* TempChrArray;

		SetFilePointer(Map, SectionInfo.offsetPUNI, NULL, FILE_BEGIN);

		TempChrArray = (char*)malloc(2736);
		ReadFile(Map, TempChrArray, 2736, &TempNumOfBytesRead, NULL);
		sPuni.CopyData(TempChrArray, 0);
		TempChrArray = (char*)realloc(TempChrArray, 228);
		ReadFile(Map, TempChrArray, 228, &TempNumOfBytesRead, NULL);
		sPuni.CopyData(TempChrArray, 1);
		TempChrArray = (char*)realloc(TempChrArray, 2736);
		ReadFile(Map, TempChrArray, 2736, &TempNumOfBytesRead, NULL);
		sPuni.CopyData(TempChrArray, 2);

		free(TempChrArray);
	}
	if(true == SectionInfo.preUNIT)
	{
		char* TempDataChunk = (char*)malloc(SectionInfo.slUNIT);

		SetFilePointer(Map, SectionInfo.offsetUNIT, NULL, FILE_BEGIN);

		ReadFile(Map, TempDataChunk, SectionInfo.slUNIT, &TempNumOfBytesRead, NULL);
		sUnit.CopyData(TempDataChunk, SectionInfo.slUNIT);

		free(TempDataChunk);
	}
	if(true == SectionInfo.preISOM)
	{
		if(SectionInfo.slISOM == (DWORD)(sDim.GetData(1) + 1) * (sDim.GetData(0) / 2 + 1) * 4 * 2)
		{
			RECT* TempRectArray;
			short TempWidth;
			short TempHeight;
			if(0 == sDim.GetData(0) % 2)
			{
				TempWidth = sDim.GetData(0) / 2 + 1;
			}
			else
			{
				TempWidth = (sDim.GetData(0) - 1) / 2 + 1;
			}
			TempHeight = sDim.GetData(1) + 1;

			TempRectArray = (RECT*)malloc(TempWidth * TempHeight * sizeof(RECT));
			SetFilePointer(Map, SectionInfo.offsetISOM, NULL, FILE_BEGIN);

			for(int i = 0; i < TempWidth * TempHeight; i++)
			{
				ReadFile(Map, &TempRectArray[i].left, 2, &TempNumOfBytesRead, NULL);
				ReadFile(Map, &TempRectArray[i].top, 2, &TempNumOfBytesRead, NULL);
				ReadFile(Map, &TempRectArray[i].right, 2, &TempNumOfBytesRead, NULL);
				ReadFile(Map, &TempRectArray[i].bottom, 2, &TempNumOfBytesRead, NULL);
			}

			sIsom.CopyData(TempRectArray, sDim.GetData(1), sDim.GetData(0));
			free(TempRectArray);
		}
	}
	if(true == SectionInfo.preDD2)
	{
		char* TempDataChunk = (char*)malloc(SectionInfo.slDD2);
		
		SetFilePointer(Map, SectionInfo.offsetDD2, NULL, FILE_BEGIN);

		ReadFile(Map, TempDataChunk, SectionInfo.slDD2, &TempNumOfBytesRead, NULL);
		sDd2.CopyData(TempDataChunk, SectionInfo.slDD2);

		free(TempDataChunk);
	}
	if(true == SectionInfo.preTHG2)
	{
		char* TempDataChunk = (char*)malloc(SectionInfo.slTHG2);

		SetFilePointer(Map, SectionInfo.offsetTHG2, NULL, FILE_BEGIN);

		ReadFile(Map, TempDataChunk, SectionInfo.slTHG2, &TempNumOfBytesRead, NULL);
		sThg2.CopyData(TempDataChunk, SectionInfo.slTHG2);

		free(TempDataChunk);
	}
	if(true == SectionInfo.preSTR)
	{
		short TempNumberOfStrings;
		LPVOID TempStringChunk = malloc(SectionInfo.slSTR);

		SetFilePointer(Map, SectionInfo.offsetSTR, NULL, FILE_BEGIN);

		ReadFile(Map, TempStringChunk, SectionInfo.slSTR, &TempNumOfBytesRead, NULL);

		TempNumberOfStrings = ((short*)(TempStringChunk))[0];

		sStr.CopyData(ProcessStringChunk(TempStringChunk, SectionInfo.slSTR), TempNumberOfStrings);
		sStr.SetData(NULL, TempNumberOfStrings, NULL, 3);
		free(TempStringChunk);
	}
	if(true == SectionInfo.preUPRP)
	{
		unsigned long TempUnsignedLong;

		SetFilePointer(Map, SectionInfo.offsetUPRP, NULL, FILE_BEGIN);

		for(unsigned char i = 0; i < SectionInfo.slUPRP / 20; i++)
		{
			ReadFile(Map, &TempUnsignedLong, 2, &TempNumOfBytesRead, NULL);
			sUprp.SetData(i, TempUnsignedLong, 0);
			TempUnsignedLong = 0;
			ReadFile(Map, &TempUnsignedLong, 2, &TempNumOfBytesRead, NULL);
			sUprp.SetData(i, TempUnsignedLong, 1);
			TempUnsignedLong = 0;
			ReadFile(Map, &TempUnsignedLong, 1, &TempNumOfBytesRead, NULL);
			sUprp.SetData(i, TempUnsignedLong, 2);
			TempUnsignedLong = 0;
			ReadFile(Map, &TempUnsignedLong, 1, &TempNumOfBytesRead, NULL);
			sUprp.SetData(i, TempUnsignedLong, 3);
			TempUnsignedLong = 0;
			ReadFile(Map, &TempUnsignedLong, 1, &TempNumOfBytesRead, NULL);
			sUprp.SetData(i, TempUnsignedLong, 4);
			TempUnsignedLong = 0;
			ReadFile(Map, &TempUnsignedLong, 1, &TempNumOfBytesRead, NULL);
			sUprp.SetData(i, TempUnsignedLong, 5);
			TempUnsignedLong = 0;
			ReadFile(Map, &TempUnsignedLong, 4, &TempNumOfBytesRead, NULL);
			sUprp.SetData(i, TempUnsignedLong, 6);
			TempUnsignedLong = 0;
			ReadFile(Map, &TempUnsignedLong, 2, &TempNumOfBytesRead, NULL);
			sUprp.SetData(i, TempUnsignedLong, 7);
			TempUnsignedLong = 0;
			ReadFile(Map, &TempUnsignedLong, 2, &TempNumOfBytesRead, NULL);
			sUprp.SetData(i, TempUnsignedLong, 8);
			TempUnsignedLong = 0;
			ReadFile(Map, &TempUnsignedLong, 4, &TempNumOfBytesRead, NULL);
			sUprp.SetData(i, TempUnsignedLong, 9);
			TempUnsignedLong = 0;
		}
	}
	if(true == SectionInfo.preUPUS)
	{
		if(64 == SectionInfo.slUPUS)
		{
			char* TempCharArray = (char*)malloc(64);

			SetFilePointer(Map, SectionInfo.offsetUPUS, NULL, FILE_BEGIN);
		
			ReadFile(Map, TempCharArray, 64, &TempNumOfBytesRead, NULL);

			sUpus.CopyData(TempCharArray);

			free(TempCharArray);
		}
	}
	if(true == SectionInfo.preMRGN)
	{
		if(SectionInfo.slMRGN > 1280)
		{
			sMrgn.SetBWBit(1);
		}
		else
		{
			sMrgn.SetBWBit(0);
		}

		long TempLong;

		SetFilePointer(Map, SectionInfo.offsetMRGN, NULL, FILE_BEGIN);

		for(unsigned char i = 0; i < SectionInfo.slMRGN / 20; i++)
		{
			ReadFile(Map, &TempLong, 4, &TempNumOfBytesRead, NULL);
			sMrgn.SetData(i, TempLong, 0);
			TempLong = 0;
			ReadFile(Map, &TempLong, 4, &TempNumOfBytesRead, NULL);
			sMrgn.SetData(i, TempLong, 1);
			TempLong = 0;
			ReadFile(Map, &TempLong, 4, &TempNumOfBytesRead, NULL);
			sMrgn.SetData(i, TempLong, 2);
			TempLong = 0;
			ReadFile(Map, &TempLong, 4, &TempNumOfBytesRead, NULL);
			sMrgn.SetData(i, TempLong, 3);
			TempLong = 0;
			ReadFile(Map, &TempLong, 2, &TempNumOfBytesRead, NULL);
			sMrgn.SetData(i, TempLong, 4);
			TempLong = 0;
			ReadFile(Map, &TempLong, 2, &TempNumOfBytesRead, NULL);
			sMrgn.SetData(i, TempLong, 5);
			TempLong = 0;
		}
	}
	if(true == SectionInfo.preTRIG)
	{
		char* TempDataChunk = (char*)malloc(SectionInfo.slTRIG);

		SetFilePointer(Map, SectionInfo.offsetTRIG, NULL, FILE_BEGIN);

		ReadFile(Map, TempDataChunk, SectionInfo.slTRIG, &TempNumOfBytesRead, NULL);
		sTrig.CopyData(TempDataChunk, SectionInfo.slTRIG);

		free(TempDataChunk);
	}
	if(true == SectionInfo.preMBRF)
	{
		char* TempDataChunk = (char*)malloc(SectionInfo.slMBRF);

		SetFilePointer(Map, SectionInfo.offsetMBRF, NULL, FILE_BEGIN);

		ReadFile(Map, TempDataChunk, SectionInfo.slMBRF, &TempNumOfBytesRead, NULL);
		sMbrf.CopyData(TempDataChunk, SectionInfo.slMBRF);

		free(TempDataChunk);
	}
	if(true == SectionInfo.preSPRP)
	{
		short TempShort;

		SetFilePointer(Map, SectionInfo.offsetSPRP, NULL, FILE_BEGIN);

		ReadFile(Map, &TempShort, sizeof(TempShort), &TempNumOfBytesRead, NULL);
		sSprp.SetData(TempShort, 0);
		ReadFile(Map, &TempShort, sizeof(TempShort), &TempNumOfBytesRead, NULL);
		sSprp.SetData(TempShort, 1);
	}
	if(true == SectionInfo.preFORC)
	{
		short TempShort;

		SetFilePointer(Map, SectionInfo.offsetFORC, NULL, FILE_BEGIN);

		for(char i = 0; i <= 7; i++)
		{
			ReadFile(Map, &TempShort, 1, &TempNumOfBytesRead, NULL);
			sForc.SetData(TempShort, i);
			TempShort = 0;
		}
		for(char i2 = 8; i2 <= 11; i2++)
		{
			ReadFile(Map, &TempShort, 2, &TempNumOfBytesRead, NULL);
			sForc.SetData(TempShort, i2);
			TempShort = 0;
		}
		for(char i3 = 12; i3 <= 15; i3++)
		{
			ReadFile(Map, &TempShort, 1, &TempNumOfBytesRead, NULL);
			sForc.SetData(TempShort, i3);
			TempShort = 0;
		}
	}
	if(true == SectionInfo.preWAV)
	{
		if(SectionInfo.slWAV = 2048)
		{
			long TempLongArray[512];

			SetFilePointer(Map, SectionInfo.offsetWAV, NULL, FILE_BEGIN);

			ReadFile(Map, &TempLongArray, 2048, &TempNumOfBytesRead, NULL);
			sWav.CopyData(TempLongArray);
		}
	}
	if(true == SectionInfo.preSWNM)
	{
		if(SectionInfo.slSWNM = 1024)
		{
			long TempLongArray[256];

			SetFilePointer(Map, SectionInfo.offsetSWNM, NULL, FILE_BEGIN);

			ReadFile(Map, &TempLongArray, 1024, &TempNumOfBytesRead, NULL);
			sSwnm.CopyData(TempLongArray);
		}
	}
	if(BWUsed == 2)
	{
		if(true == SectionInfo.preCOLR)
		{
			unsigned char TempCharArray[8];

			SetFilePointer(Map, SectionInfo.offsetCOLR, NULL, FILE_BEGIN);

			ReadFile(Map, &TempCharArray, 8, &TempNumOfBytesRead, NULL);
			sColr.CopyData(TempCharArray);
		}
	}
	if(2 != BWUsed)
	{
		if(true == SectionInfo.preUPGR)
		{
			sUpgr.SetData(0, 0, 0, 5);

			unsigned char* TempChrArray;

			SetFilePointer(Map, SectionInfo.offsetUPGR, NULL, FILE_BEGIN);

			for(char i = 0; i < 2; i++)
			{
				TempChrArray = (unsigned char*)malloc(552);
				ReadFile(Map, TempChrArray, 552, &TempNumOfBytesRead, NULL);
				sUpgr.CopyData(TempChrArray, i);
				free(TempChrArray);
			}
			for(; i < 4; i++)
			{
				TempChrArray = (unsigned char*)malloc(46);
				ReadFile(Map, TempChrArray, 46, &TempNumOfBytesRead, NULL);
				sUpgr.CopyData(TempChrArray, i);
				free(TempChrArray);
			}
			TempChrArray = (unsigned char*)malloc(552);
			ReadFile(Map, TempChrArray, 552, &TempNumOfBytesRead, NULL);
			sUpgr.CopyData(TempChrArray, 4);

			free(TempChrArray);
		}
	}
	if(2 != BWUsed)
	{
		if(true == SectionInfo.prePTEC)
		{
			sPtec.SetData(0, 0, 0, 5);

			char* TempChrArray;

			SetFilePointer(Map, SectionInfo.offsetPTEC, NULL, FILE_BEGIN);

			for(char i = 0; i < 2; i++)
			{
				TempChrArray = (char*)malloc(288);
				ReadFile(Map, TempChrArray, 288, &TempNumOfBytesRead, NULL);
				sPtec.CopyData(TempChrArray, i);
				free(TempChrArray);
			}
			for(; i < 4; i++)
			{
				TempChrArray = (char*)malloc(24);
				ReadFile(Map, TempChrArray, 24, &TempNumOfBytesRead, NULL);
				sPtec.CopyData(TempChrArray, i);
				free(TempChrArray);
			}
			TempChrArray = (char*)malloc(288);
			ReadFile(Map, TempChrArray, 288, &TempNumOfBytesRead, NULL);
			sPtec.CopyData(TempChrArray, 4);

			free(TempChrArray);
		}
	}
	if(2 != BWUsed)
	{
		if(true == SectionInfo.preUNIS)
		{
			sUnis.SetData(0, (LPVOID)0, 12);

			LPVOID TempDataArray;
			UNITSETTING TempUSArray[228];

			SetFilePointer(Map, SectionInfo.offsetUNIS, NULL, FILE_BEGIN);

			TempDataArray = (LPVOID)malloc(228);
			ReadFile(Map, TempDataArray, 228, &TempNumOfBytesRead, NULL);
			sUnis.CopyData(TempDataArray, 0);
			for(unsigned char i = 0; i < 228; i++)
			{
				ReadFile(Map, &TempUSArray[i].Unknown, 1, &TempNumOfBytesRead, NULL);
				ReadFile(Map, &TempUSArray[i].HitPoints, 2, &TempNumOfBytesRead, NULL);
				ReadFile(Map, &TempUSArray[i].Invincible, 1, &TempNumOfBytesRead, NULL);
			}
			sUnis.CopyData((LPVOID)TempUSArray, 1);
			TempDataArray = (LPVOID)malloc(456);
			ReadFile(Map, TempDataArray, 456, &TempNumOfBytesRead, NULL);
			sUnis.CopyData(TempDataArray, 2);
			TempDataArray = (LPVOID)realloc(TempDataArray, 228);
			ReadFile(Map, TempDataArray, 228, &TempNumOfBytesRead, NULL);
			sUnis.CopyData(TempDataArray, 3);
			free(TempDataArray);
			for(i = 4; i < 8; i++)
			{
				TempDataArray = (LPVOID)malloc(456);
				ReadFile(Map, TempDataArray, 456, &TempNumOfBytesRead, NULL);
				sUnis.CopyData(TempDataArray, i);
				free(TempDataArray);
			}
			for(; i < 10; i++)
			{
				TempDataArray = (LPVOID)malloc(200);
				ReadFile(Map, TempDataArray, 200, &TempNumOfBytesRead, NULL);
				sUnis.CopyData(TempDataArray, i);
				free(TempDataArray);
			}
		}
	}
	if(2 != BWUsed)
	{
		if(true == SectionInfo.preUPGS)
		{
			sUpgs.SetData(0, 0, 7);

			char* TempChrArray;
			short* TempShortArray;

			SetFilePointer(Map, SectionInfo.offsetUPGS, NULL, FILE_BEGIN);

			TempChrArray = (char*)malloc(46);
			ReadFile(Map, TempChrArray, 46, &TempNumOfBytesRead, NULL);
			sUpgs.CopyData(TempChrArray, NULL, 0);
			for(char i = 1; i < 7; i++)
			{
				TempShortArray = (short*)malloc(92);
				ReadFile(Map, TempShortArray, 92, &TempNumOfBytesRead, NULL);
				sUpgs.CopyData(NULL, TempShortArray, i);
				free(TempShortArray);
			}

			free(TempChrArray);
		}
	}
	if(2 != BWUsed)
	{
		if(true == SectionInfo.preTECS)
		{
			sTecs.SetData(0, 0, 5);

			char* TempChrArray;
			short* TempShortArray;

			SetFilePointer(Map, SectionInfo.offsetTECS, NULL, FILE_BEGIN);

			TempChrArray = (char*)malloc(24);
			ReadFile(Map, TempChrArray, 24, &TempNumOfBytesRead, NULL);
			sTecs.CopyData(TempChrArray, NULL, 0);
			for(char i = 1; i < 5; i++)
			{
				TempShortArray = (short*)malloc(48);
				ReadFile(Map, TempShortArray, 48, &TempNumOfBytesRead, NULL);
				sTecs.CopyData(NULL, TempShortArray, i);
				free(TempShortArray);
			}

			free(TempChrArray);
		}
	}
	if(0 != BWUsed)
	{
		if(true == SectionInfo.prePUPx)
		{
			sPupX.SetData(0, 0, 1, 5);

			unsigned char* TempChrArray;

			SetFilePointer(Map, SectionInfo.offsetPUPx, NULL, FILE_BEGIN);

			for(char i = 0; i < 2; i++)
			{
				TempChrArray = (unsigned char*)malloc(732);
				ReadFile(Map, TempChrArray, 732, &TempNumOfBytesRead, NULL);
				sPupX.CopyData(TempChrArray, i);
				free(TempChrArray);
			}
			for(; i < 4; i++)
			{
				TempChrArray = (unsigned char*)malloc(61);
				ReadFile(Map, TempChrArray, 61, &TempNumOfBytesRead, NULL);
				sPupX.CopyData(TempChrArray, i);
				free(TempChrArray);
			}
			TempChrArray = (unsigned char*)malloc(732);
			ReadFile(Map, TempChrArray, 732, &TempNumOfBytesRead, NULL);
			sPupX.CopyData(TempChrArray, 4);

			free(TempChrArray);
		}
	}
	if(0 != BWUsed)
	{
		if(true == SectionInfo.prePTEx)
		{
			sPteX.SetData(0, 0, 1, 5);

			char* TempChrArray;

			SetFilePointer(Map, SectionInfo.offsetPTEx, NULL, FILE_BEGIN);

			for(char i = 0; i < 2; i++)
			{
				TempChrArray = (char*)malloc(528);
				ReadFile(Map, TempChrArray, 528, &TempNumOfBytesRead, NULL);
				sPteX.CopyData(TempChrArray, i);
				free(TempChrArray);
			}
			for(; i < 4; i++)
			{
				TempChrArray = (char*)malloc(44);
				ReadFile(Map, TempChrArray, 44, &TempNumOfBytesRead, NULL);
				sPteX.CopyData(TempChrArray, i);
				free(TempChrArray);
			}
			TempChrArray = (char*)malloc(528);
			ReadFile(Map, TempChrArray, 528, &TempNumOfBytesRead, NULL);
			sPteX.CopyData(TempChrArray, 4);

			free(TempChrArray);
		}
	}
	if(0 != BWUsed)
	{
		if(true == SectionInfo.preUNIx)
		{
			sUniX.SetData(0, (LPVOID)1, 12);

			LPVOID TempDataArray;
			UNITSETTING TempUSArray[228];

			SetFilePointer(Map, SectionInfo.offsetUNIx, NULL, FILE_BEGIN);

			TempDataArray = (LPVOID)malloc(228);
			ReadFile(Map, TempDataArray, 228, &TempNumOfBytesRead, NULL);
			sUniX.CopyData(TempDataArray, 0);
			for(unsigned char i = 0; i < 228; i++)
			{
				ReadFile(Map, &TempUSArray[i].Unknown, 1, &TempNumOfBytesRead, NULL);
				ReadFile(Map, &TempUSArray[i].HitPoints, 2, &TempNumOfBytesRead, NULL);
				ReadFile(Map, &TempUSArray[i].Invincible, 1, &TempNumOfBytesRead, NULL);
			}
			sUniX.CopyData((LPVOID)TempUSArray, 1);
			TempDataArray = (LPVOID)realloc(TempDataArray, 456);
			ReadFile(Map, TempDataArray, 456, &TempNumOfBytesRead, NULL);
			sUniX.CopyData(TempDataArray, 2);
			TempDataArray = (LPVOID)realloc(TempDataArray, 228);
			ReadFile(Map, TempDataArray, 228, &TempNumOfBytesRead, NULL);
			sUniX.CopyData(TempDataArray, 3);
			free(TempDataArray);
			for(i = 4; i < 8; i++)
			{
				TempDataArray = (LPVOID)malloc(456);
				ReadFile(Map, TempDataArray, 456, &TempNumOfBytesRead, NULL);
				sUniX.CopyData(TempDataArray, i);
				free(TempDataArray);
			}
			for(; i < 10; i++)
			{
				TempDataArray = (LPVOID)malloc(260);
				ReadFile(Map, TempDataArray, 260, &TempNumOfBytesRead, NULL);
				sUniX.CopyData(TempDataArray, i);
				free(TempDataArray);
			}
		}
	}
	if(0 != BWUsed)
	{
		if(true == SectionInfo.preUPGx)
		{
			sUpgX.SetData(0, 1, 7);

			char* TempChrArray;
			short* TempShortArray;

			SetFilePointer(Map, SectionInfo.offsetUPGx, NULL, FILE_BEGIN);

			TempChrArray = (char*)malloc(61);
			ReadFile(Map, TempChrArray, 61, &TempNumOfBytesRead, NULL);
			sUpgX.CopyData(TempChrArray, NULL, 0);
			SetFilePointer(Map, 1, NULL, FILE_CURRENT);
			for(char i = 1; i < 7; i++)
			{
				TempShortArray = (short*)malloc(122);
				ReadFile(Map, TempShortArray, 122, &TempNumOfBytesRead, NULL);
				sUpgX.CopyData(NULL, TempShortArray, i);
				free(TempShortArray);
			}

			free(TempChrArray);
		}
	}
	if(0 != BWUsed)
	{
		if(true == SectionInfo.preTECx)
		{
			sTecX.SetData(0, 1, 5);

			char* TempChrArray;
			short* TempShortArray;

			SetFilePointer(Map, SectionInfo.offsetTECx, NULL, FILE_BEGIN);

			TempChrArray = (char*)malloc(44);
			ReadFile(Map, TempChrArray, 44, &TempNumOfBytesRead, NULL);
			sTecX.CopyData(TempChrArray, NULL, 0);
			for(char i = 1; i < 5; i++)
			{
				TempShortArray = (short*)malloc(88);
				ReadFile(Map, TempShortArray, 88, &TempNumOfBytesRead, NULL);
				sTecX.CopyData(NULL, TempShortArray, i);
				free(TempShortArray);
			}

			free(TempChrArray);
		}
	}
	//END NORMAL READ

	DetectStringUsage(0xFFFF);
}
//---------------------------------------------------------------------------

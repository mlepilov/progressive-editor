//Workspace: Progressive Editor
//File Name: SaveFunctions.cpp
#include <windows.h>
#include "ClassMap.h"
#include "ClassMapStructs.h"
//---------------------------------------------------------------------------
void MapClass::Save(LPSTR FileName, DWORD FileExt)
{
	if(CurrentMap)	// If there's a map open right now...
	{
		HANDLE TempHandle;		// Create a new handle
		char IsMpq = 0;			// "Is an mpq" variable
		HANDLE MpqHandle = NULL;// Create an mpq handle
		CloseHandle(CurrentMap);// Close & Destory last handle
		CurrentMap = NULL;

		memcpy(CurrentMapPath, FileName, MAX_PATH);	// Assigning new path as the current map path

		if(FileName == NULL)	// If it's "Save" instead of "Save As"...
		{
			memcpy(FileName, CurrentMapPath, MAX_PATH);	// Use current path to open map handle
			if(CurrentArchive)					// If an archive was opened as the original map (no change)...
				IsMpq = 1;						// Save it as an archive
		}
		else
		{
			if(FileExt == 1 || FileExt == 2)	// If the file extension chosen is "mpq", save it as an archive as well
				IsMpq = 1;
		}

		if(IsMpq)
		{
			MpqHandle = MpqOpenArchiveForUpdate(CurrentMapPath,
				MOAU_CREATE_ALWAYS | MOAU_MAINTAIN_LISTFILE, FilesInArchive);
			if(MpqHandle == INVALID_HANDLE_VALUE)
				AnnexEditMessage("I/O: WARNING!: Could not create mpq archive. See staredit/scenario.chk on the local drive for the saved .chk.");
			CreateDirectory("\\staredit", NULL);
			FileName = "\\staredit\\scenario.chk";
		}

		TempHandle = CreateFile((LPCTSTR)FileName, GENERIC_WRITE, FILE_SHARE_WRITE,
			NULL, CREATE_ALWAYS, NULL, NULL);

		CurrentMap = TempHandle;// Assigning the new handle as the current map handle

		DWORD TempNumOfBytesWritten;

		if(BWUsed > 0)
		{
			DWORD TempSectionLength = 4;
			LPSTR TempString = (LPSTR)malloc(5);
			if(BWUsed != 2)
				strcpy(TempString, "RAWS");
			else
				strcpy(TempString, "RAWB");

			WriteFile(TempHandle, "TYPE", 4, &TempNumOfBytesWritten, NULL);
			WriteFile(TempHandle, &TempSectionLength, 4, &TempNumOfBytesWritten, NULL);
			WriteFile(TempHandle, TempString, 4, &TempNumOfBytesWritten, NULL);

			free(TempString);
		}

		DWORD TempSectionLength = 2;
		short TempShort;
		if(BWUsed == 0)
			TempShort = 59;
		else if(BWUsed == 1)
			TempShort = 63;
		else if(BWUsed == 2)
			TempShort = 205;

		WriteFile(TempHandle, "VER ", 4, &TempNumOfBytesWritten, NULL);
		WriteFile(TempHandle, &TempSectionLength, 4, &TempNumOfBytesWritten, NULL);
		WriteFile(TempHandle, &TempShort, 2, &TempNumOfBytesWritten, NULL);

		if(0 == BWUsed)
		{
			DWORD TempSectionLength = 2;
			short TempShort = 10;

			WriteFile(TempHandle, "IVER", 4, &TempNumOfBytesWritten, NULL);
			WriteFile(TempHandle, &TempSectionLength, 4, &TempNumOfBytesWritten, NULL);
			WriteFile(TempHandle, &TempShort, 2, &TempNumOfBytesWritten, NULL);
		}
		if(0 != BWUsed)
		{
			DWORD TempSectionLength = 2;
			short TempShort = 11;

			WriteFile(TempHandle, "IVE2", 4, &TempNumOfBytesWritten, NULL);
			WriteFile(TempHandle, &TempSectionLength, 4, &TempNumOfBytesWritten, NULL);
			WriteFile(TempHandle, &TempShort, 2, &TempNumOfBytesWritten, NULL);
		}
		if(true == SectionInfo.preVCOD)
		{
			char* TempChrArray = sVcod.GetData();
		
			WriteFile(TempHandle, "VCOD", 4, &TempNumOfBytesWritten, NULL);
			WriteFile(TempHandle, &SectionInfo.slVCOD, 4, &TempNumOfBytesWritten, NULL);
			WriteFile(TempHandle, TempChrArray, 1040, &TempNumOfBytesWritten, NULL);
		}
		if(true == SectionInfo.preIOWN)
		{
			char* TempChrArray = sIown.GetDataArray();

			WriteFile(TempHandle, "IOWN", 4, &TempNumOfBytesWritten, NULL);
			WriteFile(TempHandle, &SectionInfo.slIOWN, 4, &TempNumOfBytesWritten, NULL);
			WriteFile(TempHandle, TempChrArray, 12, &TempNumOfBytesWritten, NULL);
		}
		if(true == SectionInfo.preOWNR)
		{
			char* TempChrArray = sOwnr.GetDataArray();

			WriteFile(TempHandle, "OWNR", 4, &TempNumOfBytesWritten, NULL);
			WriteFile(TempHandle, &SectionInfo.slOWNR, 4, &TempNumOfBytesWritten, NULL);
			WriteFile(TempHandle, TempChrArray, 12, &TempNumOfBytesWritten, NULL);
		}
		if(true == SectionInfo.preERA)
		{
			short TempShort = sEra.GetData();

			WriteFile(TempHandle, "ERA ", 4, &TempNumOfBytesWritten, NULL);
			WriteFile(TempHandle, &SectionInfo.slERA, 4, &TempNumOfBytesWritten, NULL);
			WriteFile(TempHandle, &TempShort, 2, &TempNumOfBytesWritten, NULL);
		}
		if(true == SectionInfo.preDIM)
		{
			short TempShort;

			WriteFile(TempHandle, "DIM ", 4, &TempNumOfBytesWritten, NULL);
			WriteFile(TempHandle, &SectionInfo.slDIM, 4, &TempNumOfBytesWritten, NULL);
			TempShort = sDim.GetData(0);
			WriteFile(TempHandle, &TempShort, 2, &TempNumOfBytesWritten, NULL);
			TempShort = sDim.GetData(1);
			WriteFile(TempHandle, &TempShort, 2, &TempNumOfBytesWritten, NULL);
		}
		if(true == SectionInfo.preSIDE)
		{
			char* TempChrArray = sSide.GetDataArray();

			WriteFile(TempHandle, "SIDE", 4, &TempNumOfBytesWritten, NULL);
			WriteFile(TempHandle, &SectionInfo.slSIDE, 4, &TempNumOfBytesWritten, NULL);
			WriteFile(TempHandle, TempChrArray, 12, &TempNumOfBytesWritten, NULL);
		}
		if(true == SectionInfo.preMTXM)
		{
			short* TempShortArray = sMtxm.GetDataArray();

			WriteFile(TempHandle, "MTXM", 4, &TempNumOfBytesWritten, NULL);
			WriteFile(TempHandle, &SectionInfo.slMTXM, 4, &TempNumOfBytesWritten, NULL);
			WriteFile(TempHandle, TempShortArray, sDim.GetData(0) * sDim.GetData(1) * 2,
				&TempNumOfBytesWritten, NULL);
		}
		if(true == SectionInfo.prePUNI)
		{
			char* TempChrArray;

			WriteFile(TempHandle, "PUNI", 4, &TempNumOfBytesWritten, NULL);
			WriteFile(TempHandle, &SectionInfo.slPUNI, 4, &TempNumOfBytesWritten, NULL);
			TempChrArray = sPuni.GetDataArray(0);
			WriteFile(TempHandle, TempChrArray, 2736, &TempNumOfBytesWritten, NULL);
			TempChrArray = sPuni.GetDataArray(1);
			WriteFile(TempHandle, TempChrArray, 228, &TempNumOfBytesWritten, NULL);
			TempChrArray = sPuni.GetDataArray(2);
			WriteFile(TempHandle, TempChrArray, 2736, &TempNumOfBytesWritten, NULL);
		}
		if(2 != BWUsed)
		{
			if(true == SectionInfo.preUPGR)
			{
				char* TempChrArray;

				WriteFile(TempHandle, "UPGR", 4, &TempNumOfBytesWritten, NULL);
				WriteFile(TempHandle, &SectionInfo.slUPGR, 4, &TempNumOfBytesWritten, NULL);
				TempChrArray = sUpgr.GetDataArray(0);
				WriteFile(TempHandle, TempChrArray, 552, &TempNumOfBytesWritten, NULL);
				TempChrArray = sUpgr.GetDataArray(1);
				WriteFile(TempHandle, TempChrArray, 552, &TempNumOfBytesWritten, NULL);
				TempChrArray = sUpgr.GetDataArray(2);
				WriteFile(TempHandle, TempChrArray, 46, &TempNumOfBytesWritten, NULL);
				TempChrArray = sUpgr.GetDataArray(3);
				WriteFile(TempHandle, TempChrArray, 46, &TempNumOfBytesWritten, NULL);
				TempChrArray = sUpgr.GetDataArray(4);
				WriteFile(TempHandle, TempChrArray, 552, &TempNumOfBytesWritten, NULL);
			}
		}
		if(2 != BWUsed)
		{
			if(true == SectionInfo.prePTEC)
			{
				char* TempChrArray;

				WriteFile(TempHandle, "PTEC", 4, &TempNumOfBytesWritten, NULL);
				WriteFile(TempHandle, &SectionInfo.slPTEC, 4, &TempNumOfBytesWritten, NULL);
				TempChrArray = sPtec.GetDataArray(0);
				WriteFile(TempHandle, TempChrArray, 288, &TempNumOfBytesWritten, NULL);
				TempChrArray = sPtec.GetDataArray(1);
				WriteFile(TempHandle, TempChrArray, 288, &TempNumOfBytesWritten, NULL);
				TempChrArray = sPtec.GetDataArray(2);
				WriteFile(TempHandle, TempChrArray, 24, &TempNumOfBytesWritten, NULL);
				TempChrArray = sPtec.GetDataArray(3);
				WriteFile(TempHandle, TempChrArray, 24, &TempNumOfBytesWritten, NULL);
				TempChrArray = sPtec.GetDataArray(4);
				WriteFile(TempHandle, TempChrArray, 288, &TempNumOfBytesWritten, NULL);
			}
		}
		if(true == SectionInfo.preUNIT)
		{
			UNIT_NODE* TempUnitNode = sUnit.GetData();
			DWORD TempSectionLength = sUnit.GetDataLength() * 36;

			WriteFile(TempHandle, "UNIT", 4, &TempNumOfBytesWritten, NULL);
			WriteFile(TempHandle, &TempSectionLength, 4, &TempNumOfBytesWritten, NULL);

			for(unsigned long i = 0; i < sUnit.GetDataLength(); i++)
			{
				WriteFile(TempHandle, &TempUnitNode->Unit, 36, &TempNumOfBytesWritten,
					NULL);

				TempUnitNode = TempUnitNode->Next;
			}
		}
		if(true == SectionInfo.preISOM)
		{
			RECT* TempRectArray = sIsom.GetDataArray();

			WriteFile(TempHandle, "ISOM", 4, &TempNumOfBytesWritten, NULL);
			WriteFile(TempHandle, &SectionInfo.slISOM, 4, &TempNumOfBytesWritten, NULL);
			for(long i = 0; i < (sDim.GetData(0) / 2 + 1) * (sDim.GetData(1) + 1); i++)
			{
				WriteFile(TempHandle, &TempRectArray[i].left, 2, &TempNumOfBytesWritten,
					NULL);
				WriteFile(TempHandle, &TempRectArray[i].top, 2, &TempNumOfBytesWritten,
					NULL);
				WriteFile(TempHandle, &TempRectArray[i].right, 2, &TempNumOfBytesWritten,
					NULL);
				WriteFile(TempHandle, &TempRectArray[i].bottom, 2, &TempNumOfBytesWritten,
					NULL);
			}
		}
		if(true == SectionInfo.preTILE)
		{
			short* TempShortArray = sTile.GetDataArray();

			WriteFile(TempHandle, "TILE", 4, &TempNumOfBytesWritten, NULL);
			WriteFile(TempHandle, &SectionInfo.slTILE, 4, &TempNumOfBytesWritten, NULL);
			WriteFile(TempHandle, TempShortArray, sDim.GetData(0) * sDim.GetData(1) * 2,
				&TempNumOfBytesWritten, NULL);
		}
		if(true == SectionInfo.preDD2)
		{
			DOODAD_UNIT_NODE* TempDd2Node = sDd2.GetData();
			DWORD TempSectionLength = sDd2.GetDataLength() * 8;

			WriteFile(TempHandle, "DD2 ", 4, &TempNumOfBytesWritten, NULL);
			WriteFile(TempHandle, &TempSectionLength, 4, &TempNumOfBytesWritten, NULL);

			for(unsigned long i = 0; i < sDd2.GetDataLength(); i++)
			{
				WriteFile(TempHandle, &TempDd2Node->DoodadUnit, 8, &TempNumOfBytesWritten,
					NULL);

				TempDd2Node = TempDd2Node->Next;
			}
		}
		if(true == SectionInfo.preTHG2)
		{
			DOODAD_SPRITE_NODE* TempThg2Node = sThg2.GetData();
			DWORD TempSectionLength = sThg2.GetDataLength() * 10;

			WriteFile(TempHandle, "THG2", 4, &TempNumOfBytesWritten, NULL);
			WriteFile(TempHandle, &TempSectionLength, 4, &TempNumOfBytesWritten, NULL);

			for(unsigned long i = 0; i < sThg2.GetDataLength(); i++)
			{
				WriteFile(TempHandle, &TempThg2Node->DoodadSprite, 10, &TempNumOfBytesWritten,
					NULL);

				TempThg2Node = TempThg2Node->Next;
			}
		}
		if(true == SectionInfo.preMASK)
		{
			char* TempChrArray = sMask.GetDataArray();

			WriteFile(TempHandle, "MASK", 4, &TempNumOfBytesWritten, NULL);
			WriteFile(TempHandle, &SectionInfo.slMASK, 4, &TempNumOfBytesWritten, NULL);
			WriteFile(TempHandle, TempChrArray, sDim.GetData(0) * sDim.GetData(1), 
				&TempNumOfBytesWritten, NULL);
		}
		if(true == SectionInfo.preSTR)
		{
			STRING* TempStrArray = sStr.GetDataArray();
			short TempDataLength = sStr.GetDataLength();
			unsigned short TempDefaultOffset = TempDataLength * 2 + 2;
			unsigned short TempDataOffset = TempDefaultOffset + 1;
			char Zero = 0;

			DWORD TempSectionLength = 0;
			for(int i = 0; i < TempDataLength; i++)
			{
				TempSectionLength = TempSectionLength + TempStrArray[i].Length;
			}
			TempSectionLength = TempSectionLength + (TempDataLength + 1) * 2 + 1; 

			WriteFile(TempHandle, "STR ", 4, &TempNumOfBytesWritten, NULL);
			WriteFile(TempHandle, &TempSectionLength, 4, &TempNumOfBytesWritten, NULL);
			WriteFile(TempHandle, &TempDataLength, 2, &TempNumOfBytesWritten, NULL);
			for(i = 0; i < TempDataLength; i++)
			{
				if(TempStrArray[i].Length > 0)
				{
					WriteFile(TempHandle, &TempDataOffset, 2, &TempNumOfBytesWritten, NULL);
					TempDataOffset = TempDataOffset + TempStrArray[i].Length;
				}
				else
				{
					WriteFile(TempHandle, &TempDefaultOffset, 2, &TempNumOfBytesWritten,
						NULL);
				}
			}
			WriteFile(TempHandle, &Zero, 1, &TempNumOfBytesWritten, NULL);
			for(i = 0; i < TempDataLength; i++)
			{
				WriteFile(TempHandle, &(*TempStrArray[i].Data), TempStrArray[i].Length,
					&TempNumOfBytesWritten, NULL);
			}
		}
		if(true == SectionInfo.preUPRP)
		{
			CUWPSLOT* TempUprpArray = sUprp.GetDataArray();

			WriteFile(TempHandle, "UPRP", 4, &TempNumOfBytesWritten, NULL);
			WriteFile(TempHandle, &SectionInfo.slUPRP, 4, &TempNumOfBytesWritten, NULL);
			WriteFile(TempHandle, TempUprpArray, 1280, &TempNumOfBytesWritten, NULL);
		}
		if(true == SectionInfo.preUPUS)
		{
			char* TempChrArray = sUpus.GetDataArray();

			WriteFile(TempHandle, "UPUS", 4, &TempNumOfBytesWritten, NULL);
			WriteFile(TempHandle, &SectionInfo.slUPUS, 4, &TempNumOfBytesWritten, NULL);
			WriteFile(TempHandle, TempChrArray, 64, &TempNumOfBytesWritten, NULL);
		}
		if(true == SectionInfo.preMRGN)
		{
			LOCATION* TempMrgnArray = sMrgn.GetDataArray();
			char BWBit = sMrgn.GetBWBit();

			WriteFile(TempHandle, "MRGN", 4, &TempNumOfBytesWritten, NULL);
			WriteFile(TempHandle, &SectionInfo.slMRGN, 4, &TempNumOfBytesWritten, NULL);
			if(0 == BWBit)
			{
				WriteFile(TempHandle, TempMrgnArray, 1280, &TempNumOfBytesWritten, NULL);
			}
			else
			{
				WriteFile(TempHandle, TempMrgnArray, 5100, &TempNumOfBytesWritten, NULL);
			}
		}
		if(true == SectionInfo.preTRIG)
		{
			TRIGGER_NODE* TempTrigNode = sTrig.GetData();
			DWORD TempSectionLength = sTrig.GetDataLength() * 2400;

			WriteFile(TempHandle, "TRIG", 4, &TempNumOfBytesWritten, NULL);
			WriteFile(TempHandle, &SectionInfo.slTRIG, 4, &TempNumOfBytesWritten, NULL);

			for(unsigned long i = 0; i < sTrig.GetDataLength(); i++)
			{
				WriteFile(TempHandle, &TempTrigNode->Trigger, 2400, &TempNumOfBytesWritten,
					NULL);

				TempTrigNode = TempTrigNode->Next;
			}
		}
		if(true == SectionInfo.preMBRF)
		{
			TRIGGER_NODE* TempTrigNode = sMbrf.GetData();
			DWORD TempSectionLength = sMbrf.GetDataLength() * 2400;

			WriteFile(TempHandle, "MBRF", 4, &TempNumOfBytesWritten, NULL);
			WriteFile(TempHandle, &SectionInfo.slMBRF, 4, &TempNumOfBytesWritten, NULL);

			for(unsigned long i = 0; i < sMbrf.GetDataLength(); i++)
			{
				WriteFile(TempHandle, &TempTrigNode->Trigger, 2400, &TempNumOfBytesWritten,
					NULL);

				TempTrigNode = TempTrigNode->Next;
			}
		}
		if(true == SectionInfo.preSPRP)
		{
			short TempShort;

			WriteFile(TempHandle, "SPRP", 4, &TempNumOfBytesWritten, NULL);
			WriteFile(TempHandle, &SectionInfo.slSPRP, 4, &TempNumOfBytesWritten, NULL);
			TempShort = sSprp.GetData(0);
			WriteFile(TempHandle, &TempShort, 2, &TempNumOfBytesWritten, NULL);
			TempShort = sSprp.GetData(1);
			WriteFile(TempHandle, &TempShort, 2, &TempNumOfBytesWritten, NULL);
		}
		if(true == SectionInfo.preFORC)
		{
			short TempShort;

			WriteFile(TempHandle, "FORC", 4, &TempNumOfBytesWritten, NULL);
			WriteFile(TempHandle, &SectionInfo.slFORC, 4, &TempNumOfBytesWritten, NULL);
			for(char i = 0; i < 8; i++)
			{
				TempShort = sForc.GetData(i);
				WriteFile(TempHandle, &TempShort, 1, &TempNumOfBytesWritten, NULL);
			}
			for(; i < 12; i++)
			{
				TempShort = sForc.GetData(i);
				WriteFile(TempHandle, &TempShort, 2, &TempNumOfBytesWritten, NULL);
			}
			for(; i < 16; i++)
			{
				TempShort = sForc.GetData(i);
				WriteFile(TempHandle, &TempShort, 1, &TempNumOfBytesWritten, NULL);
			}
		}
		if(true == SectionInfo.preWAV)
		{
			long* TempLongArray = sWav.GetDataArray();

			WriteFile(TempHandle, "WAV ", 4, &TempNumOfBytesWritten, NULL);
			WriteFile(TempHandle, &SectionInfo.slWAV, 4, &TempNumOfBytesWritten, NULL);
			WriteFile(TempHandle, TempLongArray, 2048, &TempNumOfBytesWritten, NULL);
		}
		if(2 != BWUsed)
		{
			if(true == SectionInfo.preUNIS)
			{
				LPVOID TempData;
				UNITSETTING* TempUSArray;

				WriteFile(TempHandle, "UNIS", 4, &TempNumOfBytesWritten, NULL);
				WriteFile(TempHandle, &SectionInfo.slUNIS, 4, &TempNumOfBytesWritten, NULL);
				TempData = sUnis.GetDataArray(0);
				WriteFile(TempHandle, TempData, 228, &TempNumOfBytesWritten, NULL);
				TempUSArray = (UNITSETTING*)sUnis.GetDataArray(1);
				for(BYTE i = 0; i < 228; i++)
				{
					WriteFile(TempHandle, &TempUSArray[i].Unknown, 1,
						&TempNumOfBytesWritten, NULL);
					WriteFile(TempHandle, &TempUSArray[i].HitPoints, 2,
						&TempNumOfBytesWritten, NULL);
					WriteFile(TempHandle, &TempUSArray[i].Invincible, 1,
						&TempNumOfBytesWritten, NULL);
				}
				TempData = sUnis.GetDataArray(2);
				WriteFile(TempHandle, TempData, 456, &TempNumOfBytesWritten, NULL);
				TempData = sUnis.GetDataArray(3);
				WriteFile(TempHandle, TempData, 228, &TempNumOfBytesWritten, NULL);
				TempData = sUnis.GetDataArray(4);
				WriteFile(TempHandle, TempData, 456, &TempNumOfBytesWritten, NULL);
				TempData = sUnis.GetDataArray(5);
				WriteFile(TempHandle, TempData, 456, &TempNumOfBytesWritten, NULL);
				TempData = sUnis.GetDataArray(6);
				WriteFile(TempHandle, TempData, 456, &TempNumOfBytesWritten, NULL);
				TempData = sUnis.GetDataArray(7);
				WriteFile(TempHandle, TempData, 456, &TempNumOfBytesWritten, NULL);
				TempData = sUnis.GetDataArray(8);
				WriteFile(TempHandle, TempData, 200, &TempNumOfBytesWritten, NULL);
				TempData = sUnis.GetDataArray(9);
				WriteFile(TempHandle, TempData, 200, &TempNumOfBytesWritten, NULL);
			}
		}
		if(2 != BWUsed)
		{
			if(true == SectionInfo.preUPGS)
			{
				LPVOID TempData;

				WriteFile(TempHandle, "UPGS", 4, &TempNumOfBytesWritten, NULL);
				WriteFile(TempHandle, &SectionInfo.slUPGS, 4, &TempNumOfBytesWritten, NULL);
				TempData = sUpgs.GetDataArray(0);
				WriteFile(TempHandle, TempData, 46, &TempNumOfBytesWritten, NULL);
				TempData = sUpgs.GetDataArray(1);
				WriteFile(TempHandle, TempData, 92, &TempNumOfBytesWritten, NULL);
				TempData = sUpgs.GetDataArray(2);
				WriteFile(TempHandle, TempData, 92, &TempNumOfBytesWritten, NULL);
				TempData = sUpgs.GetDataArray(3);
				WriteFile(TempHandle, TempData, 92, &TempNumOfBytesWritten, NULL);
				TempData = sUpgs.GetDataArray(4);
				WriteFile(TempHandle, TempData, 92, &TempNumOfBytesWritten, NULL);
				TempData = sUpgs.GetDataArray(5);
				WriteFile(TempHandle, TempData, 92, &TempNumOfBytesWritten, NULL);
				TempData = sUpgs.GetDataArray(6);
				WriteFile(TempHandle, TempData, 92, &TempNumOfBytesWritten, NULL);
			}
		}
		if(2 != BWUsed)
		{
			if(true == SectionInfo.preTECS)
			{
				LPVOID TempData;

				WriteFile(TempHandle, "TECS", 4, &TempNumOfBytesWritten, NULL);
				WriteFile(TempHandle, &SectionInfo.slTECS, 4, &TempNumOfBytesWritten, NULL);
				TempData = sTecs.GetDataArray(0);
				WriteFile(TempHandle, TempData, 24, &TempNumOfBytesWritten, NULL);
				TempData = sTecs.GetDataArray(1);
				WriteFile(TempHandle, TempData, 48, &TempNumOfBytesWritten, NULL);
				TempData = sTecs.GetDataArray(2);
				WriteFile(TempHandle, TempData, 48, &TempNumOfBytesWritten, NULL);
				TempData = sTecs.GetDataArray(3);
				WriteFile(TempHandle, TempData, 48, &TempNumOfBytesWritten, NULL);
				TempData = sTecs.GetDataArray(4);
				WriteFile(TempHandle, TempData, 48, &TempNumOfBytesWritten, NULL);
			}
		}
		if(true == SectionInfo.preSWNM)
		{
			long* TempLongData = sSwnm.GetDataArray();

			WriteFile(TempHandle, "SWNM", 4, &TempNumOfBytesWritten, NULL);
			WriteFile(TempHandle, &SectionInfo.slSWNM, 4, &TempNumOfBytesWritten, NULL);
			WriteFile(TempHandle, TempLongData, 1024, &TempNumOfBytesWritten, NULL);
		}
		if(true == SectionInfo.preCOLR)
		{
			char TempChar;

			WriteFile(TempHandle, "COLR", 4, &TempNumOfBytesWritten, NULL);
			WriteFile(TempHandle, &SectionInfo.slCOLR, 4, &TempNumOfBytesWritten, NULL);
			for(char i = 0; i < 8; i++)
			{
				TempChar = sColr.GetData(i);
				WriteFile(TempHandle, &TempChar, 1, &TempNumOfBytesWritten, NULL);
			}
		}
		if(0 != BWUsed)
		{
			if(true == SectionInfo.prePUPx)
			{
				char* TempChrArray;

				WriteFile(TempHandle, "PUPx", 4, &TempNumOfBytesWritten, NULL);
				WriteFile(TempHandle, &SectionInfo.slPUPx, 4, &TempNumOfBytesWritten, NULL);
				TempChrArray = sPupX.GetDataArray(0);
				WriteFile(TempHandle, TempChrArray, 732, &TempNumOfBytesWritten, NULL);
				TempChrArray = sPupX.GetDataArray(1);
				WriteFile(TempHandle, TempChrArray, 732, &TempNumOfBytesWritten, NULL);
				TempChrArray = sPupX.GetDataArray(2);
				WriteFile(TempHandle, TempChrArray, 61, &TempNumOfBytesWritten, NULL);
				TempChrArray = sPupX.GetDataArray(3);
				WriteFile(TempHandle, TempChrArray, 61, &TempNumOfBytesWritten, NULL);
				TempChrArray = sPupX.GetDataArray(4);
				WriteFile(TempHandle, TempChrArray, 732, &TempNumOfBytesWritten, NULL);
			}
		}
		if(0 != BWUsed)
		{
			if(true == SectionInfo.prePTEx)
			{
				char* TempChrArray;

				WriteFile(TempHandle, "PTEx", 4, &TempNumOfBytesWritten, NULL);
				WriteFile(TempHandle, &SectionInfo.slPTEx, 4, &TempNumOfBytesWritten, NULL);
				TempChrArray = sPteX.GetDataArray(0);
				WriteFile(TempHandle, TempChrArray, 528, &TempNumOfBytesWritten, NULL);
				TempChrArray = sPteX.GetDataArray(1);
				WriteFile(TempHandle, TempChrArray, 528, &TempNumOfBytesWritten, NULL);
				TempChrArray = sPteX.GetDataArray(2);
				WriteFile(TempHandle, TempChrArray, 44, &TempNumOfBytesWritten, NULL);
				TempChrArray = sPteX.GetDataArray(3);
				WriteFile(TempHandle, TempChrArray, 44, &TempNumOfBytesWritten, NULL);
				TempChrArray = sPteX.GetDataArray(4);
				WriteFile(TempHandle, TempChrArray, 528, &TempNumOfBytesWritten, NULL);
			}
		}
		if(0 != BWUsed)
		{
			if(true == SectionInfo.preUNIx)
			{
				LPVOID TempData;
				UNITSETTING* TempUSArray;

				WriteFile(TempHandle, "UNIx", 4, &TempNumOfBytesWritten, NULL);
				WriteFile(TempHandle, &SectionInfo.slUNIx, 4, &TempNumOfBytesWritten, NULL);
				TempData = sUniX.GetDataArray(0);
				WriteFile(TempHandle, TempData, 228, &TempNumOfBytesWritten, NULL);
				TempUSArray = (UNITSETTING*)sUniX.GetDataArray(1);
				for(BYTE i = 0; i < 228; i++)
				{
					WriteFile(TempHandle, &TempUSArray[i].Unknown, 1,
						&TempNumOfBytesWritten, NULL);
					WriteFile(TempHandle, &TempUSArray[i].HitPoints, 2,
						&TempNumOfBytesWritten, NULL);
					WriteFile(TempHandle, &TempUSArray[i].Invincible, 1,
						&TempNumOfBytesWritten, NULL);
				}
				TempData = sUniX.GetDataArray(2);
				WriteFile(TempHandle, TempData, 456, &TempNumOfBytesWritten, NULL);
				TempData = sUniX.GetDataArray(3);
				WriteFile(TempHandle, TempData, 228, &TempNumOfBytesWritten, NULL);
				TempData = sUniX.GetDataArray(4);
				WriteFile(TempHandle, TempData, 456, &TempNumOfBytesWritten, NULL);
				TempData = sUniX.GetDataArray(5);
				WriteFile(TempHandle, TempData, 456, &TempNumOfBytesWritten, NULL);
				TempData = sUniX.GetDataArray(6);
				WriteFile(TempHandle, TempData, 456, &TempNumOfBytesWritten, NULL);
				TempData = sUniX.GetDataArray(7);
				WriteFile(TempHandle, TempData, 456, &TempNumOfBytesWritten, NULL);
				TempData = sUniX.GetDataArray(8);
				WriteFile(TempHandle, TempData, 260, &TempNumOfBytesWritten, NULL);
				TempData = sUniX.GetDataArray(9);
				WriteFile(TempHandle, TempData, 260, &TempNumOfBytesWritten, NULL);
			}
		}
		if(0 != BWUsed)
		{
			if(true == SectionInfo.preUPGx)
			{
				LPVOID TempData;
				char Zero = 0;

				WriteFile(TempHandle, "UPGx", 4, &TempNumOfBytesWritten, NULL);
				WriteFile(TempHandle, &SectionInfo.slUPGx, 4, &TempNumOfBytesWritten, NULL);
				TempData = sUpgX.GetDataArray(0);
				WriteFile(TempHandle, TempData, 61, &TempNumOfBytesWritten, NULL);
				WriteFile(TempHandle, &Zero, 1, &TempNumOfBytesWritten, NULL);
				TempData = sUpgX.GetDataArray(1);
				WriteFile(TempHandle, TempData, 122, &TempNumOfBytesWritten, NULL);
				TempData = sUpgX.GetDataArray(2);
				WriteFile(TempHandle, TempData, 122, &TempNumOfBytesWritten, NULL);
				TempData = sUpgX.GetDataArray(3);
				WriteFile(TempHandle, TempData, 122, &TempNumOfBytesWritten, NULL);
				TempData = sUpgX.GetDataArray(4);
				WriteFile(TempHandle, TempData, 122, &TempNumOfBytesWritten, NULL);
				TempData = sUpgX.GetDataArray(5);
				WriteFile(TempHandle, TempData, 122, &TempNumOfBytesWritten, NULL);
				TempData = sUpgX.GetDataArray(6);
				WriteFile(TempHandle, TempData, 122, &TempNumOfBytesWritten, NULL);
			}
		}
		if(0 != BWUsed)
		{
			if(true == SectionInfo.preTECx)
			{
				LPVOID TempData;

				WriteFile(TempHandle, "TECx", 4, &TempNumOfBytesWritten, NULL);
				WriteFile(TempHandle, &SectionInfo.slTECx, 4, &TempNumOfBytesWritten, NULL);
				TempData = sTecX.GetDataArray(0);
				WriteFile(TempHandle, TempData, 44, &TempNumOfBytesWritten, NULL);
				TempData = sTecX.GetDataArray(1);
				WriteFile(TempHandle, TempData, 88, &TempNumOfBytesWritten, NULL);
				TempData = sTecX.GetDataArray(2);
				WriteFile(TempHandle, TempData, 88, &TempNumOfBytesWritten, NULL);
				TempData = sTecX.GetDataArray(3);
				WriteFile(TempHandle, TempData, 88, &TempNumOfBytesWritten, NULL);
				TempData = sTecX.GetDataArray(4);
				WriteFile(TempHandle, TempData, 88, &TempNumOfBytesWritten, NULL);
			}
		}

		CloseHandle(TempHandle);

		if(MpqHandle != NULL && MpqHandle != INVALID_HANDLE_VALUE)
		{
			MpqAddFileToArchive(MpqHandle, FileName, "staredit\\scenario.chk", MAFA_COMPRESS | MAFA_REPLACE_EXISTING);
			MpqCloseUpdatedArchive(MpqHandle, NULL);
		}
	}
}
//---------------------------------------------------------------------------
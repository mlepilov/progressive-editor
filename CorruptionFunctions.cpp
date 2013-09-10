//Workspace: Progressive Editor
//File Name: CorruptionFunctions.cpp
#include <windows.h>
#include "ClassMap.h"
#include "ClassMapStructs.h"
//---------------------------------------------------------------------------
BYTE MapClass::Detect()
{
	BYTE ReturnValue = 0;

	// CONDITIONAL VALUES (stuff that deals with strings, TILE, and ISOM):
	// "Inflate Strings" conditional value
	if(SectionInfo.preSTR)
	{
		if(sStr.GetDataLength() == 1024)
		{
			Corruption.Strings1024 = true;
			ReturnValue = ReturnValue | 0x01;
			AnnexEditMessage("DETECT: Cannot normalize strings: proper string number reached.\r\n");
		}
		else
		{
			Corruption.Strings1024 = false;
		}
	}
	// "Use Old Switches" internal conditional value
	if(SectionInfo.preSWNM)
	{
		long TempData;
		Corruption.SwitchesMessed = false;
		for(short i = 0; i < 256; i++)
		{
			TempData = sSwnm.GetData(i);
			if(TempData < 0 || TempData > sStr.GetDataLength())
			{
				sSwnm.SetData((long)0, i);
				Corruption.SwitchesMessed = true;
			}
		}
		if(Corruption.SwitchesMessed)
			AnnexEditMessage("DETECT: Some switch names may have been destroyed; reverting to 0.\r\n");
	}
	else
	{
		ReturnValue = ReturnValue | 0x02;
		AnnexEditMessage("DETECT: Cannot use old switch names: SWNM section not found; will rebuild.\r\n");
	}
	// "Use Old Locations" internal conditional value
	if(SectionInfo.preMRGN)
	{
		LOCATION TempData;
		Corruption.LocationsMessed = false;
		if(BWUsed == 0)
		{
			for(BYTE i = 0; i < 64; i++)
			{
				TempData = sMrgn.GetData(i);
				if(TempData.StringNumber < 0 ||
					TempData.StringNumber > sStr.GetDataLength())
				{
					Corruption.LocationsMessed = true;
					sMrgn.SetData(i, (long)0, 4);
				}
			}
		}
		else
		{
			for(short i = 0; i < 256; i++)
			{
				TempData = sMrgn.GetData((WORD)i);
				if(TempData.StringNumber < 0 ||
					TempData.StringNumber > sStr.GetDataLength())
				{
					Corruption.LocationsMessed = true;
					sMrgn.SetData((BYTE)i, (long)0, 4);
				}
			}
		}
		if(Corruption.LocationsMessed)
			AnnexEditMessage("DETECT: Some location names may have been destroyed; reverting to 0.\r\n");
	}
	// "Use Old Units" internal conditional value
	if(SectionInfo.preUNIS && BWUsed != 2)
	{
		short TempData;
		Corruption.UnitsMessed = false;
		for(BYTE i = 0; i < 228; i++)
		{
			TempData = (short)sUnis.GetData(i, 9);
			if(TempData < 0 || TempData > sStr.GetDataLength())
			{
				sUnis.SetData(i, (LPVOID)0, 9);
				Corruption.UnitsMessed = true;
			}
		}
	}
	if(SectionInfo.preUNIx && BWUsed != 0)
	{
		short TempData;
		Corruption.UnitsMessed = false;
		for(BYTE i = 0; i < 228; i++)
		{
			TempData = (short)sUniX.GetData(i, 9);
			if(TempData < 0 || TempData > sStr.GetDataLength())
			{
				sUnis.SetData(i, (LPVOID)0, 9);
				Corruption.UnitsMessed = true;
			}
		}
	}
	if(Corruption.UnitsMessed)
		AnnexEditMessage("DETECT: Some unit names may have been destroyed; reverting to 0.\r\n");

	// "Delete Comments" internal conditional value
	/*if(sTrig.GetDataLength() == 0)
	{
		ReturnValue = ReturnValue | 4;
		Corruption.DeleteComments = false;
		AnnexEditMessage("DETECT: Cannot delete comments: no triggers present.\r\n");
	}
	else
	{
		Corruption.DeleteComments = false;
		for(DWORD i = 0; i < sTrig.GetDataLength(); i++)
		{
			for(char i2 = 0; i2 < 64; i2++)
			{
				if(sTrig.GetData(i).Actions[i2].Action == 47)
				{
					Corruption.DeleteComments = true;
					break;
				}
			}
			if(Corruption.DeleteComments)
				break;
		}
		if(!Corruption.DeleteComments)
		{
			ReturnValue = ReturnValue | 4;
			AnnexEditMessage("DETECT: Cannot delete comments: no comment triggers present.\r\n");
		}
	}*/

	if(SectionInfo.slISOM != (DWORD)((sDim.GetData(0) / 2) + 1) * (sDim.GetData(1) + 1) * 8)
	{
		ReturnValue = ReturnValue | 8;
		Corruption.FakeISOM = true;
		AnnexEditMessage("DETECT: The ISOM section is corrupt; will fake.\r\n");
	}

	//TODO: Add in advanced detection of MTXM/TILE correspondence via doodad data/differences
	if(SectionInfo.slTILE != (DWORD)sDim.GetData(0) * sDim.GetData(1) * 2)
	{
		ReturnValue = ReturnValue | 16;
		Corruption.RebuildTILE = true;
		AnnexEditMessage("DETECT: The TILE section is corrupt; will rebuild.\r\n");
	}
	
	return ReturnValue;
}
//---------------------------------------------------------------------------
char MapClass::Repair(BYTE Settings)
{
	//TODO: DD2, TILE, WAV, MASK (UMS), UPRP (UMS), UPUS, MRGN (UMS), TRIG (UMS),
	// MBRF (if none), SWNM, strings (switch, location, unit, wav)

	// -- DETECTING MINIMAL SECTIONS (most necessary sections) --
	if(SectionInfo.preOWNR == false)
	{
		AnnexEditMessage("REPAIR: OWNR not found; could not repair.\r\n");
		return 0;
	}
	if(SectionInfo.preERA == false)
	{
		AnnexEditMessage("REPAIR: ERA not found; could not repair.\r\n");
		return 0;
	}
	if(SectionInfo.preSIDE == false)
	{
		AnnexEditMessage("REPAIR: SIDE not found; could not repair.\r\n");
		return 0;
	}
	if(SectionInfo.preMTXM == false)
	{
		AnnexEditMessage("REPAIR: MTXM not found; could not repair.\r\n");
		return 0;
	}
	if(SectionInfo.prePUNI == false)
	{
		AnnexEditMessage("REPAIR: PUNI not found; could not repair.\r\n");
		return 0;
	}
	if(SectionInfo.preUNIT == false)
	{
		AnnexEditMessage("REPAIR: UNIT not found; could not repair.\r\n");
		return 0;
	}
	if(SectionInfo.preTHG2 == false)
	{
		AnnexEditMessage("REPAIR: THG2 not found; could not repair.\r\n");
		return 0;
	}
	if(SectionInfo.preSPRP == false)
	{
		AnnexEditMessage("REPAIR: SPRP not found; could not repair.\r\n");
		return 0;
	}
	if(SectionInfo.preFORC == false)
	{
		AnnexEditMessage("REPAIR: FORC not found; could not repair.\r\n");
		return 0;
	}
	if(BWUsed != 2 && SectionInfo.preCOLR == false)
	{
		AnnexEditMessage("REPAIR: COLR not found; could not repair.\r\n");
		return 0;
	}
	if(BWUsed != 2 && SectionInfo.preUPGR == false)
	{
		if(BWUsed == 0)
		{
			AnnexEditMessage("REPAIR: UPGR not found; could not repair.\r\n");
			return 0;
		}
		else if(BWUsed == 1 && SectionInfo.prePUPx == false)
		{
			AnnexEditMessage("REPAIR: UPGR/PUPx not found; could not repair.\r\n");
			return 0;
		}
	}
	else if(BWUsed == 2 && SectionInfo.prePUPx == false)
	{
		AnnexEditMessage("REPAIR: PUPx not found; could not repair.\r\n");
		return 0;
	}
	if(BWUsed != 2 && SectionInfo.prePTEC == false)
	{
		if(BWUsed == 0)
		{
			AnnexEditMessage("REPAIR: PTEC not found; could not repair.\r\n");
			return 0;
		}
		else if(BWUsed == 1 && SectionInfo.prePTEx == false)
		{
			AnnexEditMessage("REPAIR: PTEC/PTEx not found; could not repair.\r\n");
			return 0;
		}
	}
	else if(BWUsed == 2 && SectionInfo.prePTEx == false)
	{
		AnnexEditMessage("REPAIR: PTEx not found; could not repair.\r\n");
		return 0;
	}
	if(BWUsed != 2 && SectionInfo.preUNIS == false)
	{
		if(BWUsed == 0)
		{
			AnnexEditMessage("REPAIR: UNIS not found; could not repair.\r\n");
			return 0;
		}
		else if(BWUsed == 1 && SectionInfo.preUNIx == false)
		{
			AnnexEditMessage("REPAIR: UNIT/UNIx not found; could not repair.\r\n");
			return 0;
		}
	}
	else if(BWUsed == 2 && SectionInfo.preUNIx == false)
	{
		AnnexEditMessage("REPAIR: UNIx not found; could not repair.\r\n");
		return 0;
	}
	if(BWUsed != 2 && SectionInfo.preUPGS == false)
	{
		if(BWUsed == 0)
		{
			AnnexEditMessage("REPAIR: UPGS not found; could not repair.\r\n");
			return 0;
		}
		else if(BWUsed == 1 && SectionInfo.preUPGx == false)
		{
			AnnexEditMessage("REPAIR: UPGS/UPGx not found; could not repair.\r\n");
			return 0;
		}
	}
	else if(BWUsed == 2 && SectionInfo.preUPGx == false)
	{
		AnnexEditMessage("REPAIR: UPGx not found; could not repair.\r\n");
		return 0;
	}
	if(BWUsed != 2 && SectionInfo.preTECS == false)
	{
		if(BWUsed == 0)
		{
			AnnexEditMessage("REPAIR: TECS not found; could not repair.\r\n");
			return 0;
		}
		else if(BWUsed == 1 && SectionInfo.preTECx == false)
		{
			AnnexEditMessage("REPAIR: TECS/TECx not found; could not repair.\r\n");
			return 0;
		}
	}
	else if(BWUsed == 2 && SectionInfo.preTECx == false)
	{
		AnnexEditMessage("REPAIR: TECx not found; could not repair.\r\n");
		return 0;
	}

	// -- RESTORING MISSING SECTIONS --
	// Restoring IOWN by copying OWNR values
	char* ChrArray = (char*)malloc(12);
	memcpy(ChrArray, sOwnr.GetDataArray(), 12);
	sIown.CopyData(ChrArray);
	AnnexEditMessage("REPAIR: OWNR values copied to IOWN.\r\n");

	// Restoring VCOD by copying locally retrieved VCOD.bin
	ChrArray = (char*)realloc(ChrArray, 1040);
	memcpy(ChrArray, m_pLocalFileData->VCODbin, 1040);
	sVcod.SetData(ChrArray);
	AnnexEditMessage("REPAIR: Set regular VCOD values.\r\n");

	free(ChrArray);

	return 1;
}
//---------------------------------------------------------------------------
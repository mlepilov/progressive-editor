//Workspace Name: Progressive Editor
//File Name: StringFunctions.cpp
#include "StringFunctions.h"
#include "ClassMap.h"
//---------------------------------------------------------------------------
// This is the function used to read and classify strings, defined in
// StringFunctions.h
//---------------------------------------------------------------------------
STRING* ProcessStringChunk(LPVOID StringChunk, unsigned long SectionLength)
{
	unsigned short TotalStrings = ((short*)(StringChunk))[0];
	unsigned short TempMin;
	unsigned short TempMax;
	STRING* TempStringArray = (STRING*)malloc(TotalStrings * sizeof(STRING));

	// The loop which processes every string but the last one (which requires
	// SectionLength to process instead of the next largest offset)
	for(int i = 0; i < TotalStrings - 1; i++)
	{
		// If the offset points to an actual string
		if(((unsigned short*)(StringChunk))[i + 1] >= TotalStrings * 2 + 2 &&
			((unsigned short*)(StringChunk))[i + 1] < SectionLength)
		{
			TempMin = ((unsigned short*)(StringChunk))[i + 1];
			TempMax = (unsigned short)SectionLength;

			TempStringArray[i].Offset = ((unsigned short*)(StringChunk))[i + 1];

			// Searching for the next largest offset to find the length
			for(int i2 = 0; i2 < TotalStrings; i2++)
			{
				if(((unsigned short*)(StringChunk))[i2 + 1] < TempMax &&
					((unsigned short*)(StringChunk))[i2 + 1] > TempMin)
				{
					TempMax = ((unsigned short*)(StringChunk))[i2 + 1];
				}
			}

			// TODO: Clean this crap up
			TempStringArray[i].Length = TempMax - TempMin;
			if(TempStringArray[i].Length != 1)
			{
				TempStringArray[i].Data = (LPSTR)malloc(TempStringArray[i].Length);
				memcpy(TempStringArray[i].Data,
					&((char*)(StringChunk))[TempStringArray[i].Offset], TempStringArray[i].Length);
			}
			else
			{
				TempStringArray[i].Length = 0;
				TempStringArray[i].Data = NULL;
			}
		}
		// If the offset is pointing to the beginning of the string chunk or is
		// greater than the section length (PROEdit 1.4.1 and on), offset is set
		// to default and length is set to zero
		else
		{
			TempStringArray[i].Offset = TotalStrings * 2 + 2;
			TempStringArray[i].Length = 0;
			TempStringArray[i].Data = NULL;
		}
	}
	// The conditions almost identical to the ones above to process the last string
	if(((unsigned short*)(StringChunk))[(TotalStrings - 1) + 1] > TotalStrings * 2 + 2 &&
		((unsigned short*)(StringChunk))[(TotalStrings - 1) + 1] < SectionLength)
	{
		TempStringArray[TotalStrings - 1].Offset =
			((unsigned short*)(StringChunk))[(TotalStrings - 1) + 1];
		TempStringArray[TotalStrings - 1].Length =
			(unsigned short)SectionLength - TempStringArray[TotalStrings - 1].Offset;
		TempStringArray[TotalStrings - 1].Data = (LPSTR)malloc(
			TempStringArray[TotalStrings - 1].Length);
		memcpy(TempStringArray[TotalStrings - 1].Data,
			&((char*)(StringChunk))[TempStringArray[TotalStrings - 1].Offset], TempStringArray[TotalStrings - 1].Length);
	}
	else
	{
		TempStringArray[TotalStrings - 1].Offset = TotalStrings * 2 + 2;
		TempStringArray[TotalStrings - 1].Length = 0;
		TempStringArray[TotalStrings - 1].Data = NULL;
	}

	return TempStringArray;
}
//---------------------------------------------------------------------------
// This is where methods dealing with strings for MapClass are defined.
//---------------------------------------------------------------------------
void MapClass::DetectStringUsage(WORD String)
{
	unsigned short i = 0;
	unsigned short Max = sStr.GetDataLength();

	if(String != 0xFFFF)
	{
		i = String;
		Max = String + 1;
	}

	// Here is where string usage is determined
	for(; i < Max; i++)
	{
		// Defaults to 0 ("Not Used")
		sStr.SetData(i, 0, NULL, 0);

		unsigned long i2;
		char i3;

		// Location strings...
		if(SectionInfo.preMRGN)
		{
			LOCATION TempLocation;
			if(sMrgn.GetBWBit() == 1)
			{
				for(i2 = 0; i2 < 256; i2++)
				{
					TempLocation = sMrgn.GetData(i2);

					if(TempLocation.StringNumber - 1 == i)
					{
						sStr.SetData(i, 1, NULL, 0);
						break;
					}
				}
			}
			else
			{
				for(i2 = 0; i2 < 64; i2++)
				{
					TempLocation = sMrgn.GetData(i2);

					if(TempLocation.StringNumber - 1 == i)
					{
						sStr.SetData(i, 1, NULL, 0);
						break;
					}
				}
			}
		}

		// Unit renaming strings...
		if(BWUsed == 0)
		{
			if(SectionInfo.preUNIS)
			{
				for(i2 = 0; i2 < 228; i2++)
				{
					if((unsigned short)(sUnis.GetData(i2, 9)) - 1 == i)
					{
						sStr.SetData(i, 1, NULL, 0);
						break;
					}
				}
			}
		}
		else
		{
			if(SectionInfo.preUNIx)
			{
				for(i2 = 0; i2 < 228; i2++)
				{
					if((unsigned short)(sUniX.GetData(i2, 9)) - 1 == i)
					{
						sStr.SetData(i, 1, NULL, 0);
						break;
					}
				}
			}
		}

		// Map description/title strings...
		if(SectionInfo.preSPRP)
		{
			if(sSprp.GetData(0) - 1 == i || sSprp.GetData(1) - 1 == i)
				sStr.SetData(i, 1, NULL, 0);
		}

		// Force name strings...
		if(SectionInfo.preFORC)
		{
			for(i2 = 8; i2 < 12; i2++)
			{
				if(sForc.GetData(i2) - 1 == i)
				{
					sStr.SetData(i, 1, NULL, 0);
					break;
				}
			}
		}

		// WAV path strings...
		if(SectionInfo.preWAV)
		{
			for(i2 = 0; i2 < 512; i2++)
			{
				if(sWav.GetData(i2) - 1 == i)
				{
					sStr.SetData(i, 1, NULL, 0);
					break;
				}
			}
		}

		// Switch name strings...
		if(SectionInfo.preSWNM)
		{
			for(i2 = 0; i2 < 256; i2++)
			{
				if(sSwnm.GetData(i2) - 1 == i)
				{
					sStr.SetData(i, 1, NULL, 0);
					break;
				}
			}
		}

		// Various trigger strings...
		if(SectionInfo.preTRIG)
		{
			TRIGGER_NODE* TempTrigger = sTrig.GetData();

			for(i2 = 0; i2 < sTrig.GetDataLength(); i2++)
			{
				if(sStr.GetData(i).Used)	// Put this here because sometimes
					break;					// it takes a LONG time to get through
											// the triggers
				for(i3 = 0; i3 < 64; i3++)
				{
					if(TempTrigger->Trigger.Actions[i3].Value2 - 1 == i ||
						TempTrigger->Trigger.Actions[i3].Value3 - 1 == i &&
						(TempTrigger->Trigger.Actions[i3].Value10 & 2) == 0)
					{
						sStr.SetData(i, 1, NULL, 0);
						break;
					}
				}

				TempTrigger = TempTrigger->Next;
			}
		}

		// Various mission briefing strings...
		if(SectionInfo.preMBRF)
		{
			TRIGGER_NODE* TempMBRF = sMbrf.GetData();

			for(i2 = 0; i2 < sMbrf.GetDataLength(); i2++)
			{
				if(sStr.GetData(i).Used)	// The same goes for mission briefings
					break;					// (look above to the TRIG comment)

				for(i3 = 0; i3 < 64; i3++)
				{
					if(TempMBRF->Trigger.Actions[i3].Value2 - 1 == i ||
						TempMBRF->Trigger.Actions[i3].Value3 - 1 == i &&
						(TempMBRF->Trigger.Actions[i3].Value10 & 2) == 0)
					{
						sStr.SetData(i, 1, NULL, 0);
						break;
					}
				}

				TempMBRF = TempMBRF->Next;
			}
		}
	}

	// The following is for DEBUG PURPOSES ONLY
	/*STRING* TempStrings = sStr.GetDataArray();

	for(i = 0; i < sStr.GetDataLength(); i++)
	{
		if(TempStrings[i].Used == 0)
		{
			TempStrings = TempStrings;
		}
	}*/
}
//---------------------------------------------------------------------------
WORD MapClass::AddString(LPSTR String)
{
	for(WORD i = 0; i < sStr.GetDataLength(); i++)
	{
		if(!strcmp(String, sStr.GetDataArray()[i].Data))
		{
			sStr.SetData(i, 1, NULL, 0);
			return i;
		}
	}

	for(i = 0; i < sStr.GetDataLength(); i++)
	{
		if(sStr.GetData(i).Used == 0)
		{
			sStr.SetData(i, NULL, String, 2);
			sStr.SetData(i, 1, NULL, 0);
			return i;
		}
	}

	sStr.SetData(NULL, sStr.GetDataLength() + 1, NULL, 3);
	sStr.SetData(sStr.GetDataLength() - 1, NULL, String, 2);
	sStr.SetData(sStr.GetDataLength() - 1, 1, NULL, 0);

	return sStr.GetDataLength() - 1;
}
//---------------------------------------------------------------------------
void MapClass::DeleteString(WORD String)
{
	DetectStringUsage(String);

	if(!sStr.GetDataArray()[String].Used)
		sStr.SetData(String, NULL, "", 2);
}
//---------------------------------------------------------------------------
WORD MapClass::EditString(LPSTR NewString, WORD String)
{
	if(!strcmp(NewString, sStr.GetDataArray()[String].Data))
		return String;

	DetectStringUsage(String);

	if(!sStr.GetDataArray()[String].Used)
	{
		sStr.SetData(String, NULL, NewString, 2);
		return String;
	}

	return AddString(NewString);
}
//---------------------------------------------------------------------------
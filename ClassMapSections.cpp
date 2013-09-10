//Workspace Name: Progressive Editor
//File Name: ClassMapSections.cpp
#include "ClassMapSections.h"
//---------------------------------------------------------------------------
//--Specific Section Methods--
//---------------------------------------------------------------------------
// They're all pretty self-explanatory except for the linked lists ones and
// sSTR. See StringFunctions.cpp for string comments and sUNIT below for
// linked list comments. The upgrade sections and TRIG/MBRF have common
// classes.
//---------------------------------------------------------------------------
void sTYPE::SetData(LPSTR String)
{
	TypeString = (LPSTR)malloc(5);
	strcpy(TypeString, String);
}
//---------------------------------------------------------------------------
LPSTR sTYPE::GetData()
{
	return TypeString;
}
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
void sVER::SetData(short Short)
{
	VerShrt = Short;
}
//---------------------------------------------------------------------------
short sVER::GetData()
{
	return VerShrt;
}
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
void sIVER::SetData(short Short)
{
	IverShrt = Short;
}
//---------------------------------------------------------------------------
short sIVER::GetData()
{
	return IverShrt;
}
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
void sIVE2::SetData(short Short)
{
	Ive2Shrt = Short;
}
//---------------------------------------------------------------------------
short sIVE2::GetData()
{
	return Ive2Shrt;
}
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
void sVCOD::SetData(char* ChrArray)
{
	memcpy(VcodString, ChrArray, 1040);
}
//---------------------------------------------------------------------------
char* sVCOD::GetData()
{
	return VcodString;
}
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
void sIOWN::CopyData(char* ChrArray)
{
	memcpy(IownPlayerFlags, ChrArray, 12);
}
//---------------------------------------------------------------------------
void sIOWN::SetData(char Data, char Player)
{
	IownPlayerFlags[Player] = Data;
}
//---------------------------------------------------------------------------
char sIOWN::GetData(char Player)
{
	return IownPlayerFlags[Player];
}
//---------------------------------------------------------------------------
char* sIOWN::GetDataArray()
{
	return IownPlayerFlags;
}
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
void sOWNR::CopyData(char* ChrArray)
{
	memcpy(OwnrPlayerFlags, ChrArray, 12);
}
//---------------------------------------------------------------------------
void sOWNR::SetData(char Data, char Player)
{
	OwnrPlayerFlags[Player] = Data;
}
//---------------------------------------------------------------------------
char sOWNR::GetData(char Player)
{
	return OwnrPlayerFlags[Player];
}
//---------------------------------------------------------------------------
char* sOWNR::GetDataArray()
{
	return OwnrPlayerFlags;
}
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
void sERA::SetData(short Short)
{
	EraTileset = Short;
}
//---------------------------------------------------------------------------
short sERA::GetData()
{
	return EraTileset;
}
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
void sDIM::SetData(short Short, char Index)
{
	switch(Index)
	{
		case 0:
			DimWidth = Short;
			break;

		case 1:
			DimHeight = Short;
			break;
	}
}
//---------------------------------------------------------------------------
short sDIM::GetData(char Index)
{
	switch(Index)
	{
		case 0:
			return DimWidth;

		case 1:
			return DimHeight;

		default:
			return 0;
	}
}
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
void sSIDE::CopyData(char* ChrArray)
{
	memcpy(SidePlayerRace, ChrArray, 12);
}
//---------------------------------------------------------------------------
void sSIDE::SetData(char Data, char Player)
{
	SidePlayerRace[Player] = Data;
}
//---------------------------------------------------------------------------
char sSIDE::GetData(char Player)
{
	return SidePlayerRace[Player];
}
//---------------------------------------------------------------------------
char* sSIDE::GetDataArray()
{
	return SidePlayerRace;
}
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
sMTXM::sMTXM()
{
	MtxmTileValues = NULL;
}
//---------------------------------------------------------------------------
void sMTXM::Size(short Height, short Width)
{
	MtxmTileValues = (short*)malloc(Height * Width * sizeof(short));
}
//---------------------------------------------------------------------------
void sMTXM::CopyData(short* ShortArray, unsigned long Length)
{
	memcpy(MtxmTileValues, ShortArray, Length);
}
//---------------------------------------------------------------------------
short sMTXM::GetData(short TotalWidth, short Height, short Width)
{
	return MtxmTileValues[Height * TotalWidth + Width];
}
//---------------------------------------------------------------------------
void sMTXM::SetData(short TotalWidth, short Height, short Width, short Data)
{
	MtxmTileValues[Height * TotalWidth + Width] = Data;
}
//---------------------------------------------------------------------------
short* sMTXM::GetDataArray()
{
	return MtxmTileValues;
}
//---------------------------------------------------------------------------
sMTXM::~sMTXM()
{
	if(MtxmTileValues)
		free(MtxmTileValues);
}
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
void sPUNI::CopyData(char* ChrArray, char Index)
{
	switch(Index)
	{
		case 0:
			memcpy(PuniPlayerAvlblity, ChrArray, 2736);
			break;

		case 1:
			memcpy(PuniGlobalAvlblity, ChrArray, 228);
			break;

		case 2:
			memcpy(PuniUseDefaults, ChrArray, 2736);
			break;
	}
}
//---------------------------------------------------------------------------
char sPUNI::GetData(unsigned char Unit, unsigned char Player, char Index)
{
	switch(Index)
	{
		case 0:
			return PuniPlayerAvlblity[12 * Unit + Player];

		case 1:
			return PuniGlobalAvlblity[Unit];

		case 2:
			return PuniUseDefaults[12 * Unit + Player];

		default:
			return 2;
	}
}
//---------------------------------------------------------------------------
void sPUNI::SetData(unsigned char Unit, unsigned char Player, char Data, char Index)
{
	switch(Index)
	{
		case 0:
			PuniPlayerAvlblity[12 * Unit + Player] = Data;
			break;

		case 1:
			PuniGlobalAvlblity[Unit] = Data;
			break;

		case 2:
			PuniUseDefaults[12 * Unit + Player] = Data;
			break;
	}
}
//---------------------------------------------------------------------------
char* sPUNI::GetDataArray(char Index)
{
	switch(Index)
	{
		case 0:
			return PuniPlayerAvlblity;

		case 1:
			return PuniGlobalAvlblity;

		case 2:
			return PuniUseDefaults;

		default:
			return 0;
	}
}
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
sUNIT::sUNIT()
{
	UnitCurrentUnits = NULL;
	UnitLastUnit = NULL;
}
//---------------------------------------------------------------------------
void sUNIT::CopyData(char* DataChunk, unsigned long SectionLength)
{
	UnitNumberOfUnits = SectionLength / 36;

	UNIT_NODE* PrevNode = NULL;
	UNIT_NODE* OrigNode = NULL;

	// Setting up the first node
	UnitCurrentUnits = new UNIT_NODE;
	UnitCurrentUnits->Prev = NULL;
	OrigNode = UnitCurrentUnits;

	for(unsigned long i = 0; i < UnitNumberOfUnits; i++)
	{
		unsigned long TempUnsignedLong = i * 36;
		UnitCurrentUnits->Unit.ID = ((unsigned long*)(DataChunk))[TempUnsignedLong / 4];
		UnitCurrentUnits->Unit.X = ((short*)(DataChunk))[TempUnsignedLong / 2 + 2];
		UnitCurrentUnits->Unit.Y = ((short*)(DataChunk))[TempUnsignedLong / 2 + 3];
		UnitCurrentUnits->Unit.UnitType = ((short*)(DataChunk))[TempUnsignedLong / 2 + 4];
		UnitCurrentUnits->Unit.BuildingRelation = ((short*)(DataChunk))[TempUnsignedLong / 2 + 5];
		UnitCurrentUnits->Unit.FlagProperties = ((unsigned short*)(DataChunk))[TempUnsignedLong / 2 + 6];
		UnitCurrentUnits->Unit.FlagElements = ((unsigned short*)(DataChunk))[TempUnsignedLong / 2 + 7];
		UnitCurrentUnits->Unit.PlayerNumber = ((unsigned char*)(DataChunk))[TempUnsignedLong + 16];
		UnitCurrentUnits->Unit.HitPoints = ((unsigned char*)(DataChunk))[TempUnsignedLong + 17];
		UnitCurrentUnits->Unit.ShieldPoints = ((unsigned char*)(DataChunk))[TempUnsignedLong + 18];
		UnitCurrentUnits->Unit.EnergyPoints = ((unsigned char*)(DataChunk))[TempUnsignedLong + 19];
		UnitCurrentUnits->Unit.ResourceAmount = ((unsigned long*)(DataChunk))[TempUnsignedLong / 4 + 5];
		UnitCurrentUnits->Unit.UnitsInHangar = ((short*)(DataChunk))[TempUnsignedLong / 2 + 12];
		UnitCurrentUnits->Unit.FlagState = ((unsigned short*)(DataChunk))[TempUnsignedLong / 2 + 13];
		UnitCurrentUnits->Unit.Unknown1 = ((unsigned long*)(DataChunk))[TempUnsignedLong / 4 + 7];
		UnitCurrentUnits->Unit.RelatedID = ((unsigned long*)(DataChunk))[TempUnsignedLong / 4 + 8];

		PrevNode = UnitCurrentUnits;
		UnitCurrentUnits = new UNIT_NODE;
		PrevNode->Next = UnitCurrentUnits;
		UnitCurrentUnits->Prev = PrevNode;
	}
	// Deleting the node "stub"
	delete UnitCurrentUnits;
	UnitCurrentUnits = NULL;

	// i.e. if the unit count isn't "0"...
	if(PrevNode != NULL)
	{	// ...make the last node "the last node" and the original node
		// "UnitCurrentUnits"
		PrevNode->Next = NULL;
		UnitCurrentUnits = OrigNode;
		UnitLastUnit = PrevNode;
	}
}
//---------------------------------------------------------------------------
UNIT_NODE* sUNIT::GetData()
{
	return UnitCurrentUnits;
}
//---------------------------------------------------------------------------
void sUNIT::CreateUnit(UNIT Data)
{
	UNIT_NODE* TempUnitNode = new UNIT_NODE;
	TempUnitNode->Next = NULL;

	if(UnitNumberOfUnits != 0)
	{
		UnitLastUnit->Next = TempUnitNode;
		TempUnitNode->Prev = UnitLastUnit;
		UnitLastUnit = TempUnitNode;
	}
	else
	{
		TempUnitNode->Next = NULL;
		TempUnitNode->Prev = NULL;

		UnitCurrentUnits = TempUnitNode;
		UnitLastUnit = TempUnitNode;
	}

	UnitLastUnit->Unit = Data;

	UnitNumberOfUnits++;
}
//---------------------------------------------------------------------------
bool sUNIT::DeleteUnit(UNIT_NODE* UnitNode)
{
	if(UnitNumberOfUnits == 0)
		return false;
	if(UnitNode->Next != NULL)
		UnitNode->Next->Prev = UnitNode->Prev;
	else
		UnitLastUnit = UnitNode->Prev;
	if(UnitNode->Prev != NULL)
		UnitNode->Prev->Next = UnitNode->Next;
	else
		UnitCurrentUnits = UnitNode->Next;
	delete UnitNode;

	UnitNumberOfUnits--;

	return true;
}
//---------------------------------------------------------------------------
void sUNIT::CopyUnit(UNIT_NODE* UnitNode)
{
	CreateUnit(UnitNode->Unit);
}
//---------------------------------------------------------------------------
void sUNIT::ReplaceUnit(UNIT_NODE* UnitNode, UNIT Data)
{
	UnitNode->Unit = Data;
}
//---------------------------------------------------------------------------
unsigned long sUNIT::GetDataLength()
{
	return UnitNumberOfUnits;
}
//---------------------------------------------------------------------------
sUNIT::~sUNIT()
{
	UNIT_NODE* TempNode;

	if(UnitCurrentUnits)
	{
		for(unsigned long i = 0; i < UnitNumberOfUnits; i++)
		{
			TempNode = UnitCurrentUnits;
			UnitCurrentUnits = UnitCurrentUnits->Next;
			delete TempNode;
		}
	}
}
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
sISOM::sISOM()
{
	IsomValues = NULL;
}
//---------------------------------------------------------------------------
void sISOM::CopyData(RECT *RectArray, short Height, short Width)
{
	short TempWidth;
	short TempHeight = Height + 1;
	if(0 == Width % 2)
	{
		TempWidth = Width / 2 + 1;
	}
	else
	{
		TempWidth = (Width - 1) / 2 + 1;
	}

	IsomValues = (RECT*)malloc(TempHeight * TempWidth * sizeof(RECT));
	memcpy(IsomValues, RectArray, TempHeight * TempWidth * sizeof(RECT));
}
//---------------------------------------------------------------------------
RECT sISOM::GetData(short TotalWidth, short Height, short Width)
{
	short TempTotalWidth;
	short TempWidth;
	if(0 == TotalWidth % 2)
	{
		TempTotalWidth = TotalWidth / 2;
	}
	else
	{
		TempTotalWidth = (TotalWidth - 1) / 2;
	}
	if(0 == Width % 2)
	{
		TempWidth = Width / 2;
	}
	else
	{
		TempWidth = (Width - 1) / 2;
	}

	return IsomValues[Height * TempTotalWidth + TempWidth];
}
//---------------------------------------------------------------------------
void sISOM::SetData(short TotalWidth, short Height, short Width, RECT Data)
{
	short TempTotalWidth;
	short TempWidth;
	if(0 == TotalWidth % 2)
	{
		TempTotalWidth = TotalWidth / 2;
	}
	else
	{
		TempTotalWidth = (TotalWidth - 1) / 2;
	}
	if(0 == Width % 2)
	{
		TempWidth = Width / 2;
	}
	else
	{
		TempWidth = (Width - 1) / 2;
	}

	IsomValues[Height * TempTotalWidth + TempWidth] = Data;
}
//---------------------------------------------------------------------------
RECT* sISOM::GetDataArray()
{
	return IsomValues;
}
//---------------------------------------------------------------------------
sISOM::~sISOM()
{
	if(IsomValues)
		free(IsomValues);
}
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
sTILE::sTILE()
{
	TileTileValues = NULL;
}
//---------------------------------------------------------------------------
void sTILE::Size(short Height, short Width)
{
	TileTileValues = (short*)malloc(Height * Width * sizeof(short));
}
//---------------------------------------------------------------------------
void sTILE::CopyData(short* ShortArray, unsigned long Length)
{
	memcpy(TileTileValues, ShortArray, Length);
}
//---------------------------------------------------------------------------
short sTILE::GetData(short TotalWidth, short Height, short Width)
{
	return TileTileValues[Height * TotalWidth + Width];
}
//---------------------------------------------------------------------------
void sTILE::SetData(short TotalWidth, short Height, short Width, short Data)
{
	TileTileValues[Height * TotalWidth + Width] = Data;
}
//---------------------------------------------------------------------------
short* sTILE::GetDataArray()
{
	return TileTileValues;
}
//---------------------------------------------------------------------------
sTILE::~sTILE()
{
	if(TileTileValues)
		free(TileTileValues);
}
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
sDD2::sDD2()
{
	Dd2DoodadUnits = NULL;
	Dd2LastDoodad = NULL;
}
//---------------------------------------------------------------------------
void sDD2::CopyData(char* DataChunk, unsigned long SectionLength)
{
	Dd2NumberOfDoodads = SectionLength / 8;

	DOODAD_UNIT_NODE* PrevNode = NULL;
	DOODAD_UNIT_NODE* OrigNode = NULL;

	Dd2DoodadUnits = new DOODAD_UNIT_NODE;
	Dd2DoodadUnits->Prev = NULL;
	OrigNode = Dd2DoodadUnits;

	for(unsigned long i = 0; i < Dd2NumberOfDoodads; i++)
	{
		unsigned long TempUnsignedLong = i * 8;
		Dd2DoodadUnits->DoodadUnit.Number = ((short*)(DataChunk))[TempUnsignedLong / 2];
		Dd2DoodadUnits->DoodadUnit.X = ((short*)(DataChunk))[TempUnsignedLong / 2 + 1];
		Dd2DoodadUnits->DoodadUnit.Y = ((short*)(DataChunk))[TempUnsignedLong / 2 + 2];
		Dd2DoodadUnits->DoodadUnit.PlayerNumber = ((unsigned char*)(DataChunk))[TempUnsignedLong + 6];
		Dd2DoodadUnits->DoodadUnit.Enabled = ((char*)(DataChunk))[TempUnsignedLong + 7];

		PrevNode = Dd2DoodadUnits;
		Dd2DoodadUnits = new DOODAD_UNIT_NODE;
		PrevNode->Next = Dd2DoodadUnits;
		Dd2DoodadUnits->Prev = PrevNode;
	}
	delete Dd2DoodadUnits;
	Dd2DoodadUnits = NULL;

	if(PrevNode != NULL)
	{
		PrevNode->Next = NULL;
		Dd2DoodadUnits = OrigNode;
		Dd2LastDoodad = PrevNode;
	}
}
//---------------------------------------------------------------------------
DOODAD_UNIT_NODE* sDD2::GetData()
{
	return Dd2DoodadUnits;
}
//---------------------------------------------------------------------------
void sDD2::CreateDoodad(DOODAD_UNIT Data)
{
	DOODAD_UNIT_NODE* TempDoodadNode = new DOODAD_UNIT_NODE;
	TempDoodadNode->Next = NULL;

	if(Dd2NumberOfDoodads != 0)
	{
		Dd2LastDoodad->Next = TempDoodadNode;
		TempDoodadNode->Prev = Dd2LastDoodad;
		Dd2LastDoodad = TempDoodadNode;
	}
	else
	{
		TempDoodadNode->Prev = NULL;

		Dd2DoodadUnits = TempDoodadNode;
		Dd2LastDoodad = TempDoodadNode;
	}

	Dd2LastDoodad->DoodadUnit = Data;

	Dd2NumberOfDoodads++;
}
//---------------------------------------------------------------------------
bool sDD2::DeleteDoodad(DOODAD_UNIT_NODE* DoodadUnitNode)
{
	if(Dd2NumberOfDoodads == 0)
		return false;
	if(DoodadUnitNode->Next != NULL)
		DoodadUnitNode->Next->Prev = DoodadUnitNode->Prev;
	else
		Dd2LastDoodad = DoodadUnitNode->Prev;
	if(DoodadUnitNode->Prev != NULL)
		DoodadUnitNode->Prev->Next = DoodadUnitNode->Next;
	else
		Dd2DoodadUnits = DoodadUnitNode->Next;
	delete DoodadUnitNode;

	Dd2NumberOfDoodads--;

	return true;
}
//---------------------------------------------------------------------------
void sDD2::CopyDoodad(DOODAD_UNIT_NODE* DoodadUnitNode)
{
	CreateDoodad(DoodadUnitNode->DoodadUnit);
}
//---------------------------------------------------------------------------
void sDD2::ReplaceDoodad(DOODAD_UNIT_NODE* DoodadUnitNode, DOODAD_UNIT Data)
{
	DoodadUnitNode->DoodadUnit = Data;
}
//---------------------------------------------------------------------------
unsigned long sDD2::GetDataLength()
{
	return Dd2NumberOfDoodads;
}
//---------------------------------------------------------------------------
sDD2::~sDD2()
{
	DOODAD_UNIT_NODE* TempNode;

	if(Dd2DoodadUnits)
	{
		for(unsigned long i = 0; i < Dd2NumberOfDoodads; i++)
		{
			TempNode = Dd2DoodadUnits;
			Dd2DoodadUnits = Dd2DoodadUnits->Next;
			delete TempNode;
		}
	}
}
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
sTHG2::sTHG2()
{
	Thg2DoodadSprites = NULL;
	Thg2LastSprite = NULL;
}
//---------------------------------------------------------------------------
void sTHG2::CopyData(char* DataChunk, unsigned long SectionLength)
{
	Thg2NumberOfSprites = SectionLength / 10;

	DOODAD_SPRITE_NODE* PrevNode = NULL;
	DOODAD_SPRITE_NODE* OrigNode = NULL;

	Thg2DoodadSprites = new DOODAD_SPRITE_NODE;
	Thg2DoodadSprites->Prev = NULL;
	OrigNode = Thg2DoodadSprites;

	for(unsigned long i = 0; i < Thg2NumberOfSprites; i++)
	{
		unsigned long TempUnsignedLong = i * 10;
		Thg2DoodadSprites->DoodadSprite.UnitNumber = ((short*)(DataChunk))[TempUnsignedLong / 2];
		Thg2DoodadSprites->DoodadSprite.X = ((short*)(DataChunk))[TempUnsignedLong / 2 + 1];
		Thg2DoodadSprites->DoodadSprite.Y = ((short*)(DataChunk))[TempUnsignedLong / 2 + 2];
		Thg2DoodadSprites->DoodadSprite.PlayerNumber = ((unsigned char*)(DataChunk))[TempUnsignedLong + 6];
		Thg2DoodadSprites->DoodadSprite.Unknown1 = ((char*)(DataChunk))[TempUnsignedLong + 7];
		Thg2DoodadSprites->DoodadSprite.Unknown2 = ((short*)(DataChunk))[TempUnsignedLong / 2 + 4];

		PrevNode = Thg2DoodadSprites;
		Thg2DoodadSprites = new DOODAD_SPRITE_NODE;
		PrevNode->Next = Thg2DoodadSprites;
		Thg2DoodadSprites->Prev = PrevNode;
	}
	delete Thg2DoodadSprites;
	Thg2DoodadSprites = NULL;

	if(PrevNode != NULL)
	{
		PrevNode->Next = NULL;
		Thg2DoodadSprites = OrigNode;
		Thg2LastSprite = PrevNode;
	}
}
//---------------------------------------------------------------------------
DOODAD_SPRITE_NODE* sTHG2::GetData()
{
	return Thg2DoodadSprites;
}
//---------------------------------------------------------------------------
void sTHG2::CreateSprite(DOODAD_SPRITE Data)
{
	DOODAD_SPRITE_NODE* TempSpriteNode = new DOODAD_SPRITE_NODE;
	TempSpriteNode->Next = NULL;

	if(Thg2NumberOfSprites != 0)
	{
		Thg2LastSprite->Next = TempSpriteNode;
		TempSpriteNode->Prev = Thg2LastSprite;
		Thg2LastSprite = TempSpriteNode;
	}
	else
	{
		TempSpriteNode->Prev = NULL;

		Thg2DoodadSprites = TempSpriteNode;
		Thg2LastSprite = TempSpriteNode;
	}

	Thg2LastSprite->DoodadSprite = Data;

	Thg2NumberOfSprites++;
}
//---------------------------------------------------------------------------
bool sTHG2::DeleteSprite(DOODAD_SPRITE_NODE* DoodadSpriteNode)
{
	if(Thg2NumberOfSprites == 0)
		return false;
	if(DoodadSpriteNode->Next != NULL)
		DoodadSpriteNode->Next->Prev = DoodadSpriteNode->Prev;
	else
		Thg2LastSprite = DoodadSpriteNode->Prev;
	if(DoodadSpriteNode->Prev != NULL)
		DoodadSpriteNode->Prev->Next = DoodadSpriteNode->Next;
	else
		Thg2DoodadSprites = DoodadSpriteNode->Next;
	delete DoodadSpriteNode;

	Thg2NumberOfSprites--;

	return true;
}
//---------------------------------------------------------------------------
void sTHG2::CopySprite(DOODAD_SPRITE_NODE* DoodadSpriteNode)
{
	CreateSprite(DoodadSpriteNode->DoodadSprite);
}
//---------------------------------------------------------------------------
void sTHG2::ReplaceSprite(DOODAD_SPRITE_NODE* DoodadSpriteNode, DOODAD_SPRITE Data)
{
	DoodadSpriteNode->DoodadSprite = Data;
}
//---------------------------------------------------------------------------
unsigned long sTHG2::GetDataLength()
{
	return Thg2NumberOfSprites;
}
//---------------------------------------------------------------------------
sTHG2::~sTHG2()
{
	DOODAD_SPRITE_NODE* TempNode;

	if(Thg2DoodadSprites)
	{
		for(unsigned long i = 0; i < Thg2NumberOfSprites; i++)
		{
			TempNode = Thg2DoodadSprites;
			Thg2DoodadSprites = Thg2DoodadSprites->Next;
			delete TempNode;
		}
	}
}
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
sMASK::sMASK()
{
	MaskFOWTileValues = NULL;
}
//---------------------------------------------------------------------------
void sMASK::Size(short Height, short Width)
{
	MaskFOWTileValues = (char*)malloc(Height * Width);
}
//---------------------------------------------------------------------------
void sMASK::CopyData(char* ChrArray, unsigned long Length)
{
	memcpy(MaskFOWTileValues, ChrArray, Length);
}
//---------------------------------------------------------------------------
char sMASK::GetData(short TotalWidth, short Height, short Width)
{
	return MaskFOWTileValues[Height * TotalWidth + Width];
}
//---------------------------------------------------------------------------
void sMASK::SetData(short TotalWidth, short Height, short Width, char Data)
{
	MaskFOWTileValues[Height * TotalWidth + Width] = Data;
}
//---------------------------------------------------------------------------
char* sMASK::GetDataArray()
{
	return MaskFOWTileValues;
}
//---------------------------------------------------------------------------
sMASK::~sMASK()
{
	if(MaskFOWTileValues)
		free(MaskFOWTileValues);
}
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
sSTR::sSTR()
{
	StrStrings = NULL;
}
//---------------------------------------------------------------------------
void sSTR::CopyData(STRING* StringArray, short NumberOfStrings)
{
	StrStrings = StringArray;
}
//---------------------------------------------------------------------------
STRING sSTR::GetData(short StringNumber)
{
	return StrStrings[StringNumber];
}
//---------------------------------------------------------------------------
void sSTR::SetData(short StringNumber, short Data, LPSTR StringData, char Index)
{
	switch(Index)
	{
		case 0:
			StrStrings[StringNumber].Used = (char)Data;
			break;

		case 1:
			StrStrings[StringNumber].Length = Data;
			break;

		case 2:
			StrStrings[StringNumber].Data = (LPSTR)realloc(StrStrings[StringNumber].Data,
				strlen(StringData) + 1);
			memcpy(StrStrings[StringNumber].Data, StringData, strlen(StringData) + 1);
			StrStrings[StringNumber].Length = strlen(StringData) + 1;
			if(StrStrings[StringNumber].Length == 1)
				StrStrings[StringNumber].Length = 0;
			break;

		case 3:
			StrStrings = (STRING*)realloc(StrStrings, Data * sizeof(STRING));
			StrNumberOfStrings = Data;
			break;
	}
}
//---------------------------------------------------------------------------
short sSTR::GetDataLength()
{
	return StrNumberOfStrings;
}
//---------------------------------------------------------------------------
STRING* sSTR::GetDataArray()
{
	return StrStrings;
}
//---------------------------------------------------------------------------
sSTR::~sSTR()
{
	if(StrStrings)
	{
		for(unsigned short i = 0; i < StrNumberOfStrings; i++)
		{
			if(StrStrings)
				free(StrStrings[i].Data);
		}
		free(StrStrings);
	}
}
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
CUWPSLOT sUPRP::GetData(char SlotNumber)
{
	return UprpCuwpSlots[SlotNumber];
}
//---------------------------------------------------------------------------
void sUPRP::SetData(char SlotNumber, unsigned long Data, char Index)
{
	switch(Index)
	{
		case 0:
			UprpCuwpSlots[SlotNumber].FlagProperties = (unsigned short)Data;
			break;

		case 1:
			UprpCuwpSlots[SlotNumber].FlagElements = (unsigned short)Data;
			break;

		case 2:
			UprpCuwpSlots[SlotNumber].PlayerNumber = (char)Data;
			break;

		case 3:
			UprpCuwpSlots[SlotNumber].HitPoints = (unsigned char)Data;
			break;

		case 4:
			UprpCuwpSlots[SlotNumber].ShieldPoints = (unsigned char)Data;
			break;

		case 5:
			UprpCuwpSlots[SlotNumber].EnergyPoints = (unsigned char)Data;
			break;

		case 6:
			UprpCuwpSlots[SlotNumber].ResourceAmount = Data;
			break;

		case 7:
			UprpCuwpSlots[SlotNumber].UnitsInHangar = (short)Data;
			break;

		case 8:
			UprpCuwpSlots[SlotNumber].FlagState = (unsigned short)Data;
			break;

		case 9:
			UprpCuwpSlots[SlotNumber].Unknown2 = Data;
			break;
	}
}
//---------------------------------------------------------------------------
CUWPSLOT* sUPRP::GetDataArray()
{
	return UprpCuwpSlots;
}
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
void sUPUS::CopyData(char* CharArray)
{
	memcpy(UpusCuwpUsedSlots, CharArray, 64);
}
//---------------------------------------------------------------------------
char sUPUS::GetData(char SlotNumber)
{
	return UpusCuwpUsedSlots[SlotNumber];
}
//---------------------------------------------------------------------------
void sUPUS::SetData(char SlotNumber, char Data)
{
	UpusCuwpUsedSlots[SlotNumber] = Data;
}
//---------------------------------------------------------------------------
char* sUPUS::GetDataArray()
{
	return UpusCuwpUsedSlots;
}
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
LOCATION sMRGN::GetData(unsigned char LocationNumber)
{
	return MrgnLocations[LocationNumber];
}
//---------------------------------------------------------------------------
void sMRGN::SetData(unsigned char LocationNumber, long Data, char Index)
{
	switch(Index)
	{
		case 0:
			MrgnLocations[LocationNumber].Coordinates.left = Data;
			break;

		case 1:
			MrgnLocations[LocationNumber].Coordinates.top = Data;
			break;

		case 2:
			MrgnLocations[LocationNumber].Coordinates.right = Data;
			break;

		case 3:
			MrgnLocations[LocationNumber].Coordinates.bottom = Data;
			break;

		case 4:
			MrgnLocations[LocationNumber].StringNumber = (short)Data;
			break;

		case 5:
			MrgnLocations[LocationNumber].ElevationFlags = (short)Data;
			break;
	}
}
//---------------------------------------------------------------------------
char sMRGN::GetBWBit()
{
	return BWBit;
}
//---------------------------------------------------------------------------
void sMRGN::SetBWBit(char Bit)
{
	BWBit = Bit;
}
//---------------------------------------------------------------------------
LOCATION* sMRGN::GetDataArray()
{
	return MrgnLocations;
}
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
sTRIG::sTRIG()
{
	TrigTriggers = NULL;
}
//---------------------------------------------------------------------------
void sTRIG::CopyData(char* DataChunk, unsigned long SectionLength)
{
	TrigNumberOfTriggers = SectionLength / 2400;

	TRIGGER_NODE* PrevNode = NULL;
	TRIGGER_NODE* OrigNode = NULL;

	TrigTriggers = new TRIGGER_NODE;
	TrigTriggers->Prev = NULL;
	OrigNode = TrigTriggers;

	for(unsigned long i = 0; i < TrigNumberOfTriggers; i++)
	{
		for(unsigned long i2 = 0; i2 < 16; i2++)
		{
			unsigned long TempUnsignedLong = i * 2400 + i2 * 20;
			TrigTriggers->Trigger.Conditions[i2].Value1 = ((long*)(DataChunk))[TempUnsignedLong / 4];
			TrigTriggers->Trigger.Conditions[i2].Value2 = ((long*)(DataChunk))[TempUnsignedLong / 4 + 1];
			TrigTriggers->Trigger.Conditions[i2].Value3 = ((long*)(DataChunk))[TempUnsignedLong / 4 + 2];
			TrigTriggers->Trigger.Conditions[i2].Value4 = ((short*)(DataChunk))[TempUnsignedLong / 2 + 6];
			TrigTriggers->Trigger.Conditions[i2].Value5 = ((char*)(DataChunk))[TempUnsignedLong + 14];
			TrigTriggers->Trigger.Conditions[i2].Value6 = ((char*)(DataChunk))[TempUnsignedLong + 15];
			TrigTriggers->Trigger.Conditions[i2].Value7 = ((unsigned char*)(DataChunk))[TempUnsignedLong + 16];
			TrigTriggers->Trigger.Conditions[i2].Value8 = ((char*)(DataChunk))[TempUnsignedLong + 17];
			TrigTriggers->Trigger.Conditions[i2].Unknown1 = ((short*)(DataChunk))[TempUnsignedLong / 2 + 9];
		}
		for(i2 = 0; i2 < 64; i2++)
		{
			unsigned long TempUnsignedLong = i * 2400 + i2 * 32 + 320;
			TrigTriggers->Trigger.Actions[i2].Value1 = ((long*)(DataChunk))[TempUnsignedLong / 4];
			TrigTriggers->Trigger.Actions[i2].Value2 = ((long*)(DataChunk))[TempUnsignedLong / 4 + 1];
			TrigTriggers->Trigger.Actions[i2].Value3 = ((long*)(DataChunk))[TempUnsignedLong / 4 + 2];
			TrigTriggers->Trigger.Actions[i2].Value4 = ((unsigned long*)(DataChunk))[TempUnsignedLong / 4 + 3];
			TrigTriggers->Trigger.Actions[i2].Value5 = ((long*)(DataChunk))[TempUnsignedLong / 4 + 4];
			TrigTriggers->Trigger.Actions[i2].Value6 = ((long*)(DataChunk))[TempUnsignedLong / 4 + 5];
			TrigTriggers->Trigger.Actions[i2].Value7 = ((short*)(DataChunk))[TempUnsignedLong / 2 + 12];
			TrigTriggers->Trigger.Actions[i2].Value8 = ((char*)(DataChunk))[TempUnsignedLong + 26];
			TrigTriggers->Trigger.Actions[i2].Value9 = ((char*)(DataChunk))[TempUnsignedLong + 27];
			TrigTriggers->Trigger.Actions[i2].Value10 = ((char*)(DataChunk))[TempUnsignedLong + 28];
			TrigTriggers->Trigger.Actions[i2].Unknown1 = ((char*)(DataChunk))[TempUnsignedLong + 29];
			TrigTriggers->Trigger.Actions[i2].Unknown2 = ((short*)(DataChunk))[TempUnsignedLong / 2 + 15];
		}
		unsigned long TempUnsignedLong = i * 2400 + 2368;
		TrigTriggers->Trigger.Unknown = ((long*)(DataChunk))[TempUnsignedLong / 4];
		memcpy(&(TrigTriggers->Trigger.PlayersExecuted), &(DataChunk[TempUnsignedLong + 4]), 28);

		PrevNode = TrigTriggers;
		TrigTriggers = new TRIGGER_NODE;
		PrevNode->Next = TrigTriggers;
		TrigTriggers->Prev = PrevNode;
	}
	delete TrigTriggers;
	TrigTriggers = NULL;

	if(PrevNode != NULL)
	{
		PrevNode->Next = NULL;
		TrigTriggers = OrigNode;
		TrigLastTrigger = PrevNode;
	}
}
//---------------------------------------------------------------------------
TRIGGER_NODE* sTRIG::GetData()
{
	return TrigTriggers;
}
//---------------------------------------------------------------------------
void sTRIG::CreateTrigger(TRIGGER Data)
{
	TRIGGER_NODE* TempTriggerNode = new TRIGGER_NODE;
	TempTriggerNode->Next = NULL;

	if(TrigNumberOfTriggers != 0)
	{
		TrigLastTrigger->Next = TempTriggerNode;
		TempTriggerNode->Prev = TrigLastTrigger;
		TrigLastTrigger = TempTriggerNode;
	}
	else
	{
		TempTriggerNode->Prev = NULL;

		TrigTriggers = TempTriggerNode;
		TrigLastTrigger = TempTriggerNode;
	}

	TrigLastTrigger->Trigger = Data;

	TrigNumberOfTriggers++;
}
//---------------------------------------------------------------------------
bool sTRIG::DeleteTrigger(TRIGGER_NODE* TriggerNode)
{
	if(TrigNumberOfTriggers == 0)
		return false;
	if(TriggerNode->Next != NULL)
		TriggerNode->Next->Prev = TriggerNode->Prev;
	else
		TrigLastTrigger = TriggerNode->Prev;
	if(TriggerNode->Prev != NULL)
		TriggerNode->Prev->Next = TriggerNode->Next;
	else
		TrigTriggers = TriggerNode->Next;
	delete TriggerNode;

	TrigNumberOfTriggers--;

	return true;
}
//---------------------------------------------------------------------------
void sTRIG::CopyTrigger(TRIGGER_NODE* TriggerNode)
{
	CreateTrigger(TriggerNode->Trigger);
}
//---------------------------------------------------------------------------
void sTRIG::ReplaceTrigger(TRIGGER_NODE* TriggerNode, TRIGGER Data)
{
	TriggerNode->Trigger = Data;
}
//---------------------------------------------------------------------------
unsigned long sTRIG::GetDataLength()
{
	return TrigNumberOfTriggers;
}
//---------------------------------------------------------------------------
sTRIG::~sTRIG()
{
	TRIGGER_NODE* TempNode;

	if(TrigTriggers)
	{
		for(unsigned long i = 0; i < TrigNumberOfTriggers; i++)
		{
			TempNode = TrigTriggers;
			TrigTriggers = TrigTriggers->Next;
			delete TempNode;
		}
	}
}
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
short sSPRP::GetData(char Index)
{
	switch(Index)
	{
		case 0:
			return SprpScenarioName;
			
		case 1:
			return SprpScenarioDescription;

		default:
			return 0;
	}
}
//---------------------------------------------------------------------------
void sSPRP::SetData(short Data, char Index)
{
	switch(Index)
	{
		case 0:
			SprpScenarioName = Data;
			break;

		case 1:
			SprpScenarioDescription = Data;
			break;
	}
}
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
short sFORC::GetData(char Index)
{
	if(Index <= 7)
	{
		return ForcPlayerForce[Index];
	}
	if(Index >= 8 && Index <= 11)
	{
		return ForcNameStringNumber[Index - 8];
	}
	if(Index >= 12)
	{
		return ForcProperties[Index - 12];
	}
	return 0;
}
//---------------------------------------------------------------------------
void sFORC::SetData(short Data, char Index)
{
	if(Index <= 7)
	{
		ForcPlayerForce[Index] = (char)Data;
	}
	if(Index >= 8 && Index <= 11)
	{
		ForcNameStringNumber[Index - 8] = Data;
	}
	if(Index >= 12)
	{
		ForcProperties[Index - 12] = (char)Data;
	}
}
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
void sWAV::CopyData(long* LongArray)
{
	memcpy(WavStringNumbers, LongArray, 2048);
}
//---------------------------------------------------------------------------
long sWAV::GetData(short WavNumber)
{
	return WavStringNumbers[WavNumber];
}
//---------------------------------------------------------------------------
void sWAV::SetData(long Data, short WavNumber)
{
	WavStringNumbers[WavNumber] = Data;
}
//---------------------------------------------------------------------------
long* sWAV::GetDataArray()
{
	return WavStringNumbers;
}
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
void sSWNM::CopyData(long* LongArray)
{
	memcpy(SwnmSwitchNames, LongArray, 1024);
}
//---------------------------------------------------------------------------
long sSWNM::GetData(short SwitchNumber)
{
	return SwnmSwitchNames[SwitchNumber];
}
//---------------------------------------------------------------------------
void sSWNM::SetData(long Data, short SwitchNumber)
{
	SwnmSwitchNames[SwitchNumber] = Data;
}
//---------------------------------------------------------------------------
long* sSWNM::GetDataArray()
{
	return SwnmSwitchNames;
}
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
void sCOLR::CopyData(unsigned char* CharArray)
{
	memcpy(ColrPlayerColors, CharArray, 8);
}
//---------------------------------------------------------------------------
unsigned char sCOLR::GetData(char PlayerNumber)
{
	return ColrPlayerColors[PlayerNumber];
}
//---------------------------------------------------------------------------
void sCOLR::SetData(unsigned char Data, char PlayerNumber)
{
	ColrPlayerColors[PlayerNumber] = Data;
}
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
void sUPGR::CopyData(unsigned char* ChrArray, char Index)
{
	switch(Index)
	{
		case 0:
			if(BWBit == 0)
			{
				memcpy(UpgrPlayerMax, ChrArray, 552);
			}
			else
			{
				memcpy(UpgrPlayerMax, ChrArray, 732);
			}
			break;

		case 1:
			if(BWBit == 0)
			{
				memcpy(UpgrPlayerStart, ChrArray, 552);
			}
			else
			{
				memcpy(UpgrPlayerStart, ChrArray, 732);
			}
			break;

		case 2:
			if(BWBit == 0)
			{
				memcpy(UpgrDefaultMax, ChrArray, 46);
			}
			else
			{
				memcpy(UpgrDefaultMax, ChrArray, 61);
			}
			break;

		case 3:
			if(BWBit == 0)
			{
				memcpy(UpgrDefaultStart, ChrArray, 46);
			}
			else
			{
				memcpy(UpgrDefaultStart, ChrArray, 61);
			}
			break;

		case 4:
			if(BWBit == 0)
			{
				memcpy(UpgrPlayerOverride, ChrArray, 552);
			}
			else
			{
				memcpy(UpgrPlayerOverride, ChrArray, 732);
			}
			break;
	}
}
//---------------------------------------------------------------------------
unsigned char sUPGR::GetData(char Upgrade, char Player, char Index)
{
	switch(Index)
	{
		case 0:
			return UpgrPlayerMax[12 * Upgrade + Player];

		case 1:
			return UpgrPlayerStart[12 * Upgrade + Player];

		case 2:
			return UpgrDefaultMax[Upgrade];

		case 3:
			return UpgrDefaultStart[Upgrade];

		case 4:
			return UpgrPlayerOverride[12 * Upgrade + Player];

		case 5:
			return (unsigned char)BWBit;

		default:
			return 0;
	}
}
//---------------------------------------------------------------------------
void sUPGR::SetData(char Upgrade, char Player, unsigned char Data, char Index)
{
	switch(Index)
	{
		case 0:
			UpgrPlayerMax[12 * Upgrade + Player] = Data;
			break;

		case 1:
			UpgrPlayerStart[12 * Upgrade + Player] = Data;
			break;

		case 2:
			UpgrDefaultMax[Upgrade] = Data;
			break;

		case 3:
			UpgrDefaultStart[Upgrade] = Data;
			break;

		case 4:
			UpgrPlayerOverride[12 * Upgrade + Player] = (char)Data;
			break;

		case 5:
			BWBit = (char)Data;
			break;
	}
}
//---------------------------------------------------------------------------
char* sUPGR::GetDataArray(char Index)
{
	switch(Index)
	{
		case 0:
			return (char*)UpgrPlayerMax;

		case 1:
			return (char*)UpgrPlayerStart;

		case 2:
			return (char*)UpgrDefaultMax;

		case 3:
			return (char*)UpgrDefaultStart;

		case 4:
			return (char*)UpgrPlayerOverride;

		default:
			return 0;
	}
}
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
void sPTEC::CopyData(char* ChrArray, char Index)
{
	switch(Index)
	{
		case 0:
			if(BWBit == 0)
			{
				memcpy(PtecPlayerAvailable, ChrArray, 288);
			}
			else
			{
				memcpy(PtecPlayerAvailable, ChrArray, 528);
			}
			break;

		case 1:
			if(BWBit == 0)
			{
				memcpy(PtecPlayerResearched, ChrArray, 288);
			}
			else
			{
				memcpy(PtecPlayerResearched, ChrArray, 528);
			}
			break;

		case 2:
			if(BWBit == 0)
			{
				memcpy(PtecDefaultAvailable, ChrArray, 24);
			}
			else
			{
				memcpy(PtecDefaultAvailable, ChrArray, 44);
			}
			break;

		case 3:
			if(BWBit == 0)
			{
				memcpy(PtecDefaultResearched, ChrArray, 24);
			}
			else
			{
				memcpy(PtecDefaultResearched, ChrArray, 44);
			}
			break;
			
		case 4:
			if(BWBit == 0)
			{
				memcpy(PtecPlayerOverride, ChrArray, 288);
			}
			else
			{
				memcpy(PtecPlayerOverride, ChrArray, 528);
			}
			break;
	}
}
//---------------------------------------------------------------------------
char sPTEC::GetData(char Technology, char Player, char Index)
{
	switch(Index)
	{
		case 0:
			return PtecPlayerAvailable[12 * Technology + Player];

		case 1:
			return PtecPlayerResearched[12 * Technology + Player];

		case 2:
			return PtecDefaultAvailable[Technology];

		case 3:
			return PtecDefaultResearched[Technology];

		case 4:
			return PtecPlayerOverride[12 * Technology + Player];

		case 5:
			return BWBit;

		default:
			return 0;
	}
}
//---------------------------------------------------------------------------
void sPTEC::SetData(char Technology, char Player, char Data, char Index)
{
	switch(Index)
	{
		case 0:
			PtecPlayerAvailable[12 * Technology + Player] = Data;
			break;

		case 1:
			PtecPlayerResearched[12 * Technology + Player] = Data;
			break;

		case 2:
			PtecDefaultAvailable[Technology] = Data;
			break;

		case 3:
			PtecDefaultResearched[Technology] = Data;
			break;

		case 4:
			PtecPlayerOverride[12 * Technology + Player] = Data;
			break;

		case 5:
			BWBit = Data;
			break;
	}
}//---------------------------------------------------------------------------
char* sPTEC::GetDataArray(char Index)
{
	switch(Index)
	{
		case 0:
			return PtecPlayerAvailable;

		case 1:
			return PtecPlayerResearched;

		case 2:
			return PtecDefaultAvailable;

		case 3:
			return PtecDefaultResearched;

		case 4:
			return PtecPlayerOverride;

		default:
			return 0;
	}
}
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
void sUNIS::CopyData(LPVOID DataArray, char Index)
{
	switch(Index)
	{
		case 0:
			memcpy(UnisUseDefaults, DataArray, 228);
			break;

		case 1:
			memcpy(UnisHitPointStruct, DataArray, 228 * sizeof(UNITSETTING));
			break;

		case 2:
			memcpy(UnisShieldPoints, DataArray, 456);
			break;

		case 3:
			memcpy(UnisArmorPoints, DataArray, 228);
			break;

		case 4:
			memcpy(UnisBuildTime, DataArray, 456);
			break;

		case 5:
			memcpy(UnisMineralCost, DataArray, 456);
			break;

		case 6:
			memcpy(UnisGasCost, DataArray, 456);
			break;

		case 7:
			memcpy(UnisStringNumber, DataArray, 456);
			break;

		case 8:
			if(BWBit == 0)
			{
				memcpy(UnisWeaponBaseDamage, DataArray, 200);
			}
			else
			{
				memcpy(UnisWeaponBaseDamage, DataArray, 260);
			}
			break;

		case 9:
			if(BWBit == 0)
			{
				memcpy(UnisWeaponBonusDamage, DataArray, 200);
			}
			else
			{
				memcpy(UnisWeaponBonusDamage, DataArray, 260);
			}
			break;
	}
}
//---------------------------------------------------------------------------
LPVOID sUNIS::GetData(unsigned char UnitWeapon, char Index)
{
	switch(Index)
	{
		case 0:
			return (LPVOID)UnisUseDefaults[UnitWeapon];

		case 1:
			return (LPVOID)UnisHitPointStruct[UnitWeapon].Unknown;

		case 2:
			return (LPVOID)UnisHitPointStruct[UnitWeapon].HitPoints;

		case 3:
			return (LPVOID)UnisHitPointStruct[UnitWeapon].Invincible;

		case 4:
			return (LPVOID)UnisShieldPoints[UnitWeapon];

		case 5:
			return (LPVOID)UnisArmorPoints[UnitWeapon];

		case 6:
			return (LPVOID)UnisBuildTime[UnitWeapon];

		case 7:
			return (LPVOID)UnisMineralCost[UnitWeapon];

		case 8:
			return (LPVOID)UnisGasCost[UnitWeapon];

		case 9:
			return (LPVOID)UnisStringNumber[UnitWeapon];

		case 10:
			return (LPVOID)UnisWeaponBaseDamage[UnitWeapon];

		case 11:
			return (LPVOID)UnisWeaponBonusDamage[UnitWeapon];

		case 12:
			return (LPVOID)BWBit;

		default:
			return NULL;
	}
}
//---------------------------------------------------------------------------
void sUNIS::SetData(unsigned char UnitWeapon, LPVOID Data, char Index)
{
	switch(Index)
	{
		case 0:
			UnisUseDefaults[UnitWeapon] = (char)Data;
			break;

		case 1:
			UnisHitPointStruct[UnitWeapon].Unknown = (char)Data;
			break;

		case 2:
			UnisHitPointStruct[UnitWeapon].HitPoints = (short)Data;
			break;

		case 3:
			UnisHitPointStruct[UnitWeapon].Invincible = (char)Data;
			break;

		case 4:
			UnisShieldPoints[UnitWeapon] = (unsigned short)Data;
			break;

		case 5:
			UnisArmorPoints[UnitWeapon] = (unsigned char)Data;
			break;

		case 6:
			UnisBuildTime[UnitWeapon] = (unsigned short)Data;
			break;

		case 7:
			UnisMineralCost[UnitWeapon] = (unsigned short)Data;
			break;

		case 8:
			UnisGasCost[UnitWeapon] = (unsigned short)Data;
			break;

		case 9:
			UnisStringNumber[UnitWeapon] = (unsigned short)Data;
			break;

		case 10:
			UnisWeaponBaseDamage[UnitWeapon] = (unsigned short)Data;
			break;

		case 11:
			UnisWeaponBonusDamage[UnitWeapon] = (unsigned short)Data;
			break;

		case 12:
			BWBit = (char)Data;
			break;
	}
}
//---------------------------------------------------------------------------
LPVOID sUNIS::GetDataArray(char Index)
{
	switch(Index)
	{
		case 0:
			return (LPVOID)UnisUseDefaults;

		case 1:
			return (LPVOID)UnisHitPointStruct;

		case 2:
			return (LPVOID)UnisShieldPoints;

		case 3:
			return (LPVOID)UnisArmorPoints;

		case 4:
			return (LPVOID)UnisBuildTime;

		case 5:
			return (LPVOID)UnisMineralCost;

		case 6:
			return (LPVOID)UnisGasCost;

		case 7:
			return (LPVOID)UnisStringNumber;

		case 8:
			return (LPVOID)UnisWeaponBaseDamage;

		case 9:
			return (LPVOID)UnisWeaponBonusDamage;

		default:
			return 0;
	}
}
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
void sUPGS::CopyData(char* ChrArray, short* ShortArray, char Index)
{
	switch(Index)
	{
		case 0:
			if(BWBit == 0)
			{
				memcpy(UpgsUseDefaults, ChrArray, 46);
			}
			else
			{
				memcpy(UpgsUseDefaults, ChrArray, 61);
			}
			break;

		case 1:
			if(BWBit == 0)
			{
				memcpy(UpgsBaseMineralCost, ShortArray, 92);
			}
			else
			{
				memcpy(UpgsBaseMineralCost, ShortArray, 122);
			}
			break;

		case 2:
			if(BWBit == 0)
			{
				memcpy(UpgsFactorMineralCost, ShortArray, 92);
			}
			else
			{
				memcpy(UpgsFactorMineralCost, ShortArray,  122);
			}
			break;

		case 3:
			if(BWBit == 0)
			{
				memcpy(UpgsBaseGasCost, ShortArray, 92);
			}
			else
			{
				memcpy(UpgsBaseGasCost, ShortArray, 122);
			}
			break;

		case 4:
			if(BWBit == 0)
			{
				memcpy(UpgsFactorGasCost, ShortArray, 92);
			}
			else
			{
				memcpy(UpgsFactorGasCost, ShortArray, 122);
			}
			break;

		case 5:
			if(BWBit == 0)
			{
				memcpy(UpgsBaseTimeCost, ShortArray, 92);
			}
			else
			{
				memcpy(UpgsBaseTimeCost, ShortArray, 122);
			}
			break;

		case 6:
			if(BWBit == 0)
			{
				memcpy(UpgsFactorTimeCost, ShortArray, 92);
			}
			else
			{
				memcpy(UpgsFactorTimeCost, ShortArray, 122);
			}
			break;
	}
}
//---------------------------------------------------------------------------
short sUPGS::GetData(char Upgrade, char Index)
{
	switch(Index)
	{
		case 0:
			return UpgsUseDefaults[Upgrade];

		case 1:
			return UpgsBaseMineralCost[Upgrade];

		case 2:
			return UpgsFactorMineralCost[Upgrade];

		case 3:
			return UpgsBaseGasCost[Upgrade];

		case 4:
			return UpgsFactorGasCost[Upgrade];

		case 5:
			return UpgsBaseTimeCost[Upgrade];

		case 6:
			return UpgsFactorTimeCost[Upgrade];

		case 7:
			return (short)BWBit;

		default:
			return 0;
	}
}
//---------------------------------------------------------------------------
void sUPGS::SetData(char Upgrade, unsigned short Data, char Index)
{
	switch(Index)
	{
		case 0:
			UpgsUseDefaults[Upgrade] = (char)Data;
			break;

		case 1:
			UpgsBaseMineralCost[Upgrade] = Data;
			break;

		case 2:
			UpgsFactorMineralCost[Upgrade] = Data;
			break;

		case 3:
			UpgsBaseGasCost[Upgrade] = Data;
			break;

		case 4:
			UpgsFactorGasCost[Upgrade] = Data;
			break;

		case 5:
			UpgsBaseTimeCost[Upgrade] = (short)Data;
			break;

		case 6:
			UpgsFactorTimeCost[Upgrade] = (short)Data;
			break;

		case 7:
			BWBit = (char)Data;
			break;
	}
}
//---------------------------------------------------------------------------
LPVOID sUPGS::GetDataArray(char Index)
{
	switch(Index)
	{
		case 0:
			return (LPVOID)UpgsUseDefaults;

		case 1:
			return (LPVOID)UpgsBaseMineralCost;

		case 2:
			return (LPVOID)UpgsFactorMineralCost;

		case 3:
			return (LPVOID)UpgsBaseGasCost;

		case 4:
			return (LPVOID)UpgsFactorGasCost;

		case 5:
			return (LPVOID)UpgsBaseTimeCost;

		case 6:
			return (LPVOID)UpgsFactorTimeCost;

		default:
			return 0;
	}
}
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
void sTECS::CopyData(char* ChrArray, short* ShortArray, char Index)
{
	switch(Index)
	{
		case 0:
			if(BWBit == 0)
			{
				memcpy(TecsUseDefaults, ChrArray, 24);
			}
			else
			{
				memcpy(TecsUseDefaults, ChrArray, 44);
			}
			break;

		case 1:
			if(BWBit == 0)
			{
				memcpy(TecsMineralCost, ShortArray, 48);
			}
			else
			{
				memcpy(TecsMineralCost, ShortArray, 88);
			}
			break;

		case 2:
			if(BWBit == 0)
			{
				memcpy(TecsGasCost, ShortArray, 48);
			}
			else
			{
				memcpy(TecsGasCost, ShortArray, 88);
			}
			break;

		case 3:
			if(BWBit == 0)
			{
				memcpy(TecsTimeCost, ShortArray, 48);
			}
			else
			{
				memcpy(TecsTimeCost, ShortArray, 88);
			}
			break;

		case 4:
			if(BWBit == 0)
			{
				memcpy(TecsEnergyCost, ShortArray, 48);
			}
			else
			{
				memcpy(TecsEnergyCost, ShortArray, 88);
			}
			break;
	}
}
//---------------------------------------------------------------------------
short sTECS::GetData(char Technology, char Index)
{
	switch(Index)
	{
		case 0:
			return (short)TecsUseDefaults[Technology];

		case 1:
			return TecsMineralCost[Technology];

		case 2:
			return TecsGasCost[Technology];

		case 3:
			return TecsTimeCost[Technology];

		case 4:
			return TecsEnergyCost[Technology];

		case 5:
			return (short)BWBit;

		default:
			return 0;
	}
}
//---------------------------------------------------------------------------
void sTECS::SetData(char Technology, unsigned short Data, char Index)
{
	switch(Index)
	{
		case 0:
			TecsUseDefaults[Technology] = (char)Data;
			break;

		case 1:
			TecsMineralCost[Technology] = Data;
			break;

		case 2:
			TecsGasCost[Technology] = Data;
			break;

		case 3:
			TecsTimeCost[Technology] = (short)Data;
			break;

		case 4:
			TecsEnergyCost[Technology] = Data;
			break;

		case 5:
			BWBit = (char)Data;
			break;
	}
}
//---------------------------------------------------------------------------
LPVOID sTECS::GetDataArray(char Index)
{
	switch(Index)
	{
		case 0:
			return (LPVOID)TecsUseDefaults;

		case 1:
			return (LPVOID)TecsMineralCost;

		case 2:
			return (LPVOID)TecsGasCost;

		case 3:
			return (LPVOID)TecsTimeCost;

		case 4:
			return (LPVOID)TecsEnergyCost;

		default:
			return 0;
	}
}
//---------------------------------------------------------------------------
//Workspace: Progressive Editor
//File Name: ClassMapSections.h
#ifndef _CLASSMAPSECTIONS_H_
#define _CLASSMAPSECTIONS_H_

#include "ClassMapStructs.h"
//---------------------------------------------------------------------------
// The following classes are the various section classes for the map
// ----
// Information:
// 1. The "Size" functions are used for setting the number of structures, and
// allocating memory to their respective arrays within the class.
// 2. The "GetData" functions are used to retrieve a value or structure, NOT
// specific values within structures. (EXCEPTIONS: sUNIS, sUNIx)
// 3. The "SetData" functions, on the other hand, are used to set values or
// values within structures.
// 4. The "CopyData" functions are used to copy large arrays of data.
// 5. See ClassMapSections.cpp for the respective code of the classes below and
// ClassMapStructs.h for the custom structures used within the classes below.
//---------------------------------------------------------------------------
class sTYPE
{
public:
	void SetData(LPSTR String);
	LPSTR GetData();

private:
	LPSTR TypeString;
};
//---------------------------------------------------------------------------
class sVER
{
public:
	void SetData(short Short);
	short GetData();

private:
	short VerShrt;
};
//---------------------------------------------------------------------------
class sIVER
{
public:
	void SetData(short Short);
	short GetData();

private:
	short IverShrt;
};
//---------------------------------------------------------------------------
class sIVE2
{
public:
	void SetData(short Short);
	short GetData();

private:
	short Ive2Shrt;
};
//---------------------------------------------------------------------------
class sVCOD
{
public:
	void SetData(char* ChrArray);
	char* GetData();

private:
	char VcodString[1040];
};
//---------------------------------------------------------------------------
class sIOWN
{
public:
	void CopyData(char* ChrArray);
	void SetData(char Data, char Player);
	char GetData(char Player);
	char* GetDataArray();

private:
	char IownPlayerFlags[12];
};
//---------------------------------------------------------------------------
class sOWNR
{
public:
	void CopyData(char* ChrArray);
	void SetData(char Data, char Player);
	char GetData(char Player);
	char* GetDataArray();

private:
	char OwnrPlayerFlags[12];
};
//---------------------------------------------------------------------------
class sERA
{
public:
	void SetData(short Short);
	short GetData();

public:
	short EraTileset;
};
//---------------------------------------------------------------------------
class sDIM
{
public:
	void SetData(short Short, char Index);
	short GetData(char Index);

private:
	short DimWidth;
	short DimHeight;
};
//---------------------------------------------------------------------------
class sSIDE
{
public:
	void CopyData(char* ChrArray);
	void SetData(char Data, char Player);
	char GetData(char Player);
	char* GetDataArray();

private:
	char SidePlayerRace[12];
};
//---------------------------------------------------------------------------
class sMTXM
{
public:
	sMTXM();
	void Size(short Height, short Width);
	void CopyData(short* ShortArray, unsigned long Length);
	short GetData(short TotalWidth, short Height, short Width);
	void SetData(short TotalWidth, short Height, short Width, short Data);
	short* GetDataArray();
	virtual ~sMTXM();
	
private:
	short* MtxmTileValues;
};
//---------------------------------------------------------------------------
class sPUNI
{
public:
	void CopyData(char* ChrArray, char Index);
	char GetData(unsigned char Unit, unsigned char Player, char Index);
	void SetData(unsigned char Unit, unsigned char Player, char Data, char Index);
	char* GetDataArray(char Index);

private:
	char PuniPlayerAvlblity[2736];
	char PuniGlobalAvlblity[228];
	char PuniUseDefaults[2736];
};
//---------------------------------------------------------------------------
class sUNIT
{
public:
	sUNIT();
	void CopyData(char* DataChunk, unsigned long SectionLength);
	UNIT_NODE* GetData();
	void CreateUnit(UNIT Data);
	bool DeleteUnit(UNIT_NODE* UnitNode);
	void CopyUnit(UNIT_NODE* UnitNode);
	void ReplaceUnit(UNIT_NODE* UnitNode, UNIT Data);
	unsigned long GetDataLength();
	virtual ~sUNIT();

private:
	unsigned long UnitNumberOfUnits;
	UNIT_NODE* UnitCurrentUnits;
	UNIT_NODE* UnitLastUnit;
};
//---------------------------------------------------------------------------
class sISOM
{
public:
	sISOM();
	void CopyData(RECT* RectArray, short Height, short Width);
	RECT GetData(short TotalWidth, short Height, short Width);
	void SetData(short TotalWidth, short Height, short Width, RECT Data);
	RECT* GetDataArray();
	virtual ~sISOM();

private:
	RECT* IsomValues;
};
//---------------------------------------------------------------------------
class sTILE
{
public:
	sTILE();
	void Size(short Height, short Width);
	void CopyData(short* ShortArray, unsigned long Length);
	short GetData(short TotalWidth, short Height, short Width);
	void SetData(short TotalWidth, short Height, short Width, short Data);
	short* GetDataArray();
	virtual ~sTILE();
	
private:
	short* TileTileValues;
};
//---------------------------------------------------------------------------
class sDD2
{
public:
	sDD2();
	void CopyData(char* DataChunk, unsigned long SectionLength);
	DOODAD_UNIT_NODE* GetData();
	void CreateDoodad(DOODAD_UNIT Data);
	bool DeleteDoodad(DOODAD_UNIT_NODE* DoodadUnitNode);
	void CopyDoodad(DOODAD_UNIT_NODE* DoodadUnitNode);
	void ReplaceDoodad(DOODAD_UNIT_NODE* DoodadUnitNode, DOODAD_UNIT Data);
	unsigned long GetDataLength();
	virtual ~sDD2();

private:
	unsigned long Dd2NumberOfDoodads;
	DOODAD_UNIT_NODE* Dd2DoodadUnits;
	DOODAD_UNIT_NODE* Dd2LastDoodad;
};
//---------------------------------------------------------------------------
class sTHG2
{
public:
	sTHG2();
	void CopyData(char* DataChunk, unsigned long SectionLength);
	DOODAD_SPRITE_NODE* GetData();
	void CreateSprite(DOODAD_SPRITE Data);
	bool DeleteSprite(DOODAD_SPRITE_NODE* DoodadSpriteNode);
	void CopySprite(DOODAD_SPRITE_NODE* DoodadSpriteNode);
	void ReplaceSprite(DOODAD_SPRITE_NODE* DoodadSpriteNode, DOODAD_SPRITE Data);
	unsigned long GetDataLength();
	virtual ~sTHG2();

private:
	unsigned long Thg2NumberOfSprites;
	DOODAD_SPRITE_NODE* Thg2DoodadSprites;
	DOODAD_SPRITE_NODE* Thg2LastSprite;
};
//---------------------------------------------------------------------------
class sMASK
{
public:
	sMASK();
	void Size(short Height, short Width);
	void CopyData(char* ChrArray, unsigned long Length);
	char GetData(short TotalWidth, short Height, short Width);
	void SetData(short TotalWidth, short Height, short Width, char Data);
	char* GetDataArray();
	virtual ~sMASK();

private:
	char* MaskFOWTileValues;
};
//---------------------------------------------------------------------------
// This is a pretty screwed up section, so here's what you need to know:
//
// 1. On read, ProcessStringChunk is called (StringFunctions.h), then the pointer
// of the result is passed to CopyData to be used as THE array to work with.
// 2. With SetData, you can independently set the Length part (bad things can
// happen with this if you're not careful... so mostly don't use).
// 3. Whenever you update a string, the "Length" part is automatically updated.
// 4. You can resize the array to be smaller or larger via Index 3 (changes
// StrNumberOfStrings and calls realloc).
class sSTR
{
public:
	sSTR();
	void CopyData(STRING* StringArray, short NumberOfStrings);
	STRING GetData(short StringNumber);
	void SetData(short StringNumber, short Data, LPSTR StringData, char Index);
	short GetDataLength();
	STRING* GetDataArray();
	virtual ~sSTR();

private:
	STRING* StrStrings;
	short StrNumberOfStrings;
};
//---------------------------------------------------------------------------
class sUPRP
{
public:
	CUWPSLOT GetData(char SlotNumber);
	void SetData(char SlotNumber, unsigned long Data, char Index);
	CUWPSLOT* GetDataArray();

private:
	CUWPSLOT UprpCuwpSlots[64];
};
//---------------------------------------------------------------------------
class sUPUS
{
public:
	void CopyData(char* CharArray);
	char GetData(char SlotNumber);
	void SetData(char SlotNumber, char Data);
	char* GetDataArray();

private:
	char UpusCuwpUsedSlots[64];
};
//---------------------------------------------------------------------------
class sMRGN
{
public:
	// BWBit is on for more than 64 locations
	LOCATION GetData(unsigned char LocationNumber);
	void SetData(unsigned char LocationNumber, long Data, char Index);
	char GetBWBit();
	void SetBWBit(char Bit);
	LOCATION* GetDataArray();

private:
	char BWBit;
	LOCATION MrgnLocations[256];
};
//---------------------------------------------------------------------------
class sTRIG
{
public:
	sTRIG();
	void CopyData(char* DataChunk, unsigned long SectionLength);
	TRIGGER_NODE* GetData();
	void CreateTrigger(TRIGGER Data);
	bool DeleteTrigger(TRIGGER_NODE* TriggerNode);
	void CopyTrigger(TRIGGER_NODE* TriggerNode);
	void ReplaceTrigger(TRIGGER_NODE* TriggerNode, TRIGGER Data);
	unsigned long GetDataLength();
	virtual ~sTRIG();

private:
	unsigned long TrigNumberOfTriggers;
	TRIGGER_NODE* TrigTriggers;
	TRIGGER_NODE* TrigLastTrigger;
};
//---------------------------------------------------------------------------
class sSPRP
{
public:
	void SetData(short Data, char Index);
	short GetData(char Index);

private:
	short SprpScenarioName;
	short SprpScenarioDescription;
};
//---------------------------------------------------------------------------
class sFORC
{
public:
	void SetData(short Data, char Index);
	short GetData(char Index);

private:
	char ForcPlayerForce[8];
	short ForcNameStringNumber[4];
	char ForcProperties[4];
};
//---------------------------------------------------------------------------
class sWAV
{
public:
	void CopyData(long* LongArray);
	void SetData(long Data, short WavNumber);
	long GetData(short WavNumber);
	long* GetDataArray();

private:
	long WavStringNumbers[512];
};
//---------------------------------------------------------------------------
class sSWNM
{
public:
	void CopyData(long* LongArray);
	void SetData(long Data, short SwitchNumber);
	long GetData(short SwitchNumber);
	long* GetDataArray();

private:
	long SwnmSwitchNames[256];
};
//---------------------------------------------------------------------------
class sCOLR
{
public:
	void CopyData(unsigned char* CharArray);
	void SetData(unsigned char Data, char PlayerNumber);
	unsigned char GetData(char PlayerNumber);

private:
	unsigned char ColrPlayerColors[8];
};
//---------------------------------------------------------------------------
class sUPGR
{
public:
	// BWBit is on for PUPx
	void CopyData(unsigned char* ChrArray, char Index);
	unsigned char GetData(char Upgrade, char Player, char Index);
	void SetData(char Upgrade, char Player, unsigned char Data, char Index);
	char* GetDataArray(char Index);

private:
	unsigned char UpgrPlayerMax[732];
	unsigned char UpgrPlayerStart[732];
	unsigned char UpgrDefaultMax[61];
	unsigned char UpgrDefaultStart[61];
	char UpgrPlayerOverride[732];
	char BWBit;
};
//---------------------------------------------------------------------------
class sPTEC
{
public:
	// BWBit is on for PTEx
	void CopyData(char* ChrArray, char Index);
	char GetData(char Technology, char Player, char Index);
	void SetData(char Technology, char Player, char Data, char Index);
	char* GetDataArray(char Index);

private:
	char PtecPlayerAvailable[528];
	char PtecPlayerResearched[528];
	char PtecDefaultAvailable[44];
	char PtecDefaultResearched[44];
	char PtecPlayerOverride[528];
	char BWBit;
};
//---------------------------------------------------------------------------
class sUNIS
{
public:
	// BWBit is on for UNIx
	void CopyData(LPVOID DataArray, char Index);
	LPVOID GetData(unsigned char UnitWeapon, char Index);
	void SetData(unsigned char UnitWeapon, LPVOID Data, char Index);
	LPVOID GetDataArray(char Index);

private:
	char UnisUseDefaults[228];
	UNITSETTING UnisHitPointStruct[228];
	unsigned short UnisShieldPoints[228];
	unsigned char UnisArmorPoints[228];
	unsigned short UnisBuildTime[228];
	unsigned short UnisMineralCost[228];
	unsigned short UnisGasCost[228];
	unsigned short UnisStringNumber[228];
	unsigned short UnisWeaponBaseDamage[130];
	unsigned short UnisWeaponBonusDamage[130];
	char BWBit;
};
//---------------------------------------------------------------------------
class sUPGS
{
public:
	// BWBit is on for UPGx
	void CopyData(char* ChrArray, short* ShortArray, char Index);
	short GetData(char Upgrade, char Index);
	void SetData(char Upgrade, unsigned short Data, char Index);
	LPVOID GetDataArray(char Index);

private:
	char UpgsUseDefaults[61];
	unsigned short UpgsBaseMineralCost[61];
	unsigned short UpgsFactorMineralCost[61];
	unsigned short UpgsBaseGasCost[61];
	unsigned short UpgsFactorGasCost[61];
	short UpgsBaseTimeCost[61];
	short UpgsFactorTimeCost[61];
	char BWBit;
};
//---------------------------------------------------------------------------
class sTECS
{
public:
	// BWBit is on for TECx
	void CopyData(char* ChrArray, short* ShortArray, char Index);
	short GetData(char Technology, char Index);
	void SetData(char Technology, unsigned short Data, char Index);
	LPVOID GetDataArray(char Index);

private:
	char TecsUseDefaults[44];
	unsigned short TecsMineralCost[44];
	unsigned short TecsGasCost[44];
	short TecsTimeCost[44];
	unsigned short TecsEnergyCost[44];
	char BWBit;
};
//---------------------------------------------------------------------------
#endif //ifndef _CLASSMAPSECTIONS_H_
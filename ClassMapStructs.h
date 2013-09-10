//Workspace: Progressive Editor
//File Name: ClassMapStructs.h
#ifndef _CLASSMAPSTRUCTS_H_
#define _CLASSMAPSTRUCTS_H_

#include <windows.h>
#include "StringFunctions.h"
//TODO: Research various unknowns in the structures
//---------------------------------------------------------------------------
// The following substructures are for the TRIGGER structure
//---------------------------------------------------------------------------
// Note: They're all named "Value" because they serve many purposes depending
// on the trigger/mission briefing number.
//---------------------------------------------------------------------------
typedef struct _SUBCONDITION
{
	long Value1;
	long Value2;
	long Value3;
	short Value4;
	char Value5;
	char Value6;
	unsigned char Value7;
	char Value8;
	short Unknown1;
} SUBCONDITION;
//---------------------------------------------------------------------------
typedef struct _SUBACTION
{
	long Value1;
	long Value2;
	long Value3;
	unsigned long Value4;
	long Value5;
	long Value6;
	short Value7;
	char Value8;
	char Value9;
	char Value10;
	char Unknown1;
	short Unknown2;
} SUBACTION;
//---------------------------------------------------------------------------
// The following structures are for various classes within the map
// The ones with nodes are used for sections with linked lists (UNIT, DD2,
// THG2, TRIG, and MBRF)
//---------------------------------------------------------------------------
typedef struct _UNIT
{
	unsigned long ID;
	short X;
	short Y;
	short UnitType;
	short BuildingRelation;
	unsigned short FlagProperties;
	unsigned short FlagElements;
	unsigned char PlayerNumber;
	unsigned char HitPoints;
	unsigned char ShieldPoints;
	unsigned char EnergyPoints;
	unsigned long ResourceAmount;
	short UnitsInHangar;
	unsigned short FlagState;
	unsigned long Unknown1;
	unsigned long RelatedID;
} UNIT;
//---------------------------------------------------------------------------
typedef struct _UNIT_NODE
{
	UNIT Unit;
	_UNIT_NODE* Next;
	_UNIT_NODE* Prev;
} UNIT_NODE;
//---------------------------------------------------------------------------
typedef struct _DOODAD_UNIT
{
	short Number;
	short X;
	short Y;
	unsigned char PlayerNumber;
	char Enabled;
} DOODAD_UNIT;
//---------------------------------------------------------------------------
typedef struct _DOODAD_UNIT_NODE
{
	DOODAD_UNIT DoodadUnit;
	_DOODAD_UNIT_NODE* Next;
	_DOODAD_UNIT_NODE* Prev;
} DOODAD_UNIT_NODE;
//---------------------------------------------------------------------------
typedef struct _DOODAD_SPRITE
{
	short UnitNumber;
	short X;
	short Y;
	unsigned char PlayerNumber;
	char Unknown1;
	short Unknown2;
} DOODAD_SPRITE;
//---------------------------------------------------------------------------
typedef struct _DOODAD_SPRITE_NODE
{
	DOODAD_SPRITE DoodadSprite;
	_DOODAD_SPRITE_NODE* Next;
	_DOODAD_SPRITE_NODE* Prev;
} DOODAD_SPRITE_NODE;
//---------------------------------------------------------------------------
typedef struct _CUWPSLOT
{
	unsigned short FlagProperties;
	unsigned short FlagElements;
	char PlayerNumber;
	unsigned char HitPoints;
	unsigned char ShieldPoints;
	unsigned char EnergyPoints;
	unsigned long ResourceAmount;
	short UnitsInHangar;
	unsigned short FlagState;
	unsigned long Unknown2;
} CUWPSLOT;
//---------------------------------------------------------------------------
typedef struct _CUWPSLOT_NODE
{
	CUWPSLOT CuwpSlot;
	_CUWPSLOT_NODE* Next;
	_CUWPSLOT_NODE* Prev;
} CUWPSLOT_NODE;
//---------------------------------------------------------------------------
typedef struct _LOCATION
{
	RECT Coordinates;
	short StringNumber;
	short ElevationFlags;
} LOCATION;
//---------------------------------------------------------------------------
typedef struct _TRIGGER
{
	SUBCONDITION Conditions[16];
	SUBACTION Actions[64];
	long Unknown;
	char PlayersExecuted[28];
} TRIGGER;
//---------------------------------------------------------------------------
typedef struct _TRIGGER_NODE
{
	TRIGGER Trigger;
	_TRIGGER_NODE* Next;
	_TRIGGER_NODE* Prev;
} TRIGGER_NODE;
//---------------------------------------------------------------------------
typedef struct _UNITSETTING
{
	char Unknown;
	short HitPoints;
	char Invincible;
} UNITSETTING;
//---------------------------------------------------------------------------
// This structure is where some of the map corruption data is set (basically
// what needs to be corrected, NOT included is the stuff that is done mandatory)
//---------------------------------------------------------------------------
struct CORRUPTION
{
	// Conditional values for checkboxes
	bool Strings1024;
	bool LocationsMessed;
	bool SwitchesMessed;
	bool UnitsMessed;
	bool DeleteComments;
	bool FakeISOM;
	bool RebuildTILE;
};
//---------------------------------------------------------------------------
// This structure is where the location and presence of a section is stored,
// as well as its section length
//---------------------------------------------------------------------------
struct SECTIONINFORMATION
{
	DWORD offsetTYPE;
	bool preTYPE;
	DWORD slTYPE;
	DWORD offsetVER;
	bool preVER;
	DWORD slVER;
	DWORD offsetIVER;
	bool preIVER;
	DWORD slIVER;
	DWORD offsetIVE2;
	bool preIVE2;
	DWORD slIVE2;
	DWORD offsetVCOD;
	bool preVCOD;
	DWORD slVCOD;
	DWORD offsetIOWN;
	bool preIOWN;
	DWORD slIOWN;
	DWORD offsetOWNR;
	bool preOWNR;
	DWORD slOWNR;
	DWORD offsetERA;
	bool preERA;
	DWORD slERA;
	DWORD offsetDIM;
	bool preDIM;
	DWORD slDIM;
	DWORD offsetSIDE;
	bool preSIDE;
	DWORD slSIDE;
	bool preMTXM;
	DWORD slMTXM;
	DWORD offsetPUNI;
	bool prePUNI;
	DWORD slPUNI;
	DWORD offsetUNIT;
	bool preUNIT;
	DWORD slUNIT;
	DWORD offsetISOM;
	bool preISOM;
	DWORD slISOM;
	bool preTILE;
	DWORD slTILE;
	DWORD offsetDD2;
	bool preDD2;
	DWORD slDD2;
	DWORD offsetTHG2;
	bool preTHG2;
	DWORD slTHG2;
	bool preMASK;
	DWORD slMASK;
	DWORD offsetSTR;
	bool preSTR;
	DWORD slSTR;
	DWORD offsetUPRP;
	bool preUPRP;
	DWORD slUPRP;
	DWORD offsetUPUS;
	bool preUPUS;
	DWORD slUPUS;
	DWORD offsetMRGN;
	bool preMRGN;
	DWORD slMRGN;
	DWORD offsetTRIG;
	bool preTRIG;
	DWORD slTRIG;
	DWORD offsetMBRF;
	bool preMBRF;
	DWORD slMBRF;
	DWORD offsetSPRP;
	bool preSPRP;
	DWORD slSPRP;
	DWORD offsetFORC;
	bool preFORC;
	DWORD slFORC;
	DWORD offsetWAV;
	bool preWAV;
	DWORD slWAV;
	DWORD offsetSWNM;
	bool preSWNM;
	DWORD slSWNM;
	DWORD offsetCOLR;
	bool preCOLR;
	DWORD slCOLR;
	DWORD offsetPUPx;
	bool prePUPx;
	DWORD slPUPx;
	DWORD offsetUPGR;
	bool preUPGR;
	DWORD slUPGR;
	DWORD offsetPTEx;
	bool prePTEx;
	DWORD slPTEx;
	DWORD offsetPTEC;
	bool prePTEC;
	DWORD slPTEC;
	DWORD offsetUNIx;
	bool preUNIx;
	DWORD slUNIx;
	DWORD offsetUNIS;
	bool preUNIS;
	DWORD slUNIS;
	DWORD offsetUPGx;
	bool preUPGx;
	DWORD slUPGx;
	DWORD offsetUPGS;
	bool preUPGS;
	DWORD slUPGS;
	DWORD offsetTECx;
	bool preTECx;
	DWORD slTECx;
	DWORD offsetTECS;
	bool preTECS;
	DWORD slTECS;
};
//---------------------------------------------------------------------------
#endif //ifndef _CLASSMAPSTRUCTS_H_
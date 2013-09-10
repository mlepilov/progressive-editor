//Workspace: Progressive Editor
//File Name: ClassMap.h
#ifndef _CLASSMAP_H_
#define _CLASSMAP_H_

#include <windows.h>
#include "ClassMapSections.h"
#include "LocalFileFunctions.h"
#include "lib/lmpqapi/LMPQAPI.h"
//---------------------------------------------------------------------------
// This is the map class itself that contains all the specific classes and the handle to the file
//---------------------------------------------------------------------------
class MapClass
{
public:
	// Constructor opens a file for writing and returns the handle to CurrentMap
	// Also, it sets CurrentMapSize as the file size of the map and "sorts out" mpq stuff
	// Destructor deletes any temp files caused by mpq opening
	MapClass(LPSTR FileName, HWND* EditBox, LOCALFILEDATA* LocalFileData);
	virtual ~MapClass();

	// GUI methods
	void AnnexEditMessage(char* Message);

	// Methods used for getting data from private
	HANDLE GetCurrentArchive();
	short GetFilesInArchive();
	HANDLE GetCurrentMap();
	SECTIONINFORMATION GetSectionInfo();
	char* GetMapPath();

	// Methods used for various actions within the class
	// Scan: determines the place of each section, as well as map dimentions and version path
	char Scan(HANDLE Map);						// Scan: classifies each section into memory
	void Read(HANDLE Map);						// Save: saves each section into a map .chk
	void Save(LPSTR FileName, DWORD FileExt);	// Detect: partly configures Corruption and
	BYTE Detect();								// returns which checkboxes are not applicable
	char Repair(BYTE Settings);

	// String methods (see StringFunctions.cpp)
	// When using AddString, DeleteString, or EditString, unlink the strings from known instances
	// before using them
	// DetectStringUsage: determines all string usage across all sections if String == 0xFFFF,
	// otherwise it determines the usage of the string with the number "String"
	void DetectStringUsage(WORD String);			// AddString: references another existing string
	WORD AddString(LPSTR String);					// or creates a new one, returns string number
	WORD EditString(LPSTR NewString, WORD String);	// EditString: checks usage & either changes the
	void DeleteString(WORD String);					// same string or calls AddString, returns string #
													// DeleteString: checks usage & blanks a string
private:
	// GUI stuff
	HWND* m_pEditBox;

	// General I/O stuff
	HANDLE CurrentArchive;
	short FilesInArchive;
	HANDLE CurrentMap;
	DWORD CurrentMapSize;
	char CurrentMapPath[MAX_PATH];

	// General map stuff
	SECTIONINFORMATION SectionInfo;
	CORRUPTION Corruption;
	// Local file data structure pointer
	LOCALFILEDATA* m_pLocalFileData;
	// If the BW code path is chosen, this is 2. If 1.04 is chosen, this is 1. If it's none
	// of the previous options, this is 0.
	char BWUsed;

	// Individual section classes, see ClassMapSections.h
	sTYPE sType;
	sVER sVer;
	sIVER sIver;
	sIVE2 sIve2;
	sVCOD sVcod;
	sIOWN sIown;
	sOWNR sOwnr;
	sERA sEra;
	sDIM sDim;
	sSIDE sSide;
	sMTXM sMtxm;
	sPUNI sPuni;
	sUNIT sUnit;
	sISOM sIsom;
	sTILE sTile;
	sDD2 sDd2;
	sTHG2 sThg2;
	sMASK sMask;
	sSTR sStr;
	sUPRP sUprp;
	sUPUS sUpus;
	sMRGN sMrgn;
	sTRIG sTrig;
	sTRIG sMbrf;
	sSPRP sSprp;
	sFORC sForc;
	sWAV sWav;
	sSWNM sSwnm;
	sCOLR sColr;
	sUPGR sUpgr;
	sPTEC sPtec;
	sUNIS sUnis;
	sUPGS sUpgs;
	sTECS sTecs;
	sUPGR sPupX;
	sPTEC sPteX;
	sUNIS sUniX;
	sUPGS sUpgX;
	sTECS sTecX;
};
//---------------------------------------------------------------------------
#endif //ifndef _CLASSMAP_H_
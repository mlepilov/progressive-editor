//Workspace: Progressive Editor
//File Name: LocalFileFunctions.h
#ifndef _LOCALFILEFUNCTIONS_H_
#define _LOCALFILEFUNCTIONS_H_

#include <windows.h>
//---------------------------------------------------------------------------
// Here is the local file manipulation function (VCOD.bin, .mpq detection,
// manipulation of terrain files), along with the local file data structure
//---------------------------------------------------------------------------
typedef struct _LOCALFILEDATA
{
	char VCODbin[1040];
} LOCALFILEDATA;
//---------------------------------------------------------------------------
char GetLocalFileData(LOCALFILEDATA* m_pLocalFileData);
//---------------------------------------------------------------------------
#endif //ifndef _LOCALFILEFUNCTIONS_H_
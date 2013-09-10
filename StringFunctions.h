//Workspace Name: Progressive Editor
//File Name: StringFunctions.h
#ifndef _STRINGFUNCTIONS_H_
#define _STRINGFUNCTIONS_H_

#include <windows.h>
//---------------------------------------------------------------------------
struct STRING
{
	LPSTR Data;
	unsigned short Length;	// Not including null-terminator
	unsigned short Offset;	// Offset given from STR; mainly for debugging purposes
	char Used;				// 00 for no, 01 for yes
};
//---------------------------------------------------------------------------
STRING* ProcessStringChunk(LPVOID StringChunk, unsigned long SectionLength);
//---------------------------------------------------------------------------
#endif //ifndef _STRINGFUNCTIONS_H_
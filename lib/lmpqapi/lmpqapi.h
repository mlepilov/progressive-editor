/*

  Lelik's MPQ API Library. (c) Andrey lelikov, Moscow 1999.
  
  All functions below are actually located in storm.dll or staredit.exe.
  This library loads staredit.exe in "server" mode, and interacts as
  "client", providing a gateway to call mpq-related functions.

  Revision History:
  2000/11 2.00 (quantam@softhome.net)
  + 1 year anniversary blowout, including:
  - New coauthor (hi!)
  - Renamed Storm-based functions to "SFile" prefix to avoid confusion
  - Added MpqAddWAVToArchive, MpqRenameFile, MpqCompactArchive,
    SFileGetFileInfo, and MpqGetVersion functions
  - Figured out all but 2 of the unknown parameters in all functions combined
  - Added full error-handling capabilities through GetLastError()
  - Improved reliability a bit
  - LMPQAPI now requires StarEdit.exe from either Starcraft or Brood War 1.07.
    No other versions will work
  - Working on a comprehensive user's manual right now

  2000/01 1.04 (alelikov@mtu-net.ru)
  - Added function MpqDeleteFile

  2000/01 1.03 (alelikov@mtu-net.ru)
  - Discovered last parameter in MpqOpenArchiveForUpdate

  1999/12 1.02 (alelikov@mtu-net.ru)
  - Added constants for MOAU_MAINTAIN_LISTFILE & MAFA_REPLACE_EXISTING flags.

  1999/11 1.00 (alelikov@mtu-net.ru)
  - First version.

  This library is freeware, you can do anything you want with it but with
  one exception. If you use it in your program, you must specify this fact
  in Help|About box or in similar way. You can obtain version string using
  MpqGetVersionString call.

  THIS LIBRARY IS DISTRIBUTED "AS IS".  NO WARRANTY OF ANY KIND IS EXPRESSED
  OR IMPLIED. YOU USE AT YOUR OWN RISK. THE AUTHOR WILL NOT BE LIABLE FOR 
  DATA LOSS, DAMAGES, LOSS OF PROFITS OR ANY OTHER KIND OF LOSS WHILE USING
  OR MISUSING THIS SOFTWARE.

  Any comments or suggestions are accepted at ALelikov@mtu-net.ru (Lelik) or omega@dragonfire.net (Quantam)
*/

#ifndef LMPQAPI_H_INCLUDED
#define LMPQAPI_H_INCLUDED

#ifdef LMPQAPI_EXPORTS
#define LMPQAPI __declspec(dllexport)
#else
#define LMPQAPI __declspec(dllimport)
#endif

#ifdef __cplusplus
extern "C" {
#endif

BOOL   LMPQAPI WINAPI MpqInitialize();
LPCSTR LMPQAPI WINAPI MpqGetVersionString();
float  LMPQAPI WINAPI MpqGetVersion();

//General error codes
#define MPQ_ERROR_INIT_FAILED      0x85000001 //Unspecified error
#define MPQ_ERROR_NO_STAREDIT      0x85000002 //Can't find StarEdit.exe
#define MPQ_ERROR_BAD_STAREDIT     0x85000003 //Bad version of StarEdit.exe. Need SC/BW 1.07
#define MPQ_ERROR_STAREDIT_RUNNING 0x85000004 //StarEdit.exe is running. Must be closed

#define MPQ_ERROR_MPQ_INVALID      0x85200065
#define MPQ_ERROR_FILE_NOT_FOUND   0x85200066
#define MPQ_ERROR_DISK_FULL        0x85200068 //Physical write file to MPQ failed. Not sure of exact meaning
#define MPQ_ERROR_HASH_TABLE_FULL  0x85200069
#define MPQ_ERROR_ALREADY_EXISTS   0x8520006A
#define MPQ_ERROR_BAD_OPEN_MODE    0x8520006C //When MOAU_READ_ONLY is used without MOAU_OPEN_EXISTING

#define MPQ_ERROR_COMPACT_ERROR    0x85300001

//MpqOpenArchiveForUpdate flags
#define MOAU_CREATE_NEW        0x00
#define MOAU_CREATE_ALWAYS     0x08 //Was wrongly named MOAU_CREATE_NEW
#define MOAU_OPEN_EXISTING     0x04
#define MOAU_OPEN_ALWAYS       0x20
#define MOAU_READ_ONLY         0x10 //Must be used with MOAU_OPEN_EXISTING
#define MOAU_MAINTAIN_LISTFILE 0x01

// AddFileToArchive flags
#define MAFA_EXISTS           0x80000000 //Will be added if not present
#define MAFA_UNKNOWN40000000  0x40000000
#define MAFA_MODCRYPTKEY      0x00020000
#define MAFA_ENCRYPT          0x00010000
#define MAFA_COMPRESS         0x00000200
#define MAFA_COMPRESS2        0x00000100
#define MAFA_REPLACE_EXISTING 0x00000001

// AddWAVToArchive flags
#define MAWA_QUALITY_HIGH    1
#define MAWA_QUALITY_MEDIUM  0
#define MAWA_QUALITY_LOW     2

// SFileGetFileInfo flags
#define SFILE_INFO_BLOCK_SIZE      0x01 //Block size in MPQ
#define SFILE_INFO_HASH_TABLE_SIZE 0x02 //Hash table size in MPQ
#define SFILE_INFO_NUM_FILES       0x03 //Number of files in MPQ
#define SFILE_INFO_TYPE            0x04 //Is MPQHANDLE a file or an MPQ?
#define SFILE_INFO_SIZE            0x05 //Size of MPQ or uncompressed file
#define SFILE_INFO_COMPRESSED_SIZE 0x06 //Size of compressed file
#define SFILE_INFO_FLAGS           0x07 //File flags (compressed, etc.)
#define SFILE_INFO_PARENT          0x08 //Handle of MPQ that file is in
#define SFILE_INFO_POSITION        0x09 //Position of file pointer in files

#define SFILE_TYPE_MPQ  0x01
#define SFILE_TYPE_FILE 0x02

typedef HANDLE MPQHANDLE;

// Defines for backward compatability with old function names
#define MpqAddFileToArcive MpqAddFileToArchive
#define MpqOpenArchive     SFileOpenArchive
#define MpqOpenFileEx      SFileOpenFileEx
#define MpqGetFileSize     SFileGetFileSize
#define MpqReadFile        SFileReadFile
#define MpqCloseFile       SFileCloseFile
#define MpqCloseArchive    SFileCloseArchive

// Staredit Function Prototypes
MPQHANDLE LMPQAPI WINAPI MpqOpenArchiveForUpdate(LPCSTR lpFileName, DWORD dwFlags, DWORD dwMaximumFilesInArchive);
DWORD     LMPQAPI WINAPI MpqCloseUpdatedArchive(MPQHANDLE hMPQ, DWORD dwUnknown2);
BOOL      LMPQAPI WINAPI MpqAddFileToArchive(MPQHANDLE hMPQ, LPCSTR lpSourceFileName, LPCSTR lpDestFileName, DWORD dwFlags);
BOOL      LMPQAPI WINAPI MpqAddWaveToArchive(MPQHANDLE hMPQ, LPCSTR lpSourceFileName, LPCSTR lpDestFileName, DWORD dwFlags, DWORD dwQuality);
BOOL      LMPQAPI WINAPI MpqRenameFile(MPQHANDLE hMPQ, LPCSTR lpcOldFileName, LPCSTR lpcNewFileName);
BOOL      LMPQAPI WINAPI MpqDeleteFile(MPQHANDLE hMPQ, LPCSTR lpFileName);
BOOL      LMPQAPI WINAPI MpqCompactArchive(MPQHANDLE hMPQ);

// Storm Function Prototypes
BOOL  LMPQAPI WINAPI SFileOpenArchive(LPCSTR lpFilename, DWORD dwMPQID, DWORD p3, MPQHANDLE *hMPQ);
BOOL  LMPQAPI WINAPI SFileCloseArchive(MPQHANDLE hMPQ);
BOOL  LMPQAPI WINAPI SFileOpenFileEx(MPQHANDLE hMPQ, LPCSTR lpFileName, DWORD dwFlags, MPQHANDLE *hFile);
BOOL  LMPQAPI WINAPI SFileCloseFile(MPQHANDLE hFile);
DWORD LMPQAPI WINAPI SFileGetFileSize(MPQHANDLE hFile, DWORD dwFlags);
DWORD LMPQAPI WINAPI SFileGetFileInfo(MPQHANDLE hFile, DWORD dwInfoType);
DWORD LMPQAPI WINAPI SFileSetFilePointer(MPQHANDLE hFile, long lDistanceToMove, PLONG lplDistanceToMoveHigh, DWORD dwMoveMethod);
BOOL  LMPQAPI WINAPI SFileReadFile(MPQHANDLE hFile,LPVOID lpBuffer,DWORD nNumberOfBytesToRead,LPDWORD lpNumberOfBytesRead,LPOVERLAPPED lpOverlapped);
LCID  LMPQAPI WINAPI SFileSetLocale(LCID nNewLocale);

#ifdef __cplusplus
};  // extern "C" 
#endif

#endif

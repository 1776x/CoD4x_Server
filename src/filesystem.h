/*
===========================================================================
    Copyright (C) 2010-2013  Ninja and TheKelm
    Copyright (C) 1999-2005 Id Software, Inc.

    This file is part of CoD4X18-Server source code.

    CoD4X18-Server source code is free software: you can redistribute it and/or modify
    it under the terms of the GNU Affero General Public License as
    published by the Free Software Foundation, either version 3 of the
    License, or (at your option) any later version.

    CoD4X18-Server source code is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU Affero General Public License for more details.

    You should have received a copy of the GNU Affero General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>
===========================================================================
*/



#ifndef __FILESYSTEM_H__
#define __FILESYSTEM_H__

#include "q_shared.h"
#include "cvar.h"
#include "zlib/unzip.h"
#include "filesystem_types.h"
/* #define fs_searchpaths (searchpath_t*)*((int*)(0x13f9da28)) */

// TTimo - https://zerowing.idsoftware.com/bugzilla/show_bug.cgi?id=540
// wether we did a reorder on the current search path when joining the server

// last valid game folder used

#ifdef FS_MISSING
FILE*		missingFiles = NULL;
#endif

extern cvar_t*	fs_homepath;
extern cvar_t*	fs_debug;
extern cvar_t*	fs_basepath;
extern cvar_t*	fs_gameDirVar;



void FS_CopyFile(char* FromOSPath,char* ToOSPath);
int FS_Read(void* data, int length, fileHandle_t);
long FS_FOpenFileRead(const char* filename, fileHandle_t* returnhandle);
long FS_FOpenFileReadThread1(const char* filename, fileHandle_t* returnhandle);
long FS_FOpenFileReadThread2(const char* filename, fileHandle_t* returnhandle);
fileHandle_t FS_FOpenFileWrite(const char* filename);
fileHandle_t FS_FOpenFileAppend(const char* filename);
qboolean FS_Initialized();
int FS_filelength( fileHandle_t f );

qboolean FS_HomeRemove( const char *path );
qboolean FS_SV_HomeRemove( const char *path );

qboolean FS_FileExists( const char *file );
qboolean FS_SV_FileExists( const char *file );
qboolean FS_SV_HomeFileExists( const char *file );

char* FS_SV_GetFilepath( const char *file, char* buf, int buflen );

void FS_Rename( const char *from, const char *to );
void FS_SV_Rename( const char *from, const char *to );
qboolean FS_FCloseFile( fileHandle_t f );
qboolean FS_FilenameCompare( const char *s1, const char *s2 );
char *FS_ShiftedStrStr(const char *string, const char *substring, int shift);
long FS_fplength(FILE *h);

qboolean FS_IsExt(const char *filename, const char *ext, int namelen);

void FS_ConvertPath( char *s );

int FS_PathCmp( const char *s1, const char *s2 );
int	FS_FTell( fileHandle_t f );
void	FS_Flush( fileHandle_t f );
void FS_FreeFile( void *buffer );
void FS_FreeFileKeepBuf( );
void FS_FreeFileOSPath( void *buffer );
int FS_ReadLine( void *buffer, int len, fileHandle_t f );
fileHandle_t FS_SV_FOpenFileWrite( const char *filename );
long FS_SV_FOpenFileRead( const char *filename, fileHandle_t *fp );
fileHandle_t FS_SV_FOpenFileAppend( const char *filename );
int FS_Write( const void *buffer, int len, fileHandle_t h );
int FS_ReadFile( const char *qpath, void **buffer );
int FS_ReadFileOSPath( const char *ospath, void **buffer );
int FS_SV_ReadFile( const char *qpath, void **buffer );
int FS_WriteFile( const char *qpath, const void *buffer, int size );

#define FS_SV_WriteFile FS_SV_HomeWriteFile
int FS_SV_HomeWriteFile( const char *qpath, const void *buffer, int size );
int FS_SV_BaseWriteFile( const char *qpath, const void *buffer, int size );
void FS_BuildOSPathForThread(const char *base, const char *game, const char *qpath, char *fs_path, int fs_thread);

void QDECL FS_Printf( fileHandle_t h, const char *fmt, ... );
int FS_Seek( fileHandle_t f, long offset, int origin );
__cdecl const char* FS_GetBasepath();
qboolean FS_VerifyPak( const char *pak );
void	FS_ForceFlush( fileHandle_t f );
void __cdecl FS_InitFilesystem(void);
void __cdecl FS_Shutdown(qboolean);
void __cdecl FS_ShutdownIwdPureCheckReferences(void);
void __cdecl FS_ShutdownServerIwdNames(void);
void __cdecl FS_ShutdownServerReferencedIwds(void);
void __cdecl FS_ShutdownServerReferencedFFs(void);
const char* __cdecl FS_LoadedIwdPureChecksums(void);
void FS_LoadedPaks(char* outsums, char* outnames, int maxlen);
char* __cdecl FS_GetMapBaseName( const char* mapname );
qboolean FS_CreatePath (char *OSPath);
void FS_SV_HomeCopyFile(char* from, char* to);
void FS_Restart(int checksumfeed);

void __cdecl FS_Startup(const char* game);
void FS_InitCvars();
unsigned Com_BlockChecksumKey32( void *buffer, int length, int key );
void FS_PatchFileHandleData();
int FS_LoadStack();
void FS_CopyCvars();
qboolean FS_SV_BaseRemove( const char *path );

void FS_RemoveOSPath(const char *);
qboolean FS_FileExistsOSPath( const char *ospath );
void FS_RenameOSPath( const char *from_ospath, const char *to_ospath );
qboolean FS_SetPermissionsExec(const char* ospath);
__regparm3 void DB_BuildOSPath(const char *filename, int ffdir, int len, char *buff);
void DB_BuildQPath(const char *filename, int ffdir, int len, char *buff);
int     FS_FOpenFileByMode( const char *qpath, fileHandle_t *f, fsMode_t mode );
void FS_ReferencedPaks(char *outChkSums, char *outPathNames, int maxlen);
void FS_AddIwdPureCheckReference(searchpath_t *search);
void FS_StripSeperators(char* path);
void FS_StripTrailingSeperator( char *path );
void FS_ReplaceSeparators( char *path );
int FS_CalculateChecksumForFile(const char* filename, int *crc32);
int FS_WriteChecksumInfo(const char* filename, byte* data, int maxsize);
int FS_WriteFileOSPath( char *ospath, const void *buffer, int size );
void FS_ClearPakReferences( int flags );
int FS_filelengthForOSPath( const char* ospath );
#endif

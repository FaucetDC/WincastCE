/*++
THIS CODE AND INFORMATION IS PROVIDED "AS IS" WITHOUT WARRANTY OF
ANY KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED TO
THE IMPLIED WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A
PARTICULAR PURPOSE.
Copyright (c) 1995-1998  Microsoft Corporation

Module Name:  

mwindbas.h

Abstract:

private portion of windbase.h

Notes: 


--*/
   
   
    
#ifndef _MACRO_WINDBASE_H_
#define _MACRO_WINDBASE_H_

#ifndef WINCEMACRO
#error WINCEMACRO not defined __FILE__
#endif

// SDK functions
#define CeOidGetInfoEx WIN32_FS_CALL(BOOL, 12, (PCEGUID pguid, CEOID oid, CEOIDINFO *oidInfo))
#define CeFindFirstDatabaseEx WIN32_FS_CALL(HANDLE, 13, (PCEGUID pguid, DWORD dwClassID))
#define CeFindNextDatabaseEx WIN32_DBFIND_CALL(CEOID, 2, (HANDLE hEnum, PCEGUID pguid))
#define CeCreateDatabaseEx WIN32_FS_CALL(CEOID, 14, (PCEGUID pguid, CEDBASEINFO *pInfo))
#define CeSetDatabaseInfoEx WIN32_FS_CALL(BOOL, 15, (PCEGUID pguid, CEOID oidDbase, CEDBASEINFO *pNewInfo))
#define CeOpenDatabaseEx WIN32_FS_CALL(HANDLE, 16, (PCEGUID pguid, PCEOID poid, LPWSTR lpszName, CEPROPID propid, DWORD dwFlags, CENOTIFYREQUEST *pRequest))
#define CeDeleteDatabaseEx WIN32_FS_CALL(BOOL, 28, (PCEGUID pguid, CEOID oid))
#define CeSeekDatabase WIN32_DBFILE_CALL(CEOID, 2, (HANDLE hDatabase, DWORD dwSeekType, DWORD dwValue, LPDWORD lpdwIndex))
#define CeDeleteRecord WIN32_DBFILE_CALL(BOOL, 3, (HANDLE hDatabase, CEOID oidRecord))
#define CeReadRecordPropsEx WIN32_DBFILE_CALL(CEOID, 4, (HANDLE hDbase, DWORD dwFlags, LPWORD lpcPropID, CEPROPID *rgPropID, LPBYTE *lplpBuffer, LPDWORD lpcbBuffer, HANDLE hHeap))
#define CeWriteRecordProps WIN32_DBFILE_CALL(CEOID, 5, (HANDLE hDbase, CEOID oidRecord, WORD cPropID, CEPROPVAL *rgPropVal))
#define CeMountDBVol WIN32_FS_CALL(BOOL, 58, (PCEGUID pguid, LPWSTR lpszVol, DWORD dwFlags))
#define CeUnmountDBVol WIN32_FS_CALL(BOOL, 60, (PCEGUID pguid))
#define CeFlushDBVol WIN32_FS_CALL(BOOL, 61, (PCEGUID pguid))
#define CeEnumDBVolumes WIN32_FS_CALL(BOOL, 59, (PCEGUID pguid, LPWSTR lpBuf, DWORD dwSize))
#define GetStoreInformation WIN32_FS_CALL(BOOL, 32, (LPSTORE_INFORMATION lpsi))
#define CeFreeNotification WIN32_FS_CALL(BOOL, 62, (PCENOTIFYREQUEST pRequest, PCENOTIFICATION pNotify))

// OAK functions  
#define CeGetReplChangeMask WIN32_FS_CALL(BOOL, 33, (LPDWORD lpmask))
#define CeSetReplChangeMask WIN32_FS_CALL(BOOL, 34, (DWORD mask))
#define CeGetReplChangeBitsEx WIN32_FS_CALL(BOOL, 35, (PCEGUID pguid, CEOID oid, LPDWORD lpbits, DWORD dwFlags))
#define CeSetReplChangeBitsEx WIN32_FS_CALL(BOOL, 51, (PCEGUID pguid, CEOID oid, DWORD mask))
#define CeClearReplChangeBitsEx WIN32_FS_CALL(BOOL, 36, (PCEGUID pguid, CEOID oid, DWORD mask))
#define CeGetReplOtherBitsEx WIN32_FS_CALL(BOOL, 37, (PCEGUID pguid, CEOID oid, LPDWORD lpbits))
#define CeSetReplOtherBitsEx WIN32_FS_CALL(BOOL, 38, (PCEGUID pguid, CEOID oid, DWORD bits))
#define CeChangeDatabaseLCID WIN32_FS_CALL(VOID, 56, (PCEGUID pguid, DWORD LCID))
#define CeRegisterFileSystemNotification WIN32_FS_CALL(BOOL, 10, (HWND hWnd))
#define CeRegisterReplNotification WIN32_FS_CALL(BOOL, 11, (CENOTIFYREQUEST *pRequest))
#define RegisterAFS WIN32_FS_CALL (BOOL, 45, (int index, HANDLE h, DWORD dw, DWORD version))
#define RegisterHiddenAFS WIN32_FS_CALL (BOOL, 55, (int index, HANDLE h, DWORD dw, DWORD version))
#define DeregisterAFS WIN32_FS_CALL (BOOL, 46, (int index))
#define GetSystemMemoryDivision WIN32_FS_CALL(BOOL, 39, (LPDWORD lpdwStorePages, LPDWORD lpdwRamPages, LPDWORD lpdwPageSize))
#define SetSystemMemoryDivision WIN32_FS_CALL(DWORD, 40, (DWORD dwStorePages))

#define RegisterAFSName WIN32_FS_CALL(int,52,(LPCWSTR pName))
#define DeregisterAFSName WIN32_FS_CALL(BOOL,53,(int index))

#define DumpFileSystemHeap WIN32_FS_CALL(void,57,(void))

#endif //_MACRO_WINDBASE_H_
    

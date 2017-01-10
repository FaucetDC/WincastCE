/*++
THIS CODE AND INFORMATION IS PROVIDED "AS IS" WITHOUT WARRANTY OF
ANY KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED TO
THE IMPLIED WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A
PARTICULAR PURPOSE.
Copyright (c) 1995-1998  Microsoft Corporation

Module Name:  

mwinbase.h

Abstract:  

Notes: 


--*/

#ifndef __MWINBASE_H__
#define __MWINBASE_H__

#ifndef WINCEMACRO
#error WINCEMACRO not defined __FILE__
#endif

/* Win32 Base Dir API Function Indices */
#define WIN32_FS_CALL(type, api, args) (*(type (*) args)IMPLICIT_CALL(SH_FILESYS_APIS, api))
#define WIN32_DEV_CALL(type, api, args) (*(type (*) args)IMPLICIT_CALL(SH_DEVMGR_APIS, api))
#define WIN32_FILE_CALL(type, api, args) (*(type (*) args)IMPLICIT_CALL(HT_FILE, api))
#define WIN32_FIND_CALL(type, api, args) (*(type (*) args)IMPLICIT_CALL(HT_FIND, api))
#define WIN32_DBFILE_CALL(type, api, args) (*(type (*) args)IMPLICIT_CALL(HT_DBFILE, api))
#define WIN32_DBFIND_CALL(type, api, args) (*(type (*) args)IMPLICIT_CALL(HT_DBFIND, api))

// external exports from filesys
#define CreateDirectoryW WIN32_FS_CALL(BOOL, 2, (LPCWSTR lpPathName, LPSECURITY_ATTRIBUTES lpSecurityAttributes))
#define RemoveDirectoryW WIN32_FS_CALL(BOOL, 3, (LPCWSTR lpPathName))
#define MoveFileW WIN32_FS_CALL(BOOL, 4, (LPCWSTR lpExistingFileName, LPCWSTR lpNewFileName))
#define CopyFileW WIN32_FS_CALL(BOOL, 5, (LPCTSTR  lpszExistingFile, LPCTSTR  lpszNewFile, BOOL  fFailIfExists))
#define DeleteFileW WIN32_FS_CALL(BOOL, 6, (LPCWSTR lpFileName))
#define GetFileAttributesW WIN32_FS_CALL(DWORD, 7, (LPCTSTR  lpFileName))
#define FindFirstFileW WIN32_FS_CALL(HANDLE, 8, (LPCWSTR lpFileName, LPWIN32_FIND_DATAW lpFindFileData))
#define CreateFileW WIN32_FS_CALL(HANDLE, 9, (LPCTSTR lpFileName, DWORD dwDesiredAccess, DWORD dwShareMode, LPSECURITY_ATTRIBUTES lpSecurityAttributes, DWORD dwCreationDisposition, DWORD dwFlagsAndAttributes, HANDLE hTemplateFile))

#define SetFileAttributesW WIN32_FS_CALL(BOOL, 31, (LPCWSTR lpszName, DWORD dwAttributes))
#define GetStoreInformation WIN32_FS_CALL(BOOL, 32, (LPSTORE_INFORMATION lpsi))

#define ReadFile WIN32_FILE_CALL(BOOL, 2, (HANDLE hFile, LPVOID lpBuffer, DWORD nNumberOfBytesToRead, LPDWORD lpNumberOfBytesRead, LPOVERLAPPED lpOverlapped))
#define WriteFile WIN32_FILE_CALL(BOOL, 3, (HANDLE hFile, LPCVOID lpBuffer, DWORD nNumberOfBytesToWrite,   LPDWORD lpNumberOfBytesWritten, LPOVERLAPPED lpOverlapped))
#define GetFileSize WIN32_FILE_CALL(DWORD, 4, (HANDLE hFile, LPDWORD lpFileSizeHigh))
#define SetFilePointer WIN32_FILE_CALL(DWORD, 5, (HANDLE hFile, LONG lDistanceToMove, PLONG lpDistanceToMoveHigh, DWORD dwMoveMethod))
#define GetFileInformationByHandle WIN32_FILE_CALL(DWORD, 6, (HANDLE hFile, LPBY_HANDLE_FILE_INFORMATION lpFileInformation))
#define FlushFileBuffers WIN32_FILE_CALL(BOOL, 7, (HANDLE hFile))
#define GetFileTime WIN32_FILE_CALL(BOOL, 8, (HANDLE hFile, LPFILETIME lpCreation, LPFILETIME lpLastAccess, LPFILETIME lpLastWrite))
#define SetFileTime WIN32_FILE_CALL(BOOL, 9, (HANDLE hFile, CONST FILETIME *lpCreation, CONST FILETIME *lpLastAccess, CONST FILETIME *lpLastWrite))
#define SetEndOfFile WIN32_FILE_CALL(BOOL, 10, (HANDLE hFile))
#define DeviceIoControl WIN32_FILE_CALL(BOOL, 11, (HANDLE hDevice, DWORD dwIoControlCode, LPVOID lpInBuf, DWORD nInBufSize, LPVOID lpOutBuf, DWORD nOutBufSize, LPDWORD lpBytesReturned, LPOVERLAPPED lpOverlapped))

#define FindClose WIN32_FIND_CALL(BOOL, 0, (HANDLE hFindFile))
#define FindNextFileW WIN32_FIND_CALL(BOOL, 2, (HANDLE hFindFile, LPWIN32_FIND_DATAW lpFindFileData))
#define DeleteAndRenameFile WIN32_FS_CALL (BOOL, 43, (LPCWSTR lpszOldFile, LPCWSTR lpszNewFile))
#define CheckPassword WIN32_FS_CALL (BOOL, 29, (LPWSTR lpszPassword))
#define GetDiskFreeSpaceExW WIN32_FS_CALL (BOOL, 54, (LPCTSTR lpDirectoryName, PULARGE_INTEGER lpFreeBytesAvailableToCaller, PULARGE_INTEGER lpTotalNumberOfBytes, PULARGE_INTEGER lpTotalNumberOfFreeBytes))
#define GetTempPathW WIN32_FS_CALL (DWORD, 27, (DWORD nBufferLength, LPWSTR lpBuffer))

// external exports from device
#define RegisterDevice WIN32_DEV_CALL(HANDLE, 2, (LPCWSTR lpszName, DWORD index, LPCWSTR lpszLib, DWORD dwInfo))
#define DeregisterDevice WIN32_DEV_CALL(BOOL, 3, (HANDLE hDevice))
#define LoadFSD WIN32_DEV_CALL(BOOL, 6, (HANDLE hDevice, LPCWSTR lpFSDName))
#define ActivateDevice WIN32_DEV_CALL(HANDLE, 7, (LPCWSTR lpszDevKey, DWORD dwClientInfo))
#define DeactivateDevice WIN32_DEV_CALL(BOOL, 8, (HANDLE hDevice))

// internal exports from filesystem
#define FileSystemPowerFunction WIN32_FS_CALL(void, 50, (DWORD flags))
#define CloseAllFileHandles WIN32_FS_CALL (void, 42, ())
#define SetPassword WIN32_FS_CALL (BOOL, 30, (LPWSTR lpszOldpassword, LPWSTR lspzNewPassword))
#define GetPasswordActive WIN32_FS_CALL (BOOL, 47, (void))
#define SetPasswordActive WIN32_FS_CALL (BOOL, 48, (BOOL bActive, LPWSTR lpszPassword))
#define ReadFileWithSeek WIN32_FILE_CALL(BOOL, 12, (HANDLE hFile, LPVOID lpBuffer, DWORD nNumberOfBytesToRead, LPDWORD lpNumberOfBytesRead, LPOVERLAPPED lpOverlapped, DWORD dwLowOffset, DWORD dwHighOffset))
#define WriteFileWithSeek WIN32_FILE_CALL(BOOL, 13, (HANDLE hFile, LPCVOID lpBuffer, DWORD nNumberOfBytesToWrite,   LPDWORD lpNumberOfBytesWritten, LPOVERLAPPED lpOverlapped, DWORD dwLowOffset, DWORD dwHighOffset))

// internal exports from device
#define CloseAllDeviceHandles WIN32_DEV_CALL(void, 4, (HANDLE hProc))
#define CreateDeviceHandle WIN32_DEV_CALL(HANDLE, 5, (LPCWSTR, DWORD, DWORD, HPROCESS))

#endif //__MWINBASE_H__


/*++
THIS CODE AND INFORMATION IS PROVIDED "AS IS" WITHOUT WARRANTY OF
ANY KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED TO
THE IMPLIED WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A
PARTICULAR PURPOSE.
Copyright (c) 1995-1998  Microsoft Corporation

Module Name:  

pwinreg.h

Abstract:

Private version of winreg.h. This module contains the function prototypes
and constant, type and structure definitions for the WINCE Implementeation
of the Windows 32-Bit Registry API.

Notes: 


--*/

#ifndef _MACRO_WINREG_H_
#define _MACRO_WINREG_H_

#ifndef WINCEMACRO
#error WINCEMACRO not defined __FILE__
#endif

#ifdef __cplusplus
extern "C" {
#endif

// SDK exports
#define RegCloseKey WIN32_FS_CALL(LONG, 17, (HKEY hKey))

#define RegFlushKey WIN32_FS_CALL(LONG, 49, (HKEY hKey))

#define RegCreateKeyExW WIN32_FS_CALL(LONG, 18, (HKEY hKey, LPCWSTR lpSubKey, \
	DWORD Reserved, LPWSTR lpClass, DWORD dwOptions, REGSAM samDesired,	\
	LPSECURITY_ATTRIBUTES lpSecurityAttributes, PHKEY phkResult, LPDWORD lpdwDisposition))

#define RegDeleteKeyW WIN32_FS_CALL(LONG, 19, (HKEY hKey, LPCWSTR lpSubKey))

#define RegDeleteValueW WIN32_FS_CALL(LONG, 20, (HKEY hKey, LPCWSTR lpValueName))

#define RegEnumValueW WIN32_FS_CALL(LONG, 21, (HKEY hKey, DWORD dwIndex, \
	LPWSTR lpValueName, LPDWORD lpcbValueName, LPDWORD lpReserved, LPDWORD lpType, \
	LPBYTE lpData, LPDWORD lpcbData))

#define RegEnumKeyExW WIN32_FS_CALL(LONG, 22, (HKEY hKey, DWORD dwIndex, \
	LPWSTR lpName, LPDWORD lpcbName, LPDWORD lpReserved, LPWSTR lpClass, \
	LPDWORD lpcbClass, PFILETIME lpftLastWriteTime))

#define RegOpenKeyExW WIN32_FS_CALL(LONG, 23, (HKEY hKey, LPCWSTR lpSubKey, \
	DWORD ulOptions, REGSAM samDesired, PHKEY phkResult))

#define RegQueryInfoKeyW WIN32_FS_CALL(LONG, 24, (HKEY hKey, LPWSTR lpClass, \
	LPDWORD lpcbClass, LPDWORD lpReserved, LPDWORD lpcSubKeys, \
	LPDWORD lpcbMaxSubKeyLen, LPDWORD lpcbMaxClassLen, LPDWORD lpcValues, \
	LPDWORD lpcbMaxValueNameLen, LPDWORD lpcbMaxValueLen, \
	LPDWORD lpcbSecurityDescriptor, PFILETIME lpftLastWriteTime))

#define RegQueryValueExW WIN32_FS_CALL(LONG, 25, (HKEY hKey, LPCWSTR lpValueName, \
	LPDWORD lpReserved, LPDWORD lpType, LPBYTE lpData, LPDWORD lpcbData))

#define RegSetValueExW WIN32_FS_CALL (LONG, 26, (HKEY hKey, LPCWSTR lpValueName, \
	DWORD Reserved, DWORD dwType, CONST BYTE* lpData, DWORD cbData))

// OAK exports
#define RegCopyFile WIN32_FS_CALL (BOOL, 41, (LPCWSTR lpszFile))

#define RegRestoreFile WIN32_FS_CALL (BOOL, 44, (LPCWSTR lpszFile))


#ifdef __cplusplus
}
#endif

#endif // _MACRO_WINREG_

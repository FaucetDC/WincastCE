/*++
THIS CODE AND INFORMATION IS PROVIDED "AS IS" WITHOUT WARRANTY OF
ANY KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED TO
THE IMPLIED WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A
PARTICULAR PURPOSE.
Copyright (c) 1995-1998  Microsoft Corporation

Module Name:  

mkfuncs.h

Abstract:  

Notes: 


--*/
#ifndef __MKFUNCS_H__
#define __MKFUNCS_H__ 1

#ifndef WINCEMACRO
#error WINCEMACRO not defined __FILE__
#endif

#include <toolhelp.h>

#define CloseHandle METHOD_DECL(BOOL, ID_ALLHANDLE_FREE, (HANDLE hObject))

#define IsBadCodePtr(lpfnProc) IsBadPtr(VERIFY_EXECUTE_FLAG, (LPBYTE)(lpfnProc), 1)
#define IsBadReadPtr(lpvPtr, cbBytes) IsBadPtr(VERIFY_READ_FLAG, (LPBYTE)(lpvPtr), (cbBytes))
#define IsBadWritePtr(lpvPtr, cbBytes) IsBadPtr(VERIFY_WRITE_FLAG, (LPBYTE)(lpvPtr), (cbBytes))

// WIN32 calls
#define CreateAPISet WIN32_CALL(HANDLE, CreateAPISet, \
	(char acName[4], USHORT cFunctions, const PFNVOID *ppfnMethods, const DWORD *pdwSig))
#define VirtualAlloc WIN32_CALL(LPVOID, VirtualAlloc, \
    (LPVOID lpvAddress, DWORD cbSize, DWORD fdwAllocationType, DWORD fdwProtect))
#define VirtualFree WIN32_CALL(BOOL, VirtualFree, \
    (LPVOID lpvAddress, DWORD cbSize, DWORD fdwFreeType))
#define VirtualProtect WIN32_CALL(BOOL, VirtualProtect, \
    (LPVOID lpvAddress, DWORD cbSize, DWORD fdwNewProtect, PDWORD pfdwOldProtect))
#define VirtualQuery WIN32_CALL(DWORD, VirtualQuery, \
    (LPCVOID lpvAddress, PMEMORY_BASIC_INFORMATION pmbiBuffer, DWORD cbLength))
#define VirtualCopy WIN32_CALL(BOOL, VirtualCopy, \
	(LPVOID lpvDest, LPVOID lpvSrc, DWORD cbSize, DWORD fdwProtect))
#ifdef SH4
#define VirtualSetPageFlags WIN32_CALL(BOOL, VirtualSetPageFlags, \
	(LPVOID lpvAddress, DWORD cbSize, DWORD dwFlags, LPDWORD lpdwOldFlags))
#define SetRAMMode WIN32_CALL(BOOL, SetRAMMode, \
	(BOOL bEnable, LPVOID *lplpvAddress, LPDWORD lpLength))
#define SetStoreQueueBase WIN32_CALL(LPVOID, SetStoreQueueBase, (DWORD dwPhysPage))
#endif

#define LockPages WIN32_CALL(BOOL, LockPages, \
    (LPVOID lpvAddress, DWORD cbSize, PDWORD pPFNs, int fOptions))
#define UnlockPages WIN32_CALL(BOOL, UnlockPages, \
    (LPVOID lpvAddress, DWORD cbSize))

#define LoadLibraryW WIN32_CALL(HINSTANCE, LoadLibraryW, (LPCTSTR lpszFile))
#define FreeLibrary WIN32_CALL(BOOL, FreeLibrary, (HANDLE hInst))
#define GetProcAddressW WIN32_CALL(LPVOID, GetProcAddressW, (HANDLE hInst, LPCWSTR lpszProc))
#define ThreadAttachAllDLLs WIN32_CALL(void, ThreadAttachAllDLLs, (void))
#define ThreadDetachAllDLLs WIN32_CALL(void, ThreadDetachAllDLLs, (void))
#define GetTickCount WIN32_CALL(DWORD, GetTickCount, (VOID))
#define OutputDebugStringW WIN32_CALL(VOID, OutputDebugStringW, (LPCWSTR str))
#define TlsCall WIN32_CALL(DWORD, TlsCall, (DWORD,DWORD))
#define GetSystemInfo WIN32_CALL(VOID, GetSystemInfo, (LPSYSTEM_INFO lpSystemInfo))
#define U_ropen WIN32_CALL(int, ropen, (const WCHAR *, UINT))
#define U_rread WIN32_CALL(int, rread, (int, BYTE *, int))
#define U_rwrite WIN32_CALL(int, rwrite, (int, BYTE *, int))
#define U_rlseek WIN32_CALL(int, rlseek, (int, int, int))
#define U_rclose WIN32_CALL(int, rclose, (int))
#define RegisterDbgZones WIN32_CALL(BOOL, RegisterDbgZones, (HMODULE hMod, LPDBGPARAM lpdbgparam))
#define NKvDbgPrintfW WIN32_CALL(VOID, NKvDbgPrintfW, (LPWSTR lpszFmt, ...))
#define ProfileSyscall WIN32_CALL(VOID, ProfileSyscall, (LPDWORD))
#define FindResourceW WIN32_CALL(HRSRC, FindResource, (HANDLE hModule, LPCWSTR lpszName, LPCWSTR lpszType))
#define LoadResource WIN32_CALL(HGLOBAL, LoadResource, (HANDLE hModule, HANDLE hRsrc))
#define SizeofResource WIN32_CALL(DWORD, SizeofResource, (HANDLE hModule, HANDLE hRsrc))
#define GetRealTime WIN32_CALL(BOOL, GetRealTime,(LPSYSTEMTIME))
#define SetRealTime WIN32_CALL(BOOL, SetRealTime,(LPSYSTEMTIME))
#define ProcessDetachAllDLLs WIN32_CALL(void, ProcessDetachAllDLLs, (void))
#define ExtractResource WIN32_CALL(LPVOID, ExtractResource, \
	(LPCWSTR lpszFile, LPCWSTR lpszName, LPCWSTR lpszType))
#define KernExtractIcons WIN32_CALL(UINT, KernExtractIcons, \
	(LPCWSTR lpszFile, int nIconIndex, LPBYTE *pIconLarge, LPBYTE *pIconSmall, CALLBACKINFO *pcbi))
#define GetRomFileInfo WIN32_CALL(BOOL, GetRomFileInfo, \
	(DWORD type, LPWIN32_FIND_DATA  lpfd, DWORD count))
#define GetRomFileBytes WIN32_CALL(DWORD, GetRomFileBytes, \
	(DWORD type, DWORD count, DWORD pos, LPVOID buffer, DWORD nBytesToRead))
#define CacheSync WIN32_CALL(void, CacheSync, (int flags))
#define AddTrackedItem WIN32_CALL(BOOL, AddTrackedItem, \
	(DWORD dwType, HANDLE handle, TRACKER_CALLBACK cb, DWORD dwProc, \
	 DWORD dwSize, DWORD dw1, DWORD dw2))
#define DeleteTrackedItem WIN32_CALL(BOOL, DeleteTrackedItem, (DWORD dwType, HANDLE handle))
#define PrintTrackedItem WIN32_CALL(BOOL, PrintTrackedItem, \
	(DWORD dwFlag, DWORD dwType, DWORD dwProcID, HANDLE handle))
#define GetKPhys WIN32_CALL(BOOL, GetKPhys, (void *ptr, ULONG length))
#define GiveKPhys WIN32_CALL(BOOL, GiveKPhys, (void *ptr, ULONG length))
#define SetExceptionHandler WIN32_CALL(void, SetExceptionHandler, (PEXCEPTION_ROUTINE per))
#define RegisterTrackedItem WIN32_CALL(DWORD, RegisterTrackedItem, (LPWSTR szName))
#define FilterTrackedItem WIN32_CALL(VOID, FilterTrackedItem, (DWORD dwFlags, DWORD dwType, DWORD dwProcID))
#define SetKernelAlarm WIN32_CALL(void, SetKernelAlarm, (HANDLE hEvent, LPSYSTEMTIME lpst))
#define RefreshKernelAlarm WIN32_CALL(void, RefreshKernelAlarm, (void))
#define SetPFHandle WIN32_CALL(BOOL, SetPFHandle, (LPVOID lpvAddress, HANDLE hPf))
#define CloseProcOE WIN32_CALL(void, CloseProcOE, (DWORD))
#define SetGwesOOMEvent WIN32_CALL(VOID, SetGwesOOMEvent, \
	(HANDLE hEvt, DWORD cpLow, DWORD cpCritical, DWORD cpLowBlockSize, \
	 DWORD cpCriticalBlockSize))
#define StringCompress WIN32_CALL(DWORD, StringCompress, \
	(LPBYTE bufin, DWORD lenin, LPBYTE bufout, DWORD lenout))
#define StringDecompress WIN32_CALL(DWORD, StringDecompress, \
	(LPBYTE bufin, DWORD lenin, LPBYTE bufout, DWORD lenout))
#define BinaryCompress WIN32_CALL(DWORD, BinaryCompress, \
	(LPBYTE bufin, DWORD lenin, LPBYTE bufout, DWORD lenout))
#define BinaryDecompress WIN32_CALL(DWORD, BinaryDecompress, \
	(LPBYTE bufin, DWORD lenin, LPBYTE bufout, DWORD lenout, DWORD skip))
#define CreateEventW WIN32_CALL(HANDLE, CreateEvent, \
	(LPSECURITY_ATTRIBUTES lpsa, BOOL fManual, BOOL fInit, LPCWSTR lpName))
#define CreateProcessW WIN32_CALL(BOOL, CreateProc, \
	(LPCWSTR, LPCWSTR, LPSECURITY_ATTRIBUTES, LPSECURITY_ATTRIBUTES, \
	 BOOL, DWORD, LPVOID, LPWSTR, LPSTARTUPINFO, LPPROCESS_INFORMATION))
#define CreateThread WIN32_CALL(HANDLE, CreateThread, \
	(LPSECURITY_ATTRIBUTES lpsa, DWORD cbStack, LPTHREAD_START_ROUTINE lpStartAddr, \
	 LPVOID lpvThreadParm, DWORD fdwCreate, LPDWORD lpIDThread))
#define InputDebugCharW WIN32_CALL(int, InputDebugCharW, (VOID))
#define TakeCritSec WIN32_CALL(void, TakeCritSec, (LPCRITICAL_SECTION lpcs))
#define LeaveCritSec WIN32_CALL(void, LeaveCritSec, (LPCRITICAL_SECTION lpcs))
#define MapPtrToProcess WIN32_CALL(LPVOID, MapPtrToProcess, (LPVOID lpv, HANDLE hProc))
#define MapPtrUnsecure WIN32_CALL(LPVOID, MapPtrUnsecure, (LPVOID lpv, HANDLE hProc))
#define GetProcFromPtr WIN32_CALL(HANDLE, GetProcFromPtr, (LPVOID lpv))
#define IsBadPtr WIN32_CALL(BOOL, IsBadPtr, (DWORD flags, LPBYTE ptr, UINT length))
#define GetProcAddrBits WIN32_CALL(DWORD, GetProcAddrBits, (HANDLE hProc))
#define GetFSHeapInfo WIN32_CALL(DWORD, GetFSHeapInfo, (void))
#define OtherThreadsRunning WIN32_CALL(BOOL, OtherThreadsRunning,(void))
#define KillAllOtherThreads WIN32_CALL(VOID, KillAllOtherThreads,(void))
#define GetOwnerProcess WIN32_CALL(HANDLE, GetOwnerProcess, (void))
#define GetCallerProcess WIN32_CALL(HANDLE, GetCallerProcess, (void))
#define GetIdleTime WIN32_CALL(DWORD, GetIdleTime, (void))
#define SetLowestScheduledPriority WIN32_CALL(DWORD, SetLowestScheduledPriority, (DWORD maxprio))
#define IsPrimaryThread WIN32_CALL(BOOL, IsPrimaryThread,(void))
#define SetProcPermissions WIN32_CALL(DWORD, SetProcPermissions, (DWORD))
#define GetCurrentPermissions WIN32_CALL(DWORD, GetCurrentPermissions, (void))
#define SetGwesHeapMark WIN32_CALL(void, SetGwesHeapMark, (DWORD dwSize))
#define SetDaylightTime WIN32_CALL(void, SetDaylightTime, (DWORD dst))
#define SetTimeZoneBias WIN32_CALL(void, SetTimeZoneBias, (DWORD dwBias, DWORD dwDaylightBias))
#define SetCleanRebootFlag WIN32_CALL(void, SetCleanRebootFlag, (void))
#define CreateCrit WIN32_CALL(HANDLE, CreateCrit, (LPCRITICAL_SECTION lpcs))
#define PowerOffSystem WIN32_CALL(void, PowerOffSystem, (void))
#define CreateMutexW WIN32_CALL(HANDLE, CreateMutex, \
	(LPSECURITY_ATTRIBUTES lpsa, BOOL bInitialOwner, LPCTSTR lpName))
#define SetDbgZone WIN32_CALL(BOOL, SetDbgZone, \
	(DWORD dwProcid, LPVOID lpvMod, LPVOID baseptr, DWORD zone, LPDBGPARAM lpdbgTgt))
#define TurnOnProfiling WIN32_CALL(VOID, TurnOnProfiling, (HANDLE hThread))
#define TurnOffProfiling WIN32_CALL(VOID, TurnOffProfiling, (HANDLE hThread))
#define TurnOnSyscallProfiling WIN32_CALL(VOID, TurnOnSyscallProfiling, (HANDLE hThread))
#define TurnOffSyscallProfiling WIN32_CALL(VOID, TurnOffSyscallProfiling, (HANDLE hThread))
#define NKTerminateThread WIN32_CALL(void, NKTerminateThread, (DWORD dwExitCode))
#define SetLastError WIN32_CALL(VOID, SetLastError, (DWORD))
#define GetLastError WIN32_CALL(DWORD, GetLastError, (void))
#define GetProcName WIN32_CALL(LPCHAR, GetProcName, (void))
#define ExitProcess WIN32_CALL(void, TerminateSelf, (void))
#define CloseAllHandles WIN32_CALL(void, CloseAllHandles, (void))
#define SetHandleOwner WIN32_CALL(BOOL, SetHandleOwner, (HANDLE h, HANDLE hProc))
#define LoadDriver WIN32_CALL(HINSTANCE, LoadDriver, (LPCTSTR lpszFile))
#define CreateFileMappingW WIN32_CALL(HANDLE, CreateFileMapping, (HANDLE hFile, LPSECURITY_ATTRIBUTES lpsa, \
	DWORD flProtect, DWORD dwMaxSizeHigh, DWORD dwMaxSizeLow, LPCTSTR lpName))
#define UnmapViewOfFile WIN32_CALL(BOOL, UnmapViewOfFile, (LPVOID lpvAddr))
#define FlushViewOfFile WIN32_CALL(BOOL, FlushViewOfFile, (LPCVOID lpBaseAddress, DWORD dwNumberOfBytesToFlush))
#define FlushViewOfFileMaybe WIN32_CALL(BOOL, FlushViewOfFileMaybe, (LPCVOID lpBaseAddress, DWORD dwNumberOfBytesToFlush))
#define CreateFileForMappingW WIN32_CALL(HANDLE, CreateFileForMappingW, (LPCTSTR lpFileName, DWORD dwDesiredAccess, \
	DWORD dwShareMode, LPSECURITY_ATTRIBUTES lpSecurityAttributes, DWORD dwCreationDisposition, \
	DWORD dwFlagsAndAttributes, HANDLE hTemplateFile))
#define KernelIoControl WIN32_CALL(BOOL, KernelIoControl, (DWORD dwIoControlCode, \
	LPVOID lpInBuf, DWORD nInBufSize, \
	LPVOID lpOutBuf, DWORD nOutBufSize, LPDWORD lpBytesReturned))
#define MapUncompressedFileW WIN32_CALL(LPVOID, MapUncompressedFileW, (LPCWSTR pFileName, LPDWORD pLen))
#define PPSHRestart WIN32_CALL(void, PPSHRestart, ())
#define SignalStarted WIN32_CALL(void, SignalStarted, (DWORD))
#define UpdateNLSInfo WIN32_CALL(void, UpdateNLSInfo, (DWORD ocp, DWORD acp, DWORD locale))
#define ConnectDebugger WIN32_CALL(BOOL, ConnectDebugger, (LPVOID pInit))
#define InterruptInitialize WIN32_CALL(BOOL, InterruptInitialize, \
	(DWORD idInt, HANDLE hEvent, LPVOID pvData, DWORD cbData))
#define InterruptDone WIN32_CALL(void, InterruptDone, (DWORD idInt))
#define InterruptDisable WIN32_CALL(void, InterruptDisable, (DWORD idInt))
#define SetKMode WIN32_CALL(BOOL, SetKMode, (BOOL))
#define SetPowerOffHandler WIN32_CALL(BOOL, SetPowerOffHandler, (FARPROC pfn))
#define SetGwesPowerHandler WIN32_CALL(BOOL, SetGwesPowerHandler, (FARPROC pfn))
#define SetWDevicePowerHandler WIN32_CALL(BOOL, SetWDevicePowerHandler, (FARPROC pfn))
#define SetHardwareWatch WIN32_CALL(BOOL, SetHardwareWatch, (LPVOID vAddr, DWORD flags))
#define QueryAPISetID WIN32_CALL(int, QueryAPISetID, (char *pName))
#define RaiseException WIN32_CALL(VOID, RaiseException, \
    (DWORD dwExceptionCode, DWORD dwExceptionFlags, DWORD cArgs, CONST DWORD *lpArgs))
#define GetCallerProcessIndex WIN32_CALL(DWORD, GetCallerProcessIndex, (void))
#define WaitForDebugEvent WIN32_CALL(BOOL, WaitForDebugEvent, (LPDEBUG_EVENT lpDebugEvent, DWORD dwMilliseconds))
#define ContinueDebugEvent WIN32_CALL(BOOL, ContinueDebugEvent, (DWORD dwProcessId, DWORD dwThreadId, DWORD dwContinueStatus))
#define DebugNotify WIN32_CALL(void, DebugNotify, (DWORD dwFlags, DWORD data))
#define OpenProcess WIN32_CALL(HANDLE, OpenProcess, (DWORD fdwAccess, BOOL fInherit, DWORD IDProcess))
#define THCreateSnapshot WIN32_CALL(THSNAP *, THCreateSnapshot, (DWORD dwFlags, DWORD dwProcID))
#define THGrow WIN32_CALL (LPBYTE, THGrow, (THSNAP *pSnap, DWORD dwSize))
#ifdef BUILDING_DEBUGGER
#define Sleep WIN32_CALL(VOID, Sleep, (DWORD cMilliseconds))
#define WaitForMultipleObjects WIN32_CALL(DWORD, WaitForMultiple, \
	(DWORD cObjects, CONST HANDLE *lphObjects, BOOL fWaitAll, DWORD dwTimeout))
#else
#define KernelSleep WIN32_CALL(VOID, Sleep, (DWORD cMilliseconds))
#define KernelWaitForMultipleObjects WIN32_CALL(DWORD, WaitForMultiple, \
	(DWORD cObjects, CONST HANDLE *lphObjects, BOOL fWaitAll, DWORD dwTimeout))
#ifdef COREDLL
void xxx_Sleep(DWORD);
#define Sleep xxx_Sleep
DWORD xxx_WaitForMultipleObjects(DWORD cObjects, CONST HANDLE *lphObjects, BOOL fWaitAll, DWORD dwTimeout);
#define WaitForMultipleObjects xxx_WaitForMultipleObjects
#endif
#endif
#define NotifyForceCleanboot WIN32_CALL(void, NotifyForceCleanboot, (void))
#define DumpKCallProfile WIN32_CALL(void, DumpKCallProfile, (DWORD bReset))
#define GetProcessVersion WIN32_CALL(DWORD, GetProcessVersion, (DWORD ProcessId))
#define GetModuleFileNameW WIN32_CALL(DWORD, GetModuleFileNameW, (HANDLE hModule, LPWSTR lpFilename, DWORD nSize))
#define QueryPerformanceCounter WIN32_CALL(BOOL, QueryPerformanceCounter, (LARGE_INTEGER *lpPerformanceCount))
#define QueryPerformanceFrequency WIN32_CALL(BOOL, QueryPerformanceFrequency, (LARGE_INTEGER *lpPerformanceCount))
#define WriteDebugLED WIN32_CALL(void, WriteDebugLED, (WORD wIndex, DWORD dwPattern))
#define ForcePageout WIN32_CALL(void, ForcePageout, (void))
#define GetThreadTimes WIN32_CALL(BOOL, GetThreadTimes, (HANDLE hThread, LPFILETIME lpCreationTime, LPFILETIME lpExitTime, LPFILETIME lpKernelTime, LPFILETIME lpUserTime))
#define GetModuleHandleW WIN32_CALL(HMODULE, GetModuleHandleW, (LPCWSTR lpModuleName))
#define SetStdioPathW WIN32_CALL(BOOL,SetStdioPathW, (DWORD id, LPCWSTR pwszPath))
#define GetStdioPathW WIN32_CALL(BOOL, GetStdioPathW, (DWORD id, PWSTR pwszBuf, LPDWORD lpdwLen))
#define ReadRegistryFromOEM WIN32_CALL(DWORD, ReadRegistryFromOEM, (DWORD dwFlags, LPBYTE pBuf, DWORD len))
#define WriteRegistryToOEM WIN32_CALL (BOOL, WriteRegistryToOEM, (DWORD dwFlags, LPBYTE pBuf, DWORD len))

// THREAD calls
#ifdef BUILDING_DEBUGGER
#define SuspendThread _THREAD_CALL(DWORD, SUSPEND, (HANDLE hThread))
#else
#define KernelSuspendThread _THREAD_CALL(DWORD, SUSPEND, (HANDLE hThread))
#ifdef COREDLL
DWORD WINAPI xxx_SuspendThread(HANDLE hThread);
#define SuspendThread xxx_SuspendThread
#endif
#endif
#define ResumeThread _THREAD_CALL(DWORD, RESUME, (HANDLE hThread))
#define SetThreadPriority _THREAD_CALL(BOOL, SETTHREADPRIO, (HANDLE hThread, int nPriority))
#define GetThreadPriority _THREAD_CALL(int, GETTHREADPRIO, (HANDLE hThread))
#define GetExitCodeThread _THREAD_CALL(BOOL, GETRETCODE, (HANDLE hThread, LPDWORD lpretval))
#define GetThreadContext _THREAD_CALL(BOOL, GETCONTEXT, (HANDLE hThread, LPCONTEXT lpContext))
#define SetThreadContext _THREAD_CALL(BOOL, SETCONTEXT, (HANDLE hThread, CONST CONTEXT *lpContext))
#define TerminateThread _THREAD_CALL(BOOL, TERMINATE, (HANDLE hThread, DWORD dwExitCode))

// PROCESS calls
#define TerminateProcess _PROCESS_CALL(BOOL, TERMINATE, (HANDLE hProc, DWORD dwExitCode))
#define GetExitCodeProcess _PROCESS_CALL(BOOL, GETRETCODE, (HANDLE hProcess, LPDWORD lpretval))
#define GetProcessIndexFromID _PROCESS_CALL(DWORD, GETINDEX, (HANDLE hProcess))
#define FlushInstructionCache _PROCESS_CALL(BOOL, FLUSHICACHE, (HANDLE hProc, LPCVOID lpBaseAddress, DWORD dwSize))
#define ReadProcessMemory _PROCESS_CALL(BOOL, READMEMORY, (HANDLE hProcess, LPCVOID lpBaseAddress, LPVOID lpBuffer, DWORD nSize, LPDWORD lpNumberOfBytesRead))
#define WriteProcessMemory _PROCESS_CALL(BOOL, WRITEMEMORY, (HANDLE hProcess, LPVOID lpBaseAddress, LPVOID lpBuffer, DWORD nSize, LPDWORD lpNumberOfBytesWritten))
#define DebugActiveProcess _PROCESS_CALL(BOOL, DEBUGACTIVE, (DWORD dwProcessId))

// EVENT calls
#define EventModify _EVENT_CALL(BOOL, MODIFY, (HANDLE hEvent, DWORD func))
#define AddEventAccess _EVENT_CALL(BOOL, ADDACCESS, (HANDLE hEvent))

// APISET calls
#define RegisterAPISet _APISET_CALL(BOOL, REGISTER, (HANDLE hASet, DWORD dwSetID))
#define CreateAPIHandle _APISET_CALL(HANDLE, CREATEHANDLE, (HANDLE hASet, LPVOID pvData))
#define VerifyAPIHandle _APISET_CALL(LPVOID, VERIFY, (HANDLE hASet, HANDLE h))

// MAPPED FILE calls
#define MapViewOfFile _FSMAP_CALL(LPVOID, MAPVIEWOFFILE, (HANDLE hMap, DWORD fdwAccess, DWORD dwOffsetHigh, \
	DWORD dwOffsetLow, DWORD cbMap))

// MUTEX calls

#define ReleaseMutex _MUTEX_CALL(BOOL, RELEASEMUTEX, (HANDLE hMutex))

#endif


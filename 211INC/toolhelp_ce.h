#include "resource.h"
#include "SpyControl.h"
#include "SpyEngine.h"
#include "SysDecls.h"
#include "htrace.h"

/*
*****************   Beginning of Toolhelp replacement *************/
//Beginning of Toolhelp replacement. PocketPC emulation and retail 
//devices do have toolhelp support, but CE.NET emulation version 
//does not include toolhelp.dll.  Therefore, I have to reimplement 
//some toolhelp methods myself using public declarations of necessary
//structures in PUBLIC\COMMON\OAK\INC\TOOLHELP.H.

typedef HANDLE WINAPI T_CreateToolhelp32Snapshot
    (DWORD dwFlags, DWORD th32ProcessID);
typedef BOOL WINAPI T_CloseToolhelp32Snapshot(HANDLE hSnapshot);
typedef BOOL WINAPI T_Module32First
    (HANDLE hSnapshot, LPMODULEENTRY32 lpme);
typedef BOOL WINAPI T_Module32Next
    (HANDLE hSnapshot, LPMODULEENTRY32 lpme);
typedef BOOL WINAPI T_Process32First
    (HANDLE hSnapshot, LPPROCESSENTRY32 lppe);
typedef BOOL WINAPI T_Process32Next
    (HANDLE hSnapshot, LPPROCESSENTRY32 lppe);

T_CreateToolhelp32Snapshot * g_pCreateToolhelp32Snapshot = NULL;
T_CloseToolhelp32Snapshot  * g_pCloseToolhelp32Snapshot = NULL;
T_Module32First * g_pModule32First = NULL;
T_Module32Next  * g_pModule32Next  = NULL;
T_Process32First* g_pProcess32First = NULL;
T_Process32Next * g_pProcess32Next  = NULL;


//From PUBLIC\COMMON\OAK\INC\TOOLHELP.H:
typedef struct TH32PROC {
	PROCESSENTRY32 procentry;
	void *pMainHeapEntry;
	struct TH32PROC *pNext;
} TH32PROC;
typedef struct TH32MOD {
	MODULEENTRY32 modentry;
	struct TH32MOD *pNext;
} TH32MOD;
typedef struct THSNAP {
	LPBYTE pNextFree;
	LPBYTE pHighCommit;
	LPBYTE pHighReserve;
	TH32PROC *pProc;
	TH32MOD *pMod;
	void *pThread;
	void *pHeap;
} THSNAP;

/*-------------------------------------------------------------------
   FUNCTION: MyCreateToolhelp32Snapshot
   PURPOSE:  Replacement to ToolHelp CreateToolhelp32Snapshot.
   Parameters and return value are identical to
   documented CreateToolhelp32Snapshot.
-------------------------------------------------------------------*/
HANDLE MyCreateToolhelp32Snapshot
(
    DWORD p_dwFlags, 
    DWORD p_th32ProcessID
)
{
    THSNAP * l_pSnapshot = (THSNAP *)
        THCreateSnapshot(p_dwFlags, p_th32ProcessID);
    HTRACE(TG_DebugSpyBrief, _T("THCreateSnapshot ret %x"), 
        l_pSnapshot);
    return (HANDLE)l_pSnapshot;
}

/*-------------------------------------------------------------------
   FUNCTION: MyCloseToolhelp32Snapshot
   PURPOSE:  Replacement to ToolHelp CloseToolhelp32Snapshot.
   Parameters and return value are identical to
   documented CloseToolhelp32Snapshot.
-------------------------------------------------------------------*/
BOOL MyCloseToolhelp32Snapshot(HANDLE p_hSnapshot)
{
    MEMORY_BASIC_INFORMATION l_MemInfo;
    if(!VirtualQuery((void*)p_hSnapshot, 
        &l_MemInfo, sizeof(l_MemInfo)))
        return FALSE;
    VirtualFree((void*)p_hSnapshot, 
        l_MemInfo.RegionSize, MEM_DECOMMIT);
    VirtualFree((void*)p_hSnapshot, 0, MEM_RELEASE);
    return TRUE;
}

/*-------------------------------------------------------------------
   FUNCTION: MyModule32First
   PURPOSE:  Replacement to ToolHelp Module32First.
   Parameters and return value are identical to
   documented Module32First.
-------------------------------------------------------------------*/
BOOL MyModule32First(HANDLE p_hSnapshot, LPMODULEENTRY32 p_lpme)
{
    THSNAP * l_pSnapshot = (THSNAP*)p_hSnapshot;
    if(!l_pSnapshot || !l_pSnapshot->pMod || !p_lpme  || 
        p_lpme->dwSize < sizeof(MODULEENTRY32))
        return FALSE;
    memcpy(p_lpme, &l_pSnapshot->pMod->modentry, 
        sizeof(MODULEENTRY32));
    p_lpme->dwFlags = (DWORD)l_pSnapshot->pMod->pNext;
    //Kludge. dwFlags is reserved, so reuse it.
    return TRUE;
}

/*-------------------------------------------------------------------
   FUNCTION: MyModule32Next
   PURPOSE:  Replacement to ToolHelp Module32Next.
   Parameters and return value are identical to
   documented Module32Next.
-------------------------------------------------------------------*/
BOOL MyModule32Next(HANDLE p_hSnapshot, LPMODULEENTRY32 p_lpme)
{
    THSNAP * l_pSnapshot = (THSNAP*)p_hSnapshot;
    if(!l_pSnapshot || !l_pSnapshot->pMod || !p_lpme)
        return FALSE;
    if(p_lpme->dwFlags < (DWORD)l_pSnapshot || 
        p_lpme->dwFlags >= (DWORD)l_pSnapshot->pHighCommit)
        return FALSE;
    TH32MOD * l_pNextMod = (TH32MOD*)p_lpme->dwFlags;
    //Kludge. dwFlags is reserved, so reuse it.
    memcpy(p_lpme, &l_pNextMod->modentry, sizeof(MODULEENTRY32));
    p_lpme->dwFlags = (DWORD)l_pNextMod->pNext;
    //Kludge. dwFlags is reserved, so reuse it.
    return TRUE;
}

/*-------------------------------------------------------------------
   FUNCTION: MyProcess32First
   PURPOSE:  Replacement to ToolHelp Process32First.
   Parameters and return value are identical to
   documented Process32First.
-------------------------------------------------------------------*/
BOOL MyProcess32First(HANDLE p_hSnapshot, LPPROCESSENTRY32 p_lppe)
{
    THSNAP * l_pSnapshot = (THSNAP*)p_hSnapshot;
    if(!l_pSnapshot || !l_pSnapshot->pProc || !p_lppe  || 
        p_lppe->dwSize < sizeof(PROCESSENTRY32))
        return FALSE;
    memcpy(p_lppe, &l_pSnapshot->pProc->procentry, 
        sizeof(PROCESSENTRY32));
    p_lppe->dwFlags = (DWORD)l_pSnapshot->pProc->pNext;
    //Kludge. dwFlags is reserved, so reuse it.
    return TRUE;
}

/*-------------------------------------------------------------------
   FUNCTION: MyProcess32Next
   PURPOSE:  Replacement to ToolHelp Process32Next.
   Parameters and return value are identical to
   documented Process32Next.
-------------------------------------------------------------------*/
BOOL MyProcess32Next(HANDLE p_hSnapshot, LPPROCESSENTRY32 p_lppe)
{
    THSNAP * l_pSnapshot = (THSNAP*)p_hSnapshot;
    if(!l_pSnapshot || !l_pSnapshot->pProc || !p_lppe)
        return FALSE;
    if(p_lppe->dwFlags < (DWORD)l_pSnapshot || 
        p_lppe->dwFlags >= (DWORD) l_pSnapshot->pHighCommit)
        return FALSE;
    TH32PROC * l_pNextProc = (TH32PROC*)p_lppe->dwFlags;
    //Kludge. dwFlags is reserved, so reuse it.
    memcpy(p_lppe, &l_pNextProc->procentry, 
        sizeof(PROCESSENTRY32));
    p_lppe->dwFlags = (DWORD)l_pNextProc->pNext;
    //Kludge. dwFlags is reserved, so reuse it.
    return TRUE;
}

/*-------------------------------------------------------------------
   FUNCTION: LoadToolHelp
   PURPOSE:  Loads ToolHelp API or, if it is missing, initialize
   pointers to our replacement routines.
   RETURNS: TRUE on success, FALSE on failure
-------------------------------------------------------------------*/
BOOL LoadToolHelp()
{
    if(g_pCreateToolhelp32Snapshot)
        return TRUE;
    HINSTANCE l_hInst = LoadLibrary(_T("TOOLHELP"));
    if(!l_hInst)
    {
        HTRACE(TG_DebugSpyBrief, 
            _T("Cannot find ToolHelp library. %d"), GetLastError());
    }
    else
    {
        g_pCreateToolhelp32Snapshot = (T_CreateToolhelp32Snapshot *)
            GetProcAddress(l_hInst, _T("CreateToolhelp32Snapshot"));
        g_pCloseToolhelp32Snapshot = (T_CloseToolhelp32Snapshot  *)
            GetProcAddress(l_hInst, _T("CloseToolhelp32Snapshot"));
        g_pModule32First = (T_Module32First * )
            GetProcAddress(l_hInst, _T("Module32First"));
        g_pModule32Next  = (T_Module32Next  * )
            GetProcAddress(l_hInst, _T("Module32Next"));
        g_pProcess32First = (T_Process32First* )
            GetProcAddress(l_hInst, _T("Process32First"));
        g_pProcess32Next  = (T_Process32Next * )
            GetProcAddress(l_hInst, _T("Process32Next"));

        if(g_pCreateToolhelp32Snapshot && g_pCloseToolhelp32Snapshot 
            && g_pModule32First && g_pModule32Next &&
            g_pProcess32First && g_pProcess32Next)
            return TRUE;
        HTRACE(TG_Error, 
            _T("Cannot find methods in ToolHelp library"));
    }
    if(l_hInst != NULL)
    {
        FreeLibrary(l_hInst);
    }
    g_pCreateToolhelp32Snapshot = MyCreateToolhelp32Snapshot;
    g_pCloseToolhelp32Snapshot = MyCloseToolhelp32Snapshot;
    g_pModule32First = MyModule32First;
    g_pModule32Next  = MyModule32Next;
    g_pProcess32First = MyProcess32First;
    g_pProcess32Next  = MyProcess32Next;
    HTRACE(TG_DebugSpyBrief, _T("Use our own toolhelp replacement"));
    return TRUE;
}
/*****************   End of Toolhelp replacement *******************/

/*-------------------------------------------------------------------
   FUNCTION: InitProcessList
   PURPOSE:  InitProcessList uses Toolhelp API to enumerate running 
   processes and store process information to our 
   g_SpyEngine.m_Processes array. This will allow accessing this 
   process information from our interceptor routines.
   RETURNS: TRUE on success, FALSE on failure
-------------------------------------------------------------------*/
/********************************************************************
Module : SpyEngine.h - part of CeApiSpyDll implementation 
             Written 2003 by Dmitri Leman
             for an article about CE Api Spy.
Purpose: Contains declaration of SpyEngine structure.

  This file was compiled using eMbedded Visual C++ 3.0 
  with Pocket PC 2002 SDK and 4.0 with Standard SDK.
********************************************************************/

#ifndef _SPY_ENGINE_H_
#define _SPY_ENGINE_H_

#include <tlhelp32.h>

//Redefinitions for some CE internal structures and undocumented APIs
#include "SysDecls.h" 

extern BOOL InstallInterceptors();

struct CINFO;

#define NUM_SYSTEM_SETS 32 //size of system API table

/*
struct HookedAPI holds information for one system API, 
which is hooked by us.
*/
struct HookedAPI
{
    BOOL    m_bUsed;
    BOOL    m_bSwapped;
    int     m_iOrigApiSetId;
    CINFO * m_pOrigApiSet;
    CINFO * m_pOurApiSet;
};

/*
struct SpyEngine is the main data of the Spy engine. 
Only one static instance exists.
*/
struct SpyEngine
{
    //API for custom interceptors:
    PFNVOID HookMethod(int p_iAPISetId, int p_iMethodIndex, 
        PFNVOID p_pHookMethod);

    //Implementation:

    //CE has up to 32 running processes. 
    //Therefore, reserve 32 PROCESSENTRY32 structures indexed by the
    //process slot number.
    PROCESSENTRY32 m_Processes[32];
    
    //Since we load SpyDll into all running processes,
    //we need to keep handles in m_hSpyDllLoaded
    HINSTANCE m_hSpyDllLoaded[32];

    //Address of the memory slot of the ApiSpy process.
    DWORD m_dwCurrentProcBase;

    DWORD m_dwOrigThreadId;

    //Pointer to an array of system APIs.
    CINFO ** m_pSystemAPISets;

    //Pointers to the kernel Win32 method table 
    //and extra methods table.
    PFNVOID * m_ppWin32Methods;
    PFNVOID * m_ppExtraMethods;

    PFNVOID * m_ppHookWin32Methods;
    DWORD   * m_pdwHookWin32Signatures;

    PFNVOID * m_ppHookExtraMethods;
    DWORD   * m_pdwHookExtraSignatures;
#define SIZE_EXTRA_TABLE 256 //no way to know the actual size

    HANDLE    m_hOurApiHandle;
    int       m_iNumOurApiMethods;
    PFNVOID * m_ppOurApiMethods;
    DWORD   * m_pdwOurApiSignatures;

    int       m_iHookAPISetID;
    CINFO   * m_pHookAPISet;

    LPTSTR    m_pszSpyDllPathInKernelMemory;

    PFNVOID   m_pOriginalLoadLibrary;

    BOOL      m_bCoredllHooked;

    long      m_lNumCalls;
    long      m_lNumHooksActive;

    //Reserve a table for all system APIs.
    HookedAPI m_HookedAPI[NUM_SYSTEM_SETS];

    BOOL DoStart();
    BOOL DoStop();

    BOOL CreateDuplicateApi(int p_iAPISetId);

    HINSTANCE LoadHookDllIntoProcess(HANDLE p_hProcess);
    BOOL UnloadHookDllInProcess
        (HANDLE p_hProcess, HINSTANCE p_hInst);
    void LoadHookDllInAllProcesses();
    PFNVOID SetPrivateApiMethod(PFNVOID p_pHookMethod);

};//struct SpyEngine

extern SpyEngine g_SpyEngine;
//The only static instance of SpyEngine.

#endif

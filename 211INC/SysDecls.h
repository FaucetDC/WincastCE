/********************************************************************
Module : SpyEngine.h - part of CeApiSpyDll implementation 
             Written 2003 by Dmitri Leman
             for an article about CE Api Spy.
Purpose: Contains redefinitions for some CE internal 
    structures and undocumented APIs

  This file was compiled using eMbedded Visual C++ 3.0 
  with Pocket PC 2002 SDK and 4.0 with Standard SDK.
********************************************************************/

#ifndef _SYS_DECLS_H_
#define _SYS_DECLS_H_

/********   Beginning of undocumented functions declarations *******/
extern "C"
{
//The following functions exported from coredll.dll are documented in
//Platform Builder help and declared in 
//PUBLIC\COMMON\OAK\INC\pkfuncs.h,
//but not in SDK, so declare them here:
DWORD __stdcall SetProcPermissions(DWORD);
LPVOID __stdcall MapCallerPtr(LPVOID ptr, DWORD dwLen);
LPVOID __stdcall MapPtrToProcess (LPVOID lpv, HANDLE hProc);
LPVOID __stdcall UnMapPtr(LPVOID lpv);
HANDLE __stdcall GetOwnerProcess (void); 
HANDLE __stdcall GetCallerProcess (void); 
BOOL __stdcall SetKMode(BOOL fMode);
BOOL __stdcall IsAPIReady(DWORD hAPI);

//The following are undocumented structures declared in
//PUBLIC\COMMON\OAK\INC\pkfuncs.h, which we have to redeclare here.
//WARNING: undocumented structures and functions may change in the 
//future.
struct CALLBACKINFO 
{
    HANDLE  m_hDestinationProcessHandle;
    FARPROC m_pFunction;
    PVOID   m_pFirstArgument;
};

//The following undocumented functions exported from coredll.dll
//and declared in PUBLIC\COMMON\OAK\INC\pkfuncs.h,
//but not in SDK, so declare them here:
//WARNING: undocumented structures and functions may change in the 
//future.
HANDLE __stdcall CreateAPISet(char acName[4], USHORT cFunctions, 
    const PFNVOID *ppfnMethods, const DWORD *pdwSig);
BOOL  __stdcall RegisterAPISet(HANDLE hASet, DWORD dwSetID);
int  __stdcall QueryAPISetID(char *pName);
FARPROC  __stdcall GetAPIAddress(int setId, int iMethod);
HLOCAL __stdcall LocalAllocInProcess(UINT uFlags, UINT uBytes, 
                                     HPROCESS hProc);
HANDLE __stdcall GetProcFromPtr(LPVOID p);
DWORD  __stdcall PerformCallBack4(CALLBACKINFO *pcbi, 
                                  DWORD dw1, DWORD dw2, DWORD dw3);
BOOL __stdcall GetRomFileInfo(DWORD type, 
                              LPWIN32_FIND_DATA lpfd, DWORD count);
DWORD __stdcall GetProcessIndexFromID(HANDLE hProc);
LPBYTE __stdcall THCreateSnapshot(DWORD dwFlags, DWORD dwProcID);

//The following are API handles from PUBLIC\COMMON\OAK\INC\psyscall.h
//(in addition to SH_* handles defined in SDK kfuncs.h file).
#define HT_EVENT				4	
#define HT_MUTEX				5	
#define HT_APISET				6	
#define HT_FILE					7	
#define HT_FIND					8	
#define HT_DBFILE				9	
#define HT_DBFIND				10	
#define HT_SOCKET				11	
#define HT_INTERFACE			12
#define HT_SEMAPHORE			13	
#define HT_FSMAP				14	
#define HT_WNETENUM             15  

//The following are some methods in the SH_WIN32 table.
//The full list is in psyscall.h.
#define W32_LoadLibraryW		 8
#define W32_GetRomFileInfo		32
#define W32_CreateProc          53
#define W32_PerformCallBack 	113

//The following are some methods in the SH_FILESYS_APIS table.
#define FILESYS_CreateFile      9

}//extern "C"
/********   End of undocumented functions declarations *************/

/********   Beginning of kernel data structure declarations ********/
//The key for accessing CE kernel data structure (KDataStruct) is 
//PUserKData. PUserKData is defined in kfuncs.h in SDK as 0xFFFFC800 
//on ARM and 0x00005800 on other CPUs. It is used in the same header 
//to define macros GetCurrentThreadId and GetCurrentProcessId, which 
//directly access the kernel data structures.
//Several kernel data structures are accessed using predefined 
//offsets from PUserKData. For example, SYSHANDLE_OFFSET (defined in
//kfuncs.h), gives access to an array of system handles, KINFO_OFFSET
//(defined in PUBLIC\COMMON\OAK\INC\pkfuncs.h) gives access to 
//UserKInfo array. About 30 indexes in this array are defined in 
//pkfuncs.h (KINX_*) to provide access to such kernel data structures
//as process array, module list, kernel heap, etc.
//Here we are only interested in KINX_APISETS and KINX_API_MASK.
//KINX_APISETS slot holds a pointer to an array of system API sets
//(SystemAPISets). 
//KINX_API_MASK slot is a bit mask of installed APIs.

#define KINFO_OFFSET     0x300

#define KINX_API_MASK 18
#define KINX_APISETS 24

#define UserKInfo  ((long *)(PUserKData+KINFO_OFFSET))

//pointer to struct Process declared in Kernel.h.
typedef void * PPROCESS;
//I will not bother redeclaring this large structure.
//I will only define offsets to 2 fields used in DumpApis():
#define PROCESS_NUM_OFFSET  0    //process number (index of the slot)
#define PROCESS_NAME_OFFSET 0x20 //pointer to the process name

//Also declare structure CINFO, which holds an information 
//about an API (originally declared in  
//PRIVATE\WINCEOS\COREOS\NK\INC\Kernel.h). 
struct CINFO 
{
    char     m_szApiName[4];//used in CreateAPISet and QueryAPISetID
    BYTE     m_byDispatchType;//kernel vs user mode, 
                             //handle-based vs direct.
    BYTE     m_byApiHandle;//ID of the API, such as 
                           //SH_WIN32, SH_SHELL, etc.
    WORD     m_wNumMethods;//number of methods listed in array 
                           //m_ppMethods
    PFNVOID* m_ppMethods;  //array of pointers to methods
    DWORD  * m_pdwMethodSignatures;//DWORD-encoded methods arguments
    PPROCESS m_pProcessServer;//pointer to a process, 
                              //which serves this API.
};

//pkfuncs.h defines a lot of signature generation macros for methods
//with different number of arguments. The purpose of signatures is to
//figure out which arguments are pointers, so the dispatcher may 
//properly map them. We only need to redefine a single macro 
//FNSIG0(), which means that no arguments will be mapped.
#define FNSIG0()    0

//psyscall.h defined macros for calling API methods, 
//such as IMPLICIT_CALL
#if defined(x86)
#define FIRST_METHOD 	0xFFFFFE00
#define APICALL_SCALE	2
#elif defined(ARM)
#define FIRST_METHOD 	0xF0010000
#define APICALL_SCALE	4
#elif defined(SHx)
#define FIRST_METHOD 	0xFFFFFE01
#define APICALL_SCALE	2
#else
#error "Unknown CPU type"
#endif
#define HANDLE_SHIFT 	8
#define IMPLICIT_CALL(ApiID, MethodIdx) \
 (FIRST_METHOD - ((ApiID)<<HANDLE_SHIFT | (MethodIdx))*APICALL_SCALE)

/********   End of kernel data structure declarations **************/

#endif //SYS_DECLS
//------------------------------------------------------------------------------
//
//  THIS CODE AND INFORMATION IS PROVIDED "AS IS" WITHOUT WARRANTY OF
//  ANY KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED TO
//  THE IMPLIED WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A
//  PARTICULAR PURPOSE.
//  Copyright (c) 1995-1998  Microsoft Corporation
//  
//------------------------------------------------------------------------------
//
//  Module Name:  
//  
//      schedlog.h
//  
//  Abstract:  
//      
//      Header file for hooking the kernel's scheduler logging functions
//      in the OAL. There are two levels of support for scheduler logging. For 
//      minimal intrusiveness, the logging functions should be implemented
//      directly in the OAL. Optionally, the SCHEDLOG library can be used to export
//      the logging functions to a user process for greater flexbility. The user
//      process can hook the functions by making a KernelIoControl call.
//      
//------------------------------------------------------------------------------
#ifndef _SCHEDLOG_H
#define _SCHEDLOG_H


//------------------------------------------------------------------------------
//
//                     Kernel Scheduler Logging Hooks
//
//------------------------------------------------------------------------------
//
//  These functions are called by the scheduler when threads and processes 
//  are created and deleted and also when execution switched to a new thread.
//
//  The ID's provided by these functions are only guaranteed to be unique and 
//  do not directly correlate to any other handles or ID's in the system.
//  The SCHEDLOG library can optionally be used to translate this ID into a 
//  standard thread or process handle.
//
//------------------------------------------------------------------------------
typedef void (* LogThreadCreate_t)  (DWORD dwThreadID, DWORD dwProcID);
typedef void (* LogThreadDelete_t)  (DWORD dwThreadID, DWORD dwProcID);
typedef void (* LogProcessCreate_t) (DWORD dwProcID);
typedef void (* LogProcessDelete_t) (DWORD dwProcID);
typedef void (* LogThreadSwitch_t)  (DWORD dwThreadID, DWORD dwProcID);

//------------------------------------------------------------------------------
//
//  The kernel has 5 function pointers that must be set in order to 
//  hook into the scheduler. When not hooked, these function pointers must be 
//  set to NULL.
//
//------------------------------------------------------------------------------
extern LogThreadCreate_t  pLogThreadCreate;
extern LogThreadDelete_t  pLogThreadDelete;
extern LogProcessCreate_t pLogProcessCreate;
extern LogProcessDelete_t pLogProcessDelete;
extern LogThreadSwitch_t  pLogThreadSwitch;




//------------------------------------------------------------------------------
//
//  The SCHEDLOG library can be optionally used to wrap the kernel's calls and
//  pass them to functions in a user process. The calls are still in kernel 
//  mode and have MANY critical restrictions. They MUST NOT cause any exceptions, 
//  including page faults, thus the code must be loaded into memory. 
//  The LoadDriver function can be used to guarantee the code won't be paged.
//  The wrapped functions are NOT called in the process's context (not
//  in Slot 0), so ALL pointers must be explicitily mapped (NO slot 0 pointers).
//  No function calls can be made (since the code would think it is in Slot 0).
//  To facilitate this, when hooking the functions the app should provide a 
//  single DWORD that will be passed back to itself. This should be a mapped
//  pointer to any global variables required (buffer pointers, etc).
//
//  The wrapped functions provide the value of the performance counter, the 
//  user DWORD value, thread and/or process handles (not arbitrary ID's). The 
//  thread switch function also provides an optional interrupt code that can be
//  set by ISR's to log their occurrance, and the instruction pointer of the
//  thread that is about to run.
//
//------------------------------------------------------------------------------
typedef void (* UserLogThreadCreate_t) (DWORD dwUser, LARGE_INTEGER liPerfCount, 
                                        HANDLE hThread, HANDLE hProc);

typedef void (* UserLogThreadDelete_t) (DWORD dwUser, LARGE_INTEGER liPerfCount, 
                                        HANDLE hThread, HANDLE hProc);

typedef void (* UserLogProcessCreate_t)(DWORD dwUser, LARGE_INTEGER liPerfCount, 
                                        HANDLE hProc);

typedef void (* UserLogProcessDelete_t)(DWORD dwUser, LARGE_INTEGER liPerfCount, 
                                        HANDLE hProc);

typedef void (* UserLogThreadSwitch_t) (DWORD dwUser, LARGE_INTEGER liPerfCount, 
                                        HANDLE hThread, HANDLE hProc,
                                        DWORD dwIntCode, DWORD dwProgCounter);


//------------------------------------------------------------------------------
//  SchedLog library function prototypes
//------------------------------------------------------------------------------
typedef struct tSCHEDLOG_ENABLE {
    UserLogThreadCreate_t  pUserLogThreadCreate;    // Mapped function pointer
    UserLogThreadDelete_t  pUserLogThreadDelete;    //  "
    UserLogProcessCreate_t pUserLogProcessCreate;   //  "
    UserLogProcessDelete_t pUserLogProcessDelete;   //  "
    UserLogThreadSwitch_t  pUserLogThreadSwitch;    //  "
    DWORD dwUser;                                   // Value to be passed back
    DWORD dwPermissions;                            // Permissions of the user app
} SCHEDLOG_ENABLE, *PSCHEDLOG_ENABLE;



//------------------------------------------------------------------------------
//
// Enable/disable the scheduler logging functions. NULL parameter disables logging.
//
//------------------------------------------------------------------------------
BOOL 
SchedLogEnable(
    PSCHEDLOG_ENABLE pSLE
    );

//------------------------------------------------------------------------------
//
// Translate the kernel ID's to handles. pThreadHandle can be NULL if only a 
// process handle is being translated.
//
//------------------------------------------------------------------------------
void 
SchedLogTranslate(
    DWORD   dwThreadID,
    HANDLE* pThreadHandle,
    DWORD   dwProcID,
    HANDLE* pProcessHandle
    );

//------------------------------------------------------------------------------
//
// Get the DWORD pointer that ISR's can use to log their occurance.
//
//------------------------------------------------------------------------------
PDWORD
SchedLogGetIntCodePtr();

#endif


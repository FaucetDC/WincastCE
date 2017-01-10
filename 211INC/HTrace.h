/**************************************************************
Module : HTrace.h  Declaration of tracing routines.
             Written 1998,1999,2000 by Dmitri Leman
Purpose: Tracing framework allows inserting HTRACE and HTRACEK
  tracing statements to applications and drivers.
  Tracing messages may redirected to various output streams 
  without rebuilding the whole application.
  To enable the trace, define TRACE_ in the compiler settings.
  To compile for NT kernel mode driver, add TRACER_NTDRIVER 
  definition. To compile with Java JNI support, add TRACE_JNI.
  This file was compiled using Visual C++ 6.0 for WIN32 and NT
  kernel mode, 
  g++ version egcs-2.91 for Red Hat Linux 6.1  on Pentium
  Most of the tracer routines are also callable from C.
**************************************************************/
#ifndef TRACE_H /*{*/
#define TRACE_H

/*
The following are constants for various thread groups used in
the CeApiSpy application.
To use the trace in other applications, different groups
should be defined.
*/
enum TraceGroups
{
    TG_InterceptedInfo  = 1,/*The main output of the Spy -intercepted
                           functions, parameters, etc. */
    
    TG_DebugSpyBrief    = 2, /* Debug the Spy itself */
    TG_DebugSpyDetailed = 4, /*Detailed prints from Spy's internals*/

    TG_PrintAlways      = 8, /* Important messages */

/*The following are groups for error messages:*/
    TG_MessageBox =  0x1000000,/*errors and warnings*/

    TG_Error      = 0x80000000 /*errors*/
};/*enum TraceGroups*/


#ifdef __cplusplus
extern "C" {
#else
typedef int bool;
#endif

#ifdef WIN32
#include <tchar.h>

#else

#include <limits.h>
typedef unsigned long DWORD;
typedef unsigned long ULONG;
typedef unsigned long * PDWORD;
typedef unsigned long * PULONG;
typedef const char * LPCTSTR;
typedef const char * LPCSTR;
typedef const char * PCSTR;
typedef char * PTSTR;
typedef char * PSTR;
typedef char   TCHAR;
#define _tcslen strlen
#define IN
#define OUT
typedef struct
{
    int QuadPart;
} LARGE_INTEGER, *PLARGE_INTEGER;

typedef int HANDLE;
#define INVALID_HANDLE_VALUE -1

#define _MAX_PATH PATH_MAX

/*
These are replacement for Windows interlocked routines
for Linux implemented using Pentium inline assembly.
*/
long InterlockedExchangeAdd(long * p_plValue, long p_lAdd);
long InterlockedIncrement(long * p_plValue);
long InterlockedDecrement(long * p_plValue);

#endif

/*
The following are keyword to enable tracing of various 
routines in the applications and the driver.
*/
#define KeyWordDriverDebug "DrvD"
#define KeyWordAppDebug    "AppD"

/*
The following are constants for various trace output streams.
To add a new method of trace output just add a new constant,
then write a new output routine and add a new row in s_Outputs
array in htrace.cpp. For example one routine may send trace 
messages to a remote computer, another - to a database.
After that you can redirect selected trace groups to your 
new output stream by calling TraceAssignGroupsToStream
*/
enum TraceOutputs
{
    TO_DebugMonitor = 1,
    TO_File         = 2,
    TO_FlushFile    = 4,/*this is not a stream, but a command 
      to flush the file after a message is printed to TO_File*/
    TO_MessageBox   = 8,
    TO_Console      = 0x10,
    TO_MemoryBuffer = 0x20,
    TO_OutputLog    = 0x40,
};/*enum TraceOutputs*/

/*
The following is support for the trace memory buffer.
Most of the space in the trace buffer will be filled by actual
trace messages, but it also should keep several integers
used during tracing: buffer size, number of bytes written,
"stop after" threshold, frozen flag, enabled group mask, 
enabled keywords and keyword modification counter.

The purpose of m_dwStopAfterThreshold is to freeze the output
as soon as m_dwNumBytesWritten exceeds its value. Then m_iFrozen
will be set to 1 and no more traces will be added to the buffer.

We cannot keep integers in the header, because it will prevent
text editors from seeing our trace file as text. Therefore,
we will store size of the buffer as a text string at the
beginning of the buffer and the rest of the integer at the end.
This way text editors will be happy to open the buffer as text.

Layout of the memory trace buffer:
Header + 0: Signature       - 4 bytes
Header + 4: SizeTextAreaHex - 10 byte hexadecimal string
Actual text buffer of size == SizeTextAreaHex
Footer + 0: Number of bytes written - 4 bytes integer
Footer + 4: Threshold to stop       - 4 bytes integer
Footer + 8: Frozen or not           - 4 bytes integer
Footer + C: Group Mask              - 4 bytes integer
Footer + 10: Group Keyword Mask      - 256 bytes string
Footer + 110: Keyword modification counter - 4 bytes
*/
#define TRACE_BUFFER_SIGNATURE 0x46425254 /*"TRBF"*/
struct GlobalTraceBufferHeader/*may be in shared memory*/
{
    ULONG m_dwSignature;/*TRACE_BUFFER_SIGNATURE*/
    char  m_cSizeTextArea[12];
};/*struct GlobalTraceBufferHeader*/
struct GlobalTraceBufferFooter /*may be in shared memory*/
{
    ULONG m_dwNumBytesWritten;
    ULONG m_dwStopAfterThreshold;
    ULONG m_dwFrozen;
    ULONG m_dwEnabledGroups;
    ULONG m_dwEnabledGroupsTotal;
    char  m_szKeyWordMask[256];
    ULONG m_dwKeyWordModificationCounter;
};/*struct GlobalTraceBufferHeader*/
struct LocalTraceBufferPointers  /*kept local by application*/
{
    struct GlobalTraceBufferHeader *   m_pGlobalHeader;
    LPTSTR                      m_pTextArea;
    ULONG                       m_dwTextAreaSize;
    struct GlobalTraceBufferFooter *   m_pGlobalFooter;
};
#define TRACE_BUFFER_EXTRA_SIZE \
    (sizeof(GlobalTraceBufferHeader)+\
    sizeof(GlobalTraceBufferFooter))

#ifdef TRACE_ /*{*/
/*
Current implementation does not allow simultaneous modification
of trace parameters by multiple threads. Ideally, a process 
should initialize trace from the beginning and, may be, 
update trace parameters from a single thread.
Functions, which generate trace, such as HTraceImpl and 
OutputTraceString can be called by any thread at any time(after
the trace is initialized by TraceInitialize.
*/

/*
TraceInitialize should be called once for any process, which 
use the trace. TraceUnInitialize should be called before
the process terminates.
In some platforms C++ constructors can be used for this
purpose, but many other platforms lack such support.
*/
bool TraceInitialize(void);
bool TraceUnInitialize(void);

/*
TraceAssignGroupsToStream is the most important function of
the trace. It allows turning on and off individual group 
flags defined in enum TraceGroups for each trace output 
specified by constants in enum TraceOutputs, which will 
enable/disable and redirect the specified trace groups 
for the given output streams.
PARAMETERS:                   .
    p_dwTraceOutputs       flags from TraceOutputs.
    p_dwNewGroupFlags      groups to print
    p_dwGroupFlagsToModify which bits can be modified
*/
bool TraceAssignGroupsToStream
(
    ULONG   p_dwTraceOutputs,
    ULONG   p_dwNewGroupFlags,
    ULONG   p_dwGroupFlagsToModify

);
/*
TraceAssignGroupKeyWordToStream is useful when there is not
enough bit positions in 32 bit number to assign for various
trace groups in the program. In such a case string keywords
can be assigned to trace groups. 
TraceAssignGroupKeyWordToStream allows assigning
individual group keywords for each trace output 
specified by constants in enum TraceOutputs. 
PARAMETERS:                   .
    p_dwTraceOutputs       flags from TraceOutputs.
    char  *  p_pszGroupKeyWord      new keyword mask
*/
bool TraceAssignGroupKeyWordToStream
(
    ULONG   p_dwTraceOutputs,
    char  * p_pszGroupKeyWord
);
/*
TraceGetAssignedGroupsToStream and 
TraceGetAssignedGroupKeyWordsToStream allow to get currently
enabled trace groups for a particular trace output.
PARAMETERS:                   .
    p_dwTraceOutputs       flags from TraceOutputs.
*/
ULONG TraceGetAssignedGroupsToStream(ULONG   p_dwTraceOutputs);
LPCSTR TraceGetAssignedGroupKeyWordsToStream
    (ULONG p_dwTraceOutputs);

/*
TraceReadWriteSettings allows to read and write
the current trace settings, including group masks and keywords 
for some or all output streams to/from system registry or 
an INI file under WIN32. This allows defining trace settings 
in registry or INI file without modifying the program.
   PARAMETERS:                   .
    HKEY    p_hKeyRoot            root registry key (for example
        HKEY_CURRENT_USER). May be NULL - in that case p_pszPath
        should be a path to .INI file (if platform supports it).
    LPCTSTR  p_pszPath   if p_hKeyRoot != NULL - registry path
                         if p_hKeyRoot == NULL - INI file path
    bool    p_bWrite              true to write, false to read
    ULONG   p_ulOutputsToProcess  flags from TraceOutputs - 
        chose which stream settings to read/write
*/
bool TraceReadWriteSettings(HKEY p_hKeyRoot, LPCTSTR p_pszPath,
    bool p_bWrite, ULONG   p_ulOutputsToProcess);

#ifndef TRACER_NTDRIVER
/*
TraceSetOutputToFile enables tracing to a file. Unlike 
memory-mapped file, output to a file will directly print 
trace messages to a file, 
which allows an unlimited size, but may be slower.
This function accepts 2 masks: p_dwNewGroupFlags to decide
which trace statements should be printed to file and 
p_dwNewFlushBits to determine which trace statements should
also flush the file. Flushing the file allows to preserve
the trace if an application crashes, but is much slower.
   PARAMETERS:                   .
    LPCTSTR p_pszFileName       - file name to print traces to
    ULONG   p_dwNewGroupFlags     -  groups to print
    ULONG   p_dwGroupFlagsToModify-trace groups flags to change
    ULONG   p_dwNewFlushBits - groups which will flush the file
    ULONG   p_dwFlushBitsToModify  - trace flags to change
*/
bool TraceSetOutputToFile
(
    LPCTSTR p_pszFileName,
    ULONG   p_dwNewGroupFlags,
    ULONG   p_dwGroupFlagsToModify,
    ULONG   p_dwNewFlushBits   ,
    ULONG   p_dwFlushBitsToModify
);
LPCTSTR TraceGetCurTraceFileName();
#endif

/*
TraceAllocateBuffer - allocate trace buffer of the given size
and enable trace groups for that output. This buffer cannot be
shared with other applications or files. This buffer should be
dumped to a file using TraceDumpBufferToFile before the program
terminates. Other ways to enable trace to a memory buffer are
TraceSetExternalBuffer, TraceAttachToNTDriverBuffer, 
TraceUseMemMapFileBuffer 
   PARAMETERS:                   .
    int p_iSize    - size of the buffer text area to allocate
    ULONG   p_dwNewGroupFlags     - groups to print
    ULONG   p_dwGroupFlagsToModify-trace groups flags to change
*/
bool TraceAllocateBuffer(int p_iSize,
    ULONG   p_dwNewGroupFlags, ULONG   p_dwGroupFlagsToModify);
/*
TraceSetExternalBuffer is used to share trace buffer between 
several application. If one application or driver created the 
trace buffer in some kind of shared memory, another application
can obtain a pointer to that buffer and call 
TraceSetExternalBuffer to start printing it's trace to the same
buffer. A care should be taken with group flags in this case,
because they will affect trace in both applications.
   PARAMETERS:                   .
    GlobalTraceBufferHeader* p_pBufferHeader - trace pointers 
                returned from pGetTraceBuffer
    ULONG   p_dwNewGroupFlags     - groups to print
    ULONG   p_dwGroupFlagsToModify-trace groups flags to change
*/
bool TraceSetExternalBuffer(
    struct GlobalTraceBufferHeader* p_pBufferHeader,
    ULONG   p_dwNewGroupFlags, ULONG   p_dwGroupFlagsToModify);
/*
TraceAttachToNTDriverBuffer is a convenience function, which
requests the shared trace buffer from an NT kernel mode driver,
and calls TraceSetExternalBuffer to share the buffer with the
driver. The driver must process necessary IOCTL requests.
To easiest way to meet these requirements, is to include 
HTrace.cpp in the driver and call TraceIoctl
from the driver's dispatch routine, as shown in HTraceD.cpp.
   PARAMETERS:
    LPCTSTR  p_pszDeviceName - name of NT device. This parameter
      can be left NULL to use our default name
      TRACER_WIN32_FILE_NAME
    int     p_iIOCTLMapTraceBuffer - NT IOCTL code to map the
      buffer. This parameter can be left -1 to use our default
      IOCTL_TRACER_MAP_BUFFER
    int     p_iIOCTLUnMapTraceBuffer - NT IOCTL code to unmap 
      the buffer. This parameter can be left -1 to use our 
      default IOCTL_TRACER_MAP_BUFFER
    bool    p_bDontComplainIfDeviceAbsent - set to true if the 
      caller expects that the driver may be absent.
    ULONG   p_dwNewGroupFlags     - groups to print
    ULONG   p_dwGroupFlagsToModify-trace groups flags to change
*/
bool TraceAttachToNTDriverBuffer
(
    LPCTSTR p_pszDeviceName,
    int     p_iIOCTLMapTraceBuffer,
    int     p_iIOCTLUnMapTraceBuffer,
    bool    p_bDontComplainIfDeviceAbsent,
    ULONG   p_dwNewGroupFlags, ULONG   p_dwGroupFlagsToModify
);
/*
TraceUseMemMapFileBuffer creates a memory mapped file
(or use an existing one) to shared trace buffer between 
several applications.
   PARAMETERS:
        p_pszMemMapFilePath  - file path
        p_iFileSize          - size (for creation)
        p_dwNewGroupFlags    - groups to print
        p_dwGroupFlagsToModify-trace groups flags to change
*/
bool TraceUseMemMapFileBuffer
(
    LPCTSTR p_pszMemMapFilePath,
    int     p_iFileSize,
    ULONG   p_dwNewGroupFlags, 
    ULONG   p_dwGroupFlagsToModify
);
/*
TraceFreeBuffer frees the trace buffer (if it was allocated),
releases memory mapped file or calls NT driver to detach from 
the buffer, which was shared by TraceAttachToNTDriverBuffer.
*/
bool TraceFreeBuffer();
/*
TraceDumpBufferToFile prints the memory buffer to the specified
file. It is usually called before the program terminates.
This function can handle circular buffers.
*/
bool TraceDumpBufferToFile(LPCTSTR p_pszFileName);

/*
pGetTraceBuffer returns LocalTraceBufferPointers structure,
which keeps pointers to the currently allocated trace buffer
(if any) including header, text area, size and footer.
*/
struct LocalTraceBufferPointers * pGetTraceBuffer();

/*
TraceFreezeBufferAfter will freeze output to the trace buffer
after the specified amount of data (measured in percents
from the buffer size). 
Common use:
- TraceFreezeBufferAfter(0) to freeze output immediately - 
    last printed trace will remain the last in the buffer.
- TraceFreezeBufferAfter(50) - last printed trace will be
        approximately at the middle of the buffer
- TraceFreezeBufferAfter(100) - last printed trace will be
   the first in the trace buffer after freeze.
*/
void TraceFreezeBufferAfter(int p_iPercent);

/*
TraceEraseBuffer erases the trace buffer by resetting 
the "number of bytes written" field of the trace buffer
*/
void TraceEraseBuffer();

#ifdef TRACER_NTDRIVER
typedef struct _DRIVER_OBJECT *PDRIVER_OBJECT;
/*
EnableTraceToOutputLog used by NT drivers to enable some trace
groups to be printed to the system log.
*/
bool EnableTraceToOutputLog(PDRIVER_OBJECT p_pDriverObject,
    ULONG   p_dwNewGroupFlags, ULONG   p_dwGroupFlagsToModify);
#endif

/*Actual trace output routines with group bit masks:*/
/*
OutputTraceString is the fastest tracing routine.It does no 
formatting, it simply copies the specified string to output 
streams, which matches the specified group mask.
   PARAMETERS:                   .
                        
    ULONG p_dwMask          flags from TraceGroups
    LPCSTR p_pszMessage,    string
    int     p_iLen          Number of characters in the string
*/
void OutputTraceString(ULONG p_dwMask, LPCTSTR p_pszMessage, 
                       int p_iLen);
/*
HTraceImpl and macro HTRACE are used to format trace message
and print it to streams,which matches the specified group mask.
*/
void HTraceImpl(ULONG p_dwMask, LPCTSTR p_pszFormat, ...);
#define HTRACE HTraceImpl
/*
OutputTraceStringUnconditional disregards group masks
and copies the given string to all output streams,
which has their TO_* constants included in p_dwOutputMask
*/
void OutputTraceStringUnconditional(ULONG   p_dwOutputMask,
    LPCTSTR  p_pszMessage, int     p_iLenChars);

void RegisterTraceView(LPCTSTR p_pszClassName);

/*Support for keyword masks*/
#ifdef __cplusplus
class TraceKeywordCheck 
{
public:
    void Output(char * p_pszKeyWord, LPCTSTR p_pszFormat,
        ...);
    void CompareKeyWords(const char * p_pszKeyWord);

    ULONG m_dwEnabledStreams;
    ULONG m_dwModificationCounter;
};/*class TraceKeywordCheck*/

/*
Parameters of HTRACEK must be enclosed in double brackets like:
HTRACEK(("KeyWord", "Format %s %d", "First Param", 123))
This macro formats the trace messages and prints it to the
output streams, which have keyword masks that matches the 
given keyword.
*/
#define HTRACEK(Params)  {  \
    static TraceKeywordCheck l_Check = {false, 0}; \
    l_Check.Output Params ;   \
}

#endif /*__cplusplus*/

#else /* } TRACE_ {*/

#if defined(__cplusplus) && !defined(TRACE_CPP) /* {*/
/*
The following are empty versions of all functions,
which are used then TRACE_ macro is not defined.
They should be completely optimized out by the compiler,
so the all trace calls can be left in the release version
of the program.
*/

inline bool TraceInitialize(){return false;};
inline bool TraceUnInitialize(){return false;};

inline bool TraceAssignGroupsToStream
    (ULONG   p_dwTraceOutputs, ULONG   p_dwNewGroupFlags,
    ULONG   p_dwGroupFlagsToModify) {return false;}
inline bool TraceAssignGroupKeyWordToStream
    (ULONG   p_dwTraceOutputs, char  * p_pszGroupKeyWord)
    {return false;}
inline ULONG TraceGetAssignedGroupsToStream
    (ULONG p_dwTraceOutputs) {return 0;}
inline LPCSTR TraceGetAssignedGroupKeyWordsToStream
    (ULONG p_dwTraceOutputs) {return NULL;};
inline bool TraceReadWriteSettings
    (HKEY p_hKeyRoot, LPCTSTR p_pszPath,
    bool p_bWrite, ULONG   p_ulOutputsToProcess) 
    {return false;}

#ifndef TRACER_NTDRIVER
inline bool TraceSetOutputToFile(LPCTSTR p_pszFileName,
    ULONG   p_dwNewGroupFlags, ULONG   p_dwGroupFlagsToModify,
    ULONG   p_dwNewFlushBits ,ULONG   p_dwFlushBitsToModify)
    {return false;}
inline LPCTSTR TraceGetCurTraceFileName(){return NULL;};
#endif

inline bool TraceAllocateBuffer(int p_iSize,
    ULONG   p_dwNewGroupFlags, ULONG   p_dwGroupFlagsToModify)
    {return false;}
inline bool TraceSetExternalBuffer(
    GlobalTraceBufferHeader* p_pBufferHeader,
    ULONG   p_dwNewGroupFlags, ULONG   p_dwGroupFlagsToModify)
    {return false;}
inline bool TraceAttachToNTDriverBuffer
(
    LPCSTR  p_pszDeviceName,
    int    p_iIOCTLMapTraceBuffer,int p_iIOCTLUnMapTraceBuffer,
    bool    p_bDontComplainIfDeviceAbsent,
    ULONG   p_dwNewGroupFlags, ULONG   p_dwGroupFlagsToModify
){return false;}
inline bool TraceUseMemMapFileBuffer
(
    LPCTSTR p_pszMemMapFilePath,
    int     p_iFileSize,
    ULONG   p_dwNewGroupFlags, 
    ULONG   p_dwGroupFlagsToModify
){return false;}
inline bool TraceFreeBuffer(){return false;}
inline bool TraceDumpBufferToFile(LPCTSTR p_pszFileName)
{return false;}
inline LocalTraceBufferPointers*pGetTraceBuffer(){return NULL;}

#ifdef TRACER_NTDRIVER
typedef struct _DRIVER_OBJECT *PDRIVER_OBJECT;
inline bool EnableTraceToOutputLog(
    PDRIVER_OBJECT p_pDriverObject, ULONG   p_dwNewGroupFlags, 
    ULONG   p_dwGroupFlagsToModify) {return false;}
#endif

/*Actual trace output routines with group bit masks:*/
inline void OutputTraceString(ULONG p_dwMask, 
    LPCTSTR p_pszMessage, int p_iLen) {}
inline void HTraceImpl(ULONG p_dwMask, 
                       LPCTSTR p_pszFormat, ...){}
inline void OutputTraceStringUnconditional
    (ULONG p_dwOutputMask, LPCSTR  p_pszMessage, int p_iLen) {}
inline void RegisterTraceView(LPCTSTR p_pszClassName) {}
inline void Dummy(...){}
#define HTRACE            1 ? (void)0 : HTraceImpl
#define HTRACEK           1 ? (void)0 : Dummy

#endif /* #if defined(__cplusplus) && !defined(TRACE_CPP) }*/
#endif/*TRACE_ else }*/

/*The following definitions are for communication with NT 
driver*/
#if defined(WIN32) && !defined(TRACER_NTDRIVER)
#include <winioctl.h>
#endif

#if defined(WIN32) || defined(TRACER_NTDRIVER) /*{*/

#define TRACER_KERNEL_DEVICE_NAME L"\\Device\\HTrcDrv"
#define TRACER_DOS_DEVICE_NAME_A  "\\DosDevices\\HTrcDrv"
#define TRACER_DOS_DEVICE_NAME_W  L"\\DosDevices\\HTrcDrv"

#define TRACER_WIN32_FILE_NAME_W    L"\\\\.\\HTrcDrv"
#define TRACER_WIN32_FILE_NAME      _T("\\\\.\\HTrcDrv")

/*
Define a random device type and IOCTL codes, which will be used
by our launcher application to call our driver
*/
#define FILE_DEVICE_TRACER     0x83ff

#define IOCTL_TRACER_CHECK_ACTIVE ((ULONG) CTL_CODE\
( FILE_DEVICE_TRACER, 0x01, METHOD_BUFFERED, FILE_ANY_ACCESS ))
#define IOCTL_TRACER_DUMP_TRACE   ((ULONG) CTL_CODE\
( FILE_DEVICE_TRACER, 0x02, METHOD_BUFFERED, FILE_ANY_ACCESS ))
#define IOCTL_TRACER_MAP_BUFFER ((ULONG) CTL_CODE\
( FILE_DEVICE_TRACER, 0x03, METHOD_BUFFERED, FILE_ANY_ACCESS ))
#define IOCTL_TRACER_UNMAP_BUFFER ((ULONG) CTL_CODE\
( FILE_DEVICE_TRACER, 0x04, METHOD_BUFFERED, FILE_ANY_ACCESS ))

#endif /*#if defined(WIN32) || defined(TRACER_NTDRIVER) } */

#ifdef TRACER_NTDRIVER/* { */
/*
The following routines to be used by a NT driver to map, 
unmap and print trace buffer to a file
*/
#ifdef TRACE_ /* { */
/*
TraceIoctl: This function should be called by driver's dispatch
    routine to allow the tracer to respond to request for 
    mapping and unmapping trace buffer and dumping it to a file
      
PARAMETERS:                   .
                                  
   IN PDEVICE_OBJECT   p_pDeviceObject        our device object
   IN PIRP             p_pIrp                 request packet
          The following are IOCTL codes for tracer requests.
          Usually these are IOCTL_TRACER_* defined in HTrace.h,
          but the driver may assign different codes.
   IN ULONG p_dwIoctlCheckActive  - check presence of tracer.
              This code will be returned in the output buffer.
   IN ULONG p_dwIoctlDumpTrace    - dump the content of trace
              memory buffer to the file. IOCTL input buffer
              has the name of the file.
   IN ULONG p_dwIoctlMapBuffer    - map the trace memory buffer
              to the user space of the current application and
              return the address in the IOCTL output buffer.
   IN ULONG p_dwIoctlUnMapBuffer  - unmap the trace buffer.
           The IOCTL input buffer should have the user address,
           which was previously returned by p_iIoctlMapBuffer
*/
NTSTATUS TraceIoctl
( 
    IN PDEVICE_OBJECT   p_pDeviceObject, 
    IN PIRP             p_pIrp,
    IN ULONG            p_dwIoctlCheckActive,
    IN ULONG            p_dwIoctlDumpTrace,
    IN ULONG            p_dwIoctlMapBuffer,
    IN ULONG            p_dwIoctlUnMapBuffer
);
/*
MapTraceMemory map the trace buffer to the address context of the
current application and store the new MapMem object into
the given FILE_OBJECT, so we will be able to unmap the 
memory when the file is closed.
   PARAMETERS:
    PFILE_OBJECT p_pFileObject - file object, which was created 
        specifically for communication with the tracer driver.
        Don't try to call this function on other file objects,
        because it will overwrite FsContext field.
    ULONG   *p_pulReturnUserAddress - return the mapped address
*/
NTSTATUS MapTraceMemory(PFILE_OBJECT p_pFileObject, 
                        ULONG *p_pulReturnUserAddress);
/*
UnmapTraceMemory unmaps the trace buffer, which was mapped by 
    MapTraceMemory.
   PARAMETERS:
    ULONG        p_ulUserAddress - the address, which was
        returned by MapTraceMemory
    PFILE_OBJECT p_pFileObject - must be the file object, which
       was created for communication with the tracer driver and
       was used in call to MapTraceMemory.
*/
NTSTATUS UnmapTraceMemory(ULONG p_ulUserAddress, 
                          PFILE_OBJECT p_pFileObject);
#else
inline NTSTATUS TraceIoctl
( 
    IN PDEVICE_OBJECT   p_pDeviceObject, 
    IN PIRP             p_pIrp,
    IN ULONG            p_dwIoctlCheckActive,
    IN ULONG            p_dwIoctlDumpTrace,
    IN ULONG            p_dwIoctlMapBuffer,
    IN ULONG            p_dwIoctlUnMapBuffer
    ){return STATUS_NOT_IMPLEMENTED;}
inline NTSTATUS MapTraceMemory(PFILE_OBJECT p_pFileObject, 
                        ULONG *p_pulReturnUserAddress)
                        {return STATUS_NOT_IMPLEMENTED;}
inline NTSTATUS UnmapTraceMemory(ULONG p_ulUserAddress, 
                          PFILE_OBJECT p_pFileObject)
                          {return STATUS_NOT_IMPLEMENTED;}
#endif /*#ifdef TRACE_ else }*/
#endif /*#ifdef TRACER_NTDRIVER }*/

#ifdef __cplusplus
}/*extern "C"*/
#endif

#if defined(TRACE_) && defined WIN32 && !defined(TRACER_NTDRIVER)//{
#if defined(__cplusplus) /*{*/
/*
class LocalStringHolder, strGetErrorExplanation and ERR_EXPL
are useful for printing Win32 error messages.
For example : HTRACE(TG_Error, "ERROR: CreateFile failed - %s",
            ERR_EXPL(GetLastError());

class LocalStringHolder simply keeps a string allocated using 
LocalAlloc API function and frees this function in destructor.
*/
class LocalStringHolder
{
public:
    LocalStringHolder()
    {
        m_pszString = m_szDummy;
        *m_szDummy = 0;
    }
    ~LocalStringHolder(){Free();}
    LocalStringHolder(const LocalStringHolder & p_rScr) 
    {
        m_pszString = m_szDummy;
        *m_szDummy = 0;
        StrDup(p_rScr.m_pszString);
    }
    LocalStringHolder & operator = 
        (const LocalStringHolder & p_rScr) 
    {
        Free();
        StrDup(p_rScr.m_pszString);
        return *this;
    }

    void StrDup(PTSTR p_pszStr)
    {
        Free();
        int l_iSize = (_tcslen(p_pszStr)+1)*sizeof(TCHAR);
        m_pszString = (PTSTR)LocalAlloc(LPTR, l_iSize);
        if(!m_pszString)
            m_pszString = m_szDummy;
        else
            memcpy(m_pszString, p_pszStr, l_iSize);
    }/*void SetStr*/

    void AdoptStr(PTSTR p_pszStr)
        /*p_pszStr must be allocated using LocalAlloc*/
    {
        Free();
        m_pszString = p_pszStr;
    }
    LPCTSTR strGetStr(){return m_pszString;}
    void Free()
    {
        if(m_pszString != m_szDummy)
            LocalFree(m_pszString);
        m_pszString = m_szDummy;
    }/*void Free()*/
protected:
    PTSTR   m_pszString;
    TCHAR   m_szDummy[1];
};/*class LocalStringHolder*/

/*
strGetErrorExplanation takes WIN32 error code and returns 
error message
*/
LocalStringHolder strGetErrorExplanation(DWORD p_dwErrCode);

/*
ERR_EXPL is a convenient macro to be used in printf and 
HTRACE calls to print Win32 error messages.
*/
#define ERR_EXPL(ErrorCode) \
    ((LPCTSTR)strGetErrorExplanation(ErrorCode).strGetStr())

#endif /*defined(__cplusplus) } */
#endif /*defined WIN32 && !defined(TRACER_NTDRIVER) }*/

#if defined(_WIN32_WCE)

/*
#undef RETAILMSG
#define RETAILMSG(mask, printf_exp)  HTraceImpl(mask, A printf_exp)

#undef DEBUGZONE
#define DEBUGZONE(n) n
*/
#endif


#endif /*TRACE_H }*/

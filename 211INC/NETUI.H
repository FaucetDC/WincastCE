/*++
THIS CODE AND INFORMATION IS PROVIDED "AS IS" WITHOUT WARRANTY OF
ANY KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED TO
THE IMPLIED WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A
PARTICULAR PURPOSE.
Copyright (c) 1995-1998  Microsoft Corporation

Module Name:  

netui.h

Abstract:  

Functions:


Notes: 
    The netui library cannot be loaded before GWE has initialized (since it
    initializes common controls on DLL entry).  So, check that the WMGR API
    set has been registered before loading netui.dll.

--*/

#ifndef _NETUI_H_
#define _NETUI_H_
// @CESYSGEN IF CE_MODULES_NETUI

#include <windev.h>

// 
// ----------------------------------------------------------------
//
// GetNetString function parameters.
//
// ----------------------------------------------------------------
#define NETUI_GETNETSTR_DIRECT_NAME	     0
#define NETUI_GETNETSTR_OPEN_FILE_CONF   1
#define NETUI_GETNETSTR_BAD_RES_NAME     2
#define NETUI_GETNETSTR_ERR_ADDCONNECT   3
#define NETUI_GETNETSTR_ERR_INV_COMPNAME 4
#define NETUI_GETNETSTR_ERR_ADDNAME      5
#define NETUI_GETNETSTR_DISCON_ERROR     6
#define NETUI_GETNETSTR_SAVE_PWD         7
#define NETUI_GETNETSTR_DFLT_LOCALNAME   8
#define NETUI_GETNETSTR_NO_IPADDR		 9
#define NETUI_GETNETSTR_LEASE_EXPIRED	 10
#define NETUI_GETNETSTR_CACHED_LEASE	 11
#define NETUI_GETNETSTR_PRINT_COMPLETE   12
#define NETUI_GETNETSTR_PRINT_STATUS     13
#define NETUI_GETNETSTR_PRINT_STATUS_OFFLINE  14
#define NETUI_GETNETSTR_PRINT_STATUS_PAPER    15
#define NETUI_GETNETSTR_PRINT_STATUS_OTHER    16
#define NETUI_GETNETSTR_PRINT_STATUS_NETERR   17
#define NETUI_GETNETSTR_USB_INSTALL_FAILURE   18 

int GetNetString (UINT uID, LPTSTR lpBuffer, int nBufferMax);
typedef int (WINAPI *PFN_GetNetString) (UINT uID,
										LPTSTR lpBuffer,
										int nBufferMax);

// 
// ----------------------------------------------------------------
//
// GetUsernamePassword function parameters.
//
// ----------------------------------------------------------------


#include "lmcons.h"

typedef struct _NETUI_USERPWD {
	TCHAR	szUserName[UNLEN + 1];
	TCHAR	szPassword[PWLEN + 1];
	TCHAR	szDomain[DNLEN + 1];
	DWORD	dwFlags;
#define NETUI_USERPWD_SAVEPWD		0x00000001	// SavePwd box is checked
#define NETUI_USERPWD_SHOW_SAVEPWD	0x00000002	// Show the SavePwd control
#define NETUI_USERPWD_SERVERLOGON   0x00000004  // Connecting to network server
    TCHAR   szResourceName[RMLEN];              // Only valid if SERVERLOGON flag set
    
} NETUI_USERPWD, *PNETUI_USERPWD;

BOOL WINAPI GetUsernamePassword (HWND hParent, PNETUI_USERPWD pUserPwd);
typedef BOOL (WINAPI *PFN_GetUsernamePassword)(HWND hParent,
											   PNETUI_USERPWD pUserPwd);

// 
// ----------------------------------------------------------------
//
// GetResourcePassword function parameters.
//
// ----------------------------------------------------------------


typedef struct _NETUI_RESPWD {
	TCHAR	szPassword[PWLEN + 1];
    TCHAR   szResourceName[RMLEN];
    
} NETUI_RESPWD, *PNETUI_RESPWD;

BOOL WINAPI GetResourcePassword (HWND hParent, PNETUI_RESPWD pResPwd);
typedef BOOL (WINAPI *PFN_GetResourcePassword)(HWND hParent,
											   PNETUI_RESPWD pResPwd);

// 
// ----------------------------------------------------------------
//
// GetIPAddress Dialog
//
// ----------------------------------------------------------------
DWORD GetIPAddress ( HWND hParent );
typedef BOOL (WINAPI *PFN_GetIPAddress)(HWND hParent);

// 
// ----------------------------------------------------------------
//
// IP Address Control info
//
// ----------------------------------------------------------------

// Messages sent to IPAddress controls

#define	IP_CLEARADDRESS	WM_USER+100	// no parameters
#define	IP_SETADDRESS	WM_USER+101	// lparam = TCP/IP address
#define IP_GETADDRESS	WM_USER+102	// lresult = TCP/IP address
#define IP_SETRANGE	WM_USER+103	// wparam = field, lparam = range
#define IP_SETFOCUS	WM_USER+104	// wparam = field


// IP Address style bits

#define	IP_LEFT		0x00000001L	// left justify fields
#define IP_RIGHT	0x00000002L	// right justify fields
#define	IP_CENTER	0x00000004L	// center fields
#define IP_ZERO		0x00000008L	// Zero fill the fields


// The following is a useful macro for passing the range values in the
// IP_SETRANGE message.

#define	MAKERANGE(low, high)	((LPARAM)(WORD)(((BYTE)(high) << 8) + (BYTE)(low)))

// And this is a useful macro for making the IP Address to be passed
// as a LPARAM.

#define MAKEIPADDRESS(b1,b2,b3,b4)	((LPARAM)(((DWORD)(b1)<<24)+((DWORD)(b2)<<16)+((DWORD)(b3)<<8)+((DWORD)(b4))))

void WINAPI RegisterIPClass(HINSTANCE hInst);
void WINAPI UnregisterIPClass(HINSTANCE hInst);
// 
// ----------------------------------------------------------------
//
// Unimodem Config dialog
//
// ----------------------------------------------------------------
typedef struct {
	DWORD	dwVersion;
#define NETUI_LCD_STRUCTVER				1
	DWORD	dwBaudRate;					// Baud Rate (i.e. 9600, 115200)
	DWORD	dwSettableBaud;				// Baud Rates Supported (see COMMPROP)
	BYTE	bByteSize;					// Number of Bits/Byte 4-8
	BYTE	bParity;					// 0-4=None, Odd, Even, Mark, Space
	BYTE	bStopBits;					// 0,1,2 = 1, 1.5, 2
	BYTE	bReserved;					// Alignment
	WORD	wSettableData;				// Which of the Byte/Stop/Parity
										// are settable (see COMMPROP)
	WORD	wWaitBong;					// Wait for Bong time
	DWORD	dwCallSetupFailTimer;		// Dial timeout
	DWORD	dwModemOptions;				// Modem Options
#define NETUI_LCD_MDMOPT_SOFT_FLOW		0x00000001	// Hardware flow control
#define NETUI_LCD_MDMOPT_HARD_FLOW		0x00000002	// Software flow control
#define NETUI_LCD_MDMOPT_BLIND_DIAL		0x00000004	// Blind Dial
	
	DWORD	dwTermOptions;				// Terminal Options
#define NETUI_LCD_TRMOPT_MANUAL_DIAL	0x00000001	// Manual dial terminal
#define NETUI_LCD_TRMOPT_PRE_DIAL		0x00000002	// Pre-dial terminal
#define NETUI_LCD_TRMOPT_POST_DIAL		0x00000004	// Post-dial terminal
	
	DWORD	dwDdevCapFlags;				// Not supported yet.
	
#define NETUI_LCD_DIAL_MOD_LEN	128
	DWORD	dwModMaxLen;				// Length to allow user to edit.
	TCHAR	szDialModifier[NETUI_LCD_DIAL_MOD_LEN+1];
} LINECONFIGDATA, *PLINECONFIGDATA;

BOOL WINAPI LineConfigEdit (HWND hParent, PLINECONFIGDATA pLineConfigData);
typedef BOOL (WINAPI *PFN_LineConfigEdit)(HWND hParent,
										  PLINECONFIGDATA pLineConfigData);

// 
// ----------------------------------------------------------------
//
// LineTranslateDialog
//
// ----------------------------------------------------------------
DWORD LineTranslateDialog ( HWND hParent, HWND *pDialogWnd );
typedef BOOL (WINAPI *PFN_LineTranslateDialog)(HWND hParent, HWND *pDialogWnd);

// 
// ----------------------------------------------------------------
//
// WNetAddConnect dialog
//
// ----------------------------------------------------------------
typedef struct _addconnect_dlgparams
{
    WCHAR LocalName[RMLEN + 10]; // Give space for "share on server"
    WCHAR RemoteName[RMLEN];
    BOOL  bReadOnly;             // If TRUE, make remote name read only
    
} ADDCONNECT_DLGPARAMS, *PADDCONNECT_DLGPARAMS;

BOOL WINAPI ConnectionDialog (HWND hParent, PADDCONNECT_DLGPARAMS pDlgParams);
typedef BOOL (WINAPI *PFN_ConnectionDialog)(HWND hParent,
                                            PADDCONNECT_DLGPARAMS pDlgParams);

// 
// ----------------------------------------------------------------
//
// WNetDisconnect dialog
//
// ----------------------------------------------------------------
BOOL WINAPI DisconnectDialog (HWND hParent, DWORD dwType);
typedef BOOL (WINAPI *PFN_DisconnectDialog)(HWND hParent, DWORD dwType);


// 
// ----------------------------------------------------------------
//
// NetMsgBox dialog
//
// ----------------------------------------------------------------
BOOL WINAPI NetMsgBox (HWND hParent, DWORD dwFlags, TCHAR *szStr);
typedef BOOL (WINAPI *PFN_NetMsgBox)(HWND hParent, DWORD dwFlags, TCHAR *szStr);
// Defs for flags
#define NMB_FL_OK       0x00000001
#define NMB_FL_EXCLAIM  0x00000002
#define NMB_FL_YESNO    0x00000004
#define NMB_FL_TOPMOST	0x00000008

// Default title for MB is "Windows CE Networking". Override with these flags.
#define NMB_FL_TITLEUSB 0x00001000


// 
// ----------------------------------------------------------------
//
// AdapterIPProperties dialog
//
// ----------------------------------------------------------------
BOOL AdapterIPProperties (HWND hWndOwner, LPTSTR szAdapterName);
typedef BOOL (WINAPI *PFN_AdapterIPProperties)(HWND hWndOwner, LPTSTR szAdapterName);


// 
// ----------------------------------------------------------------
//
// GetDriverName function parameters.
//
// ----------------------------------------------------------------

#define DRIVER_NAME_LEN 128
// This function is shared by USB
#define PCCARDTYPE_USB  0x80000000
typedef struct _GETDRIVERNAMEPARMS {
    WCHAR DriverName[DRIVER_NAME_LEN];
    DWORD Socket;
    DWORD PCCardType;
} GETDRIVERNAMEPARMS, * PGETDRIVERNAMEPARMS;

BOOL WINAPI GetDriverName (HWND hParent, PGETDRIVERNAMEPARMS pDriverParms);
typedef BOOL (WINAPI *PFN_GetDriverName)(HWND hParent,
									   PGETDRIVERNAMEPARMS pDriverParms);

// 
// ----------------------------------------------------------------
//
// Inline functions
//
// Use these functions to call the dll, will return appropriate
// failure codes if the DLL does not exist.
//
// ----------------------------------------------------------------

_inline int
CallGetNetString (UINT uID, LPTSTR lpBuffer, int nBufferMax)
{
	HINSTANCE	hLibInst;
	PFN_GetNetString pfnGetNetString;
	int			RetVal;

	if (IsAPIReady(SH_WMGR) && ((hLibInst = LoadLibrary(TEXT("netui.dll"))) != NULL)) {
		pfnGetNetString = (PFN_GetNetString)GetProcAddress (
			hLibInst, TEXT("GetNetString"));
		if (pfnGetNetString) {
			RetVal = pfnGetNetString(uID, lpBuffer, nBufferMax);
		} else {
			RETAILMSG (1, (TEXT("Can't find GetNetString")));
			SetLastError (ERROR_FILE_NOT_FOUND);
			RetVal = 0;
		}
	} else {
		RETAILMSG (1, (TEXT("Can't load netui.dll")));
		SetLastError (ERROR_PATH_NOT_FOUND);
		RetVal = 0;
	}
	if (hLibInst) {
		FreeLibrary(hLibInst);
	}
	return RetVal;
}


_inline BOOL
CallGetUsernamePassword (HWND hParent, PNETUI_USERPWD pUserPwd)
{
	HINSTANCE	hLibInst;
	PFN_GetUsernamePassword pfnGetUsernamePassword;
	BOOL		RetVal;

	if (IsAPIReady(SH_WMGR) && ((hLibInst = LoadLibrary(TEXT("netui.dll"))) != NULL)) {
		pfnGetUsernamePassword = (PFN_GetUsernamePassword)GetProcAddress (
			hLibInst, TEXT("GetUsernamePassword"));
		if (pfnGetUsernamePassword) {
			RetVal = pfnGetUsernamePassword(hParent, pUserPwd);
		} else {
			RETAILMSG (1, (TEXT("Can't find GetUsernamePassword")));
			SetLastError (ERROR_FILE_NOT_FOUND);
			RetVal = FALSE;
		}
	} else {
		RETAILMSG (1, (TEXT("Can't load netui.dll")));
		SetLastError (ERROR_PATH_NOT_FOUND);
		RetVal = FALSE;
	}
	if (hLibInst) {
		FreeLibrary(hLibInst);
	}
	return RetVal;
}


_inline BOOL
CallGetResourcePassword (HWND hParent, PNETUI_RESPWD pResPwd)
{
	HINSTANCE	hLibInst;
	PFN_GetResourcePassword pfnGetResourcePassword;
	BOOL		RetVal;

	if (IsAPIReady(SH_WMGR) && ((hLibInst = LoadLibrary(TEXT("netui.dll"))) != NULL)) {
		pfnGetResourcePassword = (PFN_GetResourcePassword)GetProcAddress (
			hLibInst, TEXT("GetResourcePassword"));
		if (pfnGetResourcePassword) {
			RetVal = pfnGetResourcePassword(hParent, pResPwd);
		} else {
			RETAILMSG (1, (TEXT("Can't find GetResourcePassword")));
			SetLastError (ERROR_FILE_NOT_FOUND);
			RetVal = FALSE;
		}
	} else {
		RETAILMSG (1, (TEXT("Can't load netui.dll")));
		SetLastError (ERROR_PATH_NOT_FOUND);
		RetVal = FALSE;
	}
	if (hLibInst) {
		FreeLibrary(hLibInst);
	}
	return RetVal;
}

_inline DWORD
CallGetIPAddress (HWND hParent)
{
	HINSTANCE	hLibInst;
	PFN_GetIPAddress pfnGetIPAddress;
	DWORD		RetVal;

	if (IsAPIReady(SH_WMGR) && ((hLibInst = LoadLibrary(TEXT("netui.dll"))) != NULL)) {
		pfnGetIPAddress = (PFN_GetIPAddress)GetProcAddress (
			hLibInst, TEXT("GetIPAddress"));
		if (pfnGetIPAddress) {
			RetVal = pfnGetIPAddress(hParent);
		} else {
			RETAILMSG (1, (TEXT("Can't find GetIPAddress")));
			SetLastError (ERROR_FILE_NOT_FOUND);
			RetVal = 0;
		}
	} else {
		RETAILMSG (1, (TEXT("Can't load netui.dll")));
		SetLastError (ERROR_PATH_NOT_FOUND);
		RetVal = 0;
	}
	if (hLibInst) {
		FreeLibrary(hLibInst);
	}
	return RetVal;
}


_inline BOOL
CallLineConfigEdit (HWND hParent, PLINECONFIGDATA pLineConfigData)
{
	HINSTANCE	hLibInst;
	PFN_LineConfigEdit pfnLineConfigEdit;
	BOOL		fRetVal;

	if (IsAPIReady(SH_WMGR) && ((hLibInst = LoadLibrary(TEXT("netui.dll"))) != NULL)) {
		pfnLineConfigEdit = (PFN_LineConfigEdit)GetProcAddress (
			hLibInst, TEXT("LineConfigEdit"));
		if (pfnLineConfigEdit) {
			fRetVal = pfnLineConfigEdit(hParent,pLineConfigData);
		} else {
			RETAILMSG (1, (TEXT("Can't find LineConfigEdit")));
			SetLastError (ERROR_FILE_NOT_FOUND);
			fRetVal = FALSE;
		}
	} else {
		RETAILMSG (1, (TEXT("Can't load netui.dll")));
		SetLastError (ERROR_PATH_NOT_FOUND);
		fRetVal = FALSE;
	}
	if (hLibInst) {
		FreeLibrary(hLibInst);
	}
	return fRetVal;
}

_inline BOOL
CallLineTranslateDialog (HWND hParent, HWND *pDialogWnd)
{
	HINSTANCE	hLibInst;
	PFN_LineTranslateDialog pfnLineTranslateDialog;
	DWORD		RetVal;

	if (IsAPIReady(SH_WMGR) && ((hLibInst = LoadLibrary(TEXT("netui.dll"))) != NULL)) {
		pfnLineTranslateDialog = (PFN_LineTranslateDialog)GetProcAddress (
			hLibInst, TEXT("LineTranslateDialog"));
		if (pfnLineTranslateDialog) {
			RetVal = pfnLineTranslateDialog(hParent, pDialogWnd);
		} else {
			RETAILMSG (1, (TEXT("Can't find LineTranslateDialog")));
			SetLastError (ERROR_FILE_NOT_FOUND);
			RetVal = 0;
		}
	} else {
		RETAILMSG (1, (TEXT("Can't load netui.dll")));
		SetLastError (ERROR_PATH_NOT_FOUND);
		RetVal = 0;
	}
	if (hLibInst) {
		FreeLibrary(hLibInst);
	}
	return RetVal;
}


_inline BOOL
CallConnectionDialog (HWND hParent,PADDCONNECT_DLGPARAMS pDlgParams)
{
	HINSTANCE	hLibInst;
	PFN_ConnectionDialog pfnConnectionDialog;
	BOOL		RetVal;

	if (IsAPIReady(SH_WMGR) && ((hLibInst = LoadLibrary(TEXT("netui.dll"))) != NULL)) {
		pfnConnectionDialog = (PFN_ConnectionDialog)GetProcAddress (
			hLibInst, TEXT("ConnectionDialog"));
		if (pfnConnectionDialog) {
			RetVal = pfnConnectionDialog(hParent, pDlgParams);
		} else {
			RETAILMSG (1, (TEXT("Can't find ConnectionDialog")));
			SetLastError (ERROR_FILE_NOT_FOUND);
			RetVal = FALSE;
		}
	} else {
		RETAILMSG (1, (TEXT("Can't load netui.dll")));
		SetLastError (ERROR_PATH_NOT_FOUND);
		RetVal = FALSE;
	}
	if (hLibInst) {
		FreeLibrary(hLibInst);
	}
	return RetVal;
}


_inline BOOL
CallDisconnectDialog (HWND hParent, DWORD dwType)
{
	HINSTANCE	hLibInst;
	PFN_DisconnectDialog pfnDisconnectDialog;
	BOOL		RetVal;

	if (IsAPIReady(SH_WMGR) && ((hLibInst = LoadLibrary(TEXT("netui.dll"))) != NULL)) {
		pfnDisconnectDialog = (PFN_DisconnectDialog)GetProcAddress (
			hLibInst, TEXT("DisconnectDialog"));
		if (pfnDisconnectDialog) {
			RetVal = pfnDisconnectDialog(hParent,dwType);
		} else {
			RETAILMSG (1, (TEXT("Can't find DisconnectDialog")));
			SetLastError (ERROR_FILE_NOT_FOUND);
			RetVal = FALSE;
		}
	} else {
		RETAILMSG (1, (TEXT("Can't load netui.dll")));
		SetLastError (ERROR_PATH_NOT_FOUND);
		RetVal = FALSE;
	}
	if (hLibInst) {
		FreeLibrary(hLibInst);
	}
	return RetVal;
}


_inline BOOL WINAPIV
CallNetMsgBox (HWND hParent, DWORD dwFlags, UINT uStrID, ...)
{
	HINSTANCE	hLibInst;
	PFN_NetMsgBox pfnNetMsgBox;
	BOOL		RetVal=TRUE;
	TCHAR *szStr=NULL;

	if (IsAPIReady(SH_WMGR) && ((hLibInst = LoadLibrary(TEXT("netui.dll"))) != NULL)) {
		pfnNetMsgBox = (PFN_NetMsgBox)GetProcAddress (
			hLibInst, TEXT("NetMsgBox"));
		if (pfnNetMsgBox) {
			TCHAR szFmtBuf[200];

			if (!CallGetNetString(uStrID, szFmtBuf,sizeof(szFmtBuf)/sizeof(szFmtBuf[0])))
				RetVal = FALSE;
			else {
				va_list		varglist;
				va_start(varglist, uStrID);
				if (FormatMessage(FORMAT_MESSAGE_ALLOCATE_BUFFER|FORMAT_MESSAGE_FROM_STRING,
								  szFmtBuf,0,0,(LPTSTR)&szStr,sizeof(szFmtBuf)/sizeof(szFmtBuf[0]),&varglist) == 0) {
				   RETAILMSG(1,(TEXT("!CallNetMsgBox: Error %u in FormatMessage, ID:%u\r\n"),
								GetLastError(),uStrID));
				   RetVal = FALSE;
				}
				va_end(varglist);
				
				if (RetVal) 
					RetVal = pfnNetMsgBox(hParent, dwFlags, szStr);
			}
		} else {
			RETAILMSG (1, (TEXT("Can't find NetMsgBox")));
			SetLastError (ERROR_FILE_NOT_FOUND);
			RetVal = FALSE;
		}
	} else {
		RETAILMSG (1, (TEXT("Can't load netui.dll")));
		SetLastError (ERROR_PATH_NOT_FOUND);
		RetVal = FALSE;
	}
	if (hLibInst) {
		FreeLibrary(hLibInst);
	}
	if (szStr) {
		LocalFree(szStr);
	}
	return RetVal;
}


// Second version of this function that allows the function pointers to be preloaded.
// This is necessary for file system drivers (e.g. redirector) which can't wait for
// LoadLibrary().
_inline BOOL WINAPIV
CallNetMsgBox2 (PFN_NetMsgBox pfnNetMsgBox, PFN_GetNetString pfnGetNetString, HWND hParent, DWORD dwFlags, UINT uStrID, ...)
{
	BOOL		RetVal=TRUE;
	TCHAR *szStr=NULL;

	TCHAR szFmtBuf[200];

	if (!pfnGetNetString(uStrID, szFmtBuf,sizeof(szFmtBuf)/sizeof(szFmtBuf[0])))
		RetVal = FALSE;
	else {
		va_list 	varglist;
		va_start(varglist, uStrID);
		if (FormatMessage(FORMAT_MESSAGE_ALLOCATE_BUFFER|FORMAT_MESSAGE_FROM_STRING,
						  szFmtBuf,0,0,(LPTSTR)&szStr,sizeof(szFmtBuf)/sizeof(szFmtBuf[0]),&varglist) == 0) {
			RETAILMSG(1,(TEXT("!CallNetMsgBox2: Error %u in FormatMessage, ID:%u\r\n"),
						 GetLastError(),uStrID));
			RetVal = FALSE;
		}
		va_end(varglist);

		if (RetVal)
			RetVal = pfnNetMsgBox(hParent, dwFlags, szStr);
	}
	if (szStr) {
		LocalFree(szStr);
	}
	return RetVal;
}

_inline BOOL
CallAdapterIPProperties (HWND hParent, LPTSTR szAdapterName)
{
	HINSTANCE	hLibInst;
	PFN_AdapterIPProperties pfnAdapterIPProperties;
	BOOL		RetVal;

	if (IsAPIReady(SH_WMGR) && ((hLibInst = LoadLibrary(TEXT("netui.dll"))) != NULL)) {
		pfnAdapterIPProperties = (PFN_AdapterIPProperties)GetProcAddress (
			hLibInst, TEXT("AdapterIPProperties"));
		if (pfnAdapterIPProperties) {
			RetVal = pfnAdapterIPProperties(hParent, szAdapterName);
		} else {
			RETAILMSG (1, (TEXT("Can't find AdapterIPProperties")));
			SetLastError (ERROR_FILE_NOT_FOUND);
			RetVal = FALSE;
		}
	} else {
		RETAILMSG (1, (TEXT("Can't load netui.dll")));
		SetLastError (ERROR_PATH_NOT_FOUND);
		RetVal = FALSE;
	}
	if (hLibInst) {
		FreeLibrary(hLibInst);
	}
	return RetVal;
}


_inline BOOL
CallGetDriverName (HWND hParent, PGETDRIVERNAMEPARMS pDriverParms)
{
	HINSTANCE	hLibInst;
	PFN_GetDriverName pfnGetDriverName;
	BOOL		RetVal;

	if (IsAPIReady(SH_WMGR) && ((hLibInst = LoadLibrary(TEXT("netui.dll"))) != NULL)) {
		pfnGetDriverName = (PFN_GetDriverName)GetProcAddress (
			hLibInst, TEXT("GetDriverName"));
		if (pfnGetDriverName) {
			RetVal = pfnGetDriverName(hParent, pDriverParms);
		} else {
			RETAILMSG (1, (TEXT("Can't find GetDriverName")));
			SetLastError (ERROR_FILE_NOT_FOUND);
			RetVal = FALSE;
		}
	} else {
		RETAILMSG (1, (TEXT("Can't load netui.dll")));
		SetLastError (ERROR_PATH_NOT_FOUND);
		RetVal = FALSE;
	}
	if (hLibInst) {
		FreeLibrary(hLibInst);
	}
	return RetVal;
}


// @CESYSGEN ENDIF
#endif // _NETUI_H_

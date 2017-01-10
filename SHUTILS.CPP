/*---------------------------------------------------------------------------*\
 *
 * THIS CODE AND INFORMATION IS PROVIDED "AS IS" WITHOUT WARRANTY OF ANY KIND,
 * EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE IMPLIED 
 * WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A PARTICULAR PURPOSE.
 * 
 * Copyright (c) 1995-1998  Microsoft Corporation
 *
 *  file:  SHUTILS.CPP
 *  author:  ArulM
 *  purpose: Utility functions used by sample shell
 *
\*---------------------------------------------------------------------------*/
#include <windows.h>
#include <shlwapi.h>
#include <sipapi.h>
#pragma comment(lib, "Shell32.lib")
#pragma comment(lib, "coredll.lib")
#include <shellapi.h>
#include "commdlg.h"



typedef BOOL (WINAPI* LPFNSIP)(SIPINFO*);

BOOL DoExec(HWND hwndParent, LPCTSTR lpszApp, LPCTSTR lpszArgs)
{
	BOOL fRet;
	SHELLEXECUTEINFO sei;
	
	// Try to execute the thing. If it fails, ShellExecuteEx puts up the error msg
    memset(&sei, 0, sizeof(sei));
	sei.cbSize = sizeof(sei);
    sei.hwnd = hwndParent;
	sei.lpFile = lpszApp;
	sei.lpParameters = lpszArgs;
	sei.lpDirectory = NULL;
	sei.nShow = SW_SHOWNORMAL;

	fRet = ShellExecuteEx(&sei);
	DEBUGMSG(!fRet, (L"Taskman: ShellExecuteEx(%s, %s) FAILED GLE=%d\r\n", lpszApp, lpszArgs, GetLastError()));
	return fRet;
}

//
// This function tries to center a window on screen, taking into account 
// whether there is a SIP (soft input panel, i.e. an on-screen keyboard)
// on screen or not. If your device doesn't support a SIP, you could
// considerably simplify this. 
//
// We use this initially on creating the window. If we have a SIP then 
// we also call this whenever the SIP state changes. But to avoid excessive 
// jumping around of the window, we re-center when a SIP comes up (basically 
// trying to move out of SIP's way), but we leave it alone when the 
// SIP goes down.
// 
BOOL CenterWindowSIPAware(HWND hwnd, BOOL fInitial)
{
    SIPINFO si;
	RECT    rcWnd;
    RECT    rcWorkArea;
    int     cx, cy;
    LPFNSIP pSipGetInfo;
    HINSTANCE hinst = NULL;

    // Get the size of window
    GetWindowRect(hwnd, &rcWnd);

	// Get the size of SIP-less area OR if no SIP, then screen workarea
	memset(&si, 0, sizeof(SIPINFO));
    si.cbSize = sizeof(SIPINFO);

    if( (hinst = LoadLibrary(L"coredll.dll")) &&
        (pSipGetInfo = (LPFNSIP)GetProcAddress(hinst, TEXT("SipGetInfo"))) &&
		pSipGetInfo(&si) ) {
    	// we have a SIP
		rcWorkArea = si.rcVisibleDesktop;
    } else {
    	// either no SIP APIs on device, or SIP not operative
	    SystemParametersInfo(SPI_GETWORKAREA, FALSE, &rcWorkArea, 0);
	}
	if(hinst) FreeLibrary(hinst);

	// if we're positioning after a INICHANGE, then only do something on SIP-up, not SIP-down
	if(!fInitial && !(si.fdwFlags & SIPF_ON))
		return FALSE;

	// Calc space left on each side (may be negative is window is too big)
    cx = ((rcWorkArea.right - rcWorkArea.left) - (rcWnd.right - rcWnd.left))/2;
    cy = ((rcWorkArea.bottom - rcWorkArea.top) - (rcWnd.bottom - rcWnd.top))/2;

	DEBUGMSG(1, (L"VisibleRect=(top=%d, bottom=%d, left=%d, right=%d) Work=(top=%d, bottom=%d, left=%d, right=%d) Wnd=(top=%d, bottom=%d, left=%d, right=%d) cx=%d cy=%d\r\n",
		si.rcVisibleDesktop.top, si.rcVisibleDesktop.bottom, si.rcVisibleDesktop.left, si.rcVisibleDesktop.right,
		rcWorkArea.top, rcWorkArea.bottom, rcWorkArea.left, rcWorkArea.right,
		rcWnd.top, rcWnd.bottom, rcWnd.left, rcWnd.right, cx, cy));

	// If window is too big
	// if X is negative reset to 0 (so we fall off right edge only, not both)
	// if Y is negative reset to 0 (so we fall off bottom only, not top & bottom)
	if(cx < 0) cx = 0;
	if(cy < 0) cy = 0;

	// Do the actual window-move (finally!)
    return SetWindowPos(hwnd, NULL, rcWorkArea.left+cx, rcWorkArea.top+cy, 0, 0, SWP_NOSIZE | SWP_NOZORDER);
} 

// 
// Some useful filename & path-parsing functions
//

#define IS_SPACE(x) ( ((x) == TEXT(' ')) || ((x) == TEXT('\t')) )
void WINAPI PathRemoveBlanks(LPTSTR lpszString)
{
    LPTSTR lpszPosn = lpszString;

	/// strip leading blanks
    while(IS_SPACE(*lpszPosn)) {
        lpszPosn++;
    }
    if (lpszPosn != lpszString)
        lstrcpy(lpszString, lpszPosn);

    // strip trailing blanks
	lpszPosn = lpszString + lstrlen(lpszString);
	while (lpszPosn > lpszString && IS_SPACE(*(lpszPosn - 1))) {
		lpszPosn--;
	}
	*lpszPosn = TEXT('\0');
}

// returns a pointer to the arguments in a cmdline string
// or NULL if nor args
// Note: Assumes that spaces in LFNs are quoted

LPTSTR WINAPI PathGetArgs(LPCTSTR pszPath)
{
	BOOL fInQuotes = FALSE;
    if (!pszPath)
		return NULL;

	while (*pszPath)
    {
		if (*pszPath == TEXT('"')) {
			fInQuotes = !fInQuotes;
		} else if (!fInQuotes && IS_SPACE(*pszPath)) {
			pszPath++;
			while (IS_SPACE(*pszPath)) {
				pszPath++;
			}
			break;
		}
		pszPath++;
	}
    return (LPTSTR)pszPath;
}

// removes args from a cmdline
void WINAPI PathRemoveArgs(LPTSTR pszPath)
{
	LPTSTR pArgs = PathGetArgs(pszPath);
	if (pArgs && *pArgs) {
		while (pArgs > pszPath && IS_SPACE(*(pArgs-1))) {
			pArgs--;
		}
		*pArgs = TEXT('\0');
	}
}


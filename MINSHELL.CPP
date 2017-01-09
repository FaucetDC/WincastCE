/*---------------------------------------------------------------------------*\
 *
 * THIS CODE AND INFORMATION IS PROVIDED "AS IS" WITHOUT WARRANTY OF ANY KIND,
 * EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE IMPLIED 
 * WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A PARTICULAR PURPOSE.
 * 
 * Copyright (c) 1995-1998  Microsoft Corporation
 *
 *  file:  MinShell.c
 *  author:  ArulM
 *  purpose: Implement sampel shell Main program, initialization etc
 *
\*---------------------------------------------------------------------------*/

#include "windows.h"
#include "minshell.h"
#include <pwinuser.h>

// Debug Zones.
#ifdef DEBUG
  DBGPARAM dpCurSettings = {
    TEXT("MinShell"), {
    TEXT("Main Trace"),TEXT("Trace2"),TEXT("TraceMsgs LoFreq"),TEXT("TraceMsgs HiFreq"),
    TEXT("TaskMan"),TEXT("Desktop"),TEXT(""),TEXT(""),
    TEXT(""),TEXT(""),TEXT(""),TEXT(""),
    TEXT(""),TEXT(""),TEXT("Warning"),TEXT("Error") },
    //0x0000F023
    0x00000001
  }; 
#endif

// Globals
HINSTANCE g_hInst;
HWND g_hwndDesktop, g_hwndTaskBar, g_hwndTaskMan;
HWND g_hwndMBVL, g_hwndBBL, g_hwndBBVL;
int  g_iSignalStartedID;

// IMPORTANT NOTE: The desktop window class name MUST be 
// "DesktopExplorerWindow". See block comment on use of 
// the RegisterTaskBar API in MINTASK.CPP
TCHAR const c_szDesktopWndClass[] = TEXT("DesktopExplorerWindow");

// Local functions
BOOL InitApplication(HINSTANCE hInstance);
void CleanupApplication();
BOOL RegisterShellAPIs(VOID);
VOID UnRegisterShellAPIs(VOID);

int
WINAPI
WinMain(HINSTANCE hInstance,
		HINSTANCE hPrevInstance,
		LPWSTR    lpCmdLine,
		int       nCmdShow)
{
	DWORD dwThrdID;
	HANDLE hThread;
    MSG msg;

	DEBUGREGISTER(NULL);

	// Minshell cannot run multi-instanced
	if(hPrevInstance || FindWindow(c_szDesktopWndClass, NULL)) 
		return 0;
	
	if (!InitApplication(hInstance))
		return 0;

	// Get our start-sequence ID so we can signal it when we're ready
	// This is passed to us by the kernel when we are launched at startup
	// from the HKLM\init key. If we don't call SignalStarted() apps
	// that depend on us in the HKLM\init key will never start
	// SignalStarted is called after we're finished initializing in MINTASK.CPP
	g_iSignalStartedID=_wtol(lpCmdLine);

	if (GetAsyncKeyState(VK_SHIFT)) 
		RETAILMSG(1, (TEXT("Bypassing calibration check\r\n")));
	else
	{
		// Calibrate touch panel if neccesary
		DWORD dw, dwType;
		dw = 0;
		if (ERROR_SUCCESS != RegQueryValueEx(HKEY_LOCAL_MACHINE,
											 TEXT("CalibrationData"),
											 (LPDWORD)TEXT("HARDWARE\\DEVICEMAP\\TOUCH"),
											 &dwType,
											 NULL,
											 &dw))
		{
			RETAILMSG(1, (TEXT("No calibration data, attempting to calibrate.\r\n")));
			TouchCalibrate();
		}
	}
           

	// We use the main thread for the desktop window
	// & launch another thread for the taskbar
	
	// First register & create the desktop window
	Desktop_Register(hInstance);
	Desktop_InitInstance(SW_SHOW);
	SetForegroundWindow(g_hwndDesktop);

	// launch the Taskbar thread
	if(!(hThread = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)TaskBar_ThreadProc, (LPVOID)nCmdShow, 0, &dwThrdID)))
		return FALSE; // BUGBUG: need to do better cleanup
	CloseHandle(hThread); hThread=NULL;

	RETAILMSG(TRUE, (TEXT("MinShell desktop thread started.\r\n")));
	while (GetMessage(&msg, NULL, 0, 0)) 
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}

	CleanupApplication();
	return msg.wParam;
}

BOOL InitApplication(HINSTANCE hInstance)
{
	g_hInst = hInstance;
	return TRUE;
}

void CleanupApplication()
{
	// Unregister desktop & taskbar
	RegisterTaskBar(NULL);
}


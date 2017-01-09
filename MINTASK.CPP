/*---------------------------------------------------------------------------*\
 *
 * THIS CODE AND INFORMATION IS PROVIDED "AS IS" WITHOUT WARRANTY OF ANY KIND,
 * EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE IMPLIED 
 * WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A PARTICULAR PURPOSE.
 * 
 * Copyright (c) 1995-1998  Microsoft Corporation
 *
 *  file:  MinTask.cpp
 *  author:  ArulM
 *  purpose: Implement Sample shell "taskbar" 
 *
 *  Actually this sample implements an *invisible* taskbar, just as a dummy 
 *  window to register with GWE to get the taskbar messages. It doesn't 
 *  actually *do* anything with the taskbar except to trap special 
 *  key-sequences such as Alt-Tab & bring up a Task-Manager type dialog
 *
\*---------------------------------------------------------------------------*/
#include <windows.h>
#include <windowsx.h>
#include "minshell.h"
#include <pwinuser.h>

#define HHTASKBARCLASSNAME  TEXT("HHTaskBar")

// this sample creates a 0 hieght (hence invisible) taskbar
#define TASKBAR_HEIGHT      0 

// this timer is used for housekeeping tasks such as monitoring battery level etc
#define MINSHELL_HOUSEKEEPING_TIMER 71 // pick an random id

// Local fns
LRESULT CALLBACK TaskBarWndProc(HWND hwnd, UINT msg, WPARAM wp, LPARAM lp);
BOOL WINAPI TaskBar_CreateClass(HINSTANCE hInstance);
HWND WINAPI TaskBar_CreateWindow(HWND hwndParent);
void WINAPI TaskBar_Cleanup();
void TaskBar_SetWorkArea(void);
void TaskBar_UpdateDesktopArea(void);

BOOL TaskBar_ThreadProc(int nCmdShow)
{
	DWORD dwThrdID = 0;
    MSG msg;

	// Create Taskbar WNDCLASS
	if(!TaskBar_CreateClass(g_hInst))
		return FALSE;

	// Create Taskbar window
	if(!(g_hwndTaskBar = TaskBar_CreateWindow(NULL)))
		return FALSE;

	// This GWE API registers both the desktop & taskbar windows with GWE.
	// Both windows should be created before this API is called.
	// The Taskbar HWND is passed in explicitly. The Desktop HWND is located
	// from it's window-class, which *must* be "DesktopExplorerWindow"
	// 
	// GWE remembers these window handles as special. The desktop window 
	// is used by GWE to hide "minimized" windows (since CE doesn't support
	// true minimization, "minimized"windows just get moved behind the desktop.

	// The taskbar window is notified when top-level windows are created or
	// deleted (so it can put up taskbar icons etc if it wants to -- which 
	// this sample doesn't yet do). The taskbar window is also sent messages on
	// special Windows key sequences such as Alt-Tab, Ctrl-Esc etc.
	
	if(!RegisterTaskBar(g_hwndTaskBar))
		return FALSE;
	DEBUGMSG(ZONE_TRACE, (TEXT("Registered minshell taskbar & desktop window.\r\n")));

	// Create Taskman window *after* registertaskbar, so it can be hidden behind the desktop
	if(!TaskMan_Create())
		return FALSE;

	RETAILMSG(TRUE, (TEXT("Minshell taskbar thread started.\r\n")));

	// We call SignalStarted with our start-sequence ID to signal that we're
	// done initializing. The ID is passed to us on teh cmdline by the kernel
	// when we are launched at startup from the HKLM\init key. If we don't call
	// SignalStarted() apps that depend on us in the HKLM\init key will never start
	SignalStarted(g_iSignalStartedID);

	while (GetMessage(&msg, NULL, 0, 0)) 
	{
		// first process all the modeless dialog msgs
		if(g_hwndTaskMan && IsDialogMessage(g_hwndTaskMan, &msg))
			continue;
		if(g_hwndMBVL && IsDialogMessage(g_hwndMBVL, &msg))
			continue;
		if(g_hwndBBL && IsDialogMessage(g_hwndBBL, &msg))
			continue;
		if(g_hwndBBVL && IsDialogMessage(g_hwndBBVL, &msg))
			continue;
				
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}

	TaskBar_Cleanup();
	return msg.wParam;
}

// Create the Taskbar's Window Class
BOOL WINAPI TaskBar_CreateClass(HINSTANCE hInstance)
{
	WNDCLASS wc;

    wc.style         = /*CS_HREDRAW | CS_VREDRAW | */CS_DBLCLKS;
    wc.lpfnWndProc   = (WNDPROC)TaskBarWndProc;
    wc.cbClsExtra    = 0;
    wc.cbWndExtra    = 0;
    wc.hInstance     = hInstance;
    wc.hIcon         = NULL;
	wc.hCursor       = LoadCursor(NULL, IDC_ARROW);
	wc.hbrBackground = GetStockBrush(LTGRAY_BRUSH);
    wc.lpszMenuName  = NULL;
    wc.lpszClassName = HHTASKBARCLASSNAME;

	// Register the window class and return success/failure code.
	return RegisterClass(&wc);

}

// Create & initialize the Taskbar's Window
HWND WINAPI TaskBar_CreateWindow(HWND hwndParent)
{
	HWND hwndTB;
	DWORD dwStyle = WS_POPUP;
	RECT rc;

	if (hwndParent != NULL) 
	{
		dwStyle |= WS_CHILD;
		GetClientRect(hwndParent, &rc);
	}
	else
	{
		SetRect(&rc, 0, 0, GetSystemMetrics(SM_CXSCREEN),
				GetSystemMetrics(SM_CYSCREEN));
	}

	// Create taskbar of TASKBAR_HEIGHT at bottom of screen
	rc.top = rc.bottom - TASKBAR_HEIGHT;
	hwndTB = CreateWindow(HHTASKBARCLASSNAME, TEXT(""), dwStyle, rc.left, rc.top,
						  rc.right-rc.left, rc.bottom-rc.top, hwndParent,
						  NULL, g_hInst, NULL);

	if (hwndTB) 
	{
		DEBUGMSG(ZONE_TRACE, (TEXT("Created Minshell taskbar window.\r\n")));
		// Update desktop window size 
		TaskBar_UpdateDesktopArea();
		// Update the workarea (size of other windows)
		TaskBar_SetWorkArea();
		SetWindowPos(hwndTB, HWND_TOPMOST, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE);
		InvalidateRect(hwndTB, 0, TRUE);
		ShowWindow(hwndTB, SW_SHOWNORMAL);
		UpdateWindow(hwndTB);

		// Start 5sec housekeeping timer (used for memory & battery level 
		// checks). See handling of this in HOUSEKP.CPP
		SetTimer(hwndTB, MINSHELL_HOUSEKEEPING_TIMER, 5 * 1000, NULL);
	}
	return hwndTB;

}

void WINAPI TaskBar_Cleanup()
{
	if(g_hwndTaskBar)
		KillTimer(g_hwndTaskBar, MINSHELL_HOUSEKEEPING_TIMER);
	TaskMan_Destroy();
}

// To ensure that full-screen apps don't overlap the taskbar, be sure to
// register the new system workspace-area, as the whole screen MINUS
// the area occupied by the taskbar
void TaskBar_SetWorkArea(void)
{
	RECT rcWorkArea, rcWorkAreaNew;

	// get current work-area
	SystemParametersInfo(SPI_GETWORKAREA, 0, (void*)&rcWorkArea, 0);

	// Subtract the area occupied by the taskbar. This sample is currently 
	// hardcoded to have a taskbar at the bottom of the screen, but so long
	// as the new work area is computed appropriately, the taskbar can be 
	// on any edge.
	SetRect(&rcWorkAreaNew, 0, 0, GetSystemMetrics(SM_CXSCREEN), GetSystemMetrics(SM_CYSCREEN));
	rcWorkAreaNew.bottom -= TASKBAR_HEIGHT;
	if (rcWorkArea.bottom != rcWorkAreaNew.bottom)
		SystemParametersInfo(SPI_SETWORKAREA, 0, (void*)&rcWorkAreaNew, SPIF_SENDCHANGE);
}

// To ensure that the desktop windows doesn't overlap the taskbar, be sure to
// resize it to the whole screen MINUS the same area as the system work-area
// set in the TaskBar_SetWorkArea function (above)
void TaskBar_UpdateDesktopArea(void)
{
	RECT rcOld, rcNew;

	// resize the desktop window
	SetRect(&rcNew, 0, 0, GetSystemMetrics(SM_CXSCREEN), GetSystemMetrics(SM_CYSCREEN));
	rcNew.bottom -= TASKBAR_HEIGHT;
	GetWindowRect(g_hwndDesktop, &rcOld);
	if (rcNew.bottom != rcOld.bottom) 
		SetWindowPos(g_hwndDesktop, 0, 0, 0, rcNew.right-rcNew.left, rcNew.bottom-rcNew.top, SWP_NOACTIVATE | SWP_NOZORDER);

}

// This is the task-bar wndproc. It needs to be fleshed out considerably to
// support fuller shell-like functionality
LRESULT CALLBACK TaskBarWndProc(HWND hwnd, UINT msg, WPARAM wp, LPARAM lp)
{
	DEBUGMSG(ZONE_TRACEMSGHF, (TEXT("Taskbar Window Msg=%x wp=%x lp=%x\r\n"), msg, wp, lp));

	switch(msg)
	{
		// 5sec housekeeping timer
		case WM_TIMER:
			DoHibernate(); // check free-memory level & notify apps if neccesary
			DoPowerCheck(hwnd); // check battery levels & pop-up warning if reqd
			break;

		case WM_SYSKEYDOWN:
		case WM_KEYDOWN:
		{
			DEBUGMSG(ZONE_TRACEMSG, (TEXT("Taskbar Window WM_KEYDOWN\r\n")));
			// For now we're sending Ctrl-Esc, Alt-Esc, Alt-Tab, Ctrl-Alt-Del/Bksp all to TaskMan
			// A fuller shell would implement a Start-Menu on Alt-Esc for example.
			switch (wp) 
			{
				case VK_DELETE:
				case VK_BACK:
					// Send Ctrl-Alt-Bksp to Taskman. NOTE: GWES doesn't send us Ctrl-Alt-Del
					DEBUGMSG(ZONE_TRACEMSG, (TEXT("Taskbar Window WM_KEYDOWN, VK_BACK or VK_DELETE\r\n")));
					if (GetKeyState(VK_CONTROL) && GetKeyState(VK_MENU)) 
						Show_TaskMan();
					break;

				case VK_TAB:
					// Send Alt-Tab to TaskMan
					DEBUGMSG(ZONE_TRACEMSG, (TEXT("Taskbar Window WM_KEYDOWN, VK_TAB\r\n")));
					if (GetKeyState(VK_MENU)) 
						Show_TaskMan();
					break;
					
				case VK_ESCAPE:
					// Send Ctrl-Esc & Alt-Esc to TaskMan
					DEBUGMSG(ZONE_TRACEMSG, (TEXT("Taskbar Window WM_KEYDOWN, VK_ESCAPE\r\n")));
					if(GetKeyState(VK_CONTROL) || GetKeyState(VK_MENU))
						Show_TaskMan();
					break;

				default:
					return DefWindowProc(hwnd, msg, wp, lp);
			}
		}
		default:
			// This window will get GWE messages on window-create/delete etc. 
			// If it wants to display Win9x/NT-like task buttons etc., it 
			// should handle these messages
			return DefWindowProc(hwnd, msg, wp, lp);
	}
	return 0;
}

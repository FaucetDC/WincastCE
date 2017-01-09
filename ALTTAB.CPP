/*---------------------------------------------------------------------------*\
 *
 * THIS CODE AND INFORMATION IS PROVIDED "AS IS" WITHOUT WARRANTY OF ANY KIND,
 * EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE IMPLIED 
 * WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A PARTICULAR PURPOSE.
 * 
 * Copyright (c) 1995-1998  Microsoft Corporation
 *
 *  file:  ALTTAB.CPP
 *  author:  ArulM
 *  purpose: Implement Sample shell Task-manager-like dialog
 *
\*---------------------------------------------------------------------------*/

#include "windows.h"
#include "windowsx.h"
#include <sipapi.h>
#include "minshell.h"
#include "minshrc.h"
#include "commdlg.h"
#include <shlwapi.h>
#pragma comment(lib, "Shlwapi.lib")

// Useful macros
#define cchsizeof(x)	(sizeof(x)/sizeof(TCHAR))

#define RestoreForegroundWindow(hwnd)   \
    SetForegroundWindow((HWND)(((DWORD)hwnd) | 0x01))

// info passed to TaskMan_ReallyKill
typedef struct 
{
	HWND   hwnd;
	LPTSTR pszTitle;
}
KILLTARGETINFO;

// Local fns
int TaskMan_PopulateLB(HWND hwndLB, HWND hwndFG);
LRESULT CALLBACK TaskMan_ReallyKill(HWND hwnd, UINT msg, WPARAM wp, LPARAM lp);
LRESULT CALLBACK RunDlgProc(HWND hwnd, UINT msg, WPARAM wp, LPARAM lp);
BOOL IsOKToKill(HWND hwndApp);

// We dynamically determine whether the current OS configuration has the
// Fileopen component, by calling LoadLibrary & GetProcAddress. If we obtain
// the GetOpenFilename API then we display a Browse button on the Start-Run
// dialog. Otherwise we hide it.
typedef BOOL (APIENTRY*  PFNGETOPENFILENAME)(LPOPENFILENAME lpofn);
PFNGETOPENFILENAME g_pfnGetOpenFileName;

//
// This is the dlgproc for the Takman dialog. The dialog has a listbox of all
// top-level windows, and Switch-To and End-Task buttons, which allow the user
// to switch between apps or kill hung apps. 
// The dialog also has a Run button that brings up Start-Run type dialog, and
// of course a Cancel button
// 
// NOTE: The dialog is actually a permanent modeless dialog created on shell 
// startup. Pressing ALt-Tab merely brings it to the front, and Cancel hides
// it, rather than actually destroying the dialog
//

int CALLBACK TaskMan_DlgProc(HWND hwnd, UINT msg, WPARAM wp, LPARAM lp)
{
	int iIndex, iCount;
	HWND hwndLB = GetDlgItem(hwnd, IDC_LISTBOX);
	HWND hwndFG;

	DEBUGMSG(ZONE_TRACEMSGHF, (TEXT("AltTab Window Msg=%x wp=%x lp=%x\r\n"), msg, wp, lp));
	
	switch(msg)
	{
		// created on program startup
		case WM_INITDIALOG:
			break;

		// activated on user pressing Alt-Tab etc (see MINTASK.CPP)
		case WM_ACTIVATE:
			if(LOWORD(wp) != WA_INACTIVE)
			{
				CenterWindowSIPAware(hwnd, TRUE);
				// We use DWL_USER tp remember the window that was foreground *before*
				// this dialog came up, so that we can select it in our listbox
				hwndFG = (HWND)GetWindowLong(hwnd, DWL_USER);
				// Fill listbox with currently running top-level windows
				iCount = TaskMan_PopulateLB(hwndLB, hwndFG);
				// enable or disable SwitchTo & EndTask buttons, based on lisbox item count
				EnableWindow(GetDlgItem(hwnd, IDC_ENDTASK), iCount);
				EnableWindow(GetDlgItem(hwnd, IDOK), iCount);
				SendMessage(hwnd, WM_NEXTDLGCTL, (WPARAM)hwndLB, (LPARAM)TRUE);
			}
			break;

		case WM_SETTINGCHANGE:
			// Recenter dialog when SIP goes up (see details in the block 
			// comment at the head of the CenterWindowSIPAware function)
			if(wp==SPI_SETSIPINFO)
				CenterWindowSIPAware(hwnd, FALSE);
			break;
		
		case WM_COMMAND:
			switch (GET_WM_COMMAND_ID(wp,lp)) 
			{
				// Bring up a Start-Run type dialog
				case IDC_RUN:
				{
					// Choose the dialog template based on screen-dimensions. See details in RC file
					int idd = (GetSystemMetrics(SM_CXSCREEN) < GetSystemMetrics(SM_CYSCREEN))
											? IDD_RUN_G : IDD_RUN;
					if(-1 != DialogBox(g_hInst, MAKEINTRESOURCE(idd), hwnd, (DLGPROC)RunDlgProc))
					{
						// If user didnt cancel out of Run dialog, dismiss (hide) the Taskman dlg
						ListBox_ResetContent(hwndLB);
						ShowWindow(hwnd, SW_HIDE);
					}
					break;
				}

				// Try to kill the task. First nicely (by sending WM_CLOSE), then
				// if it doesn't respond, use TerminateProcess
				case IDC_ENDTASK:
				{
					KILLTARGETINFO killinfo;
					DECLAREWAITCURSOR;
					if((iIndex = ListBox_GetCurSel(hwndLB)) != LB_ERR) 
					{
						SetWaitCursor();
						killinfo.hwnd = (HWND)ListBox_GetItemData(hwndLB, iIndex);
						// post Close message whether window is enabled or not
						// If it has child popups active it stil needs to be closed
						PostMessage(killinfo.hwnd, WM_CLOSE, 0, 0);
						// Wait for app to actually close
						for(int i=0;IsWindow(killinfo.hwnd) && i<3;i++) 
							Sleep(1700); // sleep min 1.7s, max 5.1sec
							
						// If app is still around prompt for "really nuke?"
						// IMPORTANT: First check if it is not a system process
						if (IsWindow(killinfo.hwnd) && IsOKToKill(killinfo.hwnd)) 
						{
							int iLen = ListBox_GetTextLen(hwndLB, iIndex);
							// set up a killinfo struct with the HWND & title of the window
							// and pass it into the ReallyKill dialog.
							if(iLen && (killinfo.pszTitle=(LPTSTR)_alloca((iLen+1)*sizeof(WCHAR))))
							{
								int idd;
								killinfo.pszTitle[0]=0;
								ListBox_GetText(hwndLB, iIndex, killinfo.pszTitle);
								ResetWaitCursor();
								// Choose the dialog template based on screen-dimensions. See details in RC file
								idd = (GetSystemMetrics(SM_CXSCREEN) < GetSystemMetrics(SM_CYSCREEN))
											? IDD_REALLYKILL_G : IDD_REALLYKILL;
								DialogBoxParam(g_hInst, MAKEINTRESOURCE(idd), hwnd,
										   (DLGPROC)TaskMan_ReallyKill, (LPARAM)(&killinfo));
								// we're done -- hide the Taskman dialog
								ListBox_ResetContent(hwndLB);
								ShowWindow(hwnd, SW_HIDE);
								break;
							}
						}
						// We could not kill it. But we're done anyway. 
						// Hide the Taskman dialog
						ListBox_ResetContent(hwndLB);
						ResetWaitCursor(); // this must come *before* SW_HIDE
						ShowWindow(hwnd, SW_HIDE);
					}
					break;
				}

				case IDC_LISTBOX:
					// double-click in listbox is takedn to be a "switch-to" & falls through to IDOK
					if(HIWORD(wp) != LBN_DBLCLK)
						break;
					// else fall through
				case IDOK:
					// User pressed "Switch To"
					if((iIndex = ListBox_GetCurSel(hwndLB)) != LB_ERR)
					{
						RestoreForegroundWindow((HWND)ListBox_GetItemData(hwndLB, iIndex));
						ShowWindow(hwnd, SW_HIDE);
						ListBox_ResetContent(hwndLB);
					}
					break;

					// User pressed "Cancel"
				case IDCANCEL:
					ShowWindow(hwnd, SW_HIDE);
					ListBox_ResetContent(hwndLB);
					break;
			}
			break;
		default:
			return FALSE;
	}
	return TRUE;
}

// If the user manages to kill one of these system processes, the system will 
// crash, so disallow it. This situation can happen if, say, a device driver 
// in device.exe puts up a dialog box & the user tries to kill it
//
// Forbidden processes list. Must be all lower-case
LPTSTR rgVerboten[] = { L"device.exe", L"gwes.exe", L"nk.exe", L"filesys.exe", 0 };

// Check if a window belongs to a system process
BOOL IsOKToKill(HWND hwndApp)
{
	HANDLE hProc;
	WCHAR wszBuf[MAX_PATH];
	int i;
	DWORD dwProcessId;

	// Get the window's owning process
	GetWindowThreadProcessId(hwndApp, &dwProcessId);
	// Open the process
	hProc = OpenProcess(PROCESS_ALL_ACCESS,0,dwProcessId);
	wszBuf[0] = 0;
	// Get it's filename
	GetModuleFileName((HINSTANCE)hProc, wszBuf, MAX_PATH);
	CloseHandle(hProc);
	// lowercase the filename so substring match will suceed
	wcslwr(wszBuf);
	
	DEBUGMSG(1, (L"Trying to kill process %s\r\n", wszBuf));

	// Check if the process is in the Forbidden list
	for(i=0; rgVerboten[i]; i++)
	{
		// Note: we use a substring match so path effects are eliminated
		if(wcsstr(wszBuf, rgVerboten[i]))
		{
			RETAILMSG(1, (L"It is VERBOTEN to kill process %s\r\n", wszBuf));
			return FALSE;
		}
	}
	return TRUE;
}

//
// Walk the list of top-level windows & populate the Taskman listbox
//
int TaskMan_PopulateLB(HWND hwndLB, HWND hwndFG)
{
	int iIndex, iCount;
	HWND hwndApp;

	DEBUGMSG(ZONE_TRACETASKMAN, (L"TaskMan: Populate: hwndFG=%x hwndTaskbar=%x hwndDesktop=%x\r\n", hwndFG, g_hwndTaskBar, g_hwndDesktop));
	ListBox_ResetContent(hwndLB);

	// Iterate through all windows. Ignore all non-top-level windows
	// Also ignore taskbar & desktop. Normally we would ignore top-level popup/dialogs BUT
	// since we're a minshell here & there's no other way to get to things such as RNAAPP
	// we allow these to stay on the list.
	for(iCount=0, hwndApp=GetWindow(g_hwndTaskBar, GW_HWNDLAST); hwndApp; hwndApp = GetWindow(hwndApp, GW_HWNDPREV))
	{

		if (IsWindowVisible(hwndApp) &&
			(hwndApp != g_hwndTaskBar) &&
			(hwndApp != g_hwndDesktop) &&
			(hwndApp != g_hwndTaskMan) && 
			!GetWindow(hwndApp, GW_OWNER) /*&&
			!(GetWindowLong(hwndApp, GWL_STYLE) & WS_POPUP)*/)
		{
			WCHAR wszBuf[MAX_PATH];
			if(GetWindowText(hwndApp, wszBuf, MAX_PATH))
			{ 
				if(LB_ERR != (iIndex = ListBox_AddString(hwndLB, wszBuf)))
				{
					DEBUGMSG(ZONE_TRACETASKMAN, (L"TaskMan: Added (%s) hwnd=%x\r\n", wszBuf, hwndApp));
					ListBox_SetItemData(hwndLB, iIndex, hwndApp);
					iCount++;

					// hwndFG is the window that had the focus before Taskman was activated
					// select it in the listbox
					if(hwndApp == hwndFG)
					{
						DEBUGMSG(ZONE_TRACETASKMAN, (L"TaskMan: SELECTING (%s) hwnd=%x\r\n", wszBuf, hwndApp));
						ListBox_SetCurSel(hwndLB, iIndex);
					}
				}
				else { DEBUGMSG(ZONE_TRACETASKMAN, (L"TaskMan: hwnd=%x. GOT LB_ERR on AddString. GLE=%d\r\n", hwndApp, GetLastError())); }
			}
			else { DEBUGMSG(ZONE_TRACETASKMAN, (L"TaskMan: hwnd=%x. GetWindowText FAILED GLE=%d\r\n", hwndApp, GetLastError())); }
		}
		else { DEBUGMSG(ZONE_TRACETASKMAN, (L"TaskMan: SKIPPING hwnd=%x\r\n", hwndApp)); }
	}
	return iCount;
} 

// This is the "Really Kill?" confirmation dialog, called when trying to kill
// an app that is hung or not responding. LPARAM on WM_INITDIALOG is a 
// killinfo struct with the HWND & window name of the offending app
LRESULT CALLBACK TaskMan_ReallyKill(HWND hwnd, UINT msg, WPARAM wp, LPARAM lp)
{
	KILLTARGETINFO* pki;
	DWORD dwProcessId;
	HANDLE hProc;

	switch (msg) {
		case WM_INITDIALOG:
			// save the killinfo struct
			SetWindowLong(hwnd, DWL_USER, (LONG)lp);
			pki = (KILLTARGETINFO*)lp;
			// set our title to that of teh app being killed
			SetWindowText(hwnd, pki->pszTitle);
			MessageBeep((UINT)-1);
			break;

		case WM_COMMAND:
			switch (GET_WM_COMMAND_ID(wp,lp)) {
				case IDOK:
					// The user gave us the go ahead to TerminateProcess rudely
					pki = (KILLTARGETINFO*)GetWindowLong(hwnd, DWL_USER);
					GetWindowThreadProcessId(pki->hwnd, &dwProcessId);
					hProc = OpenProcess(PROCESS_ALL_ACCESS,0,dwProcessId);
					TerminateProcess(hProc, (UINT)-1);
					CloseHandle(hProc);

				case IDCANCEL:
					EndDialog(hwnd, GET_WM_COMMAND_ID(wp,lp));
					break;

				default:
					break;
			}
			break;
	}
    return FALSE;

} 

// This is called on process startup to create the Taskman dialog
BOOL TaskMan_Create()
{
	// Check if we have the GetOpenFilename API so we can show/hide the Browse button
	HINSTANCE hinst = LoadLibrary(L"coredll.dll");
	g_pfnGetOpenFileName = NULL;
	UINT iddDialog;
	if(hinst)
	{
		g_pfnGetOpenFileName = (PFNGETOPENFILENAME)GetProcAddress(hinst, L"GetOpenFileNameW");
		DEBUGMSG(ZONE_TRACE, (L"Taskman: GetOpenFilename %s\r\n", (g_pfnGetOpenFileName ? L"PRESENT" : L"MISSING")));
		FreeLibrary(hinst);
	}

	// Choose the dialog template based on screen-dimensions. See details in RC file
	iddDialog = (GetSystemMetrics(SM_CXSCREEN) < GetSystemMetrics(SM_CYSCREEN))
		? IDD_TASK_MANAGER_G : IDD_TASK_MANAGER;
	// Create the window and hide it
	if(g_hwndTaskMan = CreateDialog(g_hInst, MAKEINTRESOURCE(iddDialog), NULL, TaskMan_DlgProc))
	{
		DEBUGMSG(ZONE_TRACE, (TEXT("Created Minshell task-man window.\r\n")));
		ShowWindow(g_hwndTaskMan, SW_HIDE);
		return TRUE;
	}
	else
		return FALSE;
}

// called on process shutdown
void TaskMan_Destroy()
{
	if(g_hwndTaskMan) 
		DestroyWindow(g_hwndTaskMan);
}

// called on user pressing Alt-Tab etc.
void Show_TaskMan(void)
{
	// The Taskman window is created once at startup & stays around, hidden.
	if(g_hwndTaskMan) 
	{
		// We get the current foreground window & squirrel it away in the 
		// dialogs' DWL_USER so we can select it when we populate the listbox.
		HWND hwndFG = GetForegroundWindow();
		if(g_hwndTaskMan != hwndFG)
		{
			DEBUGMSG(ZONE_TRACE2, (TEXT("Show_Taskman: FG hwnd=%x\r\n"), hwndFG));
			SetWindowLong(g_hwndTaskMan, DWL_USER, (LONG)hwndFG);
		}

		// RestoreForegroundWindow is used in case the run dialog is up.  Then SetWindowPos is used
		// to make the window visible without trying to set it to the foreground.
		RestoreForegroundWindow(g_hwndTaskMan);
		SetWindowPos(g_hwndTaskMan, NULL, 0, 0, 0, 0, SWP_NOMOVE|SWP_NOSIZE|SWP_NOZORDER|SWP_NOACTIVATE|SWP_SHOWWINDOW);
	}
}

//
// Thsi is the dlgproc for the Start-Run-like dlg
//
LRESULT CALLBACK RunDlgProc(HWND hwnd, UINT msg, WPARAM wp, LPARAM lp)
{
	LPTSTR pszPath;
	switch (msg) {
        case WM_INITDIALOG:
        	CenterWindowSIPAware(hwnd, TRUE);
			ShowWindow(GetDlgItem(hwnd, IDC_BROWSE), (g_pfnGetOpenFileName ? SW_SHOW : SW_HIDE));
			EnableWindow(GetDlgItem(hwnd, IDOK), FALSE);
			SetFocus(GetDlgItem(hwnd, IDC_RUNCMD));
			return FALSE;	// prevents windows from setting the focus

		case WM_SETTINGCHANGE:
			// Recenter dialog when SIP goes up (see details in the block 
			// comment at the head of the CenterWindowSIPAware function)
			if(wp==SPI_SETSIPINFO)
				CenterWindowSIPAware(hwnd, FALSE);
			break;

		case WM_COMMAND:
			switch (GET_WM_COMMAND_ID(wp,lp)) 
			{
				case IDC_RUNCMD:
					// disable OK button if zero length string in IDC_RUNCMD
					if (HIWORD(wp) == EN_CHANGE) {
						EnableWindow(GetDlgItem(hwnd, IDOK),
							(GetWindowTextLength(GetDlgItem(hwnd, IDC_RUNCMD)) > 0));
					}
					break;
				
				// Try to run the command
				case IDOK:
				{
					TCHAR szInputBuf[MAX_PATH], szArgsBuf[MAX_PATH];
					LPTSTR lpszArgs = NULL;

					GetDlgItemText(hwnd, IDC_RUNCMD, szInputBuf, MAX_PATH);

					PathRemoveBlanks(szInputBuf);
					lpszArgs = PathGetArgs(szInputBuf);
					if (lpszArgs && lpszArgs[0]) {
						lstrcpy(szArgsBuf, lpszArgs);
						PathRemoveArgs(szInputBuf);
					} else {
						szArgsBuf[0] = 0;
					}

					// All error msgs done inside DoExec if the exec fails
					if(DoExec(hwnd, szInputBuf, szArgsBuf))
						EndDialog(hwnd, 0); // if DoExec succeeded, close Run dlg
					// else FAILED. Stay in dialog box. Errors already reported
				}
				break;
				
				case IDCANCEL:
					EndDialog(hwnd, -1);
					break;

				case IDC_BROWSE:
					if(pszPath = (LPTSTR)LocalAlloc(LPTR, sizeof(WCHAR)*MAX_PATH))
					{
						pszPath[0] = 0;
						// open Browse (file-open common dialog). Selection
						// is returned in pszPath
						if(DoBrowse(hwnd, pszPath, MAX_PATH) && pszPath[0]) {
							// Check if the returned file-name has spaces in it
							if (wcschr(pszPath, TEXT(' ')) != NULL) {
								// If spaces in filename, we need to add quotes
								int len = wcslen(pszPath);
								DEBUGCHK(len >= 0 && len <= MAX_PATH);
								if (len < MAX_PATH - 2) {
									pszPath[len++] = TEXT('"');
									// NB: inc len so the 0 is copied as well
									pszPath[len++] = 0;
									// NB: memmove handles overlapping memory
									memmove(pszPath + 1, pszPath, len * sizeof(WCHAR));
									pszPath[0] = TEXT('"');
									DEBUGCHK(pszPath[len] == 0);
								} // else {
									// DoBrowse has returned a string
									// which needs quotes but we don't have
									// room to add them, so we do nothing.
								// }
							}
							// Place result of Browse in teh IDC_RUNCMD edit box
							SetDlgItemText(hwnd, IDC_RUNCMD, pszPath);
						}
						LocalFree(pszPath);
					}
					break;

				default:
					break;
			}
			break;
	}
    return FALSE;
}

//
// Call the GetOpenFileName common dialog, if present, return
// result in pszBuf
BOOL DoBrowse(HWND hwndParent, LPTSTR pszBuf, int iBufLen)
{
#define MAX_TITLE 100
	OPENFILENAME ofn;
	int iFilterLen;
	WCHAR szFilter[MAX_PATH];
	WCHAR szTitle[MAX_TITLE];

	if(!g_pfnGetOpenFileName)
		return FALSE;

	LoadString(g_hInst, IDS_BROWSE_TITLE, szTitle, cchsizeof(szTitle));
    iFilterLen = LoadString(g_hInst, IDS_BROWSE_FILTER, szFilter, cchsizeof(szFilter));
	
	// Convert \1 in the string to \0.  We need embedded NULLs because szFilter
	// is a multi_sz string, but loadstring only reads to the first NULL.
	// So in the RC file we use \1 instead of \0
	while( iFilterLen-- ) 
	{
		if( L'\1' == szFilter[iFilterLen] ) 
			szFilter[iFilterLen] = L'\0';
	} 

    pszBuf[0] = '\0';
	memset(&ofn, 0, sizeof(OPENFILENAME));
    ofn.lStructSize       = sizeof(OPENFILENAME);
    ofn.hwndOwner         = hwndParent;
    ofn.lpstrFilter       = szFilter;
    ofn.nFilterIndex      = 1;
    ofn.lpstrFile         = pszBuf;
    ofn.nMaxFile          = iBufLen;
    ofn.lpstrInitialDir   = L"\\Windows";
    ofn.lpstrTitle        = szTitle;
    ofn.Flags             = OFN_HIDEREADONLY | OFN_FILEMUSTEXIST;
    ofn.lpstrDefExt       = L"exe";

    return g_pfnGetOpenFileName(&ofn);
}



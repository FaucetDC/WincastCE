/*---------------------------------------------------------------------------*\
 *
 * THIS CODE AND INFORMATION IS PROVIDED "AS IS" WITHOUT WARRANTY OF ANY KIND,
 * EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE IMPLIED 
 * WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A PARTICULAR PURPOSE.
 * 
 * Copyright (c) 1995-1998  Microsoft Corporation
 *
 *  file:  HOUSEKP.CPP
 *  author:  ArulM
 *  purpose: Implement Sample shell memory & battery monitoring activities
 *
\*---------------------------------------------------------------------------*/

#include <windows.h>
#include <winbase.h>
#include <windowsx.h>
#include "minshell.h"
#include "minshrc.h"
#include <../211INC/battery.h>
#pragma comment(lib, "getpower.lib")


//////////////////// Memory-level monitoring /////////////////////////
//
// The memory level monitoring works as follows. We compute a free memory
// threshold (the default is 40 pages or 128KB, whichever is higher, 
// but it can be set in the registry). On a 5min timer, we check free mem
//
// As soon as it drops below a threshold, we find the LAST top-level window
// (presumably the user's least-recently-used app) and send it a WM_HIBERNATE
// messages. At the next tick, if the memory level is adequate, we're done. 
// If not then we send the next-to-last top-level window the message, and so on
// As long as we're in the too-little-memory state, we remember all the windows
// we've sent this message to, and each time we send the message to one new
// window, working our way from the back forward. If we have done this 32 times
// and are still too low on memory, then we just sent the mesage to all the 
// remaining windows.  
//
// NOTE: Apps are expected to respond to the WM_HIBERNATE message by "going into
// hibernation", i.e. freeing up as much memory as possible and generally reducing
// their footprint to a minimum. However there is no mechanism that enforces this
// A poorly-design app may not do anything on receipt of this message, and as a 
// result the user may experience low-memory problems despite this mechanism.
//

#define HIBERNATE_BELOW             0x20000 //  128KB 
#define HIBERNATE_BELOW_PAGES       0x28
#define MAX_HIB_LIST				32
DWORD cbHibernateBelow;
BOOL  fCleanUpHibernate;
// List of windows we have sent WM_HIBERNATE message to already
HWND rghwndHibernated[MAX_HIB_LIST];
DWORD dwNumHibernated;

// check whether the HWND is one to which we have already sent a WM_HIBERNATE
// returns 0 for not on list, 1 for on list, -1 for list-full
DWORD IsHibernated(HWND hwnd)
{
	int i;
	for(i=0; i<(int)dwNumHibernated; i++)
	{
		if(hwnd == rghwndHibernated[i])
			return 1;
	}
	if(i==MAX_HIB_LIST)
		return -1;
	else
		return 0;
	
}

// add a window to the "hibernated" list
void SetHibernated(HWND hwnd)
{
	if(dwNumHibernated < MAX_HIB_LIST)
		rghwndHibernated[dwNumHibernated++]=hwnd;
}

//
// This is the function called on the 5mins timer tick. We check the free 
// memory level & if too-low, go into the WM_HIBERNATE algorithm described 
// above.
//
void DoHibernate(void)
{
	
	MEMORYSTATUS ms;

	// If this is the first time through, calculate the threshold
 	if (0 == cbHibernateBelow) 
 	{
 		SYSTEM_INFO sysinfo;
		HKEY		hkeyHibernate = NULL;
		DWORD		dwHibernateBelow = HIBERNATE_BELOW;
		DWORD		dwHibernateBelowPages = HIBERNATE_BELOW_PAGES;
		DWORD		dwSize;
		DWORD		dwType;

 		GetSystemInfo(&sysinfo);

		// try to read hibernate data from registry, if we fail, just use the defaults
		if (ERROR_SUCCESS != RegOpenKeyEx(HKEY_LOCAL_MACHINE, TEXT("SYSTEM\\Hibernate"), 0, 0, &hkeyHibernate)) {
			goto setHibernateThreshold;
		}
		dwSize = sizeof(dwHibernateBelow);
		if (ERROR_SUCCESS != RegQueryValueEx(hkeyHibernate, TEXT("Bytes"), NULL, &dwType, (LPBYTE) &dwHibernateBelow, &dwSize)
				|| dwType != REG_DWORD) {
			// default to original dwHibernateBelow value
			dwHibernateBelow = HIBERNATE_BELOW;
			goto setHibernateThreshold;
		}
		dwSize = sizeof(dwHibernateBelowPages);
		if (ERROR_SUCCESS != RegQueryValueEx(hkeyHibernate, TEXT("Pages"), NULL, &dwType, (LPBYTE) &dwHibernateBelowPages, &dwSize)
				|| dwType != REG_DWORD) {
			// default to original dwHibernateBelowPages value
			dwHibernateBelowPages = HIBERNATE_BELOW_PAGES;
//			goto setHibernateThreshold;
		}

setHibernateThreshold:
 		cbHibernateBelow = max (dwHibernateBelow, dwHibernateBelowPages * sysinfo.dwPageSize);
		if (hkeyHibernate) {
			RegCloseKey(hkeyHibernate);
		}
	}

	memset(&ms, 0, sizeof(MEMORYSTATUS));
	ms.dwLength = sizeof(MEMORYSTATUS);
	GlobalMemoryStatus(&ms);

	// Do we have enough free memory?
 	if (ms.dwAvailPhys < cbHibernateBelow) 
 	{
 		BOOL fDidSomething = FALSE;
 		
 		RETAILMSG(1, (TEXT("NEED TO HIBERNATE: bytes free: %u\n"), ms.dwAvailPhys));

		// set this flag so the next time we're above the threshold we reset the Hibernated array
		if (!fCleanUpHibernate)
			fCleanUpHibernate = TRUE;

		// Iterate through all windows. Ignore all non-top-level windows. 
		// Ignore desktop & taskbar. Don't ignore popups. Some apps (such as 
		// RNAPP) have just a dialog as their toplevel window.
		for(HWND hwndApp=GetWindow(g_hwndDesktop, GW_HWNDLAST); 
				hwndApp; hwndApp=GetWindow(hwndApp, GW_HWNDPREV))
		{
			if ( IsWindowVisible(hwndApp) &&
				 (hwndApp != g_hwndDesktop) &&
				 (hwndApp != g_hwndTaskBar) && 
				 !GetWindow(hwndApp, GW_OWNER) /*&&
				 !(GetWindowLong(hwndApp, GWL_STYLE) & WS_POPUP)*/)
			{
				// find the bottom-most window that we havn't already sent a hibernate msg to
				int fHib = IsHibernated(hwndApp);
				if(fHib==0)
				{
					// not hibernated. send it a msg
					RETAILMSG(1, (TEXT("HIBERNATE: Sending to %x\n"), hwndApp));
					PostMessage(hwndApp, WM_HIBERNATE, 0, 0);
					SetHibernated(hwndApp);
			 		fDidSomething = TRUE;
					break; 
					// done with loop
				}
				else if (fHib== -1)
				{
					// uhoh. our hibernated array overflowed. Send it a hibernate msg anyway
					RETAILMSG(1, (TEXT("HIBERNATE overflow: Sending GLOBAL Hibernate to %x\n"), hwndApp));
					PostMessage(hwndApp, WM_HIBERNATE, 0, 0);
			 		fDidSomething = TRUE;
					// keep going in loop. send msg to *everyone* after this
				}
				// else current window has been hibernated. try next
			}
		}
		if(!fDidSomething)
			RETAILMSG(1, (TEXT("HIBERNATE: Didn't find anyone\n")));
	}
	else
	{
		// If we have enough free memory and if it is the first time in
		// this state after a hibernating cycle, then clean-up our window list
		if (fCleanUpHibernate) 
		{
 			RETAILMSG(1, (TEXT("HIBERNATE reset: bytes free: %u\n"), ms.dwAvailPhys));
			dwNumHibernated = 0; // clean up window list
			fCleanUpHibernate=FALSE;
		}
	}
}
//
//
//////////////////// END Memory-level monitoring END /////////////////////////

//////////////////// Battery level Warnings //////////////////////////////////
//
// All we do here is on each 5min tick, we call the battery drivers for 
// battery state (both main & backup) and if it's too low, we put up a warning.
// We actually have two-levels of warning -- low & critically low.
//
// The dialogs are modeless, so when we return at the next timer tick, we 
// check if (a) the battery level has improved (e.g. user switched in a new
// battery or plugged in AC) in which case we should dismiss the dialog OR
// (b) we still have a problem, in which case we should bring the dialog to
// thw front
//


//////////////////// Not Needed On Dreamcast //////////////////////////////////

void ShowPowerWarning(HWND hwnd, UINT nID);
LRESULT CALLBACK PowerWarningDlgProc(HWND hwnd, UINT msg, WPARAM wp, LPARAM lp);

// Remembered power/battery state from last time
BYTE ACLineStatus, BatteryFlag, BackupBatteryFlag;
UINT dwMainVLowStart, dwBackupVLowStart;

void DoPowerCheck(HWND hwndParent)
{
	SYSTEM_POWER_STATUS_EX ps;
	
	if (GetSystemPowerStatusEx(&ps, TRUE)) 
	{
// Useful to simulate the warnings for test purposes
//#define TESTBATTERY     1
#ifdef TESTBATTERY
		ps.ACLineStatus = AC_LINE_OFFLINE;
		if (GetAsyncKeyState(VK_MENU)) {
			ps.BatteryFlag = BATTERY_FLAG_CRITICAL;

		}else if (GetAsyncKeyState(VK_SHIFT)) {
			ps.BatteryFlag = BATTERY_FLAG_LOW;

		}else{
			ps.BatteryFlag = BATTERY_FLAG_HIGH;
		}
#endif //TESTBATTERY

		// if AC state changed
		if (ACLineStatus != ps.ACLineStatus) 
		{
			ACLineStatus  = ps.ACLineStatus;
			// NOTE: Reset this in order to force a change below.
			BatteryFlag = 0;
		}

		// if battery state changed
		if (BatteryFlag != ps.BatteryFlag) 
		{
			// Reset our global vars
			BatteryFlag  = ps.BatteryFlag;
			dwMainVLowStart = 0;

			// check main battery state IFF we're on AC power
			if (ACLineStatus != AC_LINE_ONLINE) 
			{
				switch (ps.BatteryFlag) 
				{
					case BATTERY_FLAG_HIGH:
						// if battery is good, dismiss the warning dlg, if any
						if (g_hwndMBVL) 
							PostMessage(g_hwndMBVL, WM_COMMAND, IDOK, 0);
						break;

					case BATTERY_FLAG_LOW:
						// BUGBUG: Do something here too?
						break;

					case BATTERY_FLAG_CRITICAL:
					case BATTERY_FLAG_NO_BATTERY:
						// show warning dlg. Remember this time so we can 
						// periodically bring the dlg to the front
						dwMainVLowStart = GetTickCount();
						ShowPowerWarning(hwndParent, IDD_MAIN_VLOW);
						break;

					default:
					break;
				}
			}
		}

		// if backup battery state changed
		if (BackupBatteryFlag != ps.BackupBatteryFlag) 
		{
			// Reset our global vars
			BackupBatteryFlag = ps.BackupBatteryFlag;
			dwBackupVLowStart = 0;

			switch (ps.BackupBatteryFlag) 
			{
				case BATTERY_FLAG_HIGH:  // Backup Battery High
					// if battery is good, dismiss the warning dlgs, if any
					if (g_hwndBBL) PostMessage(g_hwndBBL, WM_COMMAND, IDOK, 0);
					if (g_hwndBBVL) PostMessage(g_hwndBBVL, WM_COMMAND, IDOK, 0);
					break;

				case BATTERY_FLAG_LOW:  // Backup Battery Low
					// Show warning dlg. NOTE: This dlg is less critical than
					// the VLOW dlg, so we don't keep bringing it to the front
					ShowPowerWarning(hwndParent, IDD_BACKUP_LOW);
					break;

				case BATTERY_FLAG_CRITICAL:   // Backup Battery Critical
				case BATTERY_FLAG_NO_BATTERY: // No system battery
					// show warning dlg. Remember this time so we can 
					// periodically bring the dlg to the front
					dwBackupVLowStart = GetTickCount();
					ShowPowerWarning(hwndParent, IDD_BACKUP_VLOW);
					break;

				default:
					break;
			}
		}
	}


#define RENOTIFY_INTERVAL 240000	// 4 minute, time in ms

	DWORD dwCurrent = GetTickCount();
	if (dwMainVLowStart) 
	{
		// If we've been in this state for more than 4mins
		// bring the warning dlg to the front again
		if ((dwCurrent - dwMainVLowStart) > RENOTIFY_INTERVAL) 
		{
			dwMainVLowStart = dwCurrent;
			ShowPowerWarning(hwndParent, IDD_MAIN_VLOW);
		}
	}

	if (dwBackupVLowStart) 
	{
		// If we've been in this state for more than 4mins
		// bring the warning dlg to the front again
		if ((dwCurrent - dwBackupVLowStart) > RENOTIFY_INTERVAL) 
		{
			dwBackupVLowStart = dwCurrent;
			ShowPowerWarning(hwndParent, IDD_BACKUP_VLOW);
		}
	}
}

//
// Launch the correct warning dialog (note it's modeless, so we stick the 
// HWND in a global var, so that the owning (taskbar) thread's message
// loop can dispatch our messages. 
//
// If the dialog is already up, bring it to the foreground
// 
void ShowPowerWarning(HWND hwnd, UINT nID)
{
	switch(nID) 
	{
		case IDD_BACKUP_LOW:
			if (g_hwndBBL) {
				SetForegroundWindow(g_hwndBBL);
			}else{
				g_hwndBBL = CreateDialogParam(g_hInst, MAKEINTRESOURCE(IDD_BACKUP_LOW), NULL,
											  (DLGPROC)PowerWarningDlgProc, IDD_BACKUP_LOW);
				ShowWindow(g_hwndBBL, SW_SHOWNORMAL);
			}
			break;

		case IDD_BACKUP_VLOW:
			if (g_hwndBBVL) {
				SetForegroundWindow(g_hwndBBVL);
			}else{
				g_hwndBBVL = CreateDialogParam(g_hInst, MAKEINTRESOURCE(IDD_BACKUP_VLOW), NULL,
											   (DLGPROC)PowerWarningDlgProc, IDD_BACKUP_VLOW);
				ShowWindow(g_hwndBBVL, SW_SHOWNORMAL);
			}
			break;

		case IDD_MAIN_VLOW:
			if (g_hwndMBVL) {
				SetForegroundWindow(g_hwndMBVL);
			}else{
				g_hwndMBVL = CreateDialogParam(g_hInst, MAKEINTRESOURCE(IDD_MAIN_VLOW), NULL,
											   (DLGPROC)PowerWarningDlgProc, IDD_MAIN_VLOW);
				ShowWindow(g_hwndMBVL, SW_SHOWNORMAL);
			}
			break;

		default:
			break;
	}

} 

//
// This wndproc is shared by all 3 battery warnings. LPARAM of WM_INITDIALOG
// is the dialog RC ID, so we know which dialog we're in!
// NOTE: These dialogs are modeless so we need to explicitly destroy ourselves
//
LRESULT CALLBACK PowerWarningDlgProc(HWND hwnd, UINT msg, WPARAM wp, LPARAM lp)
{
	switch (msg) {
		case WM_INITDIALOG:
			SetWindowLong(hwnd, DWL_USER, lp);
			CenterWindowSIPAware(hwnd, TRUE);
			MessageBeep((UINT)-1);
			return TRUE;
			break;

		case WM_COMMAND:
			switch (GET_WM_COMMAND_ID(wp,lp)) 
			{
				case IDOK:
				case IDCANCEL:
					// Modeless dialogs so we need to explicitly destroy 
					// ourselves & nuke the global var with our HWND
					lp = GetWindowLong(hwnd, DWL_USER);
					switch (lp) {
						case IDD_BACKUP_LOW:
							g_hwndBBL = NULL;
							break;

						case IDD_BACKUP_VLOW:
							g_hwndBBVL = NULL;
							break;

						case IDD_MAIN_VLOW:
							g_hwndMBVL = NULL;
							break;
					}
					DestroyWindow(hwnd);
					break;

				default:
					break;
			}
			break;
	}
    return FALSE;
}



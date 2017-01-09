/*---------------------------------------------------------------------------*\
 *
 * THIS CODE AND INFORMATION IS PROVIDED "AS IS" WITHOUT WARRANTY OF ANY KIND,
 * EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE IMPLIED 
 * WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A PARTICULAR PURPOSE.
 * 
 * Copyright (c) 1995-1998  Microsoft Corporation
 *
 *  file:    MinShell.h
 *  author:  ArulM
 *  purpose: sample shell common header
 *
\*---------------------------------------------------------------------------*/

// Debug zones
  #define ZONE_TRACE		DEBUGZONE(0)
  #define ZONE_TRACE2		DEBUGZONE(1)
  #define ZONE_TRACEMSG		DEBUGZONE(2)
  #define ZONE_TRACEMSGHF	DEBUGZONE(3)
  #define ZONE_TRACETASKMAN	DEBUGZONE(4)
  #define ZONE_TRACEDESKT   DEBUGZONE(5)
  #define ZONE_WARN			DEBUGZONE(14)
  #define ZONE_ERROR		DEBUGZONE(15)

// extern const defns
extern TCHAR const c_szDesktopWndClass[];

// extern global Data defns
extern HINSTANCE g_hInst;
extern HWND g_hwndDesktop, g_hwndTaskBar, g_hwndTaskMan;
extern HWND g_hwndMBVL, g_hwndBBL, g_hwndBBVL;
extern int  g_iSignalStartedID;

// extern Function defns
extern BOOL Desktop_Register(HINSTANCE hInst);
extern HRESULT Desktop_InitInstance(int nCmdShow);
extern TCHAR const c_szDesktopWndClass[];
extern HWND  g_hwndDesktop;
extern BOOL TaskBar_ThreadProc(int nCmdShow);
extern BOOL TaskMan_Create();
extern void TaskMan_Destroy();
extern void Show_TaskMan(void);
extern void DoPowerCheck(HWND);
extern void DoHibernate(void);
extern void WINAPI PathRemoveBlanks(LPTSTR lpszString);
extern LPTSTR WINAPI PathGetArgs(LPCTSTR pszPath);
extern void WINAPI PathRemoveArgs(LPTSTR pszPath);
extern BOOL DoBrowse(HWND hwndParent, LPTSTR pszBuf, int iBufLen);
extern BOOL DoExec(HWND hwndParent, LPCTSTR lpsz, LPCTSTR lpszArgs);

BOOL WINAPI CenterWindowSIPAware(HWND hwnd, BOOL fInitial);


#ifdef DEBUG
	#define DECLAREWAITCURSOR  HCURSOR hcursor_wait_cursor_save = (HCURSOR)0xDEADBEEF
	#define SetWaitCursor()   { DEBUGCHK(hcursor_wait_cursor_save == (HCURSOR)0xDEADBEEF); hcursor_wait_cursor_save = SetCursor(LoadCursor(NULL, IDC_WAIT)); }
	#define ResetWaitCursor() { DEBUGCHK(hcursor_wait_cursor_save != (HCURSOR)0xDEADBEEF); SetCursor(hcursor_wait_cursor_save); hcursor_wait_cursor_save = (HCURSOR)0xDEADBEEF; }
#else
	#define DECLAREWAITCURSOR  HCURSOR hcursor_wait_cursor_save = NULL
	#define SetWaitCursor()   { hcursor_wait_cursor_save = SetCursor(LoadCursor(NULL, IDC_WAIT)); }
	#define ResetWaitCursor() { SetCursor(hcursor_wait_cursor_save);  hcursor_wait_cursor_save = NULL; }
#endif


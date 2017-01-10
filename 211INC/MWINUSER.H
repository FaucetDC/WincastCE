/*++
THIS CODE AND INFORMATION IS PROVIDED "AS IS" WITHOUT WARRANTY OF
ANY KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED TO
THE IMPLIED WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A
PARTICULAR PURPOSE.
Copyright (c) 1995-1998  Microsoft Corporation

Module Name:

mwinuser.h

Abstract:

Notes:


--*/

#ifndef __MWINUSER_H__
#define __MWINUSER_H__

#ifndef WINCEMACRO
#error WINCEMACRO not defined __FILE__
#endif

/* Win32 User Function Indices */
#define MID_RegisterClassWStub      2
#define MID_UnregisterClassW        3
#define MID_CreateWindowExW         4
#define MID_PostMessageW            5
#define MID_PostQuitMessage         6
#define MID_SendMessageW            7
#define MID_GetMessageW             8
#define MID_TranslateMessage        9
#define MID_DispatchMessageW        10
#define MID_GetCapture              11
#define MID_SetCapture              12
#define MID_ReleaseCapture          13
#define MID_SetWindowPos            14
#define MID_GetWindowRect           15
#define MID_GetClientRect           16
#define MID_InvalidateRect          17
#define MID_GetWindow               18
#define MID_GetSystemMetrics        19
#define MID_ImageListGetDragImage   20
#define MID_ImageListGetIconSize    21
#define MID_ImageListSetIconSize    22
#define MID_ImageListGetImageInfo   23
#define MID_ImageListMerge          24
#define MID_ShowCursor	        	25
#define MID_SetCursorPos           	26
#define MID_ImageListCopyDitherImage 27
#define MID_ImageListDrawIndirect   28
#define MID_ImageListDragShowNolock 29
#define MID_WindowFromPoint         30
#define MID_ChildWindowFromPoint    31
#define MID_ClientToScreen          32
#define MID_ScreenToClient          33
#define MID_SetWindowTextW          34
#define MID_GetWindowTextW          35
#define MID_SetWindowLongW          36
#define MID_GetWindowLongW          37
#define MID_BeginPaint              38
#define MID_EndPaint                39
#define MID_GetDC                   40
#define MID_ReleaseDC               41
#define MID_DefWindowProcW          42
#define MID_GetClassLongW           43
#define MID_SetClassLongW           44
#define MID_DestroyWindow           45
#define MID_ShowWindow              46
#define MID_UpdateWindow            47
#define MID_SetParent               48
#define MID_GetParent               49
#define MID_MessageBoxW             50
#define MID_SetFocus				51
#define MID_GetFocus				52
#define MID_GetActiveWindow			53
#define MID_GetWindowDC             54
#define MID_GetSysColor             55
#define MID_AdjustWindowRectEx      56
#define MID_IsWindow                57
#define MID_CreatePopupMenu         58
#define MID_InsertMenuW             59
#define MID_AppendMenuW             60
#define MID_RemoveMenu              61
#define MID_DestroyMenu             62
#define MID_TrackPopupMenuEx        63
#define MID_LoadMenuW               64
#define MID_EnableMenuItem          65
#define MID_MoveWindow              66
#define MID_GetUpdateRgn            67
#define MID_GetUpdateRect           68
#define MID_BringWindowToTop        69
#define MID_GetWindowTextLengthW    70
#define MID_IsChild                 71
#define MID_IsWindowVisible         72
#define MID_ValidateRect            73
#define MID_LoadBitmapW             74
#define MID_CheckMenuItem           75
#define MID_CheckMenuRadioItem      76
#define MID_DeleteMenu              77
#define MID_LoadIconW               78
#define MID_DrawIconEx              79
#define MID_DestroyIcon             80
#define MID_GetAsyncKeyState        81
#define MID_LoadStringW             82
#define MID_DialogBoxIndirectParamW 83
#define MID_EndDialog               84
#define MID_GetDlgItem              85
#define MID_GetDlgCtrlID            86
#define MID_GetKeyState				87
#define MID_KeybdGetDeviceInfo		88		// OAK only
#define MID_KeybdInitStates			89		// OAK only
#define MID_PostKeybdMessage		90		// OAK only
#define MID_KeybdVKeyToUnicode		91		// OAK onlyc
#define MID_keybd_event				92		
#define MID_mouse_event				93		// OAK only
#define MID_SetScrollInfo           94
#define MID_SetScrollPos       		95
#define MID_SetScrollRange         	96
#define MID_GetScrollInfo          	97
#define MID_PeekMessageW			98
#define MID_MapVirtualKeyW			99
#define MID_GetMessageWNoWait		100		// OAK only
#define MID_GetClassNameW   		101
#define MID_MapWindowPoints         102
#define MID_LoadImageW              103
#define MID_GetForegroundWindow		104
#define MID_SetForegroundWindow		105
#define MID_RegisterTaskBar 		106
#define MID_SetActiveWindow			107
#define MID_CallWindowProcW         108
#define MID_GetClassInfoW           109
#define MID_GetNextDlgTabItem       110
#define MID_CreateDialogIndirectParamW 111
#define MID_IsDialogMessageW        112
#define MID_SetDlgItemInt           113
#define MID_GetDlgItemInt           114
#define MID_FindWindowW             115
#define MID_CreateCaret				116
#define MID_DestroyCaret			117
#define MID_HideCaret				118
#define MID_ShowCaret				119
#define MID_SetCaretPos				120
#define MID_GetCaretPos				121
#define MID_GetCursorPos			122	
#define MID_ClipCursor				123
#define MID_GetClipCursor			124
#define MID_GetCursor				125
#define MID_ExtractIconExW          126
#define MID_SetTimer				127
#define MID_KillTimer				128
#define MID_GetNextDlgGroupItem     129
#define MID_CheckRadioButton        130
#define MID_EnableWindow            131
#define MID_IsWindowEnabled         132
#define MID_CreateMenu              133
#define MID_GetSubMenu              134
#define MID_DefDlgProcW 		    135
#define MID_SendNotifyMessageW		136
#define MID_PostThreadMessageW      137
#define MID_TranslateAcceleratorW   138
#define MID_sndPlaySoundW			139         // Macro not used
#define MID_waveOutGetVolume		140         // Macro not used
#define MID_waveOutSetVolume		141         // Macro not used
#define MID_ImageListCreate         142
#define MID_ImageListDestroy        143
#define MID_ImageListGetImageCount  144
#define MID_ImageListAdd            145
#define MID_ImageListReplaceIcon    146
#define MID_ImageListSetBkColor     147
#define MID_ImageListGetBkColor     148
#define MID_ImageListSetOverlayImage    149
#define MID_ImageListDraw           150
#define MID_ImageListReplace        151
#define MID_ImageListAddMasked      152
#define MID_ImageListDrawEx         153
#define MID_ImageListRemove         154
#define MID_ImageListGetIcon        155
#define MID_ImageListLoadImage      156
#define MID_ImageListBeginDrag      157
#define MID_ImageListEndDrag        158
#define MID_ImageListDragEnter      159
#define MID_ImageListDragLeave      160
#define MID_ImageListDragMove       161
#define MID_ImageListSetDragCursorImage 162
#define MID_AudioUpdateFromRegistry 163         // Macro not used
#define MID_ScrollDC                164
#define MID_ScrollWindowEx          165
#define MID_OpenClipboard               166
#define MID_CloseClipboard              167
#define MID_GetClipboardOwner           168
#define MID_SetClipboardData            169
#define MID_GetClipboardDataStub        170
#define MID_RegisterClipboardFormatW    171
#define MID_CountClipboardFormats       172
#define MID_EnumClipboardFormats        173
#define MID_GetClipboardFormatNameW     174
#define MID_EmptyClipboard              175
#define MID_IsClipboardFormatAvailable	176
#define MID_GetPriorityClipboardFormat  177
#define MID_GetOpenClipboardWindow      178
#define MID_MessageBeep                 179
#define MID_SystemIdleTimerReset		180		// OAK only
#define MID_SystemIdleTimerUpdateMax	181		// OAK only
#define MID_GetClipboardDataAllocStub   182
#define MID_SetKeyboardTarget			183		// OAK only
#define MID_GetKeyboardTarget			184		// OAK only
#define MID_NotifyWinUserSystem			185		// OAK only
#define MID_SetMenuItemInfoW            186
#define MID_GetMenuItemInfoW            187
#define MID_SetCaretBlinkTime			188
#define MID_GetCaretBlinkTime			189
#define MID_GetMessagePos				190
#define MID_QASetWindowsJournalHook		191		// OAK only
#define MID_QAUnhookWindowsJournalHook	192		// OAK onlyc
#define MID_NLedGetDeviceInfo			193		// OAK only
#define MID_NLedSetDevice		        194		// OAK only
#define MID_EnumWindows					195
#define MID_RectangleAnimation			196		// OAK only
#define MID_MapDialogRect				197
#define MID_GetSystemPowerStatusEx 		198
#define MID_GetDialogBaseUnits			199	
#define MID_GetDoubleClickTime			200
#define MID_GetWindowThreadProcessId	201
#define MID_CreateIconIndirect			202
#define MID_ShellModalEnd				203		// OAK
#define MID_TouchCalibrate				204		// OAK only
#define MID_BatteryGetLifeTimeInfo		205		// OAK
#define MID_BatteryDrvrGetLevels		206		// OAK
#define MID_GwesPowerOffSystem			207		// OAK
#define MID_BatteryNotifyOfTimeChange   208		// OAK
#define MID_LoadCursorW					209
#define MID_SetCursor					210
#define MID_DestroyCursor				211
#define MID_DisableCaretSystemWide		212		// OAK
#define MID_EnableCaretSystemWide		213		// OAK
#define MID_GetMouseMovePoints			214		// OAK
#define MID_BatteryDrvrSupportsChangeNotification 215 //OAK
#define MID_EnableHardwareKeyboard		216
#define MID_GetKeyboardStatus			217
#define MID_RegisterSIPanel				218
#define MID_GetAsyncShiftFlags			219
#define MID_MsgWaitForMultipleObjectsEx	220
#define MID_SetAssociatedMenu			221		/* OAK */
#define MID_GetAssociatedMenu			222		/* OAK */
#define MID_DrawMenuBar                 223
#define MID_SetSysColors                224
#define MID_DrawFrameControl            225
#define MID_CreateCursor				226
#define MID_RegisterWindowMessageW		227
#define MID_SystemParametersInfo_GWE	228
#define MID_SendInput					229
#define MID_SendDlgItemMessageW			230
#define MID_SetDlgItemTextW				231
#define MID_GetDlgItemTextW				232
#define MID_GetMessageSource			233
#define MID_RegisterHotKey				234
#define MID_UnregisterHotKey			235
#define MID_ImageListCopy				236
#define MID_ImageListDuplicate			237
#define MID_ImageListSetImageCount		238
#define MID_UnregisterFunc1				239
#define MID_ImmGetContextFromWindowGwe	240
#define MID_ImmAssociateContextWithWindowGwe	241
#define MID_ImmSetHotKey				242
#define MID_BeginDeferWindowPos			243
#define MID_DeferWindowPos				244
#define MID_EndDeferWindowPos			245
#define MID_ImmGetHotKey				246
#define MID_GetDCEx						247
#define MID_GetKeyboardLayoutNameW		255





#ifndef USER_CALL
#define USER_CALL(type, api, args) \
        (*(type (*)args)IMPLICIT_CALL(SH_WMGR, MID_ ## api))
#endif


/*****************  USER SDK EXPORTS *****************/

#define RegisterClassWStub USER_CALL(ATOM, RegisterClassWStub, ( \
    CONST WNDCLASSW *lpWndClass, LPCWSTR lpszClassName, HANDLE hprcWndProc))

#define UnregisterClassW USER_CALL(BOOL, UnregisterClassW, ( \
    LPCWSTR lpClassName, HINSTANCE hInstance))

#define CreateWindowExW USER_CALL(HWND, CreateWindowExW, ( \
            DWORD dwExStyle, LPCWSTR lpClassName, LPCWSTR lpWindowName, \
            DWORD dwStyle, int X, int Y, int nWidth, int nHeight, \
            HWND hwndParent, HMENU hMenu, HINSTANCE hInstance, \
            LPVOID lpParam))

#define PostMessageW USER_CALL(BOOL, PostMessageW, ( \
            HWND hwnd, UINT Msg, WPARAM wParam, LPARAM lParam))

#define PostQuitMessage USER_CALL(VOID, PostQuitMessage, ( \
            int nExitCode))

#define SendMessageW USER_CALL(LRESULT, SendMessageW, ( \
    HWND hwnd, UINT Msg, WPARAM wParam, LPARAM lParam))

#define GetMessageW USER_CALL(BOOL, GetMessageW, ( \
    PMSG pMsgr, HWND hwnd, UINT wMsgFilterMin, UINT wMsgFilterMax))

#define TranslateMessage USER_CALL(BOOL, TranslateMessage, ( \
    CONST MSG *pMsg))

#define DispatchMessageW USER_CALL(LONG, DispatchMessageW, ( \
    CONST MSG *pMsg))

#define GetCapture USER_CALL(HWND, GetCapture, ( \
    VOID))

#define SetCapture USER_CALL(HWND, SetCapture, ( \
    HWND hWnd))

#define ReleaseCapture USER_CALL(BOOL, ReleaseCapture, ( \
    VOID))

#define SetWindowPos USER_CALL(BOOL, SetWindowPos, ( \
    HWND hwnd, HWND hwndInsertAfter, int x, int y, int dx, int dy, \
    UINT fuFlags))

#define GetWindowRect USER_CALL(BOOL, GetWindowRect, ( \
    HWND hwnd, LPRECT prc))

#define GetClientRect USER_CALL(BOOL, GetClientRect, ( \
    HWND hwnd, LPRECT prc))

#define InvalidateRect USER_CALL(BOOL, InvalidateRect, ( \
    HWND hwnd, LPCRECT prc, BOOL fErase))

#define GetWindow USER_CALL(HWND, GetWindow, ( \
    HWND hwnd, UINT uCmd))

#define GetSystemMetrics USER_CALL(int, GetSystemMetrics, ( \
    int nIndex))

#define WindowFromPoint USER_CALL(HWND, WindowFromPoint, ( \
    POINT Point))

#define ChildWindowFromPoint USER_CALL(HWND, ChildWindowFromPoint, ( \
    HWND hwndParent, POINT Point))

#define ClientToScreen USER_CALL(BOOL, ClientToScreen, ( \
    HWND hwnd, LPPOINT lpPoint))

#define ScreenToClient USER_CALL(BOOL, ScreenToClient, ( \
    HWND hwnd, LPPOINT lpPoint))

#define SetWindowTextW USER_CALL(BOOL, SetWindowTextW, ( \
    HWND hwnd, LPCTSTR psz))

#define GetWindowTextW USER_CALL(int, GetWindowTextW, ( \
    HWND hwnd, LPTSTR psz, int cchMax))

#define SetWindowLongW USER_CALL(LONG, SetWindowLongW, ( \
    HWND hwnd, int nIndex, LONG lNewLong))

#define GetWindowLongW USER_CALL(LONG, GetWindowLongW, ( \
    HWND hwnd, int nIndex))

#define BeginPaint USER_CALL(HDC, BeginPaint, ( \
    HWND hwnd, LPPAINTSTRUCT pps))

#define EndPaint USER_CALL(BOOL, EndPaint, ( \
    HWND hwnd, LPPAINTSTRUCT pps))

#define GetDC USER_CALL(HDC, GetDC, ( \
    HWND hwnd))

#define ReleaseDC USER_CALL(BOOL, ReleaseDC, ( \
    HWND hwnd, HDC hdc))

#define DefWindowProcW USER_CALL(LRESULT, DefWindowProcW, ( \
    HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam))

#define GetClassLongW USER_CALL(LONG, GetClassLongW, ( \
    HWND hwnd, INT nIndex))

#define SetClassLongW USER_CALL(DWORD, SetClassLongW, ( \
    HWND hwnd, INT nIndex, LONG lValue))

#define DestroyWindow USER_CALL(BOOL, DestroyWindow, ( \
    HWND hwnd))

#define ShowWindow USER_CALL(BOOL, ShowWindow, ( \
    HWND hwnd, INT nCmdShow))

#define UpdateWindow USER_CALL(BOOL, UpdateWindow, ( \
    HWND hwnd))

#define SetParent USER_CALL(HWND, SetParent, ( \
    HWND hwnd, HWND hwndParent))

#define GetParent USER_CALL(HWND, GetParent, ( \
    HWND hwnd))

#define MessageBoxW USER_CALL(int, MessageBoxW, ( \
    HWND hWnd, LPCWSTR lpText, LPCWSTR lpCaption, UINT uType))

#define GetWindowDC USER_CALL(HDC, GetWindowDC, ( \
    HWND hwnd))

#define SetFocus USER_CALL(HWND, SetFocus, ( \
	HWND hwnd))

#define GetFocus USER_CALL(HWND, GetFocus, ( \
	VOID))

#define GetActiveWindow USER_CALL(HWND, GetActiveWindow, ( \
	VOID ))	

#define GetSysColor USER_CALL(DWORD, GetSysColor, ( \
    int nIndex))

#define AdjustWindowRectEx USER_CALL(BOOL, AdjustWindowRectEx, ( \
    PRECT prc, DWORD dwStyle, BOOL bMenu, DWORD dwExStyle))

#define IsWindow USER_CALL(BOOL, IsWindow, ( \
    HWND hWnd))

#define CreatePopupMenu USER_CALL (HMENU, CreatePopupMenu, ( \
    VOID))

#define InsertMenuW USER_CALL (BOOL, InsertMenuW, ( \
    HMENU hMenu, UINT uPosition, UINT uFlags, UINT uIDNewItem, \
    LPCWSTR lpNewItem))

#define AppendMenuW USER_CALL (BOOL, AppendMenuW, ( \
    HMENU hMenu, UINT uFlags, UINT uIDNewItem, LPCWSTR lpNewItem))

#define RemoveMenu USER_CALL (BOOL, RemoveMenu, ( \
    HMENU hMenu, UINT uPosition, UINT uFlags))

#define DestroyMenu USER_CALL (BOOL, DestroyMenu, ( \
    HMENU hMenu))

#define TrackPopupMenuEx USER_CALL (BOOL, TrackPopupMenuEx, ( \
    HMENU hMenu, UINT uFlags, int x, int y, HWND hWnd, LPTPMPARAMS lptpm))

#define LoadMenuW USER_CALL (HMENU, LoadMenuW, ( \
    HINSTANCE hinst, LPCWSTR pszMenuName))

#define EnableMenuItem USER_CALL (BOOL, EnableMenuItem, ( \
    HMENU hMenu, UINT uIDEnableItem, UINT uEnable))

#define MoveWindow USER_CALL (BOOL, MoveWindow, ( \
    HWND hWnd, int X, int Y, int nWidth, int nHeight, BOOL bRepaint))

#define GetUpdateRgn USER_CALL (int, GetUpdateRgn, ( \
    HWND hWnd, HRGN hRgn, BOOL bErase))

#define GetUpdateRect USER_CALL (BOOL, GetUpdateRect, ( \
    HWND hWnd, LPRECT lpRect, BOOL bErase))

#define BringWindowToTop USER_CALL (BOOL, BringWindowToTop, ( \
    HWND hWnd))

#define GetWindowTextLengthW USER_CALL (int, GetWindowTextLengthW, ( \
   HWND hWnd))

#define IsChild USER_CALL (BOOL, IsChild, ( \
    HWND hWndParent, HWND hWnd))

#define IsWindowVisible USER_CALL (BOOL, IsWindowVisible, ( \
    HWND hWnd))

#define ValidateRect USER_CALL (BOOL, ValidateRect, ( \
    HWND hWnd , CONST RECT *lpRect))

#define LoadBitmapW USER_CALL (HBITMAP, LoadBitmapW, ( \
    HINSTANCE hinst, LPCWSTR pszBitmapName))

#define CheckMenuItem USER_CALL (DWORD, CheckMenuItem, ( \
    HMENU hMenu, UINT uIDCheckItem, UINT uCheck))

#define CheckMenuRadioItem USER_CALL (BOOL, CheckMenuRadioItem, ( \
    HMENU hMenu, UINT wIDFirst, UINT wIDLast, UINT wIDCheck, UINT flags))

#define DeleteMenu USER_CALL (BOOL, DeleteMenu, ( \
    HMENU hmenu, UINT uPosition, UINT uFlags))

#define LoadIconW USER_CALL (HICON, LoadIconW, ( \
    HINSTANCE hinst, LPCWSTR pszIconName))

#define DrawIconEx USER_CALL (BOOL, DrawIconEx, ( \
    HDC hDC, int X, int Y, HICON hIcon, int cxWidth, int cyWidth, \
    UINT istepIfAniCur, HBRUSH hbrFlickerFreeDraw, UINT diFlags))

#define DestroyIcon USER_CALL (BOOL, DestroyIcon, ( \
    HICON hicon))

#define GetAsyncKeyState USER_CALL (SHORT, GetAsyncKeyState, ( \
	INT	vKey))

#define LoadStringW USER_CALL (int, LoadStringW, ( \
    HINSTANCE hInstance, UINT uID, LPWSTR lpBuffer, int nBufferMax))

#define DialogBoxIndirectParamW USER_CALL (int, DialogBoxIndirectParamW, (  \
    HINSTANCE hInstance, LPCDLGTEMPLATEW lpTemplate, HWND hWndParent,   \
    DLGPROC lpDialogFunc, LPARAM dwInitParam))

#define EndDialog USER_CALL (BOOL, EndDialog, ( \
    HWND hDlg, int nResult))

#define GetDlgItem USER_CALL (HWND, GetDlgItem, (   \
    HWND hDlg, int CtrlID))

#define GetDlgCtrlID USER_CALL (int, GetDlgCtrlID, (    \
    HWND hWnd))

#define GetKeyState USER_CALL (SHORT, GetKeyState, ( \
	INT	vKey))

#define keybd_event USER_CALL (VOID, keybd_event, (	\
	BYTE	Vk,                                     \
	BYTE	Scan,                                   \
    DWORD	dwFlags,                                \
    DWORD	dwExtraInfo								\
	))

#define SetScrollInfo USER_CALL(int, SetScrollInfo, ( \
		HWND hwnd, int fnBar, LPCSCROLLINFO lpsi, BOOL fRedraw))

#define SetScrollPos USER_CALL(int, SetScrollPos, ( \
		HWND hwnd, int fnBar, int nPos, BOOL fRedraw))

#define SetScrollRange USER_CALL(int, SetScrollRange, ( \
		HWND hwnd, int fnBar, int nMinPos, int nMaxPos, BOOL fRedraw))

#define GetScrollInfo USER_CALL(int, GetScrollInfo, ( \
		HWND hwnd, int fnBar, LPCSCROLLINFO lpsi))

#define PeekMessageW USER_CALL(BOOL, PeekMessageW, ( \
		PMSG pMsg, HWND hWnd, UINT wMsgFilterMin, UINT wMsgFilterMax, UINT wRemoveMsg))



#define MapVirtualKeyW USER_CALL(UINT, MapVirtualKeyW, ( \
		UINT uCode, UINT uMapType))

#define GetClassNameW USER_CALL(int, GetClassNameW, ( \
        HWND hWnd, LPWSTR lpClassName, int nMaxCount))

#define UnregisterClassW USER_CALL(BOOL, UnregisterClassW, ( \
        LPCWSTR lpClassName, HINSTANCE hInstance))

#define MapWindowPoints USER_CALL(int, MapWindowPoints, ( \
        HWND hwndFrom, HWND hwndTo, LPPOINT ppt, UINT cPoints))

#define LoadImageW USER_CALL(HANDLE, LoadImageW, ( \
        HINSTANCE hinst, LPCTSTR lpszName, UINT uType,  int cxDesired, \
        int cyDesired, UINT fuLoad))

#define GetForegroundWindow USER_CALL(HWND, GetForegroundWindow, ( \
			VOID ))

#define SetForegroundWindow USER_CALL(BOOL, SetForegroundWindow, ( \
			HWND hWnd))

#define SetActiveWindow USER_CALL(HWND, SetActiveWindow, ( \
			HWND hwnd))

#define CreateCaret USER_CALL(BOOL, CreateCaret, ( \
			HWND hWnd, HBITMAP hBitmap, int nWidth, int nHeight))

#define DestroyCaret USER_CALL(BOOL, DestroyCaret, ( \
			VOID))

#define HideCaret USER_CALL(BOOL, HideCaret, ( \
			HWND hWnd))

#define ShowCaret USER_CALL(BOOL, ShowCaret, ( \
		HWND hWnd))

#define SetCaretPos USER_CALL(BOOL, SetCaretPos, ( \
			int X, int Y))

#define GetCaretPos USER_CALL(BOOL, GetCaretPos, ( \
			LPPOINT lpPoint))

#define SetCaretBlinkTime USER_CALL(BOOL, SetCaretBlinkTime, (	\
			UINT uMSeconds))

#define GetCaretBlinkTime USER_CALL(UINT, GetCaretBlinkTime, (	\
			VOID))


#ifdef STRICT
#define CallWindowProcW USER_CALL (LRESULT, CallWindowProcW, ( \
    WNDPROC lpPrevWndFunc, HWND hWnd, UINT Msg, WPARAM wParam, LPARAM lParam))
#else
#define CallWindowProcW USER_CALL (LRESULT, CallWindowProcW, ( \
    FARPROC lpPrevWndFunc, HWND hWnd, UINT Msg, WPARAM wParam, LPARAM lParam))
#endif /* STRICT */

#define GetClassInfoW USER_CALL (BOOL, GetClassInfoW, ( \
    HINSTANCE hInstance, LPCWSTR lpClassName, LPWNDCLASSW lpWndClass))

#define GetNextDlgTabItem USER_CALL (HWND, GetNextDlgTabItem, ( \
    HWND hDlg, HWND hCtl, BOOL bPrevious))

#define GetNextDlgGroupItem USER_CALL (HWND, GetNextDlgGroupItem, ( \
    HWND hDlg, HWND hCtl, BOOL bPrevious))

#define CreateDialogIndirectParamW USER_CALL (HWND, CreateDialogIndirectParamW, (  \
    HINSTANCE hInstance, LPCDLGTEMPLATEW lpTemplateName, HWND hWndParent,   \
    DLGPROC lpDialogFunc, LPARAM dwInitParam))

#define IsDialogMessageW USER_CALL (BOOL, IsDialogMessageW, (  \
    HWND hDlg, LPMSG lpMsg))

#define SetDlgItemInt USER_CALL (BOOL, SetDlgItemInt, (  \
    HWND hDlg, int idControl, UINT uValue, BOOL fSigned))

#define GetDlgItemInt USER_CALL (UINT, GetDlgItemInt, (  \
    HWND hDlg, int idControl, BOOL* lpSuccess, BOOL fSigned))

#define CheckRadioButton USER_CALL (BOOL, CheckRadioButton, (  \
    HWND hDlg, int idFirst, int idLast, int idCheck))

#define SendDlgItemMessageW USER_CALL (LONG, SendDlgItemMessageW, ( \
	HWND hDlg, int nIDDlgItem, UINT Msg, WPARAM wParam, LPARAM lParam))

#define SetDlgItemTextW USER_CALL (BOOL, SetDlgItemTextW, ( \
	HWND hDlg, int nIDDlgItem, LPCWSTR lpString))

#define GetDlgItemTextW USER_CALL (UINT, GetDlgItemTextW, ( \
	HWND hDlg, int nIDDlgItem, LPWSTR lpString, int nMaxCount))

#define FindWindowW USER_CALL (HWND, FindWindowW, ( \
    LPCWSTR lpClassName, LPCWSTR lpWindowName))


#define SetTimer USER_CALL (UINT, SetTimer, ( \
			HWND hwnd,                        \
			UINT idTimer,                     \
			UINT uTimeOut,                    \
			TIMERPROC pfnTimerProc))

#define KillTimer USER_CALL (BOOL, KillTimer, (	\
			HWND hwnd,                          \
			UINT idEvent))



#define ExtractIconExW USER_CALL (HICON, ExtractIconExW, ( \
    LPCWSTR lpszExeFileName, int nIconIndex, HICON FAR *phiconLarge, \
    HICON FAR *phiconSmall, UINT nIcons))

#define CreateMenu USER_CALL (HMENU, CreateMenu, ( \
    void))

#define GetSubMenu USER_CALL (HMENU, GetSubMenu, ( \
    HMENU hmenu, int nPos))

#define EnableWindow USER_CALL (BOOL, EnableWindow, ( \
    HWND hwnd, BOOL bEnable))

#define IsWindowEnabled USER_CALL (BOOL, IsWindowEnabled, ( \
    HWND hwnd))

#define DefDlgProcW USER_CALL(LRESULT, DefDlgProcW, ( \
    HWND hDlg, UINT msg, WPARAM wParam, LPARAM lParam))

#define TranslateAcceleratorW USER_CALL (int, TranslateAcceleratorW, (	\
    HWND hWnd,                                                          \
    HACCEL hAccTable,                                                   \
    LPMSG lpMsg))

#define ScrollDC USER_CALL (BOOL, ScrollDC, ( \
    HDC hDC, int dx, int dy, CONST RECT *lprcScroll, CONST RECT *lprcClip, \
    HRGN hrgnUpdate, LPRECT lprcUpdate))

#define ScrollWindowEx USER_CALL (int, ScrollWindowEx, ( \
    HWND hWnd, int dx, int dy, CONST RECT *prcScroll, CONST RECT *prcClip, \
    HRGN hrgnUpdate, LPRECT prcUpdate, UINT flags))

#define OpenClipboard USER_CALL (BOOL, OpenClipboard, ( \
    HWND hWndNewOwner))

#define CloseClipboard USER_CALL (BOOL, CloseClipboard, ( \
    VOID))

#define GetClipboardOwner USER_CALL (HWND, GetClipboardOwner, ( \
    VOID))

#define SetClipboardData USER_CALL (HANDLE, SetClipboardData, ( \
    UINT uFormat,												\
    HANDLE hMem))

#define GetClipboardData USER_CALL (HANDLE, GetClipboardDataStub, ( \
    UINT uFormat))

#define RegisterClipboardFormatW USER_CALL (UINT, RegisterClipboardFormatW, ( \
    LPCWSTR lpszFormat))

#define CountClipboardFormats USER_CALL (int, CountClipboardFormats, ( \
    VOID))

#define EnumClipboardFormats USER_CALL (UINT, EnumClipboardFormats, ( \
    UINT format))

#define GetClipboardFormatNameW USER_CALL (int, GetClipboardFormatNameW, (	\
    UINT format,															\
    LPWSTR lpszFormatName,                                                  \
    int cchMaxCount))

#define EmptyClipboard USER_CALL (BOOL, EmptyClipboard, ( \
    VOID))

#define IsClipboardFormatAvailable USER_CALL (BOOL, IsClipboardFormatAvailable, ( \
    UINT format))

#define GetPriorityClipboardFormat USER_CALL (int, GetPriorityClipboardFormat, (	\
    UINT *paFormatPriorityList,														\
    int cFormats))

#define GetOpenClipboardWindow USER_CALL (HWND, GetOpenClipboardWindow, ( \
    VOID))

#define MessageBeep USER_CALL (BOOL, MessageBeep, ( \
    UINT uType))


#define GetClipboardDataAlloc USER_CALL (HANDLE, GetClipboardDataAllocStub, ( \
    UINT uFormat))



#define SetMenuItemInfoW USER_CALL(BOOL, SetMenuItemInfoW, ( \
    HMENU hMenu, 	    \
    UINT uPosition, 	\
    BOOL fByPosition, 	\
    LPMENUITEMINFO lpmii))

#define GetMenuItemInfoW USER_CALL(BOOL, GetMenuItemInfoW, ( \
    HMENU hMenu, 	    \
    UINT uPosition, 	\
    BOOL fByPosition, 	\
    LPMENUITEMINFO lpmii))



#define GetMessagePos USER_CALL (DWORD, GetMessagePos, ( \
    VOID))

#define SendNotifyMessageW USER_CALL(LRESULT, SendNotifyMessageW, ( \
    HWND hwnd, UINT Msg, WPARAM wParam, LPARAM lParam))



#define PostThreadMessageW USER_CALL(BOOL, PostThreadMessageW, (	\
    DWORD idThread,													\
    UINT Msg,														\
    WPARAM wParam,													\
    LPARAM lParam													\
	))

#define EnumWindows USER_CALL(BOOL, EnumWindows, (	\
	WNDENUMPROC lpEnumFunc,							\
    LPARAM lParam									\
	))

#define GetSystemPowerStatusEx USER_CALL(BOOL, GetSystemPowerStatusEx, ( \
	PSYSTEM_POWER_STATUS_EX pSystemPowerStatusEx, BOOL fUpdate))

#define MapDialogRect USER_CALL(BOOL, MapDialogRect, ( \
    HWND hwnd, LPRECT prc))

#define GetDialogBaseUnits USER_CALL (LONG, GetDialogBaseUnits, (VOID))

#define GetDoubleClickTime USER_CALL (UINT, GetDoubleClickTime, (VOID))

#define GetWindowThreadProcessId USER_CALL (DWORD, GetWindowThreadProcessId, (\
		HWND hwnd, LPDWORD lpdwProcessId))

#define CreateIconIndirect USER_CALL (HICON, CreateIconIndirect, ( \
		PICONINFO piconinfo))

#define SetCursor USER_CALL (HCURSOR, SetCursor, \
		(HCURSOR hCursor))

#define DestroyCursor USER_CALL (BOOL, DestroyCursor, \
		(HCURSOR hCursor))

#define BeginDeferWindowPos USER_CALL(HDWP, BeginDeferWindowPos, \
		(int nNumWindows))

#define DeferWindowPos USER_CALL(HDWP, DeferWindowPos, \
		(HDWP hWinPosInfo, HWND hWnd, HWND hWndInsertAfter, int x, int y, int cx, int cy, UINT uFlags))

#define EndDeferWindowPos USER_CALL(BOOL, EndDeferWindowPos, \
		(HDWP hWinPosInfo))



/*****************  USER OAK EXPORTS *****************/

#define PostKeybdMessage USER_CALL (BOOL, PostKeybdMessage, (	\
     HWND			hwnd,										\
 	UINT			VKey,										\
 	UINT			KeyStateFlags,								\
 	UINT			cCharacters,								\
 	UINT			*pShiftStateBuffer,							\
 	UINT			*pCharacterBuffer))

#define GetMouseMovePoints USER_CALL(BOOL, GetMouseMovePoints, ( \
			PPOINT	pptBuf,				\
			UINT	nBufPoints,			\
			UINT	*pnPointsRetrieved))

#define SystemIdleTimerReset USER_CALL (void, SystemIdleTimerReset, (	\
 	void))

#define SetKeyboardTarget USER_CALL(HWND, SetKeyboardTarget, ( \
 	HWND hwnd))

#define GetKeyboardTarget USER_CALL(HWND, GetKeyboardTarget, ( \
 	VOID))

#define NotifyWinUserSystem USER_CALL(void, NotifyWinUserSystem, ( \
 	UINT	uEvent))


#define NLedGetDeviceInfo USER_CALL (BOOL, NLedGetDeviceInfo, ( \
 	UINT	nInfoId,											\
 	void	*pOutput											\
 	))

#define NLedSetDevice USER_CALL (BOOL, NLedSetDevice, ( \
 	UINT	nInfoId,									\
 	void	*pInput										\
 	))

#define RegisterTaskBar USER_CALL (BOOL, RegisterTaskBar, ( \
	HWND hwndTaskbar))

#define RectangleAnimation USER_CALL(BOOL, RectangleAnimation, ( \
 	HWND hWnd, LPCRECT prc, BOOL fMaximize))

#define ShellModalEnd USER_CALL (VOID, ShellModalEnd, (VOID))


#define GwesPowerOffSystem USER_CALL (void, GwesPowerOffSystem, (void))

#define BatteryGetLifeTimeInfo USER_CALL (BOOL, BatteryGetLifeTimeInfo, \
 		(LPSYSTEMTIME pstLastChange, DWORD * pcmsCpuUsage, \
 		DWORD * pcmsPreviousCpuUsage))
 	
#define BatteryDrvrGetLevels USER_CALL (LONG, BatteryDrvrGetLevels, (void))

#define BatteryDrvrSupportsChangeNotification USER_CALL (BOOL, \
								BatteryDrvrSupportsChangeNotification, (void))

#define BatteryNotifyOfTimeChange USER_CALL (void, BatteryNotifyOfTimeChange, \
 		(BOOL fForward, FILETIME *pftDelta))

#define KeybdGetDeviceInfo USER_CALL (UINT32, KeybdGetDeviceInfo, (	\
	INT		iIndex,													\
	LPVOID  lpOutput												\
	))

#define KeybdInitStates USER_CALL (BOOL, KeybdInitStates, (	\
    KEY_STATE   KeyState,										\
    void        *pKeybdDriverState								\
    ))

#define KeybdVKeyToUnicode USER_CALL (UINT32, KeybdVKeyToUnicode, (	\
    UINT32          VKey,											\
    KEY_STATE_FLAGS KeyEventFlags,									\
    KEY_STATE       KeyState,										\
    void            *KeybdDriverState,								\
    UINT32          cBufferSize,									\
    UINT32          *pcCharacters,									\
    KEY_STATE_FLAGS *pShiftStateBuffer,								\
    UINT32          *pCharacterBuffer								\
    ))

#define mouse_event USER_CALL (VOID, mouse_event, (	\
    DWORD dwFlags,                                  \
    DWORD dx,                                       \
    DWORD dy,                                       \
    DWORD cButtons,                                 \
    DWORD dwExtraInfo								\
	))

#define QASetWindowsJournalHook USER_CALL (HHOOK, QASetWindowsJournalHook, (	\
	int			nFilterType,	\
	HOOKPROC	pfnFilterProc,	\
	EVENTMSG	*pfnEventMsg	\
	))

#define QAUnhookWindowsJournalHook USER_CALL (BOOL, QAUnhookWindowsJournalHook, (	\
	int			nFilterType	\
	))

#define GetMessageWNoWait USER_CALL (BOOL, GetMessageWNoWait, ( \
    PMSG    pMsg,												\
    HWND    hWnd,                                               \
    UINT    wMsgFilterMin,                                      \
    UINT    wMsgFilterMax                                       \
    ))

#define TouchCalibrate USER_CALL (BOOL, TouchCalibrate, (	\
	VOID ))

#define DisableCaretSystemWide USER_CALL (int, DisableCaretSystemWide, (	\
	void ) )

#define EnableCaretSystemWide USER_CALL (int, EnableCaretSystemWide, (	\
	void ) )

#define GetKeyboardStatus USER_CALL (UINT32, GetKeyboardStatus, (	\
		VOID														\
		))

#define EnableHardwareKeyboard USER_CALL (BOOL, EnableHardwareKeyboard, (	\
		BOOL	fEnable														\
		))

#define RegisterSIPanel USER_CALL (BOOL, RegisterSIPanel, ( \
	HWND hwndSIPanel))

#define GetAsyncShiftFlags USER_CALL (KEY_STATE_FLAGS, GetAsyncShiftFlags, ( \
	UINT	VKey))

#define MsgWaitForMultipleObjectsEx USER_CALL (DWORD, MsgWaitForMultipleObjectsEx, ( \
    DWORD nCount,				\
    LPHANDLE pHandles,			\
    BOOL fWaitAll,				\
    DWORD dwMilliseconds,		\
    DWORD dwWakeMask))

#define SetAssociatedMenu USER_CALL (void, SetAssociatedMenu, ( \
	HWND hwnd, \
	HMENU hmenu))

#define GetAssociatedMenu USER_CALL (HMENU, GetAssociatedMenu, ( \
	HWND hwnd))

#define DrawMenuBar USER_CALL (BOOL, DrawMenuBar, ( \
	HWND hwnd))

#define SetSysColors USER_CALL (BOOL, SetSysColors, ( \
    int cElements,                  \
    CONST INT * lpaElements,        \
    CONST COLORREF * lpaRgbValues))

#define DrawFrameControl USER_CALL (BOOL, DrawFrameControl, ( \
    HDC hdc,        \
    LPRECT lprc,    \
    UINT uType,     \
    UINT uState   ))

#define ShowCursor USER_CALL (int, ShowCursor, ( \
	BOOL bShow ))
	
#define SetCursorPos USER_CALL (BOOL, SetCursorPos, ( \
    int X,	\
    int Y))
	
#define GetCursorPos USER_CALL (BOOL, GetCursorPos, ( \
	LPPOINT lpPoint))

#define ClipCursor USER_CALL (BOOL, ClipCursor, ( \
    CONST RECT *lpRect))

#define GetClipCursor USER_CALL (BOOL, GetClipCursor, ( \
    LPRECT lpRect))

#define GetCursor USER_CALL (HCURSOR, GetCursor, ( \
	void))

#define LoadCursorW USER_CALL (HCURSOR, LoadCursorW, ( \
    HINSTANCE hInstance, \
    LPCWSTR lpCursorName))

#define CreateCursor USER_CALL (HCURSOR, CreateCursor, ( \
	HINSTANCE hInst,		\
	int xHotSpot,			\
	int yHotSpot,			\
	int nWidth,				\
	int nHeight,			\
	CONST VOID *pvANDPlane,	\
	CONST VOID *pvXORPlane))


#define RegisterWindowMessageW USER_CALL (UINT, RegisterWindowMessageW, ( \
	LPCTSTR	lpString ))

#define SystemParametersInfo_GWE USER_CALL (BOOL,  SystemParametersInfo_GWE, ( \
	UINT uiAction,	\
	UINT uiParam,	\
	PVOID pvParam,	\
	UINT fWinIni	))

#define SendInput USER_CALL ( UINT, SendInput, (	\
	UINT	nInputs,	\
	LPINPUT	pInputs,	\
	int		cbSize		))


#define GetMessageSource USER_CALL ( UINT, GetMessageSource, (	\
	VOID ))


#define RegisterHotKey USER_CALL ( BOOL, RegisterHotKey, (	\
	HWND	hWnd,			\
	int		id,				\
	UINT	fsModifiers,	\
	UINT	vk ))


#define UnregisterHotKey USER_CALL ( BOOL, UnregisterHotKey, (	\
	HWND	hWnd,	\
	int		id ))


#define UnregisterFunc1 USER_CALL ( BOOL, UnregisterFunc1, ( \
	UINT	fsModifiers,	\
	UINT	vk ))


#define GetDCEx USER_CALL ( HDC, GetDCEx, ( \
	HWND	hwnd,	\
	HRGN	hrgn,	\
	DWORD	flags ))

#define GetKeyboardLayoutNameW USER_CALL ( BOOL, GetKeyboardLayoutNameW, ( \
	WCHAR	*pszNameBuf ))



//	THESE ARE ADDED TO THE GDI API SET.

#define MID_SetWindowsHookExW	98
#define MID_UnhookWindowsHookEx	99
#define MID_GetForegroundInfo	100


#ifndef USER2_CALL
#define USER2_CALL(type, api, args) \
        (*(type (*)args)IMPLICIT_CALL(SH_GDI, MID_ ## api))
#endif


#define SetWindowsHookExW USER2_CALL(HHOOK, SetWindowsHookExW, (	\
	int			idHook,		\
	HOOKPROC	lpfn,		\
	HINSTANCE	hmod,		\
	DWORD		dwThreadId))

#define UnhookWindowsHookEx USER2_CALL (BOOL, UnhookWindowsHookEx, (	\
	HHOOK hhk))

#define GetForegroundInfo USER2_CALL (BOOL, GetForegroundInfo, (	\
	GET_FOREGROUND_INFO	*pfi))


#endif /* !__MWINUSER_H__ */

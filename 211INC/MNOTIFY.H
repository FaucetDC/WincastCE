/*++
THIS CODE AND INFORMATION IS PROVIDED "AS IS" WITHOUT WARRANTY OF
ANY KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED TO
THE IMPLIED WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A
PARTICULAR PURPOSE.
Copyright (c) 1995-1998  Microsoft Corporation

Module Name:  

mnotify.h

Abstract:  

Private portion of notify.h - Header for User Notifications

Notes: 


--*/
#ifndef _MACRO_NOTIFY_H_
#define _MACRO_NOTIFY_H_
    
// SDK functions
#define CeSetUserNotification IMPLICIT_DECL(HANDLE, SH_WMGR, 248, (HANDLE hNotification, TCHAR *pwszAppName, SYSTEMTIME *lpTime, PCE_USER_NOTIFICATION lpUserNotification))
#define CeClearUserNotification IMPLICIT_DECL(BOOL, SH_WMGR, 249, (HANDLE hNotification))
#define CeRunAppAtTime          IMPLICIT_DECL(BOOL, SH_WMGR, 250, (TCHAR *pwszAppName, SYSTEMTIME *lpTime))
#define CeRunAppAtEvent         IMPLICIT_DECL(BOOL, SH_WMGR, 251, (TCHAR *pwszAppName, LONG lWhichEvent))
#define CeHandleAppNotifications IMPLICIT_DECL(BOOL, SH_WMGR, 252, (TCHAR *pwszAppName))
#define CeGetUserNotificationPreferences IMPLICIT_DECL(BOOL, SH_WMGR, 253, (HWND hWndParent, PCE_USER_NOTIFICATION lpNotification))

 // OAK functions
#define CeEventHasOccurred IMPLICIT_DECL(BOOL, SH_WMGR, 254, (LONG lWhichEvent, TCHAR *pwszEndOfCommandLine))
      
#endif /* _MACRO_NOTIFY_H_ */

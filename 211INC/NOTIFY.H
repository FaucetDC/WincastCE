/*++

Copyright (c) 1995-1998 Microsoft Corporation

Module Name:Notify.h

Purpose:Public Header for User Notifications

--*/

#ifndef _NOTIFY_H_
#define _NOTIFY_H_

// @doc NOTIFY

/*
 * Parameters to the CeRunAppAtEvent() API.
 */

#define NOTIFICATION_EVENT_NONE                 0
#define NOTIFICATION_EVENT_TIME_CHANGE          1
#define NOTIFICATION_EVENT_SYNC_END             2
#define NOTIFICATION_EVENT_ON_AC_POWER          3
#define NOTIFICATION_EVENT_OFF_AC_POWER         4
#define NOTIFICATION_EVENT_NET_CONNECT          5
#define NOTIFICATION_EVENT_NET_DISCONNECT       6
#define NOTIFICATION_EVENT_DEVICE_CHANGE        7
#define NOTIFICATION_EVENT_IR_DISCOVERED        8
#define NOTIFICATION_EVENT_RS232_DETECTED       9
#define NOTIFICATION_EVENT_RESTORE_END         10

/*
 * String passed on the command line when an app is run as the result
 * of a call to CeRunAppAtTime().
 */

#define APP_RUN_AT_TIME                 TEXT("AppRunAtTime")

/*
 * Prefix of the command line when the user requests to run the application
 * that "owns" a notification.  It is followed by a space, and the
 * stringized version of the notification handle.
 */

#define APP_RUN_TO_HANDLE_NOTIFICATION  TEXT("AppRunToHandleNotification")

/*
 * Strings passed on the command line when an event occurs that the
 * app has requested via CeRunAppAtEvent.  Note that some of these
 * strings will be used as the command line *prefix*, since the rest
 * of the command line will be used as a parameter.
 */

#define APP_RUN_AFTER_TIME_CHANGE       TEXT("AppRunAfterTimeChange")
#define APP_RUN_AFTER_SYNC              TEXT("AppRunAfterSync")
#define APP_RUN_AT_AC_POWER_ON          TEXT("AppRunAtAcPowerOn")
#define APP_RUN_AT_AC_POWER_OFF         TEXT("AppRunAtAcPowerOff")
#define APP_RUN_AT_NET_CONNECT          TEXT("AppRunAtNetConnect")
#define APP_RUN_AT_NET_DISCONNECT       TEXT("AppRunAtNetDisconnect")
#define APP_RUN_AT_DEVICE_CHANGE        TEXT("AppRunDeviceChange")
#define APP_RUN_AT_IR_DISCOVERY         TEXT("AppRunAtIrDiscovery")
#define APP_RUN_AT_RS232_DETECT         TEXT("AppRunAtRs232Detect")
#define APP_RUN_AFTER_RESTORE           TEXT("AppRunAfterRestore")

/*
 * Strings passed on the end of the command line for the event,
 * NOTIFICATION_EVENT_DEVICE_CHANGE.  The general form will be
 * "/op devicename" for instance "/ADD COM2:"
 */
#define NOTIFY_DEVICE_ADD               TEXT("/ADD")
#define NOTIFY_DEVICE_REMOVE            TEXT("/REMOVE")

/*
 * @struct CE_USER_NOTIFICATION | User Notification Structure
 *
 * @comm  This structure is passed in to <f CeGetUserNotificationPreferences>.
 * Initial settings are used to populate the dialog.  If the function
 * returns TRUE, the returned settings should be saved, and considered when
 * calling <f CeSetUserNotification>.  Settings for hardware not on the
 * current device will be ignored.
 *
 * It is also used when calling <f CeSetUserNotification>, to describe
 * what should happen when the notification time is reached.  
 */

typedef struct UserNotificationType {
    DWORD ActionFlags;      //@field Action Flags.  Any combination of the
                            // PUN_* flags.  Flags not valid on a given
                            // hardware platform will be ignored.
#define PUN_LED     1       //@flag PUN_LED | LED flag.  Set if the LED should be 
                            // flashed when the notification occurs.
#define PUN_VIBRATE 2       //@flag PUN_VIBRATE | Vibrate flag.  Set if the device should
                            // be vibrated.
#define PUN_DIALOG  4       //@flag PUN_DIALOG | Dialog flag.  Set if a dialog should be
                            // displayed (the app must provide title and text
                            // when calling <f CeSetUserNotification>).
#define PUN_SOUND   8       //@flag PUN_SOUND | Sound flag.  Set if the sound specified
                            // in pwszSound should be played.
#define PUN_REPEAT 16       //@flag PUN_REPEAT | Sound repeat flag.  Set if the sound
                            // specified in pwszSound should be repeated
                            // for a short period of time.
    TCHAR *pwszDialogTitle; //@field Dialog Title.  If NULL, no dialog will
                            // be displayed.  Ignored by
                            // CeGetUserNotificationPreferences().
    TCHAR *pwszDialogText;  //@field Dialog Text.  Ignored if Dialog Title is
                            // NULL.  Ignored by
                            // CeGetUserNotificationPreferences().
    TCHAR *pwszSound;       //@field Sound string.  The unqualified (system 
                            // media directory implied) name of a sound file
                            // to play.  CeSetUserNotification() ignores if
                            // PUN_SOUND is not set.
    DWORD nMaxSound;        //@field Max Sound string length.  Specifies the
                            // maximum length of the string that can be copied
                            // into the pwszSound buffer by
                            // CeGetUserNotificationPreferences().  In a 
                            // future release this may be a pathname, so the 
                            // buffer passed in must be at least PATH_MAX *
                            // sizeof(TCHAR)) long.  Ignored by
                            // CeSetUserNotification().
    DWORD dwReserved;       //@field Reserved.  Must be NULL.  In future 
                            // versions, this may point at an expansion
                            // structure.  The first dword of the structure
                            // will indicate the size of the structure.
} CE_USER_NOTIFICATION, *PCE_USER_NOTIFICATION;

/* Declarations of User Notification APIs. */

#ifdef __cplusplus
extern "C" {
#endif //__cplusplus

// @CESYSGEN IF GWES_NOTIFY

HANDLE CeSetUserNotification (HANDLE hNotification, TCHAR *pwszAppName, SYSTEMTIME *lpTime, PCE_USER_NOTIFICATION lpUserNotification);

BOOL CeClearUserNotification (HANDLE hNotification);

BOOL CeRunAppAtTime (TCHAR *pwszAppName, SYSTEMTIME *lpTime);

BOOL CeRunAppAtEvent(TCHAR *pwszAppName, LONG lWhichEvent);

BOOL CeHandleAppNotifications (TCHAR *pwszAppName);

BOOL CeGetUserNotificationPreferences (HWND hWndParent, PCE_USER_NOTIFICATION lpNotification);

// @CESYSGEN ENDIF

#ifdef __cplusplus
}
#endif  //__cplusplus

#ifdef WINCEOEM
#include <pnotify.h>
#ifdef WINCEMACRO
#include <mnotify.h>	// internal defines 
#endif
#endif

#endif /* _NOTIFY_H_ */

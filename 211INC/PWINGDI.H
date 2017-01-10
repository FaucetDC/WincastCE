/*++
THIS CODE AND INFORMATION IS PROVIDED "AS IS" WITHOUT WARRANTY OF
ANY KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED TO
THE IMPLIED WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A
PARTICULAR PURPOSE.
Copyright (c) 1995-1998  Microsoft Corporation

Module Name:  

pwingdi.h

Abstract:

Private portion of wingdi.h

Notes: 


--*/

#ifndef  _PRIV_INC_WINGDI_H
#define  _PRIV_INC_WINGDI_H

#define FLOODFILLBORDER		0
#define FLOODFILLSURFACE	1
#define RC_FLOODFILL        0x1000      /* supports FloodFill           */
#define DT_EDITCONTROL      0x00002000
#define DT_WORD_ELLIPSIS    0x00040000

#include <windbase.h>

#ifdef __cplusplus
extern "C" {
#endif

// Made non-public to prevent ISVs from using it on 2bpp devices.  If they did
// their apps would not work on a color device.
#define PALETTEINDEX(i)     ((COLORREF)(0x01000000 | (DWORD)(WORD)(i)))

// @CESYSGEN IF GWES_MGTT || GWES_MGRAST || GWES_GDIFONTS || GWES_PGDI
WINGDIAPI  BOOL WINAPI CeRemoveFontResource(CEOID);
// @CESYSGEN ENDIF

// GDI Escapes for ExtEscape()
#define QUERYESCSUPPORT				8

// The following are unique to CE
#define GETVFRAMEPHYSICAL			6144
#define GETVFRAMELEN				6145
#define	DBGDRIVERSTAT				6146
#define SETPOWERMANAGEMENT			6147
#define GETPOWERMANAGEMENT			6148


typedef enum _VIDEO_POWER_STATE {
    VideoPowerOn = 1,
    VideoPowerStandBy,
    VideoPowerSuspend,
    VideoPowerOff
} VIDEO_POWER_STATE, *PVIDEO_POWER_STATE;


typedef struct _VIDEO_POWER_MANAGEMENT {
    ULONG Length;
    ULONG DPMSVersion;
    ULONG PowerState;
} VIDEO_POWER_MANAGEMENT, *PVIDEO_POWER_MANAGEMENT;

//
//Length - Length of the structure in bytes. Also used to do verisioning.
//
//DPMSVersion - Version of the DPMS standard supported by the device.
//              Only used in the "GET" IOCTL.
//
//PowerState - One of the power states listed in VIDEO_POWER_STATE.
//



#ifdef __cplusplus
}
#endif

#endif //_PRIV_INC_WINGDI_H

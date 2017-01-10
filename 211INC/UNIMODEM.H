/*++
THIS CODE AND INFORMATION IS PROVIDED "AS IS" WITHOUT WARRANTY OF
ANY KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED TO
THE IMPLIED WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A
PARTICULAR PURPOSE.
Copyright (c) 1995-1998  Microsoft Corporation

Module Name:  

unimodem.h

Abstract:  

Device specific header for unimodem TSPI

Notes: 


--*/

#ifndef _UNIMODEM_H_
#define _UNIMODEM_H_

// DeviceType defines  -- Moved here from modem.h
//
#define DT_NULL_MODEM       0
#define DT_EXTERNAL_MODEM   1
#define DT_INTERNAL_MODEM   2
#define DT_PCMCIA_MODEM     3
#define DT_PARALLEL_PORT    4
#define DT_PARALLEL_MODEM   5
#define DT_IRCOMM_MODEM     6

// The following info is returned from the unimodem GetDevCaps call as the
// device specific data.  The wDeviceType indicates the type of device on
// the port, and the wActive field indicates if the port is currently active.
// This field will normally be 1 for all TAPi device except PCMCIA cards which
// have been removed from the system.
typedef struct  UNIMODEM_INFO {
    WORD        wDeviceType;
    WORD        wActive;
}   UNIMODEM_INFO;

#endif _UNIMODEM_H_

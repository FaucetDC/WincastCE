/*++
THIS CODE AND INFORMATION IS PROVIDED "AS IS" WITHOUT WARRANTY OF
ANY KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED TO
THE IMPLIED WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A
PARTICULAR PURPOSE.
Copyright (c) 1995-1998  Microsoft Corporation

Module Name:  

battery.h

Abstract:  

Interface to the Battery Driver library

Notes: 


--*/
/* 
    @doc DRIVERS

    @module Battery Device Driver | Interface to the Battery Driver library
   
    @topic Battery Driver | The Battery Driver is an object file (battery.obj) 
    that contains the functions and variables declared in Battery.h, 
    which constitute the interface by which GWE gets information about the 
    main and backup batteries and AC power.
*/   
   
#ifndef _BATTERY_H_
#define _BATTERY_H_

#ifdef __cplusplus
extern "C" {
#endif


typedef struct BATTERY_STATUS {
    BYTE  ACLineStatus;
    BYTE  BatteryFlag;
    BYTE  BatteryLifePercent;
    BYTE  Reserved1;
    DWORD BatteryLifeTime;
    DWORD BatteryFullLifeTime;
    BYTE  Reserved2;
    BYTE  BackupBatteryFlag;
    BYTE  BackupBatteryLifePercent;
    BYTE  fBatteriesChangedSinceLastCall;
    DWORD BackupBatteryLifeTime;
    DWORD BackupBatteryFullLifeTime;
}   BATTERY_STATUS, *PBATTERY_STATUS;


/* 
    @func BOOL | BatteryDrvrGetStatus | Return the status of the main and backup
	batteries
    
    @parm PBATTERY_STATUS | pSystemPowerStatusEx | Buffer to be filled 
    in with the battery status information.  See the Win32 Documentation for a
	description of the SYSTEM_POWER_STATUS structure.  

*/    
BOOL WINAPI BatteryDrvrGetStatus (PBATTERY_STATUS pbatterystatus);


/*
	@struct BATTERY_STATUS | contains information about the power status
	of the system.  See the Win32 documentation for SYSTEM_POWER_STATUS for 
	more details.  Defined constants can be found in winbase.h.

    @field BYTE | ACLineStatus | AC power status. Must be one of 
    AC_LINE_OFFLINE, AC_LINE_ONLINE, AC_LINE_BACKUP_POWER, or AC_LINE_UNKNOWN.

    @field BYTE | BatteryFlag | Battery charge status.  Must be one of 
	BATTERY_FLAG_HIGH, BATTERY_FLAG_LOW, BATTERY_FLAG_CRITICAL,
	BATTERY_FLAG_CHARGING, BATTERY_FLAG_NO_BATTERY, or BATTERY_FLAG_UNKNOWN    

    @field BYTE | BatteryLifePercent | Percentage of full battery charge 
    remaining.  Must be in the range 0 to 100, or BATTERY_PERCENTAGE_UNKNOWN.

	@field BYTE | Reserved1 | Must be zero.

    @field DWORD|  BatteryLifeTime | Number of seconds of battery life 
    remaining, or BATTERY_LIFE_UNKNOWN if remaining seconds are unknown.

    @field DWORD| BatteryFullLifeTime | Number of seconds of battery life when 
    at full charge, or BATTERY_LIFE_UNKNOWN if full lifetime is unknown. 

	@field BYTE | Reserved2 | Must be zero.

    @field BYTE | BackupBatteryFlag | Backup battery charge status.  Must be one 
    of BATTERY_FLAG_HIGH, BATTERY_FLAG_LOW, BATTERY_FLAG_CRITICAL,
	BATTERY_FLAG_CHARGING, BATTERY_FLAG_NO_BATTERY, or BATTERY_FLAG_UNKNOWN.   

    @field BYTE | BackupBatteryLifePercent |  Percentage of full backup battery 
    charge remaining.  Must be in the range 0 to 100, or 
    BATTERY_PERCENTAGE_UNKNOWN. 

	@field BYTE | fBatteriesChangedSinceLastCall | TRUE (1) if the batteries
	have been changed since the last time BatteryDrvrGetStatus was called.
	FALSE (zero) otherwise.  Usually, the driver determines this bit as
	follows. When a "Battery Cover Opened" interrupt occurs, the interrupt
	service routine (ISR) sets a global bit. Then the next time
	BatteryDrvrGetStatus is called, if the global bit is set, the driver sets
	fBatteriesChangedSinceLastCall to TRUE and resets the global bit to zero.
	If the global bit was zero, fBatteriesChangedSinceLastCall is set to FALSE.

    @field DWORD| BackupBatteryLifeTime | Number of seconds of backup battery 
    life remaining, or BATTERY_LIFE_UNKNOWN if remaining seconds are unknown.

    @field DWORD| BackupBatteryFullLifeTime | Number of seconds of backup 
    battery life when at full charge, or BATTERY_LIFE_UNKNOWN if full lifetime 
    is unknown. 

*/


/* 
    @func LONG | BatteryDrvrGetLevels | Return the number of levels the battery
    driver is capable of returning in the BatteryFlag and BackupBatteryFlag
	fields of the BATTERY_STATUS structure.
    
	@rdesc The LOWORD of the return value is the number of main battery levels
	which BatteryDrvrGetStatus is capable of returning in the BatteryFlag
	field of the BATTERY_STATUS structure.  For example, if only 
	BATTERY_FLAG_HIGH and BATTERY_FLAG_LOW can be returned, the LOWORD of the 
	return value would be 2.  If BATTERY_FLAG_CRITICAL  can also be returned,
	the LOWORD of the return value would be 3.  The values BATTERY_FLAG_CHARGING, 
	BATTERY_FLAG_NO_BATTERY, or BATTERY_FLAG_UNKNOWN are to be ignored for the 
	purposes of this count.

	The HIWORD of the return value is the number of backup battery levels which
 	BatteryDrvrGetStatus is capable of returning.  The same rules apply as to
	the main battery levels.
*/    
LONG WINAPI BatteryDrvrGetLevels (void);



/* 
    @func BOOL | BatteryDrvrSupportsChangeNotification | Returns whether the 
	hardware can detect when the batteries have been changed.  If FALSE,
	BATTERY_STATUS.fBatteriesChangedSinceLastCall will always be FALSE.
*/
BOOL WINAPI BatteryDrvrSupportsChangeNotification (void);

#ifdef __cplusplus
}
#endif

#endif

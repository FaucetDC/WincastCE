/*++
THIS CODE AND INFORMATION IS PROVIDED "AS IS" WITHOUT WARRANTY OF
ANY KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED TO
THE IMPLIED WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A
PARTICULAR PURPOSE.
Copyright (c) 1995-1998  Microsoft Corporation

Module Name:  

protect.h

Abstract:  

Notes: 


--*/
#ifndef _PROTECT_H_
#define _PROTECT_H_
/*---------------------------------------------------------------------------*\
 * CProtect: class definition
\*---------------------------------------------------------------------------*/
class CProtect
{
public:
	CProtect(LPCRITICAL_SECTION lpcs) : m_lpcs(lpcs)
		{ EnterCriticalSection(m_lpcs); }
	~CProtect() { LeaveCriticalSection(m_lpcs); }

private:
	LPCRITICAL_SECTION m_lpcs;
	
}; /* CProtect */

typedef CProtect PROTECT;
#endif _PROTECT_H_

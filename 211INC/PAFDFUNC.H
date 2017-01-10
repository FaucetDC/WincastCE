/*++
THIS CODE AND INFORMATION IS PROVIDED "AS IS" WITHOUT WARRANTY OF
ANY KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED TO
THE IMPLIED WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A
PARTICULAR PURPOSE.
Copyright (c) 1995-1998  Microsoft Corporation

Module Name:  

pafdfunc.h

Abstract:

Private version of afdfunc.h

Notes: 


--*/
  
#ifndef _PAFDFUNC_H_
#define _PAFDFUNC_H_

SOCKHAND AFDSocket(DWORD AddressFamily, DWORD SocketType, DWORD Protocol);

DWORD AFDControl(DWORD Protocol, DWORD Action, LPVOID InputBuffer,
				 LPDWORD InputBufferLength, LPVOID OutputBuffer,
				 LPDWORD OutputBufferLength);

DWORD AFDEnumProtocolsW(LPDWORD lpiProtocols, LPVOID lpProtocolBuffer,
						LPDWORD	lpdwBufferLength);

DWORD AFDGetHostentByAttr(LPSOCK_THREAD pThread, LPSTR Name,
						  LPBYTE Address);

DWORD AFDAddIPHostent(LPWSTR Hostname, char **IpAddr, LPWSTR Aliases,
					  LPFILETIME lpFileTime);

DWORD RasIOControl(LPVOID hRasConn, DWORD dwCode, PBYTE pBufIn,
				   DWORD dwLenIn, PBYTE pBufOut, DWORD dwLenOut,
				   PDWORD pdwActualOut);

DWORD AFDSelect(UINT ReadCount, LPSOCK_LIST ReadList, UINT WriteCount,
				LPSOCK_LIST WriteList, UINT ExceptCount,
				LPSOCK_LIST ExceptList, const struct timeval *timeout,
				CRITICAL_SECTION *pDllCS);


DWORD AFDAddResolver(DWORD CONTEXT, BOOL fDNS, BOOL fDelete, DWORD IpAddr);

DWORD NETbios(DWORD x1, DWORD dwOpCode, PVOID pNCB, DWORD cBuf1,
			  PBYTE pBuf1, DWORD cBuf2, PDWORD pBuf2);


#endif // __PAFDFUNC.H

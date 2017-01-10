/*++
THIS CODE AND INFORMATION IS PROVIDED "AS IS" WITHOUT WARRANTY OF
ANY KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED TO
THE IMPLIED WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A
PARTICULAR PURPOSE.
Copyright (c) 1995-1998  Microsoft Corporation

Module Name:  

ptapi.h

Abstract:

Private portion of tapi.h

Notes: 


--*/
#ifndef PTAPI_H
#define PTAPI_H

LONG WINAPI lineClose(HLINE hLine);

LONG WINAPI lineDeallocateCall(HCALL hCall);

LONG WINAPI lineDrop(HCALL hCall, LPCTSTR lpsUserUserInfo, DWORD dwSize);

LONG WINAPI lineGetDevCaps(HLINEAPP hLineApp, DWORD dwDeviceID, 
					DWORD dwAPIVersion, DWORD dwExtVersion, 
					LPLINEDEVCAPS lpLineDevCaps);

LONG WINAPI lineGetDevConfig(DWORD dwDeviceID, LPVARSTRING lpDeviceConfig, 
					  LPCTSTR lpszDeviceClass);


LONG WINAPI lineGetTranslateCaps(HLINEAPP hLineApp, DWORD dwAPIVersion, 
						  LPLINETRANSLATECAPS lpTranslateCaps);

LONG WINAPI lineInitialize(LPHLINEAPP lphLineApp, HINSTANCE hInstance, 
					LINECALLBACK lpfnCallback, LPCTSTR lpszAppName, 
					LPDWORD lpdwNumDevs);

LONG WINAPI lineMakeCall(HLINE hLine, LPHCALL lphCall, LPCTSTR lpszDestAddress, 
				  DWORD dwCountryCode, LPLINECALLPARAMS const lpCallParams);

LONG WINAPI lineNegotiateAPIVersion(HLINEAPP hLineApp, DWORD dwDeviceID, 
							 DWORD dwAPILowVersion, DWORD dwAPIHighVersion, 
							 LPDWORD lpdwAPIVersion,
							 LPLINEEXTENSIONID lpExtensionID);

LONG WINAPI lineOpen(HLINEAPP hLineApp, DWORD dwDeviceID, LPHLINE lphLine,
			  DWORD dwAPIVersion, DWORD dwExtVersion, 
			  DWORD dwCallbackInstance, DWORD dwPrivileges, 
			  DWORD dwMediaModes, LPLINECALLPARAMS const lpCallParams);

LONG WINAPI lineSetDevConfig(DWORD dwDeviceID, LPVOID const lpDeviceConfig, 
					  DWORD dwSize, LPCTSTR lpszDeviceClass);

LONG WINAPI lineSetStatusMessages(HLINE hLine, DWORD dwLineStates, 
						   DWORD dwAddressStates);

LONG WINAPI lineShutdown(HLINEAPP hLineApp);

LONG WINAPI lineTranslateAddress(HLINEAPP hLineApp, DWORD dwDeviceID, 
						  DWORD dwAPIVersion, LPCTSTR lpszAddressIn, 
						  DWORD dwCard, DWORD dwTranslateOptions,
						  LPLINETRANSLATEOUTPUT lpTranslateOutput);

LONG WINAPI lineTranslateDialog(HLINEAPP hLineApp, DWORD dwDeviceID, 
						 DWORD dwAPIVersion, HWND hwndOwner,
						 LPCTSTR lpszAddressIn);

LONG WINAPI lineConfigDialogEdit(DWORD dwDeviceID, HWND hwndOwner, 
						  LPCTSTR lpszDeviceClass,
						  LPVOID const lpDeviceConfigIn, 
						  DWORD dwSize, LPVARSTRING lpDeviceConfigOut);

LONG WINAPI lineGetID(HLINE hLine, DWORD dwAddressID, HCALL hCall,          
			   DWORD dwSelect, LPVARSTRING lpDeviceID,               
			   LPCTSTR lpszDeviceClass);

#endif // PTAPI_H


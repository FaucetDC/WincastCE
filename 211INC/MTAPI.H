/*++
THIS CODE AND INFORMATION IS PROVIDED "AS IS" WITHOUT WARRANTY OF
ANY KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED TO
THE IMPLIED WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A
PARTICULAR PURPOSE.
Copyright (c) 1995-1998  Microsoft Corporation

Module Name:  

mtapi.h

Abstract:  

Notes: 


--*/
#ifndef MTAPI_H
#define MTAPI_H

#ifndef WINCEMACRO
#error WINCEMACRO not defined __FILE__
#endif

#define lineClose IMPLICIT_DECL (LONG, SH_TAPI, 2,			 		\
			(HLINE hLine))

#define lineConfigDialogEdit IMPLICIT_DECL (LONG, SH_TAPI, 3,		\
			(DWORD dwDeviceID, HWND hwndOwner, 						\
			 LPCTSTR lpszDeviceClass, LPVOID const lpDeviceConfigIn, \
			 DWORD dwSize, LPVARSTRING lpDeviceConfigOut))

#define lineDeallocateCall IMPLICIT_DECL (LONG, SH_TAPI, 4,			\
			(HCALL hCall))

#define lineDrop IMPLICIT_DECL (LONG, SH_TAPI, 5,					\
			(HCALL hCall, LPCTSTR lpsUserUserInfo, DWORD dwSize))

#define lineGetDevCaps IMPLICIT_DECL (LONG, SH_TAPI, 6,				\
			(HLINEAPP hLineApp, DWORD dwDeviceID, 					\
			 DWORD dwAPIVersion, DWORD dwExtVersion, 				\
			 LPLINEDEVCAPS lpLineDevCaps))

#define lineGetDevConfig IMPLICIT_DECL (LONG, SH_TAPI, 7,			\
			 (DWORD dwDeviceID, LPVARSTRING lpDeviceConfig, 		\
			  LPCTSTR lpszDeviceClass))
    

#define lineGetTranslateCaps IMPLICIT_DECL (LONG, SH_TAPI, 8,		\
			(HLINEAPP hLineApp, DWORD dwAPIVersion, 				\
			 LPLINETRANSLATECAPS lpTranslateCaps))

#define TAPIlineInitialize IMPLICIT_DECL (LONG, SH_TAPI, 9,			\
			(LPHLINEAPP lphLineApp, HINSTANCE hInstance, 			\
			 HWND hWind, LPCTSTR lpszAppName,				 		\
			 LPDWORD lpdwNumDevs))

#define lineMakeCall IMPLICIT_DECL (LONG, SH_TAPI, 10,				\
			(HLINE hLine, LPHCALL lphCall, LPCTSTR lpszDestAddress, 	\
			 DWORD dwCountryCode, LPLINECALLPARAMS const lpCallParams))

#define lineNegotiateAPIVersion IMPLICIT_DECL (LONG, SH_TAPI, 11,	\
			(HLINEAPP hLineApp, DWORD dwDeviceID, 					\
			 DWORD dwAPILowVersion, DWORD dwAPIHighVersion, 		\
			 LPDWORD lpdwAPIVersion, LPLINEEXTENSIONID lpExtensionID))

#define lineOpen IMPLICIT_DECL (LONG, SH_TAPI, 12,					\
			(HLINEAPP hLineApp, DWORD dwDeviceID, LPHLINE lphLine,	\
			 DWORD dwAPIVersion, DWORD dwExtVersion, 				\
			 DWORD dwCallbackInstance, DWORD dwPrivileges, 			\
			 DWORD dwMediaModes, LPLINECALLPARAMS const lpCallParams))

#define lineSetDevConfig IMPLICIT_DECL (LONG, SH_TAPI, 13,			\
			 (DWORD dwDeviceID, LPVOID const lpDeviceConfig, 		\
			  DWORD dwSize, LPCTSTR lpszDeviceClass))

#define lineSetStatusMessages IMPLICIT_DECL (LONG, SH_TAPI, 14,		\
			 (HLINE hLine, DWORD dwLineStates, 						\
			  DWORD dwAddressStates))

#define TAPIlineShutdown IMPLICIT_DECL (LONG, SH_TAPI, 15,			\
			(HLINEAPP hLineApp))

#define lineTranslateAddress IMPLICIT_DECL (LONG, SH_TAPI, 16,		\
			(HLINEAPP hLineApp, DWORD dwDeviceID, 					\
			 DWORD dwAPIVersion, LPCTSTR lpszAddressIn, 			\
			 DWORD dwCard, DWORD dwTranslateOptions,				\
			 LPLINETRANSLATEOUTPUT lpTranslateOutput))

#define lineTranslateDialog IMPLICIT_DECL (LONG, SH_TAPI, 17,		\
			 (HLINEAPP hLineApp, DWORD dwDeviceID, 					\
			  DWORD dwAPIVersion, HWND hwndOwner, LPCTSTR lpszAddressIn))

#define lineGetID IMPLICIT_DECL (LONG, SH_TAPI, 18,			        \
             (HLINE hLine, DWORD dwAddressID, HCALL hCall,          \
              DWORD dwSelect, LPVARSTRING lpDeviceID,               \
              LPCTSTR lpszDeviceClass))

#define lineAddProvider IMPLICIT_DECL (LONG, SH_TAPI, 19,	        \
             (LPCTSTR lpszProviderFilename,							\
			  HWND hwndOwner,										\
			  LPDWORD lpdwPermanentProviderID))

#define lineSetCurrentLocation IMPLICIT_DECL (LONG, SH_TAPI, 20,	\
             (HLINEAPP hLineApp,                                    \
              DWORD dwLocation))
    
#endif // MTAPI_H


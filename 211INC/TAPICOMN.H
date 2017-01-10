/*++
THIS CODE AND INFORMATION IS PROVIDED "AS IS" WITHOUT WARRANTY OF
ANY KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED TO
THE IMPLIED WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A
PARTICULAR PURPOSE.
Copyright (c) 1995-1998  Microsoft Corporation
Portions Copyright Intel/Microsoft 1992-93.  All Rights Reserved.

Module Name:  

tapicomm.h

Abstract:  

Notes: 


--*/
#ifndef TAPICOMN_H
#define TAPICOMN_H

typedef LONG (TSPIAPI * TSPI_LINEGETPROCTABLE)(void *lplpTspiProcs) ;

//
// vtbl and associated typedefs for the tspi functions.
//
typedef struct tag_TSPI_PROCS {
    LONG (TSPIAPI * TSPI_lineAccept) (
        DRV_REQUESTID  dwRequestID,
        HDRVCALL       hdCall,
        LPCTSTR        lpsUserUserInfo,
        DWORD          dwSize);

    LONG (TSPIAPI * TSPI_lineAddToConference) (
        DRV_REQUESTID  dwRequestID,
        HDRVCALL       hdConfCall,
        HDRVCALL       hdConsultCall);

    LONG (TSPIAPI * TSPI_lineAnswer) (
        DRV_REQUESTID  dwRequestID,
        HDRVCALL       hdCall,
        LPCTSTR        lpsUserUserInfo,
        DWORD          dwSize);

    LONG (TSPIAPI * TSPI_lineBlindTransfer) (
        DRV_REQUESTID  dwRequestID,
        HDRVCALL       hdCall,
        LPCTSTR        lpszDestAddress,
        DWORD          dwCountryCode);

    LONG (TSPIAPI * TSPI_lineClose) (
        HDRVLINE  hdLine);

    LONG (TSPIAPI * TSPI_lineCloseCall) (
        HDRVCALL  hdCall);

    LONG (TSPIAPI * TSPI_lineCompleteCall) (
        DRV_REQUESTID  dwRequestID,
        HDRVCALL       hdCall,
        LPDWORD        lpdwCompletionID,
        DWORD          dwCompletionMode,
        DWORD          dwMessageID);

    LONG (TSPIAPI * TSPI_lineCompleteTransfer) (
        DRV_REQUESTID  dwRequestID,
        HDRVCALL       hdCall,
        HDRVCALL       hdConsultCall,
        HTAPICALL      htConfCall,
        LPHDRVCALL     lphdConfCall,
        DWORD          dwTransferMode);

    LONG (TSPIAPI * TSPI_lineConditionalMediaDetection) (
        HDRVLINE          hdLine,
        DWORD             dwMediaModes,
        LPLINECALLPARAMS  lpCallParams);

    LONG (TSPIAPI * TSPI_lineConfigDialog) (
        DWORD   dwDeviceID,
        HWND    hwndOwner,
        LPCTSTR  lpszDeviceClass);

    LONG (TSPIAPI * TSPI_lineDevSpecific) (
        DRV_REQUESTID  dwRequestID,
        HDRVLINE       hdLine,
        DWORD          dwAddressID,
        HDRVCALL       hdCall,
        LPVOID         lpParams,
        DWORD          dwSize);

    LONG (TSPIAPI * TSPI_lineDevSpecificFeature) (
        DRV_REQUESTID  dwRequestID,
        HDRVLINE       hdLine,
        DWORD          dwFeature,
        LPVOID         lpParams,
        DWORD          dwSize);

    LONG (TSPIAPI * TSPI_lineDial) (
        DRV_REQUESTID  dwRequestID,
        HDRVCALL       hdCall,
        LPCTSTR        lpszDestAddress,
        DWORD          dwCountryCode);

    LONG (TSPIAPI * TSPI_lineDrop) (
        DRV_REQUESTID  dwRequestID,
        HDRVCALL       hdCall,
        LPCTSTR        lpsUserUserInfo,
        DWORD          dwSize);

    LONG (TSPIAPI * TSPI_lineForward) (
        DRV_REQUESTID     dwRequestID,
        HDRVLINE          hdLine,
        DWORD             bAllAddresses,
        DWORD             dwAddressID,
        LPLINEFORWARDLIST const lpForwardList,
        DWORD             dwNumRingsNoAnswer,
        HTAPICALL         htConsultCall,
        LPHDRVCALL        lphdConsultCall,
        LPLINECALLPARAMS  const lpCallParams);

    LONG (TSPIAPI * TSPI_lineGatherDigits) (
        HDRVCALL       hdCall,
        DWORD          dwEndToEndID,
        DWORD          dwDigitModes,
        LPSTR          lpsDigits,
        DWORD          dwNumDigits,
        LPCTSTR        lpszTerminationDigits,
        DWORD          dwFirstDigitTimeout,
        DWORD          InterDigitTimeout);

    LONG (TSPIAPI * TSPI_lineGenerateDigits) (
        HDRVCALL       hdCall,
        DWORD          dwEndToEndID,
        DWORD          dwDigitMode,
        LPCTSTR        lpszDigits,
        DWORD          dwDuration);

    LONG (TSPIAPI * TSPI_lineGenerateTone) (
        HDRVCALL            hdCall,
        DWORD               dwEndToEndID,
        DWORD               dwToneMode,
        DWORD               dwDuration,
        DWORD               dwNumTones,
        LPLINEGENERATETONE  const lpTones);

    LONG (TSPIAPI * TSPI_lineGetAddressCaps) (
        DWORD              dwDeviceID,
        DWORD              dwAddressID,
        DWORD              dwTSPIVersion,
        DWORD              dwExtVersion,
        LPLINEADDRESSCAPS  lpAddressCaps);

    LONG (TSPIAPI * TSPI_lineGetAddressID) (
        HDRVLINE       hdLine,
        LPDWORD        lpdwAddressID,
        DWORD          dwAddressMode,
        LPCTSTR        lpsAddress,
        DWORD          dwSize);

    LONG (TSPIAPI * TSPI_lineGetAddressStatus) (
        HDRVLINE             hdLine,
        DWORD                dwAddressID,
        LPLINEADDRESSSTATUS  lpAddressStatus);

    LONG (TSPIAPI * TSPI_lineGetCallAddressID) (
        HDRVCALL  hdCall,
        LPDWORD   lpdwAddressID);

    LONG (TSPIAPI * TSPI_lineGetCallInfo) (
        HDRVCALL        hdCall,
        LPLINECALLINFO  lpCallInfo);

    LONG (TSPIAPI * TSPI_lineGetCallStatus) (
        HDRVCALL          hdCall,
        LPLINECALLSTATUS  lpCallStatus);

    LONG (TSPIAPI * TSPI_lineGetDevCaps) (
        DWORD          dwDeviceID,
        DWORD          dwTSPIVersion,
        DWORD          dwExtVersion,
        LPLINEDEVCAPS  lpLineDevCaps);

    LONG (TSPIAPI * TSPI_lineGetDevConfig) (
        DWORD dwDeviceID,
        LPVARSTRING lpDeviceConfig,
        LPCTSTR     lpszDeviceClass);

    LONG (TSPIAPI * TSPI_lineGetExtensionID) (
        DWORD              dwDeviceID,
        DWORD              dwTSPIVersion,
        LPLINEEXTENSIONID  lpExtensionID);

    LONG (TSPIAPI * TSPI_lineGetIcon) (
        DWORD    dwDeviceID,
        LPCTSTR  lpszDeviceClass,
        LPHICON  lphIcon);

    LONG (TSPIAPI * TSPI_lineGetID) (
        HDRVLINE       hdLine,
        DWORD          dwAddressID,
        HDRVCALL       hdCall,
        DWORD          dwSelect,
        LPVARSTRING    lpDeviceID,
        LPCTSTR        lpszDeviceClass);
    
    LONG (TSPIAPI * TSPI_lineGetLineDevStatus) (
        HDRVLINE         hdLine,
        LPLINEDEVSTATUS  lpLineDevStatus);

    LONG (TSPIAPI * TSPI_lineGetNumAddressIDs) (
        HDRVLINE    hdLine,
        LPDWORD     lpdwNumAddressIDs);

    LONG (TSPIAPI * TSPI_lineHold) (
        DRV_REQUESTID  dwRequestID,
        HDRVCALL       hdCall);

    LONG (TSPIAPI * TSPI_lineMakeCall) (
        DRV_REQUESTID     dwRequestID,
        HDRVLINE          hdLine,
        HTAPICALL         htCall,
        LPHDRVCALL        lphdCall,
        LPCTSTR           lpszDestAddress,
        DWORD             dwCountryCode,
        LPLINECALLPARAMS  const lpCallParams);

    LONG (TSPIAPI * TSPI_lineMonitorDigits) (
        HDRVCALL       hdCall,
        DWORD          dwDigitModes);

    LONG (TSPIAPI * TSPI_lineMonitorMedia) (
        HDRVCALL       hdCall,
        DWORD          dwMediaModes);

    LONG (TSPIAPI * TSPI_lineMonitorTones) (
        HDRVCALL           hdCall,
        DWORD              dwToneListID,
        LPLINEMONITORTONE  const lpToneList,
        DWORD              dwNumEntries);

    LONG (TSPIAPI * TSPI_lineNegotiateExtVersion) (
        DWORD    dwDeviceID,
        DWORD    dwTSPIVersion,
        DWORD    dwLowVersion,
        DWORD    dwHighVersion,
        LPDWORD  lpdwExtVersion);

    LONG (TSPIAPI * TSPI_lineNegotiateTSPIVersion) (
        DWORD    dwDeviceID,
        DWORD    dwLowVersion,
        DWORD    dwHighVersion,
        LPDWORD  lpdwTSPIVersion);

    LONG (TSPIAPI * TSPI_lineOpen) (
        DWORD       dwDeviceID,
        HTAPILINE   htLine,
        LPHDRVLINE  lphdLine,
        DWORD       dwTSPIVersion,
        LINEEVENT   lineEventProc);

    LONG (TSPIAPI * TSPI_linePark) (
        DRV_REQUESTID  dwRequestID,
        HDRVCALL       hdCall,
        DWORD          dwParkMode,
        LPCTSTR        lpszDirAddress,
        LPVARSTRING    lpNonDirAddress);

    LONG (TSPIAPI * TSPI_linePickup) (
        DRV_REQUESTID  dwRequestID,
        HDRVLINE       hdLine,
        DWORD          dwAddressID,
        HTAPICALL      htCall,
        LPHDRVCALL     lphdCall,
        LPCTSTR        lpszDestAddress,
        LPCTSTR        lpszGroupID);

    LONG (TSPIAPI * TSPI_linePrepareAddToConference) (
        DRV_REQUESTID     dwRequestID,
        HDRVCALL          hdConfCall,
        HTAPICALL         htConsultCall,
        LPHDRVCALL        lphdConsultCall,
        LPLINECALLPARAMS  const lpCallParams);

    LONG (TSPIAPI * TSPI_lineRedirect) (
        DRV_REQUESTID  dwRequestID,
        HDRVCALL       hdCall,
        LPCTSTR        lpszDestAddress,
        DWORD          dwCountryCode);

    LONG (TSPIAPI * TSPI_lineRemoveFromConference) (
        DRV_REQUESTID  dwRequestID,
        HDRVCALL       hdCall);

    LONG (TSPIAPI * TSPI_lineSecureCall) (
        DRV_REQUESTID  dwRequestID,
        HDRVCALL       hdCall);

    LONG (TSPIAPI * TSPI_lineSelectExtVersion) (
        HDRVLINE  hdLine,
        DWORD     dwExtVersion);

    LONG (TSPIAPI * TSPI_lineSendUserUserInfo) (
        DRV_REQUESTID  dwRequestID,
        HDRVCALL       hdCall,
        LPCTSTR        lpsUserUserInfo,
        DWORD          dwSize);

    LONG (TSPIAPI * TSPI_lineSetAppSpecific) (
        HDRVCALL       hdCall,
        DWORD          dwAppSpecific);

    LONG (TSPIAPI * TSPI_lineSetCallParams) (
        DRV_REQUESTID     dwRequestID,
        HDRVCALL          hdCall,
        DWORD             dwBearerMode,
        DWORD             dwMinRate,
        DWORD             dwMaxRate,
        LPLINEDIALPARAMS  lpDialParams);

    LONG (TSPIAPI * TSPI_lineSetDefaultMediaDetection) (
        HDRVLINE       hdLine,
        DWORD          dwMediaModes);

    LONG (TSPIAPI * TSPI_lineSetDevConfig) (
        DWORD dwDeviceID,
        LPVOID const lpDeviceConfig,
        DWORD dwSize,
        LPCTSTR lpszDeviceClass);

    LONG (TSPIAPI * TSPI_lineSetMediaControl) (
        HDRVLINE                     hdLine,
        DWORD                        dwAddressID,
        HDRVCALL                     hdCall,
        DWORD                        dwSelect,
        LPLINEMEDIACONTROLDIGIT      const lpDigitList,
        DWORD                        dwDigitNumEntries,
        LPLINEMEDIACONTROLMEDIA      const lpMediaList,
        DWORD                        dwMediaNumEntries,
        LPLINEMEDIACONTROLTONE       const lpToneList,
        DWORD                        dwToneNumEntries,
        LPLINEMEDIACONTROLCALLSTATE  const lpCallStateList,
        DWORD                        dwCallStateNumEntries);

    LONG (TSPIAPI * TSPI_lineSetMediaMode) (
        HDRVCALL       hdCall,
        DWORD          dwMediaMode);

    LONG (TSPIAPI * TSPI_lineSetStatusMessages) (
        HDRVLINE       hdLine,
        DWORD          dwLineStates,
        DWORD          dwAddressStates);

    LONG (TSPIAPI * TSPI_lineSetTerminal) (
        DRV_REQUESTID  dwRequestID,
        HDRVLINE       hdLine,
        DWORD          dwAddressID,
        HDRVCALL       hdCall,
        DWORD          dwSelect,
        DWORD          dwTerminalModes,
        DWORD          dwTerminalID,
        DWORD           bEnable);

    LONG (TSPIAPI * TSPI_lineSetupConference) (
        DRV_REQUESTID     dwRequestID,
        HDRVCALL          hdCall,
        HDRVLINE          hdLine,
        HTAPICALL         htConfCall,
        LPHDRVCALL        lphdConfCall,
        HTAPICALL         htConsultCall,
        LPHDRVCALL        lphdConsultCall,
        DWORD             dwNumParties,
        LPLINECALLPARAMS  const lpCallParams);

    LONG (TSPIAPI * TSPI_lineSetupTransfer) (
        DRV_REQUESTID     dwRequestID,
        HDRVCALL          hdCall,
        HTAPICALL         htConsultCall,
        LPHDRVCALL        lphdConsultCall,
        LPLINECALLPARAMS  const lpCallParams);

    LONG (TSPIAPI * TSPI_lineSwapHold) (
        DRV_REQUESTID  dwRequestID,
        HDRVCALL       hdActiveCall,
        HDRVCALL       hdHeldCall);

    LONG (TSPIAPI * TSPI_lineUncompleteCall) (
        DRV_REQUESTID  dwRequestID,
        HDRVLINE       hdLine,
        DWORD          dwCompletionID);

    LONG (TSPIAPI * TSPI_lineUnhold) (
        DRV_REQUESTID  dwRequestID,
        HDRVCALL       hdCall);

    LONG (TSPIAPI * TSPI_lineUnpark) (
        DRV_REQUESTID  dwRequestID,
        HDRVLINE       hdLine,
        DWORD          dwAddressID,
        HTAPICALL      htCall,
        LPHDRVCALL     lphdCall,
        LPCTSTR        lpszDestAddress);


    LONG (TSPIAPI * TSPI_providerConfig) (
        HWND   hwndOwner,
        DWORD  dwPermanentProviderID);

    LONG (TSPIAPI * TSPI_providerInit) (
        DWORD             dwTSPIVersion,
        DWORD             dwPermanentProviderID,
        DWORD             dwLineDeviceIDBase,
        DWORD             dwNumLines,
        ASYNC_COMPLETION  cbCompletionProc,
        LPDWORD           lpdwTSPIOptions);

    LONG (TSPIAPI * TSPI_providerInstall) (
        HWND   hwndOwner,
        DWORD  dwPermanentProviderID);

    LONG (TSPIAPI * TSPI_providerRemove) (
        HWND   hwndOwner,
        DWORD  dwPermanentProviderID);

    LONG (TSPIAPI * TSPI_providerShutdown) (
        DWORD    dwTSPIVersion);

    LONG (TSPIAPI * TSPI_providerEnumDevices) (
        DWORD    dwPermanentProviderID,
        LPDWORD  lpdwNumLines,
        HPROVIDER  hProvider,
        LINEEVENT  lpfnLineCreateProc);

    LONG (TSPIAPI * TSPI_lineDropOnClose) (
        HDRVCALL       hdCall);

    LONG (TSPIAPI * TSPI_lineDropNoOwner) (
        HDRVCALL       hdCall);

    LONG (TSPIAPI * TSPI_providerCreateLineDevice)(
        HKEY    hActiveKey,
        LPCTSTR lpszDevPath,
        LPCTSTR lpszDeviceName);

    LONG (TSPIAPI * TSPI_providerDeleteLineDevice)(
        DWORD      dwIdentifier);

    LONG (TSPIAPI * TSPI_lineSetCurrentLocation)(
        DWORD       dwLocation);

    LONG (TSPIAPI * TSPI_lineConfigDialogEdit) (
        DWORD   dwDeviceID,
        HWND    hwndOwner,
        LPCTSTR  lpszDeviceClass,
        LPVOID  const lpDeviceConfigIn,
        DWORD   dwSize,
        LPVARSTRING lpDeviceConfigOut);

    LONG (TSPIAPI * TSPI_lineReleaseUserUserInfo) (
        DRV_REQUESTID  dwRequestID,
        HDRVCALL       hdCall);
} TSPI_PROCS;

typedef TSPI_PROCS FAR * LPTSPI_PROCS;

typedef struct {
    HINSTANCE         provider_instance;
    DWORD             dwNegotiatedTSPIVersion;
    DWORD             dwProviderPermanentID;
    TSPI_PROCS        tspi_procs;          
} TAPIDRIVER_INFO;

typedef TAPIDRIVER_INFO FAR * LPTAPIDRIVER_INFO;
typedef LPTAPIDRIVER_INFO FAR * LPLPTAPIDRIVER_INFO;

// The following macros are used to identify the type of the handle in the
// Asynchronous request table. They are also used at runtime to check if the
// APP passed the correct handle type to TAPI.
#define ANY_RT_HLINE           202
#define ANY_RT_HLINEAPP        203
#define ANY_RT_HCALL           204 

#define TAPI_SUCCESS_RETURN    0L

#define IS_OPERATION_SYNCH(retval)  ( ((retval) > 0) ? FALSE : TRUE )  
 // Used to find out if an operation is synchronous or not

// The following macros are useful for indicating the completion type of the
// various TSPI functions.
#define OPERATION_IS_SYNCH   1
#define OPERATION_IS_ASYNCH  2

#define IsOnlyOneBitSetInWORD(target)    (! ( LOWORD((target)) & (LOWORD((target)) - 1) ))
// This macro returns TRUE iff one bit is set in the target parameter. If no 
// bit is set or more than one bits are set, then the function returns a FALSE.

#define IsOnlyOneBitSetInDWORD(target)    (! ( ((DWORD)(target)) & (((DWORD)(target)) - 1) ))

#define ALL_Fs             0xFFFFFFFF
#define WORD_Fs            0x0000FFFF
#undef LOWORD
#define LOWORD(l)          ((WORD)(((DWORD)(l)) & WORD_Fs))

// The following macro is used to find out if a selection of bits is part of
#define IS_INVAL_TAPI_WORD_MODE(bitarray, selection)       \
((!(LOWORD((selection)))) ||       \
 ((LOWORD(~(bitarray))) & (selection)))

#define IS_INVAL_TAPI_DWORD_MODE(bitarray, selection)       \
((!((selection))) ||       \
 ((~(bitarray)) & (selection)))

#define IS_INVAL_EXCL_TAPI_WORD_MODE(bitarray, selection)    \
(!IsOnlyOneBitSetInWORD((selection)) ||    \
 IS_INVAL_TAPI_WORD_MODE( (bitarray), (selection)))
                                
#define IS_INVAL_EXCL_TAPI_DWORD_MODE(bitarray, selection)  \
(!IsOnlyOneBitSetInDWORD((selection)) ||   \
 IS_INVAL_TAPI_DWORD_MODE( (bitarray), (selection)))

#define IS_INVAL_EXCL_TAPI_EXTN_WORD_MODE(bitarray, selection)  \
((!(IsOnlyOneBitSetInDWORD((selection)))) || \
 (LOWORD((selection)) &&                      \
  (IS_INVAL_EXCL_TAPI_WORD_MODE((bitarray),(selection)))))




#define FExtendedMediaMode(dwMediaMode) \
((dwMediaMode >= 0x01000000) && (dwMediaMode <= 0x80000000))
#define FOneBitOn(dw) IsOnlyOneBitSetInDWORD(dw)

#define FLineMediaMode(dwMediaMode) \
(       dwMediaMode == LINEMEDIAMODE_UNKNOWN                \
        || dwMediaMode == LINEMEDIAMODE_INTERACTIVEVOICE    \
        || dwMediaMode == LINEMEDIAMODE_AUTOMATEDVOICE      \
        || dwMediaMode == LINEMEDIAMODE_DATAMODEM               \
        || dwMediaMode == LINEMEDIAMODE_G3FAX                   \
        || dwMediaMode == LINEMEDIAMODE_TDD                     \
        || dwMediaMode == LINEMEDIAMODE_G4FAX                   \
        || dwMediaMode == LINEMEDIAMODE_DIGITALDATA         \
        || dwMediaMode == LINEMEDIAMODE_TELETEX             \
        || dwMediaMode == LINEMEDIAMODE_VIDEOTEX                \
        || dwMediaMode == LINEMEDIAMODE_MIXED                   \
        || dwMediaMode == LINEMEDIAMODE_ADSI                    \
        || dwMediaMode == LINEMEDIAMODE_VOICEVIEW)


#endif // TAPICOMN_H

#ifndef __MIMM_H__
#define __MIMM_H__



#define ImmGetContextFromWindowGwe USER_CALL ( HIMC, ImmGetContextFromWindowGwe, (	\
	HWND	hwnd ))


#define ImmAssociateContextWithWindowGwe USER_CALL (BOOL, ImmAssociateContextWithWindowGwe, (	\
	HWND	hwnd,				\
	HIMC	himc,				\
	DWORD	dwFlags,			\
	HIMC	*phimcPrev,			\
	HWND	*phwndFocus,		\
	HIMC	*phimcFocusPrev,	\
	HIMC	*phimcFocusNew))


#define ImmSetHotKey USER_CALL ( BOOL, ImmSetHotKey, ( \
	DWORD	dwHotKeyId,		\
	UINT	uModifiers,		\
	UINT	uVkey,			\
	HKL		hkl))

#define ImmGetHotKey USER_CALL ( BOOL, ImmGetHotKey, (	\
	DWORD	dwHotKeyId,		\
	UINT	*puModifiers,	\
	UINT	*puVkey,		\
	HKL		*phkl))




#endif


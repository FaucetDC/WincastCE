/*++
THIS CODE AND INFORMATION IS PROVIDED "AS IS" WITHOUT WARRANTY OF
ANY KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED TO
THE IMPLIED WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A
PARTICULAR PURPOSE.
Copyright (c) 1995-1998  Microsoft Corporation

Module Name:

mcommctr.h

Abstract:

Notes:


--*/

#ifndef __MCOMMCTR_H__
#define __MCOMMCTR_H__

#ifndef WINCEMACRO
#error WINCEMACRO not defined __FILE__
#endif

#define ImageList_Create USER_CALL (HIMAGELIST, ImageListCreate, ( \
    int cx, int cy, UINT flags, int cInitial, int cGrow))

#define ImageList_Destroy USER_CALL (BOOL, ImageListDestroy, ( \
    HIMAGELIST himl))

#define ImageList_GetImageCount USER_CALL (int, ImageListGetImageCount, ( \
    HIMAGELIST himl))

#define ImageList_Add USER_CALL (int, ImageListAdd, ( \
    HIMAGELIST himl, HBITMAP hbmImage, HBITMAP hbmMask))

#define ImageList_ReplaceIcon USER_CALL (int, ImageListReplaceIcon, ( \
    HIMAGELIST himl, int i, HICON hicon))

#define ImageList_SetBkColor USER_CALL (COLORREF, ImageListSetBkColor, ( \
    HIMAGELIST himl, COLORREF clrBk))

#define ImageList_GetBkColor USER_CALL (COLORREF, ImageListGetBkColor, ( \
    HIMAGELIST himl))

#define ImageList_SetOverlayImage USER_CALL (BOOL, ImageListSetOverlayImage, ( \
    HIMAGELIST himl, int iImage, int iOverlay))

#define ImageList_Draw USER_CALL (BOOL, ImageListDraw, ( \
    HIMAGELIST himl, int i, HDC hdcDst, int x, int y, UINT fStyle))

#define ImageList_Replace USER_CALL (BOOL, ImageListReplace, ( \
    HIMAGELIST himl, int i, HBITMAP hbmImage, HBITMAP hbmMask))

#define ImageList_AddMasked USER_CALL (int, ImageListAddMasked, ( \
    HIMAGELIST himl, HBITMAP hbmImage, COLORREF crMask))

#define ImageList_DrawEx USER_CALL (BOOL, ImageListDrawEx, ( \
    HIMAGELIST himl, int i, HDC hdcDst, int x, int y, int dx, int dy, \
    COLORREF rgbBk, COLORREF rgbFg, UINT fStyle))

#define ImageList_Remove USER_CALL (BOOL, ImageListRemove, ( \
    HIMAGELIST himl, int i))

#define ImageList_GetIcon USER_CALL (HICON, ImageListGetIcon, ( \
    HIMAGELIST himl, int i, UINT flags))

#define ImageList_LoadImage USER_CALL(HIMAGELIST, ImageListLoadImage, ( \
    HINSTANCE hinst, LPCWSTR lpbmp, int cx, int cGrow, COLORREF crMask, \
    UINT uType, UINT uFlags))

#define ImageList_BeginDrag USER_CALL (BOOL, ImageListBeginDrag, ( \
    HIMAGELIST himlTrack, int iTrack, int dxHotspot, int dyHotSpot))

#define ImageList_EndDrag USER_CALL (void, ImageListEndDrag, ( \
    void ))

#define ImageList_DragEnter USER_CALL (BOOL, ImageListDragEnter, ( \
    HWND hwndLock, int x, int y))

#define ImageList_DragLeave USER_CALL (BOOL, ImageListDragLeave, ( \
    HWND hwndLock))

#define ImageList_DragMove USER_CALL (BOOL, ImageListDragMove, ( \
    int x, int y))

#define ImageList_SetDragCursorImage USER_CALL (BOOL, ImageListSetDragCursorImage, ( \
    HIMAGELIST himl, int iDrag, int dxHotspot, int dyHotspot))

#define ImageList_DragShowNolock USER_CALL (BOOL, ImageListDragShowNolock, ( \
    BOOL fShow))

#define ImageList_GetDragImage USER_CALL (HIMAGELIST, ImageListGetDragImage, ( \
    POINT FAR *ppt, POINT FAR *pptHotspot))

#define ImageList_GetIconSize USER_CALL (BOOL, ImageListGetIconSize, ( \
    HIMAGELIST himl, int FAR *cx, int FAR *cy))

#define ImageList_SetIconSize USER_CALL (BOOL, ImageListSetIconSize, ( \
    HIMAGELIST himl, int cx, int cy))

#define ImageList_GetImageInfo USER_CALL (BOOL, ImageListGetImageInfo, ( \
    HIMAGELIST himl, int i, IMAGEINFO FAR *pImageInfo))

#define ImageList_Merge USER_CALL (HIMAGELIST, ImageListMerge, ( \
    HIMAGELIST himl1, int i1, HIMAGELIST himl2, int i2, int dx, int dy))

#define ImageList_CopyDitherImage USER_CALL (void, ImageListCopyDitherImage, ( \
    HIMAGELIST himlDest, WORD iDst, int xDst, int yDst, HIMAGELIST himlSrc, \
    int iSrc, UINT fStyle))

#define ImageList_DrawIndirect USER_CALL (BOOL, ImageListDrawIndirect, ( \
    IMAGELISTDRAWPARAMS *pimldp))

#define ImageList_Copy USER_CALL (BOOL, ImageListCopy, (	\
	HIMAGELIST himlDst,		\
	int iDst,				\
	HIMAGELIST himlSrc,		\
	int iSrc,				\
	UINT uFlags ))

#define ImageList_Duplicate USER_CALL (HIMAGELIST, ImageListDuplicate, (	\
	HIMAGELIST himl ))

#define ImageList_SetImageCount USER_CALL (BOOL, ImageListSetImageCount, (	\
	HIMAGELIST himl,	\
	UINT uNewCount ))


#endif // ! __MCOMMCTR_H__

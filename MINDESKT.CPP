/*---------------------------------------------------------------------------*\
 *
 * THIS CODE AND INFORMATION IS PROVIDED "AS IS" WITHOUT WARRANTY OF ANY KIND,
 * EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE IMPLIED 
 * WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A PARTICULAR PURPOSE.
 * 
 * Copyright (c) 1995-1998  Microsoft Corporation
 *
 *  file:  MinDeskT.cpp
 *  author:  ArulM
 *  purpose: Implement Sample shell desktop window
 *
\*---------------------------------------------------------------------------*/
#include "windows.h"
#include "minshell.h"


// Desktop bitmap globals
DWORD   g_fTileWallp;
TCHAR   g_szBMPName[MAX_PATH+1];
HBRUSH  g_hbrWallp;
RECT    g_rcWp;

LRESULT CALLBACK Desktop_WndProc(HWND hwnd, UINT msg, WPARAM wp, LPARAM lp);

// Register the desktop window class
BOOL Desktop_Register(HINSTANCE hInst)
{
	WNDCLASS wc;

	wc.style         = CS_HREDRAW | CS_VREDRAW;
    wc.lpfnWndProc   = (WNDPROC)Desktop_WndProc;
    wc.cbClsExtra    = 0;                       // No per-class extra data.
    wc.cbWndExtra    = 4;                       // No per-window extra data.
    wc.hInstance     = hInst;                   // Owner of this class
    wc.hIcon         = NULL;
    wc.hCursor       = LoadCursor(NULL, IDC_ARROW);
    wc.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
    wc.lpszMenuName  = NULL;                   // Menu name from .RC
    // IMPORTANT NOTE: The desktop window class name MUST be 
    // "DesktopExplorerWindow". See block comment on use of 
    // the RegisterTaskBar API in MINTASK.CPP
    wc.lpszClassName = c_szDesktopWndClass;

	RegisterClass(&wc);
	return TRUE;
}

// Create & show the desktop window
HRESULT Desktop_InitInstance(int nCmdShow)
{
	RECT rc;
	RECT rcWorkArea;
	
	SystemParametersInfo(SPI_GETWORKAREA, 0, (void*)&rcWorkArea, 0);
	
	
	g_hwndDesktop = CreateWindow(c_szDesktopWndClass, TEXT(""), WS_VISIBLE, 0, 0,
						  rcWorkArea.right, rcWorkArea.bottom, NULL, NULL,
						  g_hInst, (LPVOID)NULL);
	if (!g_hwndDesktop) {
        return E_FAIL;
	}
	DEBUGMSG(ZONE_TRACE, (TEXT("Created Minshell desktop window.\r\n")));

	GetClientRect(g_hwndDesktop, &rc);
		
	ShowWindow(g_hwndDesktop, nCmdShow);
	UpdateWindow(g_hwndDesktop);	

	return NOERROR;
}

HBRUSH WINAPI
SHLoadDIBitmapBrush( LPCTSTR szFileName, int *pnWidth, int *pnHeight )
{
    HBRUSH hbrush = NULL;
    BITMAPFILEHEADER bmfh;
    HANDLE hFile;
    DWORD dwFileSize, dwRead;
    BITMAPINFOHEADER *pbmih;
    
        
    hFile = CreateFile(szFileName, GENERIC_READ, FILE_SHARE_READ,
                       NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
    if (hFile == INVALID_HANDLE_VALUE) {
        return NULL;
    }

    dwFileSize = GetFileSize(hFile, NULL);
    ReadFile(hFile, (LPVOID)&bmfh, sizeof(BITMAPFILEHEADER), &dwRead, NULL);

    if( bmfh.bfType == MAKEWORD('B','M') &&
        (pbmih = (BITMAPINFOHEADER *)VirtualAlloc(
                                        NULL,
                                        (dwFileSize - dwRead),
                                        MEM_COMMIT | MEM_RESERVE,
                                        PAGE_READWRITE )) ) {

        ReadFile(hFile, (LPVOID)pbmih, (dwFileSize - dwRead), &dwRead, NULL);
    
        if( hbrush = CreateDIBPatternBrushPt(pbmih, DIB_RGB_COLORS) ) {
            *pnWidth = pbmih->biWidth;
            *pnHeight = pbmih->biHeight; 
        }

        VirtualFree(pbmih, 0, MEM_RELEASE);
    }

    CloseHandle(hFile);
    return hbrush;

}

LRESULT Desktop_LoadWallpaper(HWND hwnd, BOOL fInitial)
{
	DWORD dwSize, dwType, lRet, fTile;
	TCHAR szTemp[MAX_PATH+1];
  	HKEY  hkey;
  	int x, y;

	if(RegOpenKeyEx(HKEY_CURRENT_USER, L"ControlPanel\\Desktop", 0, 0, &hkey) == ERROR_SUCCESS) 
	{
		dwSize = sizeof(fTile);
		RegQueryValueEx(hkey, L"tile", NULL, &dwType, (LPBYTE)&fTile, &dwSize);

		dwSize = sizeof(szTemp);
		lRet = RegQueryValueEx(hkey, L"wallpaper", NULL, &dwType, (LPBYTE)szTemp, &dwSize);

		if(ERROR_SUCCESS==lRet && dwType==REG_SZ)
		{
			// if not fInitial check if the wallpaper (BMP path or tile flag) has changed
			if(!fInitial && (fTile==g_fTileWallp) && (0==lstrcmpi(szTemp, g_szBMPName)))
			{
				// no change. Skip reloading the BMP
				ASSERT(g_hbrWallp);
				return TRUE;
			}
			// else save the new values
			g_fTileWallp = fTile;
			lstrcpy(g_szBMPName, szTemp);
			
			// need to repaint whole thing, so invalidate entire desktop window
			InvalidateRect(g_hwndDesktop, NULL, TRUE);

			DEBUGMSG(ZONE_TRACEDESKT, (L"Desktop wallpaper BMP CHANGED!!\r\n"));
			
    		if( g_hbrWallp )
        		DeleteObject(g_hbrWallp);

			g_hbrWallp = SHLoadDIBitmapBrush(g_szBMPName, &x, &y);

        	if(!g_fTileWallp) 
        	{
            	g_rcWp.left = max( 0, (GetSystemMetrics( SM_CXSCREEN ) - x) / 2 );
            	g_rcWp.top = max( 0, (GetSystemMetrics( SM_CYSCREEN ) - y) / 2 );
            	g_rcWp.right = g_rcWp.left + x;
            	g_rcWp.bottom = g_rcWp.top + y;
				DEBUGMSG(ZONE_TRACEDESKT, (L"Desktop Loaded Wallpaper(%s), size=(%d, %d) loc=%d, %d)\r\n", g_szBMPName, x, y, g_rcWp.left, g_rcWp.right));
        	}
			else { DEBUGMSG(ZONE_TRACEDESKT, (L"Desktop Loaded Wallpaper(%s) TILED\r\n", g_szBMPName)); }
		}
		else { DEBUGMSG(ZONE_TRACEDESKT, (L"Desktop FAILED to get wallpaper reg entry\r\n")); }
		RegCloseKey(hkey);
	}
	else { DEBUGMSG(ZONE_TRACEDESKT, (L"Desktop NO wallpaper reg entry\r\n")); }
	
	return TRUE;
} 

void Desktop_OnPaintBkgnd(HWND hwnd, HDC hdc)
{
	RECT rc;

	DEBUGMSG(ZONE_TRACEDESKT, (L"Desktop PAINTING\r\n"));

    GetClipBox( hdc, &rc );
  	if( !g_hbrWallp ) {
    	FillRect( hdc, &rc, (HBRUSH)GetStockObject( WHITE_BRUSH ) );
    } else {
		if( g_fTileWallp ) {
        	FillRect( hdc, &rc, g_hbrWallp );
        } else {
         	FillRect( hdc, &rc, (HBRUSH)GetStockObject( WHITE_BRUSH ) );
            SetBrushOrgEx( hdc, g_rcWp.left, g_rcWp.top, NULL );
            FillRect( hdc, &g_rcWp, g_hbrWallp );
    	}
    }
}


LRESULT CALLBACK
Desktop_WndProc(HWND hwnd, UINT msg, WPARAM wp, LPARAM lp)
{
	DEBUGMSG(ZONE_TRACEMSGHF, (TEXT("Desktop Window Msg=%x wp=%x lp=%x\r\n"), msg, wp, lp));
	switch(msg)
	{
    case WM_CREATE:
        Desktop_LoadWallpaper(hwnd, TRUE);
        break;

    case WM_SETTINGCHANGE:
        // This message is sent out when the desktop wallpaper setting is 
        // changed (and on much else). Read our regkeys again & see if our 
        // wallpaper really changed
		Desktop_LoadWallpaper(hwnd, FALSE);
		break;

    case WM_DESTROY:
        if( g_hbrWallp ) 
        {
            DeleteObject(g_hbrWallp);
            g_hbrWallp = NULL;
        }
        break;    

	case WM_ERASEBKGND: 
		Desktop_OnPaintBkgnd(hwnd, (HDC)wp);
		break;
		
	default: 
		return DefWindowProc(hwnd, msg, wp, lp);
	}
	return 0;
}

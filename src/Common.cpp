// This file is part of Notepad++ project
// Copyright (C)2020 Don HO <don.h@free.fr>
//
// This program is free software; you can redistribute it and/or
// modify it under the terms of the GNU General Public License
// as published by the Free Software Foundation; either
// version 2 of the License, or (at your option) any later version.
//
// Note that the GPL places important restrictions on "derived works", yet
// it does not provide a detailed definition of that term.  To avoid
// misunderstandings, we consider an application to constitute a
// "derivative work" for the purpose of this license if it does any of the
// following:
// 1. Integrates source code from Notepad++.
// 2. Integrates/includes/aggregates Notepad++ into a proprietary executable
//    installer, such as those produced by InstallShield.
// 3. Links to a library or executes a program that does any of the above.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with this program; if not, write to the Free Software
// Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.

// NOTE : Extremely cleaned out, if you need more go to: https://github.com/notepad-plus-plus/notepad-plus-plus/blob/master/PowerEditor/src/MISC/Common/Common.cpp

#include "Common.h"
#include <tchar.h>

COLORREF getCtrlBgColor(HWND hWnd)
{
	COLORREF crRet = CLR_INVALID;
	if (hWnd && IsWindow(hWnd))
	{
		RECT rc;
		if (GetClientRect(hWnd, &rc))
		{
			HDC hDC = GetDC(hWnd);
			if (hDC)
			{
				HDC hdcMem = CreateCompatibleDC(hDC);
				if (hdcMem)
				{
					HBITMAP hBmp = CreateCompatibleBitmap(hDC,
					rc.right, rc.bottom);
					if (hBmp)
					{
						HGDIOBJ hOld = SelectObject(hdcMem, hBmp);
						if (hOld)
						{
							if (SendMessage(hWnd, WM_ERASEBKGND, reinterpret_cast<WPARAM>(hdcMem), 0))
							{
								crRet = GetPixel(hdcMem, 2, 2); // 0, 0 is usually on the border
							}
							SelectObject(hdcMem, hOld);
						}
						DeleteObject(hBmp);
					}
					DeleteDC(hdcMem);
				}
				ReleaseDC(hWnd, hDC);
			}
		}
	}
	return crRet;
}

generic_string GetLastErrorAsString(DWORD errorCode)
{
    generic_string errorMsg(_T(""));
    // Get the error message, if any.
    // If both error codes (passed error n GetLastError) are 0, then return empty
    if (errorCode == 0)
        errorCode = GetLastError();
    if (errorCode == 0)
        return errorMsg; //No error message has been recorded

    LPWSTR messageBuffer = nullptr;
    FormatMessageW(FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM | FORMAT_MESSAGE_IGNORE_INSERTS,
        nullptr, errorCode, MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT), (LPWSTR)&messageBuffer, 0, nullptr);

    errorMsg += messageBuffer;

    //Free the buffer.
    LocalFree(messageBuffer);

    return errorMsg;
}

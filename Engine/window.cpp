/*
Copyright (c) 2013, walking cat team
All rights reserved.

Redistribution and use in source and binary forms, with or without modification,
are permitted provided that the following conditions are met:

* Redistributions of source code must retain the above copyright notice, this
list of conditions and the following disclaimer.

* Redistributions in binary form must reproduce the above copyright notice, this
list of conditions and the following disclaimer in the documentation and/or
other materials provided with the distribution.

* Neither the name of the walking cat team nor the names of its
contributors may be used to endorse or promote products derived from
this software without specific prior written permission.

THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR
ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
(INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON
ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
(INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
*/
#include <windows.h>
#include "window.h"

CWindow::CWindow()
{

}

CWindow::~CWindow()
{

};

LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
    switch(msg)
    {
    case WM_CLOSE:
        DestroyWindow(hwnd);
        break;
    case WM_DESTROY:
        PostQuitMessage(0);
        break;
    default:
        return DefWindowProc(hwnd, msg, wParam, lParam);
    }
    return 0;
}

bool CWindow::Create(int width, int height, CWindow** ppWindow)
{
    *ppWindow = new CWindow;
    WNDCLASSEX WndClass;

    //Step 1: Registering the Window Class
    WndClass.cbSize        = sizeof(WNDCLASSEX);
    WndClass.style         = 0;
    WndClass.lpfnWndProc   = WndProc;
    WndClass.cbClsExtra    = 0;
    WndClass.cbWndExtra    = 0;
    WndClass.hInstance     = NULL;
    WndClass.hIcon         = LoadIcon(NULL, IDI_APPLICATION);
    WndClass.hCursor       = LoadCursor(NULL, IDC_ARROW);
    WndClass.hbrBackground = (HBRUSH)(COLOR_WINDOW+1);
    WndClass.lpszMenuName  = NULL;
    WndClass.lpszClassName = L"Engine";
    WndClass.hIconSm       = LoadIcon(NULL, IDI_APPLICATION);

    if(!RegisterClassEx(&WndClass))
    {
//        ERROR_MB(L"Window Registration Failed!");
        return false;
    }

    // Step 2: Creating the Window

    RECT R = {0, 0, width, height};
    DWORD dwStyle;
    dwStyle = WS_OVERLAPPEDWINDOW & ~(WS_THICKFRAME | WS_MAXIMIZEBOX);

    AdjustWindowRect(&R, dwStyle, false);
    (*ppWindow)->m_hWindow = CreateWindowEx(
        WS_EX_CLIENTEDGE,
        L"Engine",
        L"Engine",
        dwStyle,
        CW_USEDEFAULT, 
        CW_USEDEFAULT,
        R.right,
        R.bottom,
        NULL, 
        NULL, 
        NULL, 
        NULL);

    if((*ppWindow)->m_hWindow == NULL)
    {
//        ERROR_MB(L"Window Registration Failed!");
        return false;
    }

    ShowWindow((*ppWindow)->m_hWindow, SW_SHOWNORMAL);
    UpdateWindow((*ppWindow)->m_hWindow);

    return true;
}
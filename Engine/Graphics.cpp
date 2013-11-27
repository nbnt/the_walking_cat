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
#include <d3d11.h>
#include "Graphics.h"

CGraphics::CGraphics()
{

}

CGraphics::~CGraphics()
{

};
bool CGraphics::Create(HWND hwnd, int width, int height, CGraphics** ppGraphics)
{
    *ppGraphics = new CGraphics;

    DXGI_SWAP_CHAIN_DESC SwapChain;
    SwapChain.BufferDesc.Width = width;
    SwapChain.BufferDesc.Height = height;
    SwapChain.BufferDesc.RefreshRate.Numerator = 60;
    SwapChain.BufferDesc.RefreshRate.Denominator = 1;
    SwapChain.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM_SRGB;
    SwapChain.BufferDesc.ScanlineOrdering = DXGI_MODE_SCANLINE_ORDER_UNSPECIFIED;
    SwapChain.BufferDesc.Scaling = DXGI_MODE_SCALING_UNSPECIFIED;

    SwapChain.SampleDesc.Count = 1;
    SwapChain.SampleDesc.Quality = 0;

    SwapChain.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
    SwapChain.BufferCount = 1;
    SwapChain.OutputWindow = hwnd;
    SwapChain.Windowed = true;
    SwapChain.SwapEffect = DXGI_SWAP_EFFECT_DISCARD;
    SwapChain.Flags = 0;

    // Create the DX10 device
    UINT DeviceFlags = 0;
#ifdef _DEBUG
    DeviceFlags = D3D10_CREATE_DEVICE_DEBUG;
#endif
    D3D_FEATURE_LEVEL featureLevel;

    D3D11CreateDeviceAndSwapChain(nullptr, 
        D3D_DRIVER_TYPE_HARDWARE, 
        nullptr, 
        DeviceFlags, 
        nullptr, 
        0, 
        D3D11_SDK_VERSION, 
        &SwapChain, 
        &(*ppGraphics)->m_pSwapChain, &(*ppGraphics)->m_pDevice, &featureLevel, &(*ppGraphics)->m_pImmediateContext);

    // Create the back buffer
    ID3D11Texture2D* backBuffer;
    (*ppGraphics)->m_pSwapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), (void**)(&backBuffer));
    (*ppGraphics)->m_pDevice->CreateRenderTargetView(backBuffer, 0, &(*ppGraphics)->m_pBackBufferRTV);

    return true;
}

void CGraphics::ClearWindow()
{
    float clear[4] = {1, 0, 0, 1};
    m_pImmediateContext->ClearRenderTargetView(m_pBackBufferRTV, clear);
    m_pSwapChain->Present(0, 0);
}
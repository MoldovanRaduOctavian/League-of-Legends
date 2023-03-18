#pragma once

#define WIN32_LEAN_AND_MEAN 

#pragma comment(lib, "d3d11.lib")
#pragma comment(lib, "dcomp.lib")

#include <windows.h>
#include <iostream>
#include <d3d11.h>
#include <dinput.h>
#include <dxgi.h>
#include <dcomp.h>
#include "imgui.h"
#include "imgui_impl_dx11.h"
#include "imgui_impl_win32.h"
#include <tchar.h>
#include "types.h"
#include "renderer.h"

#define WIDTH 1920
#define HEIGHT 1080

extern ID3D11Device* dxDeviceEx;
extern ID3D11DeviceContext* dxDeviceContextEx;
extern IDXGISwapChain1* dxSwapChainEx;
extern ID3D11RenderTargetView* dxRenderTargetEx;

class Context
{
public:

    HWND hWnd;
    HINSTANCE hInstance;

    ID3D11Device* dxDevice;
    ID3D11DeviceContext* dxDeviceContext;
    IDXGISwapChain1* dxSwapChain;
    ID3D11RenderTargetView* dxRenderTarget;

    Context();
    ~Context();
    bool initContext();
    bool initDx();
    void startFrame();
    void endFrame();
    void drawOverlay();
    void addCircle(Renderer renderer, ImDrawList* drawList, vec3 pos, float radius);
    void storePoints(Renderer renderer, ImVec2* points, int* plen, vec3 pos, int x, int z);
    void cleanDx();
};



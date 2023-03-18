#include "context.h"

ID3D11Device* dxDeviceEx = NULL;
ID3D11DeviceContext* dxDeviceContextEx = NULL;
IDXGISwapChain1* dxSwapChainEx = NULL;
ID3D11RenderTargetView* dxRenderTargetEx = NULL;


extern IMGUI_IMPL_API LRESULT ImGui_ImplWin32_WndProcHandler(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);
LRESULT WINAPI WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
    if (ImGui_ImplWin32_WndProcHandler(hWnd, msg, wParam, lParam))
        return true;

    switch (msg)
    {   
    case WM_SYSCOMMAND:
        if ((wParam & 0xfff0) == SC_KEYMENU) // Disable ALT application menu
            return 0;
        break;
    case WM_DESTROY:
        ::PostQuitMessage(0);
        return 0;
    }
    return ::DefWindowProc(hWnd, msg, wParam, lParam);
}

Context::Context(){};
Context::~Context(){};

bool Context::initContext()
{
    hInstance = GetModuleHandle(NULL);

    SetConsoleTitleA("DA FRATE!!!");

    WNDCLASSEXA wc = {sizeof(WNDCLASSEX), CS_CLASSDC, WndProc, 0L, 0L, hInstance,
    NULL, NULL, NULL, NULL, "TestClass", NULL};

    if (!RegisterClassExA(&wc))
    {
        std::cout << "BAG PULA IN WIN32 API\n";
        return false;
    }

    uint32_t window_style = WS_EX_LAYERED | WS_EX_NOACTIVATE | WS_EX_TOPMOST | WS_EX_TRANSPARENT;
    //uint32_t window_style = WS_EX_TOPMOST;
    //uint32_t window_style = CS_HREDRAW | CS_VREDRAW;

    hWnd = CreateWindowExA(window_style, "TestClass", "SUGI", WS_POPUP,
                           1, 1, GetSystemMetrics(SM_CXSCREEN), GetSystemMetrics(SM_CYSCREEN),
                           nullptr, nullptr, hInstance, nullptr);

    if (hWnd == NULL) { std::cout << "Aici e problema\n";  return false; }
    
    ShowWindow(hWnd, SW_SHOW);
    
    if (!initDx()) { std::cout << "DX init crapa\n"; return false; }

    dxDeviceEx = dxDevice;
    dxDeviceContextEx = dxDeviceContext;
    dxSwapChainEx = dxSwapChain;
    dxRenderTargetEx = dxRenderTarget;

    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO();
    io.ConfigWindowsMoveFromTitleBarOnly = true;

    ImGui::StyleColorsDark();

    ImGui_ImplWin32_Init(hWnd);
    ImGui_ImplDX11_Init(dxDevice, dxDeviceContext);
    ImGui::GetStyle().Alpha = 1;

    return true;

}

bool Context::initDx()
{
    D3D11CreateDevice
    (
     nullptr,
     D3D_DRIVER_TYPE_HARDWARE,
     nullptr,
     D3D11_CREATE_DEVICE_BGRA_SUPPORT,
     nullptr,
     0,
     D3D11_SDK_VERSION,
     &dxDevice,
     nullptr,
     &dxDeviceContext
     );

     IDXGIDevice* dxgiDevice;
     if (dxDevice->QueryInterface(__uuidof(IDXGIDevice), (void**)&dxgiDevice) != S_OK)
     {
         std::cout << "DXGIDevice crapa\n";
         return false;
     }

     IDXGIAdapter* dxgiAdapter;
     if (dxgiDevice->GetParent(__uuidof(IDXGIAdapter), (void**)&dxgiAdapter) != S_OK)
     {
         std::cout << "DXGIAdapter crapa\n";
         return false;
     }

     IDXGIFactory2* dxgiFactory;
     if (dxgiAdapter->GetParent(__uuidof(IDXGIFactory2), (void**)&dxgiFactory) != S_OK)
     {
         std::cout << "DXGIFactory crapa\n";
         return false;
     }

    DXGI_SWAP_CHAIN_DESC1 desc = {};
    desc.Format = DXGI_FORMAT_B8G8R8A8_UNORM;
    desc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
    desc.SwapEffect = DXGI_SWAP_EFFECT_FLIP_SEQUENTIAL;
    desc.BufferCount = 2;
    desc.SampleDesc.Count = 1;
    desc.AlphaMode = DXGI_ALPHA_MODE_PREMULTIPLIED;
    desc.Scaling = DXGI_SCALING_STRETCH;
    
    RECT rect = {};
    GetClientRect(hWnd, &rect);
    desc.Width = rect.right - rect.left;
    desc.Height = rect.bottom - rect.top;

    if (dxgiFactory->CreateSwapChainForComposition(dxgiDevice, &desc,
        nullptr, &dxSwapChain) != S_OK)
    {
        std::cout << "Swap Chain crapa\n";
        return false;
    }

    IDCompositionDevice* dcompDevice;
    if (DCompositionCreateDevice(dxgiDevice, __uuidof(dcompDevice), (void**)&dcompDevice) != S_OK)
    {
        std::cout << "Composition Device crapa\n";
        return false;
    }

    IDCompositionTarget* target;
    if (dcompDevice->CreateTargetForHwnd(hWnd, true, &target) != S_OK)
    {
        std::cout << "Composition Target crapa\n";
        return false;
    }

    IDCompositionVisual* visual;
    dcompDevice->CreateVisual(&visual);
    visual->SetContent(dxSwapChain);
    target->SetRoot(visual);
    dcompDevice->Commit();

    ID3D11Resource* pBackBuffer;
    dxSwapChain->GetBuffer(0, IID_PPV_ARGS(&pBackBuffer));

    dxDevice->CreateRenderTargetView(pBackBuffer, NULL, &dxRenderTarget);

    pBackBuffer->Release();

    return true;
}


void Context::startFrame()
{
    MSG msg;
    ZeroMemory(&msg, sizeof(MSG));

    if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
    {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }

    ImGui_ImplDX11_NewFrame();
    ImGui_ImplWin32_NewFrame();
    ImGui::NewFrame();

}

void Context::endFrame()
{
    ImVec4 color = ImVec4(0, 0, 0, 0);

    ImGui::End();
    ImGui::EndFrame();
    ImGui::Render();
    dxDeviceContext->OMSetRenderTargets(1, &dxRenderTarget, NULL);
    dxDeviceContext->ClearRenderTargetView(dxRenderTarget, (float*)&color);
    ImGui_ImplDX11_RenderDrawData(ImGui::GetDrawData());
    dxSwapChain->Present(0, 0);

}

void Context::drawOverlay()
{
    auto io = ImGui::GetIO();
    ImGui::SetNextWindowSize(io.DisplaySize);
    ImGui::SetNextWindowPos(ImVec2(0, 0));
    if (!ImGui::Begin("##Overlay", nullptr,
        ImGuiWindowFlags_NoTitleBar |
        ImGuiWindowFlags_NoResize |
        ImGuiWindowFlags_NoMove |
        ImGuiWindowFlags_NoScrollbar |
        ImGuiWindowFlags_NoSavedSettings |
        ImGuiWindowFlags_NoInputs |
        ImGuiWindowFlags_NoBackground
    ))
        std::cout << "Problema la desenare\n";
 
    //globalData->drawData = ImGui::GetWindowDrawList();

    //ImGui::End();
}

void Context::cleanDx()
{
    if (dxRenderTarget) { dxRenderTarget->Release(); dxRenderTarget = NULL;}
    if (dxSwapChain) { dxSwapChain->Release(); dxSwapChain = NULL; }
    if (dxDeviceContext) { dxDeviceContext->Release(); dxDeviceContext = NULL; }
    if (dxDevice) { dxDevice->Release(); dxDevice = NULL; }
}

void Context::storePoints(Renderer renderer, ImVec2* points, int* plen, vec3 pos, int x, int z)
{
    vec3 aux = pos;
    aux.x += x; aux.z += z;
    vec2 rez = renderer.worldToScreen(aux);
    points[(*plen)++] = ImVec2(rez.x, rez.y);

    aux = pos;
    aux.x -= x; aux.z += z;
    rez = renderer.worldToScreen(aux);
    points[(*plen)++] = ImVec2(rez.x, rez.y);

    aux = pos;
    aux.x += x; aux.z -= z;
    rez = renderer.worldToScreen(aux);
    points[(*plen)++] = ImVec2(rez.x, rez.y);

    aux = pos;
    aux.x -= x; aux.z -= z;
    rez = renderer.worldToScreen(aux);
    points[(*plen)++] = ImVec2(rez.x, rez.y);

    aux = pos;
    aux.x += z; aux.z += x;
    rez = renderer.worldToScreen(aux);
    points[(*plen)++] = ImVec2(rez.x, rez.y);

    aux = pos;
    aux.x -= z; aux.z += x;
    rez = renderer.worldToScreen(aux);
    points[(*plen)++] = ImVec2(rez.x, rez.y);

    aux = pos;
    aux.x += z; aux.z -= x;
    rez = renderer.worldToScreen(aux);
    points[(*plen)++] = ImVec2(rez.x, rez.y);

    aux = pos;
    aux.x -= z; aux.z -= x;
    rez = renderer.worldToScreen(aux);
    points[(*plen)++] = ImVec2(rez.x, rez.y);
}

void Context::addCircle(Renderer renderer, ImDrawList* drawList, vec3 pos, float radius)
{
    ImVec2 points[5000] = {};

    int plen = 0;
    int x = 0, z = radius;
    int d = 3 - 2 * radius;
    int xc = pos.x, yc = pos.y, zc = pos.z;

    vec2 center = renderer.worldToScreen(pos);
    ImVec2 p = { center.x, center.y };
    
    

    storePoints(renderer, points, &plen, pos, x, z);
    int it = 0;

    while (z >= x)
    {
        x++;
        if (d > 0)
        {
            z--;
            d = d + 4 * (x - z) + 10;
        }
        else
            d = d + 4 * x + 6;

        storePoints(renderer, points, &plen, pos, x, z);
       
    }

    ImColor col = ImColor(0, 0xff, 0, 0xff);
    for (int i = 0; i < plen; i++)
        drawList->AddCircleFilled(points[i], 0.5f, col);

    drawList->AddCircleFilled(p, 2, col);

}
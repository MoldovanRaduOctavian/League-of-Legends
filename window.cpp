#include "window.h"

LRESULT CALLBACK WindowProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
     switch (uMsg)
     {
        case WM_CLOSE:
            DestroyWindow(hWnd);
            break;
        case WM_DESTROY:
            PostQuitMessage(0);
            return 0;
     }

     return DefWindowProc(hWnd, uMsg, wParam, lParam);
}

Window::Window()
{
    hInstance = GetModuleHandle(nullptr);
    const char* CLASS_NAME = "Test";

    WNDCLASS wndClass = {};
    wndClass.lpszClassName = CLASS_NAME;
    wndClass.hInstance = hInstance;
    wndClass.hIcon = LoadIcon(NULL, IDI_WINLOGO);
    wndClass.hCursor = LoadCursor(NULL, IDC_ARROW);
    wndClass.lpfnWndProc = WindowProc;

    RegisterClass(&wndClass);
    DWORD style = WS_CAPTION | WS_MINIMIZE | WS_SYSMENU;

    int width = 640, height = 480;

    RECT rect;
    rect.left = 250;
    rect.top = 250;
    rect.right = rect.left + width;
    rect.bottom = rect.top + height;

    AdjustWindowRect(&rect, style, false);

    hWnd = CreateWindowEx(0, CLASS_NAME, "Testing",
                          style, rect.left, rect.top, rect.right - rect.left, rect.bottom - rect.top
                          , NULL, NULL, hInstance, NULL);

    ShowWindow(hWnd, SW_SHOW);

}

Window::~Window()
{
    const char* CLASS_NAME = "Test";
    UnregisterClass(CLASS_NAME, hInstance);
}

bool Window::processMessages()
{
    MSG msg = {};

    while (PeekMessage(&msg, NULL, 0u, 0u, PM_REMOVE))
    {
        if (msg.message == WM_QUIT) return false;

        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }

    return true;
}

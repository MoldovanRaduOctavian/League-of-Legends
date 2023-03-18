#ifndef WINDOW_H
#define WINDOW_H

#include <windows.h>

LRESULT CALLBACK WindowProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

class Window
{
public:
    Window();
    ~Window();
    bool processMessages();

    HINSTANCE hInstance;
    HWND hWnd;
};

#endif // WINDOW_H

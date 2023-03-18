#pragma once

#define WIN32_LEAN_AND_MEAN 
#include <windows.h>
#include <psapi.h>
#include <iostream>

class Hook
{
public:

    HANDLE hProc;
    DWORD dwPid;
    HWND hWind;
    DWORD_PTR dwBase;

    Hook();
    ~Hook();
    bool initHook();
};

extern DWORD_PTR baseEx;
extern HANDLE hProcEx;


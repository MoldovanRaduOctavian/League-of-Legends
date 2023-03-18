#include "hook.h"

DWORD_PTR baseEx = 0;
HANDLE hProcEx = NULL;

Hook::Hook()
{
    hProc = NULL;
    dwPid = 0;
    hWind = NULL;
    dwBase = 0;
}

Hook::~Hook(){};

bool Hook::initHook()
{
    hWind = FindWindowA("RiotWindowClass", NULL);
    if (hWind == NULL)
    {
        return false;
    }

    GetWindowThreadProcessId(hWind, &dwPid);
    if (dwPid == 0)
    {
        return false;
    }

    hProc = OpenProcess(PROCESS_ALL_ACCESS, FALSE, dwPid);
    if (hProc == NULL)
    {
        return false;
    }

    HMODULE module[1024];
    DWORD cb;

    if (!EnumProcessModules(hProc, module, sizeof(module), &cb))
        return false;

    dwBase = (DWORD_PTR)module[0];

    baseEx = dwBase;
    hProcEx = hProc;

    return true;
}

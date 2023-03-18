#include "read.h"

bool readDw(int offset, void* buf)
{
    return ReadProcessMemory(hProcEx,(LPCVOID)offset, buf, sizeof(DWORD), NULL);
}

bool readMem(int offset, void* buf, int si)
{
    return ReadProcessMemory(hProcEx, (LPCVOID)offset, buf, si, NULL);
}

bool readStr(int offset, char* buf)
{
    char aux = 0x7f;
    int c = 0;
    char a[150];

    if (!ReadProcessMemory(hProcEx, (LPCVOID)offset, a, 140 * sizeof(char), NULL))
        return false;

    while (aux != '\0')
    {
        aux = a[c];
        buf[c] = aux;
        c++;
    }

    return true;
}

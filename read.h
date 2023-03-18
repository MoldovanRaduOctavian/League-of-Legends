#pragma once

#define WIN32_LEAN_AND_MEAN 
#include <iostream>
//#include <memoryapi.h>
#include <stdio.h>
#include "hook.h"

bool readDw(int offset, void* buf);
bool readMem(int offset, void* buf, int si);
bool readStr(int offset, char* buf);


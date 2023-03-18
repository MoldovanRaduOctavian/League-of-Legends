#pragma once

#define WIN32_LEAN_AND_MEAN 
#include <windows.h>
#include "read.h"
#include "offsets.h"
#include <ostream>
#include <stdio.h>
#include <string.h>

class Spell
{
    public:
    char name[100];
    int level;
    float ready;

    Spell();
    ~Spell();
    void readSpell(int address);
    friend std::ostream& operator << (std::ostream& os, const Spell& spell);
};


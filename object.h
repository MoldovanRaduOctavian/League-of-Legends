#pragma once

#define WIN32_LEAN_AND_MEAN 
#include <windows.h>
#include <iostream>
#include <ostream>
#include <stdio.h>
#include <string.h>
#include <vector>
#include "spell.h"
#include "hook.h"
#include "read.h"
#include "offsets.h"

class Object
{
public:
    float health;
    float maxHealth;
    float baseAttack;
    float bonusAttack;
    float mana;
    float maxMana;
    float armor;
    float magicResist;
    float crit;
    float critMulti;
    float abilityPower;
    float attackSpeeMulti;
    float movementSpeed;
    float attackRange;

    int level;
    float experience;

    int recallState;

    int netId;
    int objectIndex;
    int team;
    int visible;

    char name[100];
    float position[3];
    float lastVisible[3];

    Spell spells[6];

    Object();
    ~Object();
    void readObject(int address);
    void readChampion(int address);

    bool isVisible();

    friend std::ostream& operator << (std::ostream& os, const Object& obj);
};



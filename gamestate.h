#pragma once

#define WIN32_LEAN_AND_MEAN 
#include "object.h"
#include "hook.h"
#include "offsets.h"
#include "read.h"

class GameState
{
public:
   float gameTime;
   Object champions[30];
   Object turrets[30];
   Object minions[250];
   Object localPlayer;

   int champLen;
   int turLen;
   int minLen;

   GameState();
   ~GameState();

   void readGameTime();
   void readChampions();
   void readTurrets();
   void readMinions();
   void readGameState();

};


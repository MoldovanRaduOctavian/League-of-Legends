#define WIN32_LEAN_AND_MEAN 
#include <iostream>
#include "hook.h"
#include "object.h"
#include "offsets.h"
#include "gamestate.h"
#include "context.h"
#include "renderer.h"
#include "types.h"
#include "globaldata.h"
#include "rangescript.h"
#include "infoscript.h"
#include "scriptmanager.h"
using namespace std;

int main(int argc, char** argv)
{
    Hook* hook = new Hook();
    if (!hook->initHook())
        cout << "Hook failed!\n";
    else
        cout << "Hook succeded!\n";

    Object* player = new Object();
   
    Renderer* renderer = new Renderer();
    renderer->readMatrix();
    cout << renderer->width << " " << renderer->height << '\n';

    GameState* gameState = new GameState();
    gameState->readGameState();

    DWORD heroList;
    readDw(baseEx + HeroList, &heroList);

    DWORD champP;
    readDw(heroList + 0x04, &champP);

    DWORD ch;
    readDw(champP, &ch);
    player->readChampion(ch);

    //cout << *player << '\n';
    cout << gameState->localPlayer << '\n';

    //cout << *player << '\n';

    

    //cout << gameState->minLen << "\n";

    /*Context* context = new Context();
    if (!context->initContext())
    {
        cout << "SUGI PULA\n";
        return 0;
    }
    else
    {
        cout << "Ma pis pe ea fereastra blocata\n";
    }*/

    bool x = true;
    
    vec3 v1;
    vec2 v2;
    Object champ;

    GlobalData* globalData = new GlobalData();
    
    RangeScript* rangeScript = new RangeScript();
    rangeScript->globalData = globalData;
    
    InfoScript* infoScript = new InfoScript();
    infoScript->globalData = globalData;

    ScriptManager* scriptManager = new ScriptManager();
    scriptManager->globalData = globalData;
    
    //scriptManager->add(rangeScript);
    scriptManager->add(infoScript);

    for (;;)
    {
        scriptManager->tick();
    }

    UnregisterClassA("TestClass", NULL);

    return 0;
}



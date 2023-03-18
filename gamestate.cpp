#include "gamestate.h"

GameState::GameState()
{
    champLen = 0;
    turLen = 0;
    minLen = 0;
};
GameState::~GameState(){};

void GameState::readGameTime()
{
    float time;
    readDw(baseEx + GameTime, &time);
    gameTime = time;
}

void GameState::readChampions()
{
    int heroList;
    readDw(baseEx + HeroList, &heroList);

    int champP;
    readDw(heroList + 0x04, &champP);

    int ch = 1;
    Object aux;
    int id;

    int i = 0, c = 0;

    int local;
    readDw(baseEx + LocalPlayer, &local);

    while (ch)
    {
        if (!readDw(champP + i, &ch)) break;
        if (!readDw(ch, &id)) break;
        if (ch == 0) break;

        //Magic Numbers
        if ((id & 0xffff) != HeroMagicId)
            break;

        aux.readChampion(ch);

        if (local == ch)
            localPlayer = aux;

        this->champions[c++] = aux;

        i += 4;
    }

    champLen = c;
}

void GameState::readTurrets()
{
    int turretList;
    readDw(baseEx + TurretList, &turretList);

    int turretP;
    readDw(turretList + 0x04, &turretP);

    int th = 1, id, i = 0, c = 0;
    Object aux;

    while (th)
    {
        if (!readDw(turretP + i, &th)) break;
        if (!readDw(th, &id)) break;
        if (th == 0) break;

        if ((id & 0xffff) != TurretMagicId)
            break;

        aux.readObject(th);
        this->turrets[c++] = aux;

        i += 4;
    }

    turLen = c;
}


void GameState::readMinions()
{
    int minionList;
    readDw(baseEx + MinionList, &minionList);

    int minionP;
    readDw(minionList + 0x04, &minionP);

    Object aux;
    int id, mh = 1, i = 0, c = 0;

    while (mh)
    {
        if (!readDw(minionP + i, &mh)) break;
        if (!readDw(mh, &id)) break;
        if (mh == 0) break;

        if ((id & 0xffff) != MinionMagicId)
            break;

        aux.readObject(mh);
        this->minions[c++] = aux;

        i += 4;
    }

    minLen = c;
}


void GameState::readGameState()
{
    readGameTime();
    readChampions();
    readTurrets();
    readMinions();
}

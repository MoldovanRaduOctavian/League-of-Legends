#pragma once

#include <stdlib.h>
#include "context.h"
#include "texture.h"
#include "object.h"

class ChampData
{
public:

	int init = 0;
	Texture* icon;
	Texture* spells[6];
	float hpBarHeight;

	ChampData();
	~ChampData();

	bool loadChampData(Object champ);
};
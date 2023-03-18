#pragma once

#include "champdata.h"
#include <map>

class DataManager
{
public:

	ChampData* data[10];

	DataManager();
	~DataManager();

	ChampData* get(int i, Object obj);

};
#pragma once

#include "globaldata.h"

class Script
{
public:
	
	GlobalData* globalData;
	virtual void run();
};


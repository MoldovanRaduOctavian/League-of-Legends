#pragma once

#include "script.h"
#include "rangescript.h"

class ScriptManager
{

public:

	GlobalData* globalData;
	Script* scripts[100];
	int sLen;

	ScriptManager();
	~ScriptManager();

	void add(Script* script);
	void tick();
};

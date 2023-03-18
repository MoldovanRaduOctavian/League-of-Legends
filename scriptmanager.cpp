#include "scriptmanager.h"

ScriptManager::ScriptManager()
{
	globalData = NULL;
	sLen = 0;
}

ScriptManager::~ScriptManager() {};

void ScriptManager::add(Script* script)
{
	scripts[sLen++] = script;
}

void ScriptManager::tick()
{
	globalData->renderer->readMatrix();
	globalData->gameState->readGameState();

	globalData->context->startFrame();
	globalData->context->drawOverlay();

	for (int i = 0; i < sLen; i++)
		scripts[i]->run();

	globalData->context->endFrame();
}
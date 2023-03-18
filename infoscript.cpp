#include "infoscript.h"

void InfoScript::run()
{
	globalData->drawList = ImGui::GetWindowDrawList();
	ChampData* cData;


	for (int i = 0; i < globalData->gameState->champLen; i++)
	{
		Object obj = globalData->gameState->champions[i];
		if (obj.team != globalData->gameState->localPlayer.team)
		{
			cData = globalData->dataManager->get(i, globalData->gameState->champions[i]);
			globalData->drawTexture(cData->icon, { 0, 50.f + (i * 50.f) }, { 50.f, 50.f + 50.f + (i * 50) });

			float hpc = (obj.health / obj.maxHealth);
			float mnc = (obj.mana / obj.maxMana);

			globalData->drawRect({ 0, 100.f + (i * 50) }, { hpc * 50.f, 125.f + (i * 50) }, ImColor(0, 0xff, 0, 0xff));


		}
	}
}
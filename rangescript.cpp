#include "rangescript.h"

void RangeScript::run()
{
	Object obj;
	vec3 v1;
	vec2 v2;

	for (int i = 0; i < globalData->gameState->turLen; i++)
	{
		obj = globalData->gameState->turrets[i];
		v1 = { obj.position[0], obj.position[1], obj.position[2] };

		v2 = globalData->renderer->worldToScreen(v1);
		if (globalData->renderer->screenOnScreen(v2) && obj.health > 0.1f 
			&& obj.team != globalData->gameState->localPlayer.team && obj.isVisible())
			globalData->context->addCircle(*globalData->renderer, ImGui::GetWindowDrawList(), v1, 850);

	}

	for (int i = 0; i < globalData->gameState->champLen; i++)
	{
		obj = globalData->gameState->champions[i];
		v1 = { obj.position[0], obj.position[1], obj.position[2] };

		v2 = globalData->renderer->worldToScreen(v1);
		if (globalData->renderer->screenOnScreen(v2) && obj.health > 0.1f 
			&& obj.team != globalData->gameState->localPlayer.team && obj.attackRange > 200.f && obj.isVisible())
			globalData->context->addCircle(*globalData->renderer, ImGui::GetWindowDrawList(), v1, obj.attackRange + 50);
	}

	obj = globalData->gameState->localPlayer;
	v1 = { obj.position[0], obj.position[1], obj.position[2] };
	
	v2 = globalData->renderer->worldToScreen(v1);

	if (globalData->renderer->screenOnScreen(v2) && obj.health > 0.1f && obj.attackRange > 200.f)
		globalData->context->addCircle(*globalData->renderer, ImGui::GetWindowDrawList(), v1, obj.attackRange + 50);

	globalData->drawList = ImGui::GetWindowDrawList();
	ChampData* cData;

	/*for (int i = 0; i < globalData->gameState->champLen; i++)
	{
		cData = globalData->dataManager->get(i, globalData->gameState->champions[i]);
		globalData->drawTexture(cData->icon, { 0, (i * 50.f) }, { 50.f, 50.f + (i * 50)});
	}
	*/

	/**for (int i = 0; i < 6; i++)
		globalData->drawTexture(cData.spells[i], { 0, (i + 1) * 50.f }, { 50, (i + 2) * 50.f });*/



}
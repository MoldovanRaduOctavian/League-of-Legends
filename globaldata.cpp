#include "globaldata.h"

GlobalData::GlobalData() 
{
	gameState = new GameState();
	drawList = NULL;
	renderer = new Renderer();
	
	//con = new Context();
	context = new Context();
	context->initContext();

	dataManager = new DataManager();

};
GlobalData::~GlobalData() {};

void GlobalData::drawText(vec2 pos, const char* text, ImVec4 color)
{
	if (drawList == NULL) return;
	drawList->AddText(ImVec2(pos.x, pos.y), ImColor(color), text);
}

void GlobalData::drawRect(vec2 p1, vec2 p2, ImVec4 color)
{
	if (drawList == NULL) return;
	drawList->AddRectFilled(ImVec2(p1.x, p1.y), ImVec2(p2.x, p2.y), ImColor(color));
}

// Cele mai cretine functii pe care le am scris vreodata
// Pt ca n am voie sa dezaloc in functie, ca atunci textura devine NULL inainte ca ImGui sa dea render si nu se vede nimic
// Nu le folosi
void GlobalData::drawImage(const char* img, vec2 p1, vec2 p2)
{
	if (drawList == NULL) { std::cout << "SUGI\n"; return; }
	Texture* texture = Texture::loadTexture(context->dxDevice, img);
	drawList->AddImage(texture->resourceView, ImVec2(p1.x, p1.y), ImVec2(p2.x, p2.y));
	//delete texture;
}

void GlobalData::drawImageRound(const char* img, vec2 p1, vec2 p2, ImVec4 color, float rounding)
{
	if (drawList == NULL) return;

	ImVec2 v1 = { 0.f, 0.f };
	ImVec2 v2 = { 1.f, 1.f };
	
	Texture* texture = Texture::loadTexture(context->dxDevice, img);
	drawList->AddImageRounded(texture->resourceView, ImVec2(p1.x, p1.y), ImVec2(p2.x, p2.y), v1, v2, ImColor(color), rounding);
	delete texture;
}

void GlobalData::drawTexture(Texture* texture, vec2 p1, vec2 p2)
{
	if (drawList == NULL) return;

	ImVec2 v1 = { 0.f, 0.f };
	ImVec2 v2 = { 1.f, 1.f };

	if (texture == NULL) return;
	drawList->AddImage(texture->resourceView, ImVec2(p1.x, p1.y), ImVec2(p2.x, p2.y));
}

void GlobalData::tick()
{
	gameState->readGameState();
	renderer->readMatrix();
	
	context->startFrame();
	context->drawOverlay();

	drawList = ImGui::GetWindowDrawList();

	Object champ;
	vec3 v1;
	vec2 v2;

	//drawImage("1.png", { 0, 0 }, { 60, 60 });
	drawRect({ 0, 0 }, { 400, 100 }, { 0xff, 0, 0, 0xff });

	for (int i = 0; i < gameState->turLen; i++)
	{
		champ = gameState->turrets[i];
		v1.x = champ.position[0];
		v1.y = champ.position[1];
		v1.z = champ.position[2];

		v2 = renderer->worldToScreen(v1);

		if (renderer->screenOnScreen(v2))
		{
			//std::cout << champ.attackRange << "\n";
			context->addCircle(*renderer, ImGui::GetWindowDrawList(), v1, 850);
		}
			
	}


	context->endFrame();

}

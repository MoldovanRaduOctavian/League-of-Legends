#pragma once

#include "texture.h"
#include "context.h"
#include "renderer.h"
#include "gamestate.h"
#include "datamanager.h"
#include "imgui.h"
#include "imgui_impl_dx11.h"
#include "imgui_impl_win32.h"

class GlobalData
{
public:

	Context* context;
	Renderer* renderer;
	GameState* gameState;
	DataManager* dataManager;
	ImDrawList* drawList;

	GlobalData();
	~GlobalData();

	void drawText(vec2 pos, const char* text, ImVec4 color);
	void drawRect(vec2 p1, vec2 p2, ImVec4 color);
	void drawImage(const char* img, vec2 p1, vec2 p2);
	void drawImageRound(const char* img, vec2 p1, vec2 p2, ImVec4 color, float rounding);
	void drawTexture(Texture* texture, vec2 p1, vec2 p2);
	void tick();

};
#include "champdata.h"

ChampData::ChampData() {};
ChampData::~ChampData() {};

bool ChampData::loadChampData(Object champ)
{
	char aux[100];
	sprintf_s(aux, "12.6.1\\img\\champion\\%s.png", champ.name);
	
	icon = Texture::loadTexture(dxDeviceEx, aux);
	if (icon == NULL) { std::cout << "SA MA SUGA DE CARICI!!!\n"; return false; }
	


	for (int i = 0; i < 6; i++)
	{
		sprintf_s(aux, "12.6.1\\img\\spell\\%s.png", champ.spells[i].name);
		spells[i] = Texture::loadTexture(dxDeviceEx, aux);
		if (spells[i] == NULL) return false;
	}
	
	init = 1;
	return true;
}
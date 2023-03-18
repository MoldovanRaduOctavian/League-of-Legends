#include "datamanager.h"

DataManager::DataManager() 
{
	for (int i = 0; i < 10; i++)
		data[i] = NULL;
};
DataManager::~DataManager() {};

ChampData* DataManager::get(int i, Object obj)
{
	if (data[i] == NULL)
	{
		ChampData* cData = new ChampData();
		cData->loadChampData(obj);
		data[i] = cData;
		return cData;
	}

	return data[i];
}
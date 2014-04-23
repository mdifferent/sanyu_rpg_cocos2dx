#include "BattleData.h"
#include "ScriptReader.h"

BattleData::BattleData(void)
{
}


BattleData::~BattleData(void)
{
}

BattleData *BattleData::loadData(int iSceneNo)
{
	BattleData *pData = new BattleData();
	if (pData)
	{
		pData->setMapName(ScriptReader::getMapNameByNo(iSceneNo));
		return pData;
	}
	else
		return NULL;
}

void BattleData::setMapName(string &mapName)
{
}

string &BattleData::getMapName()
{
	return NULL;
}

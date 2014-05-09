#include "ScriptReader.h"
#include "SaveProcessor.h"

ScriptReader::ScriptReader(void)
{
}


ScriptReader::~ScriptReader(void)
{
}

BattleData *ScriptReader::loadBattleData(int iSceneNo, int iSaveNo)
{
	return NULL;
}

string ScriptReader::getMapNameByNo(int sceneN)
{
	return "sanyu/bk.jpg";
}

string ScriptReader::getMapBgmByNo(int iSceneNo)
{
	return "";
}


map<int,PlayerData*> *ScriptReader::loadPlayersFromSaveFile(int iSaveNo)
{
	return SaveProcessor::loadPlayerData(iSaveNo);
}
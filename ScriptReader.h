#pragma once
#include "BattleData.h"
#include "../support/tinyxml2/tinyxml2.h"
#include <string>

using namespace std;
using namespace tinyxml2;

class ScriptReader
{
public:
	ScriptReader(void);
	~ScriptReader(void);
	static BattleData *loadBattleData(int iSceneNo, int iSaveNo);

	static string getMapNameByNo(int iSceneNo);
	static string getMapBgmByNo(int iSceneNo);
	static map<int,PlayerData*> *getPlayers(int iSceneNo);
	static const int getPlayerCount(int iSceneNo);
	static map<int,MonsterData*> *getMonsters(int iSceneNo);
	static const int getMonsterCount(int iSceneNo);
	static map<int,PlayerData*> *loadPlayersFromSaveFile(int iSaveNo);

};


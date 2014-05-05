#pragma once
#include "BattleData.h"
#include <string>

using namespace std;

class ScriptReader
{
public:
	ScriptReader(void);
	~ScriptReader(void);
	static string getMapNameByNo(int iSceneNo);
	static string getMapBgmByNo(int iSceneNo);
	static const PlayerData *getPlayers(int iSceneNo);
	static const int getPlayerCount(int iSceneNo);
	static const MonsterData *getMonsters(int iSceneNo);
	static const int getMonsterCount(int iSceneNo);
	//static BattleData *getBattleDataByNo(int iSceneNo);
};


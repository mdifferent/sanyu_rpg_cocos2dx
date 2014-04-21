#pragma once
#include "BattleData.h"

class ScriptReader
{
public:
	ScriptReader(void);
	~ScriptReader(void);
	static const char *getMapNameByNo(int iSceneNo);
	static const char *getMapBgmByNo(int iSceneNo);
	static const PlayerData *getPlayers(int iSceneNo);
	static const int getPlayerCount(int iSceneNo);
	static const MonsterData *getMonsters(int iSceneNo);
	static const int getMonsterCount(int iSceneNo);
	//static BattleData *getBattleDataByNo(int iSceneNo);
};


#pragma once
#include "cocoa\CCArray.h"
#include "PlayerData.h"
#include "MonsterData.h"
USING_NS_CC;

enum WINNING_CONDITIONS {
	KILL_ALL,
	KILL_SPEC,
	KEEP_ALIVE,
	NEVER
};

enum LOSE_CONDITION {
	ALL_DEAD,
	SOMEONE_DEAD,
	ROUNDS_REACH,
	ALWAYS
};

class BattleData
{
public:
	BattleData(void);
	~BattleData(void);
	void setPlayer(PlayerData newPlayer);
	void setMonster(MonsterData newMonster);
	const char *getMapName();
	void setMapName(const char *mapName);
	static BattleData *loadData(int iSceneNo);

private:
	const char *m_mapName;
	const char *m_mapBgm;
	CCArray *m_players;
	CCArray *m_monster;
	WINNING_CONDITIONS m_winCon;
	LOSE_CONDITION m_loseCon;
};


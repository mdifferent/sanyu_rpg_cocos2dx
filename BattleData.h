#pragma once
#include "PlayerData.h"
#include "MonsterData.h"
#include <set>
#include <string>

using namespace std;

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
	map<int,PlayerData> &getPlayers();
	map<int,MonsterData> &getMonsters();
	string &getMapName();
	void setMapName(string &mapName);
	static BattleData *loadData(int iSceneNo);

private:
	string m_mapName;
	string m_mapBgm;
	map<int,PlayerData> m_players;
	map<int,MonsterData> m_monsters;
	WINNING_CONDITIONS m_winCon;
	LOSE_CONDITION m_loseCon;
};


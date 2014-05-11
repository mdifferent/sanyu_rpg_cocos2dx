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
	void setPlayer(PlayerData *newPlayer);
	void loadPlayers(int iSaveNo);
	void setMonster(MonsterData newMonster);
	static BattleData *loadData(int iSceneNo);

	map<int,PlayerData*> *getPlayers(){return m_players;};
	map<int,MonsterData*> *getMonsters(){return m_monsters;};
	string &getMapName(){return m_mapName;};
	string &getBarName(){return m_barName;};
	void setMapName(string mapName){this->m_mapName = mapName;};
	void setMapBgm(string bgmName){this->m_mapBgm = bgmName;};


private:
	string m_mapName;
	string m_mapBgm;
	string m_barName;
	map<int,PlayerData*> *m_players;
	map<int,MonsterData*> *m_monsters;
	WINNING_CONDITIONS m_winCon;
	LOSE_CONDITION m_loseCon;
};


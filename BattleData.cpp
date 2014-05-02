#include "BattleData.h"
#include "ScriptReader.h"

BattleData::BattleData(void)
{
	string name1 = "sanyu/actor_1.png";
	string name2 = "sanyu/actor_2.png";
	string name3 = "sanyu/actor_3.png";
	string name4 = "sanyu/actor_4.png";
	
	PlayerData pd1(name1);
	pd1.setProperty(MAX_HP,500);
	pd1.setProperty(CURRENT_HP,500);
	pd1.setProperty(MAX_SP,500);
	pd1.setProperty(CURRENT_SP,500);
	PlayerData pd2(name2);
	pd2.setProperty(MAX_HP,500);
	pd2.setProperty(CURRENT_HP,500);
	pd2.setProperty(MAX_SP,500);
	pd2.setProperty(CURRENT_SP,500);
	PlayerData pd3(name3);
	pd3.setProperty(MAX_HP,500);
	pd3.setProperty(CURRENT_HP,500);
	pd3.setProperty(MAX_SP,500);
	pd3.setProperty(CURRENT_SP,500);
	PlayerData pd4(name4);
	pd4.setProperty(MAX_HP,500);
	pd4.setProperty(CURRENT_HP,500);
	pd4.setProperty(MAX_SP,500);
	pd4.setProperty(CURRENT_SP,500);
	m_players.insert( std::pair<int,PlayerData>(0,pd1));
	m_players.insert( std::pair<int,PlayerData>(1,pd2));
	m_players.insert( std::pair<int,PlayerData>(2,pd3));
	m_players.insert( std::pair<int,PlayerData>(3,pd4));
	/*	
	MonsterData pdm1(name1);
	MonsterData pdm2(name2);
	MonsterData pdm3(name3);
	MonsterData pdm4(name4);
	m_monsters.insert( std::pair<int,MonsterData>(0,pdm1));
	m_monsters.insert( std::pair<int,MonsterData>(1,pdm2));
	m_monsters.insert( std::pair<int,MonsterData>(2,pdm3));
	m_monsters.insert( std::pair<int,MonsterData>(3,pdm4));*/
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
	string s = "";
	return s;
}

map<int,PlayerData> &BattleData::getPlayers()
{
	return m_players;
}

map<int,MonsterData> &BattleData::getMonsters()
{
	return m_monsters;
}
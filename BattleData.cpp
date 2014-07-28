#include "BattleData.h"
#include "ScriptReader.h"
#include "ConstValues.h"

BattleData::BattleData(void)
{
	string name1 = "XT";
	string name2 = "���";
	string name3 = "����";
	string name4 = "����";
	m_barName = "sanyu/info_bar.png";
	PlayerData *pd1 = new PlayerData(name1);
	pd1->setProperty(MAX_HP,500);
	pd1->setProperty(CURRENT_HP,500);
	pd1->setProperty(MAX_SP,500);
	pd1->setProperty(CURRENT_SP,500);
	pd1->setProperty(MELEE_ATTACK,30);
	pd1->setProperty(MELEE_DEFENSE,10);
	pd1->getItem(2);
	pd1->learnSkill(1);
	PlayerData *pd2 = new PlayerData(name2);
	pd2->setProperty(MAX_HP,500);
	pd2->setProperty(CURRENT_HP,500);
	pd2->setProperty(MAX_SP,500);
	pd2->setProperty(CURRENT_SP,500);
	pd2->setProperty(MELEE_ATTACK,30);
	pd2->getItem(1);
	pd2->getItem(2);
	pd2->getItem(2);
	pd2->learnSkill(2);
	PlayerData *pd3 = new PlayerData(name3);
	pd3->setProperty(MAX_HP,500);
	pd3->setProperty(CURRENT_HP,500);
	pd3->setProperty(MAX_SP,500);
	pd3->setProperty(CURRENT_SP,500);
	pd3->setProperty(MELEE_ATTACK,30);
	pd3->learnSkill(2);
	PlayerData *pd4 = new PlayerData(name4);
	pd4->setProperty(MAX_HP,500);
	pd4->setProperty(CURRENT_HP,500);
	pd4->setProperty(MAX_SP,500);
	pd4->setProperty(CURRENT_SP,500);
	pd4->setProperty(MELEE_ATTACK,30);
	m_players = new map<int,PlayerData*>();
	m_players->insert( std::pair<int,PlayerData*>(0,pd1));
	m_players->insert( std::pair<int,PlayerData*>(1,pd2));
	m_players->insert( std::pair<int,PlayerData*>(2,pd3));
	m_players->insert( std::pair<int,PlayerData*>(3,pd4));
	MonsterData *pdm1 = new MonsterData("ɭ������");
	pdm1->setProperty(MAX_HP,200);
	pdm1->setProperty(CURRENT_HP,200);
	pdm1->setProperty(MELEE_ATTACK,50);
	pdm1->setProperty(MELEE_DEFENSE,5);
	MonsterData *pdm2 = new MonsterData("ɭ�������ϴ�");
	pdm2->setProperty(MAX_HP,300);
	pdm2->setProperty(CURRENT_HP,300);
	pdm2->setProperty(MELEE_ATTACK,70);
	pdm2->setProperty(MELEE_DEFENSE,10);
	MonsterData *pdm3 = new MonsterData("ɭ������");
	pdm3->setProperty(MAX_HP,200);
	pdm3->setProperty(CURRENT_HP,200);
	pdm3->setProperty(MELEE_ATTACK,50);
	pdm3->setProperty(MELEE_DEFENSE,5);
    m_monsters = new map<int,MonsterData*>();
	m_monsters->insert( std::pair<int,MonsterData*>(0,pdm1));
	m_monsters->insert( std::pair<int,MonsterData*>(1,pdm2));
	m_monsters->insert( std::pair<int,MonsterData*>(2,pdm3));
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
		//pData->setMapBgm(ScriptReader::getMapBgmByNo(iSceneNo));
		return pData;
	}
	else
		return NULL;
}


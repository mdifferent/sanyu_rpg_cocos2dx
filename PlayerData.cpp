#include "PlayerData.h"
#include "InstanceDatabase.h"
/*
PlayerData::PlayerData(const PlayerData &cName):
	m_name(cName.m_name),
	m_properties(cName.m_properties),
	m_items(cName.m_items),
	m_skills(cName.m_skills)
{
}
*/

/*
string PlayerData::getPlayerName() const
{
	return m_name;
}

int PlayerData::getProperty(PLAYER_PROP_TYPE cProName)
{
	if (m_properties.find(cProName) != m_properties.end())
		return m_properties.at(cProName);
	else
	{
		CCLOG("Invalid player property!");
		return -1;
	}
}

void PlayerData::setProperty(PLAYER_PROP_TYPE cProName,int iProValue)
{
	if(m_properties.find(cProName) != m_properties.end())
		m_properties[cProName] = iProValue;
	else
		m_properties.insert(std::make_pair(cProName,iProValue));
}
*/

int PlayerData::useItem(const int id) {
	m_items[id]--;
	if (m_items[id] == 0) {
		m_items.erase(id);
		return 0;
	}
	return m_items[id];
}

void PlayerData::getItem(const int id,const int iCount)
{
	if (m_items.find(id) != m_items.end())
		m_items[id] += iCount;
	else
		m_items.insert(std::make_pair(id,iCount));
}

void PlayerData::learnSkill(const int skillId, const int level)
{
	if (m_skills.find(skillId) == m_skills.end())
		m_skills.insert(make_pair<int,int>(skillId,level));
	else
		m_skills[skillId] += level;
}

void PlayerData::useSkill(const int id)
{
	const SkillData *pData = InstanceDatabase::getDatabaseInstance()->getSkillById(id);
	int cost = pData->getCost();
	int current_hp = getProperty(CURRENT_HP);
	if (current_hp > cost)
		setProperty(CURRENT_HP,current_hp-cost);
}
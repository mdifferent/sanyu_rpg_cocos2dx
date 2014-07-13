#include "PlayerData.h"
#include "InstanceDatabase.h"

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
#include "PlayerData.h"

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

int PlayerData::useItem(const string &name) {
	m_items[name]--;
	if (m_items[name] == 0) {
		m_items.erase(name);
		return 0;
	}
	return m_items[name];
}

void PlayerData::getItem(const string &sName,const int iCount)
{
	if (m_items.find(sName) != m_items.end())
		m_items[sName] += iCount;
	else
		m_items.insert(std::make_pair(sName,iCount));
}

void PlayerData::learnSkill(const string &name, const int level)
{
	if (m_skills.find(name) == m_skills.end())
		m_skills.insert(make_pair<string,int>(name,level));
	else
		m_skills[name] += level;
}
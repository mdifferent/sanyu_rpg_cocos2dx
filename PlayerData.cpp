#include "PlayerData.h"


PlayerData::PlayerData(string sName)
{
	if (!sName.empty())
	{
		this->m_name = sName;
	}
}


PlayerData::~PlayerData(void)
{
}

string PlayerData::getPlayerName() const
{
	return m_name;
}

int PlayerData::getProperty(PLAYER_PROP_TYPE cProName)
{
	if (m_properties.find(cProName) != m_properties.end())
		return m_properties.at(cProName);
	else
		CCLOG("Invalid player property!");
		return -1;
}

void PlayerData::setProperty(PLAYER_PROP_TYPE cProName,int iProValue)
{
	if(m_properties.find(cProName) != m_properties.end())
		m_properties[cProName] = iProValue;
	else
		m_properties.insert(std::make_pair(cProName,iProValue));
}
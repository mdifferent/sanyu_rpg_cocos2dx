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
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

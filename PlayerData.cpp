#include "PlayerData.h"


PlayerData::PlayerData(string m_name)
{
	if (!m_name.empty())
	{
		this->m_name = m_name;
	}
}


PlayerData::~PlayerData(void)
{
}

string PlayerData::getPlayerName() const
{
	return m_name;
}

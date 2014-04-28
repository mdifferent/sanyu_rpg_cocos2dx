#include "MonsterData.h"


MonsterData::MonsterData(string sName)
{
	if (!sName.empty())
	{
		this->m_name = sName;
	}
}


MonsterData::~MonsterData(void)
{
}

string MonsterData::getMonsterName() const
{
	return m_name;
}
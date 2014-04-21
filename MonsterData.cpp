#include "MonsterData.h"


MonsterData::MonsterData(CCString name,MONSTER_TYPE monsterType)
{
	if (name != NULL)
		m_name = name;
	if (monsterType >= 0)
		m_monsterType = monsterType;

}


MonsterData::~MonsterData(void)
{
}

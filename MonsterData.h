#pragma once
#include "AbstractBattlerData.h"

enum MONSTER_TYPE {
	A
};



class MonsterData : public AbstractBattlerData
{
public:
	MonsterData(const string cName):AbstractBattlerData(cName){}
	~MonsterData(void){}
private:
	MONSTER_TYPE m_monsterType;
	int m_exp;
};


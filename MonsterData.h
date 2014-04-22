#pragma once
#include "cocoa/CCDictionary.h"
USING_NS_CC;

enum MONSTER_TYPE {
	NORMAL
};

class MonsterData
{
public:
	MonsterData(void);
	~MonsterData(void);
private:
	CCString m_name;
	MONSTER_TYPE m_monsterType;
	CCDictionary *m_properties;
	int m_exp;
};


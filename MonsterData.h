#pragma once
//#include <string>
//#include <map>
#include "AbstractBattlerData.h"
//using namespace std;

enum MONSTER_TYPE {
	NORMAL
};

class MonsterData : public AbstractBattlerData
{
public:
	MonsterData(const string cName):AbstractBattlerData(cName){}
	~MonsterData(void){}
	//string getMonsterName() const;
	//void setProperty(string &cProName,int iProValue);
	//int getProperty(string &cProName);
private:
	//string m_name;
	MONSTER_TYPE m_monsterType;
	//map<string,int> m_properties;	//name-value
	int m_exp;
};


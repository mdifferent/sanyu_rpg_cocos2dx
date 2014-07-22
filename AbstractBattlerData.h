#pragma once
#include <map>
#include <string>
#include "cocos2d.h"
using namespace std;

enum PLAYER_PROP_TYPE
{
	MAX_HP,
	CURRENT_HP,
	MAX_SP,
	CURRENT_SP,
	LEVEL,
	EXP,
	MELEE_ATTACK,
	MELEE_DEFENSE
};

enum BATTLER_STATUS {
    NORMAL,
    DEAD,
	DEFENSE,
    FINISHED,
    BUFF,
    DEBUFF
};

const static string enum2Tag[] = {"MaxHP","HP","MaxSP","SP","Level","Exp","Attack","Defense"};

class AbstractBattlerData
{
public:
	AbstractBattlerData(string sName);
	AbstractBattlerData(const AbstractBattlerData &data);
	~AbstractBattlerData(void);

	string getName() const {return m_name;}
	BATTLER_STATUS getStatus() const {return m_status;}

	void setProperty(const PLAYER_PROP_TYPE cProName,const int iProValue);
	int getProperty(const PLAYER_PROP_TYPE cProName) const;

	map<PLAYER_PROP_TYPE,int> *getPropertyList() {return &m_properties;};
	const map<int,int> *getItemList() const {return &m_items;};
	const map<int,int> *getSkillList() const {return &m_skills;};
    
    void setStatus(BATTLER_STATUS);
    
protected:
	string m_name;
    BATTLER_STATUS m_status;
	map<PLAYER_PROP_TYPE,int> m_properties;	//name-value
	map<int,int> m_items;		//id-amount
	map<int,int> m_skills;		//id-level
	map<PLAYER_PROP_TYPE,int> m_bufs;
};

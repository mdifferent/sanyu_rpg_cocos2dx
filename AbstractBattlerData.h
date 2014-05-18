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
	DEFENSE
};

enum BATTLER_STATUS {
    NORMAL,
    DEAD,
    FINISHED,
    BUFF,
    DEBUFF
};

const static string enum2Tag[] = {"MaxHP","HP","MaxSP","SP","Level","Exp","Attack","Defense"};

class AbstractBattlerData
{
public:
	AbstractBattlerData(string sName):m_name(sName){}
	~AbstractBattlerData(void){};
	string getName() const {return m_name;}
	void setProperty(const PLAYER_PROP_TYPE cProName,const int iProValue);
	int getProperty(const PLAYER_PROP_TYPE cProName) const;

	map<PLAYER_PROP_TYPE,int> *getPropertyList(){return &m_properties;};
	map<string,int> *getItemList(){return &m_items;};
	map<string,int> *getSkillList(){return &m_skills;};
    
    void setStatus(BATTLER_STATUS);
    BATTLER_STATUS getStatus() {return m_status;}

protected:
	string m_name;
    BATTLER_STATUS m_status;
	map<PLAYER_PROP_TYPE,int> m_properties;	//name-value
	map<string,int> m_items;		//name-amount
	map<string,int> m_skills;		//name-status
};

#pragma once
#include "cocos2d.h"
#include <map>
#include <string>
using namespace std;

enum PLAYER_PROP_TYPE
{
	MAX_HP,
	CURRENT_HP,
	MAX_SP,
	CURRENT_SP,
	LEVEL,
	EXP
};

class PlayerData
{
public:
	PlayerData(string cName);
	~PlayerData(void);
	string getPlayerName() const;
	
	void setProperty(PLAYER_PROP_TYPE cProName,int iProValue);
	int getProperty(PLAYER_PROP_TYPE cProName);
	
	int useItem(string &name);

private:
	string m_name;
	map<PLAYER_PROP_TYPE,int> m_properties;	//name-value
	map<string,int> m_items;		//name-amount
	map<string,int> m_skills;		//name-status
};


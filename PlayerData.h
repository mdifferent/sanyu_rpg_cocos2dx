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
	EXP,
	ATTACK,
	DEFENSE
};

class PlayerData
{
public:
	PlayerData(const string cName);
	PlayerData(const PlayerData &cName);
	~PlayerData(void);
	string getPlayerName() const;
	
	void setProperty(PLAYER_PROP_TYPE cProName,int iProValue);
	int getProperty(PLAYER_PROP_TYPE cProName);
	
	int useItem(string &name);
	void getItem(const string &sName,const int iCount = 1);

	void learnSkill(const string &name);

private:
	string m_name;
	map<PLAYER_PROP_TYPE,int> m_properties;	//name-value
	map<string,int> m_items;		//name-amount
	map<string,int> m_skills;		//name-status
};


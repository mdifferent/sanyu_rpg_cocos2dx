#pragma once
#include "AbstractBattlerData.h"

class PlayerData : public AbstractBattlerData
{
public:
	PlayerData(const string cName):AbstractBattlerData(cName){}
	//PlayerData(const PlayerData &cName){}
	~PlayerData(void){}
	int useItem(const string &name);
	void getItem(const string &sName,const int iCount = 1);

	void learnSkill(const string &name,const int level=1);
private:
};


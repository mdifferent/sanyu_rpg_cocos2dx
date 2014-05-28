#pragma once
#include "AbstractBattlerData.h"

class PlayerData : public AbstractBattlerData
{
public:
	PlayerData(const string cName):AbstractBattlerData(cName){}
	//PlayerData(const PlayerData &cName){}
	~PlayerData(void){}
	int useItem(const int id);
	void getItem(const int id,const int iCount = 1);

	void learnSkill(const string &name,const int level=1);
private:
};


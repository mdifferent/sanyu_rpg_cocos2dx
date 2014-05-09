#pragma once
#include "PlayerData.h"
#include "../cocos2dx/support/tinyxml2/tinyxml2.h"

using namespace tinyxml2;

const char * const SAVE_FILE_PATH = "savedata.xml";

class SaveProcessor
{
public:
	SaveProcessor(void);
	~SaveProcessor(void);
	static map<int, PlayerData *> *loadPlayerData(int iSaveNo);
	static bool savePlayerDataSet(const int iSaveNo, map<int, PlayerData *> *pData);
private:
	static XMLElement *findNthSaveData(int iSaveNo);
};


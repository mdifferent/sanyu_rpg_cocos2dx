#pragma once
#include "PlayerData.h"
#include "../support/tinyxml2/tinyxml2.h"

using namespace tinyxml2;

const char * const SAVE_FILE_PATH = "savedata.xml";

class SaveProcessor
{
public:
	SaveProcessor(void);
	~SaveProcessor(void);
	static bool init();
	static map<int, PlayerData *> *loadPlayerData(int iSaveNo);
	static bool savePlayerData();
};


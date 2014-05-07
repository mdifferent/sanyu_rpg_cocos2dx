#include "SaveProcessor.h"

const int MAX_XML_KEY_LEN = 20;

SaveProcessor::SaveProcessor(void)
{
}


SaveProcessor::~SaveProcessor(void)
{
}

bool SaveProcessor::init()
{
}

map<int,PlayerData*> *SaveProcessor::loadPlayerData(const int iSaveNo)
{
	tinyxml2::XMLDocument saveDoc;

	if (saveDoc.LoadFile(SAVE_FILE_PATH)!= XML_NO_ERROR)
	{
		CCLOG("Load save file failed!");
		return NULL;
	}
	
	XMLElement *pRoot = saveDoc.FirstChildElement("Root");
	XMLElement *pSaveData = pRoot->FirstChildElement("SaveData");
	bool bRecordFound = false;
	//Find record, according to pos attribute
	while(pSaveData)			
	{
		int iPos = 0;
		pSaveData->QueryIntAttribute("pos", &iPos);
		if (iPos == iSaveNo)
		{
			bRecordFound = true;
			break;
		}
		else
			pSaveData = pSaveData->NextSiblingElement("SaveData");
	}
	if(!bRecordFound)
	{
		CCLOG("No. %d record not found!",iSaveNo);
		return NULL;
	}
	
	map<int,PlayerData*> *dataSet = new map<int,PlayerData*>();
	int i=1;
	//Get every player data
	XMLElement *pPlayerElement = pSaveData->FirstChildElement("Player");
	while(pPlayerElement)		
	{
		PlayerData *pData = new PlayerData(pPlayerElement->Attribute("name"));
		//Get every property of each player
		XMLElement *pPropertyElement = pPlayerElement->FirstChildElement();
		PLAYER_PROP_TYPE ePro = MAX_HP;
		while(pPropertyElement)			
		{
			int iValue = atoi(pPropertyElement->GetText());
			pData->setProperty(ePro,iValue);
			ePro = (PLAYER_PROP_TYPE)(ePro+1);
			pPropertyElement = pPropertyElement->NextSiblingElement();
		}
		//Get items
		XMLElement *pItemElement = pPlayerElement->FirstChildElement("ItemList")->FirstChildElement("Item");
		while(pItemElement)
		{
			string sItemName = string(pItemElement->Attribute("name"));
			int iItemCount = atoi(pItemElement->GetText());
			pData->getItem(sItemName,iItemCount);
			pItemElement = pItemElement->NextSiblingElement("Item");
		}
		//Get skills
		XMLElement *pSkillElement = pPlayerElement->FirstChildElement("SkillList")->FirstChildElement("Skill");
		while (pSkillElement)
		{
			string sSkillName = string(pSkillElement->Attribute("name"));
			int iSkillLevel = 0;
			pSkillElement->QueryIntAttribute("lv",&iSkillLevel);
			if (iSkillLevel > 0)
				pData->m_skills.insert(make_pair<string,int>(sSkillName,iSkillLevel));
			pSkillElement = pSkillElement->NextSiblingElement("Skill");
		}
		dataSet->insert(std::make_pair<int,PlayerData*>(i++,pData));
		pPlayerElement = pPlayerElement->NextSiblingElement("Player");
	}
	
	return dataSet;
}
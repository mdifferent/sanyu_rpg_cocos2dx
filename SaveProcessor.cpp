#include "SaveProcessor.h"

const int MAX_XML_KEY_LEN = 20;

SaveProcessor::SaveProcessor(void)
{
}


SaveProcessor::~SaveProcessor(void)
{
}

XMLElement *SaveProcessor::findNthSaveData(const int iSaveNo)
{
	tinyxml2::XMLDocument m_doc;
	if (m_doc.LoadFile(SAVE_FILE_PATH)!= XML_NO_ERROR) {
		CCLOG("Load save file failed!");
		return NULL;
	}
	XMLElement *pRoot = m_doc.FirstChildElement("Root");
	XMLElement *pSaveData = pRoot->FirstChildElement("SaveData");
	bool bRecordFound = false;
	//Find record, according to pos attribute
	while(pSaveData) {
		int iPos = 0;
		pSaveData->QueryIntAttribute("pos", &iPos);
		if (iSaveNo == iPos) {
			return pSaveData;
		}
		else
			pSaveData = pSaveData->NextSiblingElement("SaveData");
	}
	return NULL;
}

map<int,PlayerData*> *SaveProcessor::loadPlayerData(const int iSaveNo)
{
	//tinyxml2::XMLDocument saveDoc;


	XMLElement *pSaveData = findNthSaveData(iSaveNo);

	if (!pSaveData)	{
		CCLOG("Couldn't find save data No.%d",iSaveNo);
		return NULL;
	}
	
	map<int,PlayerData*> *dataSet = new map<int,PlayerData*>();
	int i=1;
	//Get every player data
	XMLElement *pPlayerElement = pSaveData->FirstChildElement("Player");
	while(pPlayerElement) {
		PlayerData *pData = new PlayerData(pPlayerElement->Attribute("name"));
		//Get every property of each player
		XMLElement *pPropertyElement = pPlayerElement->FirstChildElement();
		PLAYER_PROP_TYPE ePro = MAX_HP;
		while(pPropertyElement)	{
			int iValue = atoi(pPropertyElement->GetText());
			pData->setProperty(ePro,iValue);
			ePro = (PLAYER_PROP_TYPE)(ePro+1);
			pPropertyElement = pPropertyElement->NextSiblingElement();
		}
		//Get items
		XMLElement *pItemElement = pPlayerElement->FirstChildElement("ItemList")->FirstChildElement("Item");
		while(pItemElement)	{
			int iItemId = pItemElement->IntAttribute("id");
			//string sItemName = string(pItemElement->Attribute("id"));
			int iItemCount = atoi(pItemElement->GetText());
			pData->getItem(iItemId,iItemCount);
			pItemElement = pItemElement->NextSiblingElement("Item");
		}
		//Get skills
		XMLElement *pSkillElement = pPlayerElement->FirstChildElement("SkillList")->FirstChildElement("Skill");
		while (pSkillElement) {
			int iSkillId = pSkillElement->IntAttribute("id");
			int iSkillLevel = atoi(pSkillElement->GetText());
			if (iSkillLevel > 0)
				pData->learnSkill(iSkillId,iSkillLevel);
			pSkillElement = pSkillElement->NextSiblingElement("Skill");
		}
		dataSet->insert(std::make_pair<int,PlayerData*>(i++,pData));
		pPlayerElement = pPlayerElement->NextSiblingElement("Player");
	}
	
	return dataSet;
}

bool SaveProcessor::savePlayerDataSet(const int iSaveNo, map<int,PlayerData*> *pData)
{
	if (!pData || iSaveNo<1)
	{
		CCLOG("Save data parameter error!");
		return false;
	}
	/*
	XMLElement *pSaveData = findNthSaveData(iSaveNo);
	if (pSaveData)//Update exsiting save
	{
		map<int,PlayerData*>::iterator it = pData->begin();
		while (it != pData->end()) //Every playerdata in memory, since not delete player data in file
		{
			XMLElement *pPlayerElement = pSaveData->FirstChildElement("Player");
			bool isFoundInFile = false;
			while (pPlayerElement)
			{
				string sNameinFile = pPlayerElement->Attribute("name");
				if (it->second->getPlayerName() == sNameinFile)
				{
					isFoundInFile = true;
					//Update properties
					XMLElement *pPropertyElement = pPlayerElement->FirstChildElement();
					PLAYER_PROP_TYPE ePro = MAX_HP;
					while(pPropertyElement)			
					{
						int iValue = it->second->getProperty(ePro);
						char cValue[10] = {0};
						_itoa(iValue,cValue,10);
						pPropertyElement->SetValue(cValue);
						ePro = (PLAYER_PROP_TYPE)(ePro+1);
						pPropertyElement = pPropertyElement->NextSiblingElement();
					}
					//Refresh items : delete all original ones and write all new into file.
					XMLElement *pItemListElement = pPlayerElement->FirstChildElement("ItemList");
					pItemListElement->DeleteChildren();
					map<string,int>::iterator itemIt = it->second->getItemList()->begin();
					while(itemIt != it->second->getItemList()->end())
					{
						XMLElement *pNewItemNode = m_doc.NewElement("Item");
						pNewItemNode->SetAttribute("name",itemIt->first.c_str());
						char cValue[10] = {0};
						_itoa(itemIt->second,cValue,10);
						pNewItemNode->SetValue(cValue);
						pItemListElement->InsertEndChild(pNewItemNode);
						itemIt++;
					}
					//Refresh skill : delete all original ones and write all new into file.
					XMLElement *pSkillListElement = pPlayerElement->FirstChildElement("SkillList");
					pSkillListElement->DeleteChildren();
					map<string,int>::iterator skillIt = it->second->getSkillList()->begin();
					while(skillIt != it->second->getSkillList()->end())
					{
						XMLElement *pNewSkillNode = m_doc.NewElement("Skill");
						pNewSkillNode->SetAttribute("name",itemIt->first.c_str());
						char cValue[10] = {0};
						_itoa(itemIt->second,cValue,10);
						pNewSkillNode->SetValue(cValue);
						pSkillListElement->InsertEndChild(pNewSkillNode);
						skillIt++;
					}
					break;
				}
				else
					pPlayerElement = pPlayerElement->NextSiblingElement("Player");
			}
			if (!isFoundInFile)
			{
				XMLElement *pNewPlayerNode = m_doc.NewElement("Player");
				string sPlayerName = it->second->getPlayerName();
				pNewPlayerNode->SetAttribute("name",sPlayerName.c_str());
				char cValue[10];
				XMLElement *pNewMaxHPNode = m_doc.NewElement("MaxHP");
				_itoa(it->second->getPropertyList()->at(MAX_HP),cValue,10);
				pNewMaxHPNode->SetValue(cValue);
				pNewPlayerNode->InsertEndChild(pNewMaxHPNode);
				XMLElement *pNewHPNode = m_doc.NewElement("HP");
				_itoa(it->second->getPropertyList()->at(CURRENT_HP),cValue,10);
				pNewHPNode->SetValue(cValue);
				pNewPlayerNode->InsertEndChild(pNewHPNode);

			}
			it++;
		}
	}
	else								//Create new save
	{
		//TODO: Build new Save data node and write to file
	}
	*/
	return true;
}
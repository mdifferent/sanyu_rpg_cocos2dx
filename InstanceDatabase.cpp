#include "InstanceDatabase.h"
const char* DATABASE_FILE_PATH = "database.xml";

InstanceDatabase *InstanceDatabase::instance = new InstanceDatabase();
InstanceDatabase* InstanceDatabase::getDatabaseInstance() {
	if (instance == NULL) {
		instance = new InstanceDatabase();
	}
	return InstanceDatabase::instance;
}

void InstanceDatabase::releaseDatabase() {
	if (instance != NULL) {
		map<int, SkillData*>::iterator skillit = instance->m_skillDataset.begin();
		while (skillit != instance->m_skillDataset.end()) {
			delete skillit->second;
		}
		instance->m_skillDataset.clear();
		map<int, ItemData*>::iterator itemit = instance->m_itemDataset.begin();
		while (itemit != instance->m_itemDataset.end()) {
			delete itemit->second;
		}
		instance->m_itemDataset.clear();
	}
	delete instance;
	instance = NULL;
}

SkillData *InstanceDatabase::getSkillById(int id) {
	if (instance->m_skillDataset.find(id) != instance->m_skillDataset.end())
		return instance->m_skillDataset.at(id);
	else
		return NULL;
}

ItemData *InstanceDatabase::getItemById(int id) {
	if (instance->m_itemDataset.find(id) != instance->m_itemDataset.end())
		return instance->m_itemDataset.at(id);
	else
		return NULL;
}

bool InstanceDatabase::initSkillSetByIds(list<int>) {
	return true;
}

bool InstanceDatabase::initItemSetByIds(list<int>) {
	//TODO: stub data here
	ItemData *p1 = new ItemData(1,"Æ»¹û",ItemData::CONSUME,ItemData::FRIEND,false);
	p1->setEffect(make_pair<ItemData::ITEM_EFFECT_ATTRIBUTE,int>(ItemData::CURRENT_HP,10));
	m_itemDataset.insert(make_pair<int,ItemData*>(1,p1));

	ItemData *p2 = new ItemData(2,"Ñ¸½£",ItemData::CONSUME,ItemData::ENEMY,false);
	p2->setEffect(make_pair<ItemData::ITEM_EFFECT_ATTRIBUTE,int>(ItemData::CURRENT_HP,10));
	m_itemDataset.insert(make_pair<int,ItemData*>(2,p2));

	return true;
}
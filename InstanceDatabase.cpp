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
	//TODO: stub data here
	SkillData *p1 = new SkillData(1,"»ðÇò",SkillData::ENEMY,false,50,SkillData::ATTACK);
	p1->setEffect(make_pair<SkillData::EffectAttribute,int>(SkillData::CURRENT_HP,20));
	m_skillDataset.insert(make_pair<int,SkillData*>(1,p1));
	SkillData *p2 = new SkillData(2,"±©·çÑ©",SkillData::ENEMY,true,150,SkillData::ATTACK);
	p2->setEffect(make_pair<SkillData::EffectAttribute,int>(SkillData::CURRENT_HP,100));
	m_skillDataset.insert(make_pair<int,SkillData*>(2,p2));
	SkillData *p3 = new SkillData(3,"Äþ¾²Ö®Óê",SkillData::FRIEND,true,200,SkillData::RECOVER);
	p3->setEffect(make_pair<SkillData::EffectAttribute,int>(SkillData::CURRENT_HP,100));
	m_skillDataset.insert(make_pair<int,SkillData*>(3,p3));
	return true;
}

bool InstanceDatabase::initItemSetByIds(list<int>) {
	//TODO: stub data here
	ItemData *p1 = new ItemData(1,"Æ»¹û",ItemData::FRIEND,false,ItemData::CONSUME);
	p1->setEffect(make_pair<ItemData::EffectAttribute,int>(ItemData::CURRENT_HP,10));
	m_itemDataset.insert(make_pair<int,ItemData*>(1,p1));

	ItemData *p2 = new ItemData(2,"Ñ¸½£",ItemData::ENEMY,false,ItemData::CONSUME);
	p2->setEffect(make_pair<ItemData::EffectAttribute,int>(ItemData::CURRENT_HP,10));
	m_itemDataset.insert(make_pair<int,ItemData*>(2,p2));

	return true;
}
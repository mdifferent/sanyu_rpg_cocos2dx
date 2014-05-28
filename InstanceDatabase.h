#pragma once
#include "SkillData.h"
#include "ItemData.h"
#include <map>
#include <list>

using namespace std;

class InstanceDatabase {
public:
	static InstanceDatabase* getDatabaseInstance();
	static void releaseDatabase();

	SkillData *getSkillById(int id);
	ItemData *getItemById(int id);

	bool initSkillSetByIds(list<int>);
	bool initItemSetByIds(list<int>);
private:
	InstanceDatabase(){};
	~InstanceDatabase(){};
	static InstanceDatabase *instance;
	map<int, SkillData*> m_skillDataset;
	map<int, ItemData*> m_itemDataset;
};
#pragma once
#include <string>
#include <map>
using namespace std;

enum ITEM_TYPE {
	CONSUME,
	ATTRIBUTE,
	SPECIAL
};

enum ITEM_TARGET_TYPE {
	FRIEND,
	ENEMY
};

enum ITEM_EFFECT_ATTRIBUTE {
	MAX_HP,
	CURRENT_HP,
	MAX_SP,
	CURRENT_SP,
	MELEE_ATTACK = 6,
	DEFENSE
}

class ItemData
{
public:
	ItemData();
	~ItemData();
private:
	int id;
	string name;
	ITEM_TYPE type;
	ITEM_TARGET_TYPE target;
	bool isMultiTarget;
	map<ITEM_EFFECT_ATTRIBUTE,int> effect;
};
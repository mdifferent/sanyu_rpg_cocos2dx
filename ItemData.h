#pragma once
#include <string>
#include <map>
using namespace std;

class ItemData
{
public:
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
		MELEE_ATTACK = 6,	//Match attribute definition in BattlerData class
		DEFENSE
	};
		
	ItemData(int id,string name,ITEM_TYPE type,ITEM_TARGET_TYPE target,bool multi)
		:m_id(id),m_name(name),m_type(type),m_target(target),m_isMultiTarget(multi){};
	~ItemData(){}
	string getItemName() const {return m_name;}
	void setEffect(pair<ITEM_EFFECT_ATTRIBUTE,int>);
private:
	int m_id;
	string m_name;
	ITEM_TYPE m_type;
	ITEM_TARGET_TYPE m_target;
	bool m_isMultiTarget;
	map<ITEM_EFFECT_ATTRIBUTE,int> m_effects;
};
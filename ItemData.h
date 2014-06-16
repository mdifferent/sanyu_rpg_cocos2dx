#pragma once
#include "AbstractListItemData.h"
#include <string>
#include <map>
using namespace std;

class ItemData : public AbstractListItemData
{
public:
	enum ITEM_TYPE {
		CONSUME,
		ATTRIBUTE,
		SPECIAL
	};
	/*
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
		*/
	ItemData(int id, string name, TargetType target, bool multi, ITEM_TYPE type)
		:AbstractListItemData(id,name,target,multi),m_type(type) {}
//		:m_id(id),m_name(name),m_type(type),m_target(target),m_isMultiTarget(multi){};
	~ItemData(){}

//	string getItemName() const {return m_name;}
	ITEM_TYPE getItemType() const {return m_type;}
	/*
	ITEM_TARGET_TYPE getTargetType() const {return m_target;}
	bool getMultiTarget() const {return m_isMultiTarget;}
	map<ITEM_EFFECT_ATTRIBUTE,int> &getItemEffects() {return m_effects;}
	void setEffect(pair<ITEM_EFFECT_ATTRIBUTE,int>);*/
private:
	ITEM_TYPE m_type;
	/*
	int m_id;
	string m_name;
	ITEM_TARGET_TYPE m_target;
	bool m_isMultiTarget;
	map<ITEM_EFFECT_ATTRIBUTE,int> m_effects;*/
};
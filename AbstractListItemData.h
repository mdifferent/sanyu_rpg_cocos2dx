#pragma once
#include <string>
#include <map>
using namespace std;

class AbstractListItemData
{
public:
	enum TargetType {FRIEND, ENEMY};
	enum EffectAttribute {MAX_HP, CURRENT_HP, MAX_SP, CURRENT_SP, MELEE_ATTACK=6, DEFENSE};
	
	AbstractListItemData(int id,string name,ITEM_TYPE type,TargetType target,bool multi)
		:m_id(id),m_name(name),m_type(type),m_target(target),m_isMultiTarget(multi) {}
	~AbstractListItemData() {}

	string 
private:
	int m_id;
	string m_name;
	bool m_isMultiTarget;
};
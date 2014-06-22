#pragma once
#include "AbstractListItemData.h"
#include <string>
#include <map>
using namespace std;

class SkillData : public AbstractListItemData
{
public:
	enum SKILL_TYPE {
		RECOVER,
		ATTACK,
		ENHENCE,
		WEAKEN
	};
	SkillData(int id, string name, TargetType target, bool multi, int cost,SKILL_TYPE type)
		:AbstractListItemData(id,name,target,multi),m_cost(cost),m_type(type) {}
	~SkillData(){}
	
	SKILL_TYPE getSkillType() const {return m_type;}
	int getCost() const {return m_cost;}
private:
	int m_cost;
	SKILL_TYPE m_type;
};
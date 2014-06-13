#pragma once
#include <string>
#include <map>
using namespace std;

class SkillData
{
public:
	enum SKILL_TYPE {
		RECOVER,
		ATTACK,
		ENHENCE,
		WEAKEN
	};

	enum SKILL_TARGET_TYPE {
		FRIEND,
		ENEMY
	};

	enum SKILL_EFFECT_ATTRIBUTE {
		MAX_HP,
		CURRENT_HP,
		MAX_SP,
		CURRENT_SP,
		MELEE_ATTACK = 6,
		DEFENSE
	};
	SkillData(int id, string name, int cost,SKILL_TYPE type, SKILL_TARGET_TYPE target, bool multi)
		:m_id(id),m_name(name),m_cost(cost),m_type(type),m_target(target),m_isMultiTarget(multi){}
	~SkillData(){}
	
	string getSkillName() const {return m_name;}
	SKILL_TYPE getSkillType() const {return m_type;}
	SKILL_TARGET_TYPE getTargetType() const {return m_target;}
	bool getMultiTarget() const {return m_isMultiTarget;}
	map<SKILL_EFFECT_ATTRIBUTE,int> &getItemEffects() {return m_effects;}
	void setEffect(pair<SKILL_EFFECT_ATTRIBUTE,int>);
	int getCost() const {return m_cost;}
private:
	int m_id;
	string m_name;
	int m_cost;
	SKILL_TYPE m_type;
	SKILL_TARGET_TYPE m_target;
	bool m_isMultiTarget;
	map<SKILL_EFFECT_ATTRIBUTE,int> m_effects;
};
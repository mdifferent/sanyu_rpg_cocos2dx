#pragma once
#include <string>
#include <map>
using namespace std;

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
}

class SkillData
{
public:
	SkillData();
	~SkillData();
private:
	int id;
	string name;
	int cost;
	SKILL_TYPE type;
	SKILL_TARGET_TYPE target;
	bool isMultiTarget;
	map<SKILL_EFFECT_ATTRIBUTE,int> effect;
};
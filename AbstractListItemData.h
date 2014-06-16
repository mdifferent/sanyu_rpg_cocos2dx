#pragma once
#include <string>
#include <map>
using namespace std;

class AbstractListItemData
{
public:
	enum TargetType {FRIEND, ENEMY};
	enum EffectAttribute {MAX_HP, CURRENT_HP, MAX_SP, CURRENT_SP, MELEE_ATTACK=6, DEFENSE};

	AbstractListItemData(int id,string name,TargetType target,bool multi)
		:m_id(id),m_name(name),m_targetType(target),m_isMultiTarget(multi) {}
	virtual ~AbstractListItemData() {}

	string getName() const {return m_name;}
	TargetType getTargetType() const {return m_targetType;}
	bool getMultiTarget() const {return m_isMultiTarget;}
	map<EffectAttribute,int> &getItemEffects() {return m_effects;}
	void setEffect(pair<EffectAttribute,int> effect) {m_effects[effect.first] = effect.second;}
	
private:
	int m_id;
	string m_name;
	bool m_isMultiTarget;
	TargetType m_targetType;
	map<EffectAttribute,int> m_effects;
};
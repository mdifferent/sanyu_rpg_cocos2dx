#include "SkillData.h"

void SkillData::setEffect(pair<SKILL_EFFECT_ATTRIBUTE,int> effect) {
	if (m_effects.find(effect.first) == m_effects.end()) {
		m_effects.insert(effect);
	}
	else {
		m_effects[effect.first] = effect.second;
	}
}
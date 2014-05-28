#include "ItemData.h"

void ItemData::setEffect(pair<ITEM_EFFECT_ATTRIBUTE,int> effect) {
	if (m_effects.find(effect.first) == m_effects.end()) {
		m_effects.insert(effect);
	}
	else {
		m_effects[effect.first] = effect.second;
	}
}
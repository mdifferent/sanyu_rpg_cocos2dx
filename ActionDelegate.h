#pragma once
#include "PlayerLayer.h"
#include "MonsterLayer.h"

class ActionDelegate
{
public:
	ActionDelegate(PlayerLayer *sourcePlayer, MonsterLayer *targetLayer);
	~ActionDelegate(void);
	
	void runAttack();
private:
	PlayerLayer *m_playerLayer;
	MonsterLayer *m_monsterLayer;
};


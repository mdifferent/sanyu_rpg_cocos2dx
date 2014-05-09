#include "ActionDelegate.h"


ActionDelegate::ActionDelegate(PlayerLayer *sourcePlayer, MonsterLayer *targetLayer):m_playerLayer(sourcePlayer),m_monsterLayer(targetLayer)
{
}


ActionDelegate::~ActionDelegate(void)
{
}

void ActionDelegate::runAttack()
{
	m_monsterLayer->setTouchEnabled(true);
	m_monsterLayer->setWaitForClick(true);
}
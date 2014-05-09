#pragma once
#include "../cocos2dx/layers_scenes_transitions_nodes/CCScene.h"
#include "BattleData.h"
#include "BackgroundLayer.h"
#include "InfoBarLayer.h"
#include "PlayerLayer.h"
#include "MonsterLayer.h"
#include "ActionDelegate.h"

USING_NS_CC;
class BattleField :
	public CCScene
{
public:
	BattleField(void);
	~BattleField(void);
	static BattleField* scene(int iSceneNo);
	virtual bool init();
private:
	BackgroundLayer *m_bg;
	InfoBarLayer *m_info_back;
	PlayerLayer *m_players;
	MonsterLayer *m_monsters;
	ActionDelegate *m_delegate;

	int m_sceneNo;
	BattleData *m_data;

};


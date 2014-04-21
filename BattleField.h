#pragma once
#include "c:\program files\cocos2d-x-2.2.2\cocos2dx\layers_scenes_transitions_nodes\ccscene.h"
#include "BattleData.h"
#include "BackgroundLayer.h"
#include "PlayerLayer.h"
#include "MonsterLayer.h"

USING_NS_CC;
class BattleField :
	public CCScene
{
public:
	BattleField(void);
	~BattleField(void);
	static CCScene* scene(int iSceneNo);
	CREATE_FUNC(BattleField);
	virtual bool init();

private:
	BackgroundLayer *m_bg;
	CCLayer *m_info_back;
	PlayerLayer *m_players;
	MonsterLayer *m_monsters;

	int m_sceneNo;
	BattleData *m_data;

};


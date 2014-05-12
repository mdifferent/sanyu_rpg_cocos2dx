#pragma once
#include "../cocos2dx/layers_scenes_transitions_nodes/CCLayer.h"
#include "cocos2d.h"
#include <map>
#include <string>
#include "MonsterData.h"

USING_NS_CC;

enum MONSTER_LAYER_STATUS {
	WAIT_TARGET,
	TARGET_SELECTED,
	SLEEP,
};

class MonsterLayer :
	public CCLayer
{
public:
	MonsterLayer(void);
	~MonsterLayer(void);
	static MonsterLayer *create(map<int,MonsterData*> *data);
	void onEnter();
    bool init();

	virtual bool ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent);

	void setStatus(MONSTER_LAYER_STATUS status){m_status = status;};
	MONSTER_LAYER_STATUS getStatus(){return m_status;};

private:
	CCArray *m_monsters;
    map<int, MonsterData*> *m_data;
	MONSTER_LAYER_STATUS m_status;
};


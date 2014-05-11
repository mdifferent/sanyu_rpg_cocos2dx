#pragma once
#include "../cocos2dx/layers_scenes_transitions_nodes/CCLayer.h"
#include "cocos2d.h"
#include <map>
#include <string>
#include "MonsterData.h"
//#include "ActionDelegate.h"

USING_NS_CC;
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
	//void setDelegate(ActionDelegate *pDelegate){m_pDelegate = pDelegate;};
	void setWaitForClick(bool bWait){m_waitForClick = bWait;};

private:
	CCArray *m_monsters;
    map<int, MonsterData*> *m_data;
	bool m_waitForClick;
	//ActionDelegate *m_pDelegate;
};


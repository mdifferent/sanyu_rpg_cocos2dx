#pragma once
#include "../cocos2dx/layers_scenes_transitions_nodes/CCLayer.h"
#include "cocos2d.h"
#include <map>
#include <string>
#include "PlayerData.h"
USING_NS_CC;

class PlayerLayer :
	public CCLayer
{
public:
	PlayerLayer(void);
	~PlayerLayer(void);
	static PlayerLayer *create(map<int,PlayerData> &data);
	void onEnter();
    bool init();
	
	virtual bool ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent);
	/*virtual void ccTouchMoved(CCTouch *pTouch, CCEvent *pEvent);
    virtual void ccTouchEnded(CCTouch *pTouch, CCEvent *pEvent);  
    virtual void ccTouchCancelled(CCTouch *pTouch, CCEvent *pEvent);*/
    
    void playerAttackCallback(CCObject* pSender);
    void playerSkillCallback(CCObject* pSender);
    void playerGuardCallback(CCObject* pSender);
    void playerEscapeCallback(CCObject* pSender);
    
private:
	//CCArray *m_players;
    map<int, PlayerData> *m_data;
};


#pragma once
#include "../cocos2dx/layers_scenes_transitions_nodes/CCLayer.h"
#include "cocos2d.h"
#include <map>
#include <string>
#include "PlayerData.h"
#include "ActionDelegate.h"

const char *HP_BAR_IMG_FILE_PATH = "sanyu/hp_bar.png";
const char *SP_BAR_IMG_FILE_PATH = "sanyu/sp_bar.png";
const int NAME_FONT_SIZE = 20;
const int MENU_FONT_SIZE = 20;
const int HP_NUM_FONT_SIZE = 16;
const char *NAME_FONT = "Arial";
const int PLAYER_SPRITE_HEIGHT = 180;
const int PLAYER_SPRITE_WIDTH = 200;

USING_NS_CC;

class PlayerLayer :
	public CCLayer
{
public:
	PlayerLayer(void);
	~PlayerLayer(void);
	static PlayerLayer *create(map<int,PlayerData*> *data);
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

	void setDelegate(ActionDelegate *pDelegate){m_pDelegate = pDelegate;};
    
private:
	//CCArray *m_players;
    map<int, PlayerData*> *m_data;
	ActionDelegate *m_pDelegate;
};


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
	enum PLAYER_LAYER_STATUS {
		WAIT_COMMAND,
		MENU_OPEN,
		MENU_SELECTED,
		WAIT_TARGET,
		TARGET_SELECTED,
		FINISHED
	};

	enum MenuStatus {
		NONE,
		ATTACK,
		SKILL,
		GUARD,
		ITEM,
		ESCAPE
	};
	PlayerLayer(void);
	~PlayerLayer(void);
	static PlayerLayer *create(map<int,PlayerData*> *data);
	void onEnter();
    bool init();
    
    PLAYER_LAYER_STATUS getStatus() {return m_status;}
    void setStatus(PLAYER_LAYER_STATUS status) {m_status = status;}
	int getSelectedPlayer() {CCLOG("Selected Player:%d",m_selectedPlayer);return m_selectedPlayer;}
	void resetSelectedPlayer() {m_selectedPlayer = -1;}
	MenuStatus getSelectedMenu() const {return m_selectedMenu;}
	void resetSelectedMenu() {m_selectedMenu = NONE;}

	virtual bool ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent);
	/*virtual void ccTouchMoved(CCTouch *pTouch, CCEvent *pEvent);
    virtual void ccTouchEnded(CCTouch *pTouch, CCEvent *pEvent);  
    virtual void ccTouchCancelled(CCTouch *pTouch, CCEvent *pEvent);*/
    
    void playerAttackCallback(CCObject* pSender);
    void playerSkillCallback(CCObject* pSender);
    void playerGuardCallback(CCObject* pSender);
    void playerEscapeCallback(CCObject* pSender);
	void playerItemCallback(CCObject* pSender);

	void onPlayerKilled(int i);
	void onPlayerPropModified(PLAYER_PROP_TYPE, int, int); 	//iDamage > 0 : Recover; <0 : Damage
	void beforeSpecialAttack(int num = 0);
	void afterSpecialAttack(int num = 0);
	void openMenu(int);
	void closeMenu(void);
    
private:
    map<int, PlayerData*> *m_data;
	PLAYER_LAYER_STATUS m_status;
	MenuStatus m_selectedMenu;
	int m_selectedPlayer;
	CCLabelBMFont *m_pFont;
};


#ifndef __TOUCHEVENTLAYER_H__
#define __TOUCHEVENTLAYER_H__
#include "../cocos2dx/layers_scenes_transitions_nodes/CCLayer.h"
#include "cocos2d.h"
#include "TouchEventProcessDelegate.h"
#include <stack>

USING_NS_CC;
using namespace std;

class TouchEventLayer : public CCLayer
{
public:
	enum Status {INIT,				//Wait user to click on player head
		WAIT_PLAYER_MENU,			//Wait user to choose action of player
		PLAYER_WAIT_TARGET,			//Wait user to choose target fron player
		MONSTER_WAIT_TARGET,		//Wait user to choose target from monster
		WAIT_SELECT_LIST,			//Wait user to choose item from select list
		SPECIAL_ATTACK				//In special attack mode
	};

	TouchEventLayer(void);
	~TouchEventLayer(void);
	bool init();
    void setDelegate(TouchEventProcessDelegate *delegate) {m_delegate = delegate;}

	void setStatus(const Status status);
	Status getStatus() const {return m_statusList.top();}
	void rollbackStatus() {m_statusList.pop();}

    //TouchDelegate
	virtual bool ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent);
    
    //Menu selectors
    void playerAttackCallback(CCObject* pSender);
    void playerSkillCallback(CCObject* pSender);
    void playerGuardCallback(CCObject* pSender);
    void playerEscapeCallback(CCObject* pSender);
	void playerItemCallback(CCObject* pSender);

private:
    float getSpriteHorizontalLeft(int num, int count);
	int getTouchedPlayerNo(float x);
	void openMenu(int x,int y);
	void closeMenu();
private:
	stack<Status> m_statusList;
    CCPoint *m_touchPoint;
    TouchEventProcessDelegate *m_delegate;
    CCMenu *m_pMenu;
};
#endif
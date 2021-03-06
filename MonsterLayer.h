#pragma once
#include "../cocos2dx/layers_scenes_transitions_nodes/CCLayer.h"
#include "cocos2d.h"
#include <map>
#include <string>
#include "MonsterData.h"

USING_NS_CC;

class MonsterLayer :
	public CCLayer
{
public:
	enum MONSTER_LAYER_STATUS {
		WAIT_TARGET,
		TARGET_SELECTED,
		SPECIAL_ATTACK_PRE,
		SPECIAL_ATTACK,
		SPECIAL_ATTACK_FINISHED,
		SLEEP,
	};
	MonsterLayer(void);
	~MonsterLayer(void);
	static MonsterLayer *create(map<int,MonsterData*> *data);
	void onEnter();
    bool init();

	virtual bool ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent);
	virtual void ccTouchMoved(CCTouch *pTouch, CCEvent *pEvent);
    virtual void ccTouchEnded(CCTouch *pTouch, CCEvent *pEvent);  
    //virtual void ccTouchCancelled(CCTouch *pTouch, CCEvent *pEvent);

	void setStatus(MONSTER_LAYER_STATUS status){m_status = status;};
	MONSTER_LAYER_STATUS getStatus(){return m_status;};
	int getTarget() {return m_target;}
	void resetTarget() {m_target = -1;}
	void killMosnter(int);
	void onAttacked(int iNum, int iDamage);
	void onMagicMatrixAvailable();
	void onMagicMatrixUnavailable();
	void initSpecialAttack(int);
	void onSpecialAttack(float);
	bool isBubbleFailed() const {return m_isBubbleFailed;}

private:
	CCArray *m_monsters;
    map<int, MonsterData*> *m_data;			//Monster data model
	CCLabelBMFont *m_pFont;
	MONSTER_LAYER_STATUS m_status;
	int m_target;
	CCSprite *m_magicTag;
	CCSprite *m_magicPointer;
	CCTexture2D *m_magicAva;
	CCTexture2D *m_magicUnava;
	bool m_isMagicMatrixAvailable;
	CCProgressTimer *m_longHPBar;
	CCSprite *m_timeBarEmpty;
	CCProgressTimer *m_timeBarFull;
	CCArray *m_bubbles;
	int m_BubbleHit;
	bool m_isBubbleFailed;
	map<int,CCPoint> m_originalPos;
};


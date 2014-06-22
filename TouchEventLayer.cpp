#include "TouchEventLayer.h"
const int PLAYER_SPRITE_HEIGHT = 180;
const int PLAYER_SPRITE_WIDTH = 200;
const char *NAME_FONT = "Arial";
const int NAME_FONT_SIZE = 20;
const int MENU_FONT_SIZE = 20;

bool TouchEventLayer::init()
{
    //Init menu
	CCMenuItemLabel *pAttackItem = CCMenuItemLabel::create(CCLabelTTF::create("ATTACK",NAME_FONT,MENU_FONT_SIZE),
                                                           this,menu_selector(TouchEventLayer::playerAttackCallback));
	CCMenuItemLabel *pSkillItem = CCMenuItemLabel::create(CCLabelTTF::create("SKILL",NAME_FONT,MENU_FONT_SIZE),
                                                          this,menu_selector(TouchEventLayer::playerSkillCallback));
	CCMenuItemLabel *pGuardItem = CCMenuItemLabel::create(CCLabelTTF::create("GUARD",NAME_FONT,MENU_FONT_SIZE),
                                                          this,menu_selector(TouchEventLayer::playerGuardCallback));
	CCMenuItemLabel *pEscapeItem = CCMenuItemLabel::create(CCLabelTTF::create("ESCAPE",NAME_FONT,MENU_FONT_SIZE),
                                                           this,menu_selector(TouchEventLayer::playerEscapeCallback));
	CCMenuItemLabel *pItemItem = CCMenuItemLabel::create(CCLabelTTF::create("ITEM",NAME_FONT,MENU_FONT_SIZE),
                                                         this,menu_selector(TouchEventLayer::playerItemCallback));
	m_pMenu = CCMenu::create(pAttackItem,pSkillItem,pItemItem,pGuardItem,pEscapeItem,NULL);
	m_pMenu->alignItemsVertically();

	return true;
}

bool TouchEventLayer::ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent)
{
	CCPoint touchPos = pTouch->getLocation();
    int iPlayerCount = m_delegate->getPlayerCount();
	switch(m_TouchStatus) {
	case INIT:
        for (int i= 0;i<iPlayerCount;++i) {
            if (touchPos.y > 0 && touchPos.y < PLAYER_SPRITE_HEIGHT) {
                float fLeftCornerX = getSpriteHorizontalLeft(i,iPlayerCount);
                float fSpriteMiddleX = fLeftCornerX+PLAYER_SPRITE_WIDTH*0.5;
                if (touchPos.x > fLeftCornerX && touchPos.x < fLeftCornerX + PLAYER_SPRITE_WIDTH) {
                    //TODO:Remember selected player
                    m_pMenu->setEnabled(true);
					m_pMenu->setVisible(true);
					m_pMenu->setPosition(ccp(fSpriteMiddleX+50,PLAYER_SPRITE_HEIGHT*0.5+60));
                    addChild(m_pMenu);
					m_pMenu->runAction(CCFadeIn::create(0.2f));
                    setStatus(WAIT_PLAYER_MENU);
                    m_delegate->receiveMessage(TouchEventProcessDelegate::SELECT_PLAYER,i);
                    break;
                }
            }
        }
		break;
	case WAIT_PLAYER_MENU:
		break;
	case PLAYER_WAIT_TARGET:
		break;
	case MONSTER_WAIT_TARGET:
		break;
	case WAIT_SELECT_LIST:
		break;
	case SPECIAL_ATTACK:
		break;
	}
	return true;
}

void TouchEventLayer::playerAttackCallback(CCObject* pSender)
{
    CCLOG("ATTACK");
}

void TouchEventLayer::playerSkillCallback(CCObject* pSender)
{
    CCLOG("SKILL");
}

void TouchEventLayer::playerGuardCallback(CCObject* pSender)
{
    CCLOG("GUARD");
}

void TouchEventLayer::playerEscapeCallback(CCObject* pSender)
{
    CCLOG("ESCAPE");
}

void TouchEventLayer::playerItemCallback(CCObject* pSender) {
	CCLOG("ITEM");
}

float getSpriteHorizontalLeft(int num, int count)
{
    float fScreenWidth = CCDirector::sharedDirector()->getVisibleSize().width;
    float fPlayerX = fScreenWidth*0.5+(num-count*0.5)*PLAYER_SPRITE_WIDTH;
    return fPlayerX;
}
#include "TouchEventLayer.h"
#include "ConstValues.h"

bool TouchEventLayer::init()
{
	if (m_statusList.empty())
		m_statusList.push(INIT);
	else
		setStatus(INIT);
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
	CCLOG("Touch at %f,%f",touchPos.x,touchPos.y);
    int iPlayerCount = m_delegate->getPlayerCount();
	int iMonsterCount = m_delegate->getMonsterCount();
	switch(getStatus()) {
	case INIT:
		if (touchPos.y > 0 && touchPos.y < PLAYER_SPRITE_HEIGHT) {
			int iTouchedPlayerNo = getTouchedPlayerNo(touchPos.x);
			m_delegate->setCurrentPlayer(iTouchedPlayerNo);
            m_delegate->receiveMessage(TouchEventProcessDelegate::SELECT_PLAYER,iTouchedPlayerNo);
			float fLeftCornerX = getSpriteHorizontalLeft(iTouchedPlayerNo,iPlayerCount);
			float fSpriteMiddleX = fLeftCornerX+PLAYER_SPRITE_WIDTH*0.5;
			openMenu(fSpriteMiddleX+50,PLAYER_SPRITE_HEIGHT*0.5+60);
			setStatus(WAIT_PLAYER_MENU);
		}
		break;
	case WAIT_PLAYER_MENU:
		if (touchPos.y > PLAYER_SPRITE_HEIGHT) {
			closeMenu();
			rollbackStatus();
		}
		else {
			int iTouchedPlayerNo = getTouchedPlayerNo(touchPos.x);
			float fLeftCornerX = getSpriteHorizontalLeft(iTouchedPlayerNo,iPlayerCount);
			float fSpriteMiddleX = fLeftCornerX+PLAYER_SPRITE_WIDTH*0.5;
			if (iTouchedPlayerNo != m_delegate->getCurrentPlayer()) {
				m_pMenu->runAction(CCFadeOut::create(0.1f));
				m_pMenu->setPosition(ccp(fSpriteMiddleX+50,PLAYER_SPRITE_HEIGHT*0.5+60));
				m_pMenu->runAction(CCFadeIn::create(0.2f));
				//m_delegate->setCurrentPlayer(iTouchedPlayerNo);
				m_delegate->receiveMessage(TouchEventProcessDelegate::SELECT_PLAYER,iTouchedPlayerNo);
			}
		}
		break;
	case PLAYER_WAIT_TARGET:
		if (touchPos.y > 0 && touchPos.y < PLAYER_SPRITE_HEIGHT) {
			int iTouchedPlayerNo = getTouchedPlayerNo(touchPos.x);
			m_delegate->setCurrentPlayer(iTouchedPlayerNo);
			setStatus(INIT);
		}
		else {
			rollbackStatus();
		}
		break;
	case MONSTER_WAIT_TARGET:
		if (touchPos.y > PLAYER_SPRITE_HEIGHT) {
			for(int i=0;i<iMonsterCount;i++)
				if (m_delegate->isSelectMonsterOfNo(i)) {
					m_delegate->receiveMessage(TouchEventProcessDelegate::SELECT_MONSTER,i);
					setStatus(INIT);
					break;
				}
		}
		//TODO:Rollback to select list
		break;
	case WAIT_SELECT_LIST:
		return false;
	case SPECIAL_ATTACK:
		break;
	}
	return true;
}

void TouchEventLayer::playerAttackCallback(CCObject* pSender)
{
    CCLOG("ATTACK");
	m_delegate->receiveMessage(TouchEventProcessDelegate::PLAYER_ACTION_ATTACK);
}

void TouchEventLayer::playerItemCallback(CCObject* pSender) {
	CCLOG("ITEM");
	m_delegate->receiveMessage(TouchEventProcessDelegate::PLAYER_ACTION_ITEM);
}

void TouchEventLayer::playerSkillCallback(CCObject* pSender)
{
    CCLOG("SKILL");
	m_delegate->receiveMessage(TouchEventProcessDelegate::PLAYER_ACTION_SKILL);
}

void TouchEventLayer::playerGuardCallback(CCObject* pSender)
{
    CCLOG("GUARD");
	m_delegate->receiveMessage(TouchEventProcessDelegate::PLAYER_ACTION_DEFENSE);
}

void TouchEventLayer::playerEscapeCallback(CCObject* pSender)
{
    CCLOG("ESCAPE");
	m_delegate->receiveMessage(TouchEventProcessDelegate::PLAYER_ACTION_ESCAPE);
}

float TouchEventLayer::getSpriteHorizontalLeft(int num, int count)
{
    float fScreenWidth = CCDirector::sharedDirector()->getVisibleSize().width;
    float fPlayerX = fScreenWidth*0.5+(num-count*0.5)*PLAYER_SPRITE_WIDTH;
    return fPlayerX;
}

int TouchEventLayer::getTouchedPlayerNo(float x) 
{
	int iPlayerCount = m_delegate->getPlayerCount();
	for (int i= 0;i<iPlayerCount;++i) {
		float fLeftCornerX = getSpriteHorizontalLeft(i,iPlayerCount);
		if (x > fLeftCornerX && x < fLeftCornerX + PLAYER_SPRITE_WIDTH) {
			return i;
		}
	}
	return -1;
}

void TouchEventLayer::openMenu(int x,int y)
{
	assert(m_pMenu);
	addChild(m_pMenu);
    m_pMenu->setEnabled(true);
	m_pMenu->setVisible(true);
	m_pMenu->setPosition(ccp(x,y));
	m_pMenu->runAction(CCFadeIn::create(0.2f));
}

void TouchEventLayer::closeMenu()
{
	m_pMenu->runAction(CCFadeOut::create(0.1f));
	m_pMenu->setTouchEnabled(false);
	m_pMenu->setVisible(false);
	removeChild(m_pMenu);
}

void TouchEventLayer::setStatus(const Status status) {
	if (status == INIT && !m_statusList.empty()) {
		while (m_statusList.top() != INIT)
			m_statusList.pop();
	}
	else
		m_statusList.push(status);
}
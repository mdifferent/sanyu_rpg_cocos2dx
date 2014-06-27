#include "MonsterLayer.h"
#include "ConstValues.h"
#include "Resources.h"


MonsterLayer::MonsterLayer(void)
{
}


MonsterLayer::~MonsterLayer(void)
{
}

bool MonsterLayer::init() {
	CCAssert(CCLayer::init(),"CCLayer init failed!");
    int iPlayerCount = m_data->size();
	this->setTouchEnabled(true);
	CCDirector::sharedDirector()->getTouchDispatcher()->addTargetedDelegate(this,1,false);
	float fScreenWidth =  CCDirector::sharedDirector()->getVisibleSize().width;
	float fScreenHeight =  CCDirector::sharedDirector()->getVisibleSize().height;
	for (int i = 0;i<iPlayerCount;++i) {
		string name = m_data->at(i)->getName();
		const char *pName = name.c_str();
        CCLOG("%s",pName);
		CCAssert(pName,"Get Monster name failed!");
		
		CCSprite *pSprite = CCSprite::create(pName);
		CCAssert(pSprite,"Get Monster sprite failed!");
		float fPlayerWidth = pSprite->getContentSize().width;
		float fPlayerHeight = pSprite->getContentSize().height;
		pSprite->setPosition(ccp(fScreenWidth*0.5+(i-iPlayerCount*0.5+0.5)*fPlayerWidth,fScreenHeight*0.5));
		pSprite->setOpacity(0);
		addChild(pSprite,0,i);
		m_monsters->addObject(pSprite);
		
		//HP Bar				
		CCProgressTimer *hpBarTimer = CCProgressTimer::create(CCSprite::create(MONSTER_HP_BAR_PATH));
		hpBarTimer->setType(kCCProgressTimerTypeBar);
		hpBarTimer->setMidpoint(ccp(0,0));
		hpBarTimer->setPercentage(100);
		hpBarTimer->setBarChangeRate(ccp(1,0));
		hpBarTimer->setPosition(ccp(pSprite->getPositionX(),
			pSprite->getPositionY() + fPlayerHeight*0.5 + hpBarTimer->getContentSize().height*0.5));
		hpBarTimer->setOpacity(0);
		addChild(hpBarTimer,1,iPlayerCount+i);
	}
	//Damage number
	m_pFont = CCLabelBMFont::create("0",FONT_PATH);
	m_pFont->setColor(ccYELLOW);
	m_pFont->setOpacity(0);
	addChild(m_pFont,4);

	//Magic matrix tag
	m_magicTag = CCSprite::create(MAGIC_BTN_PATH);
	m_magicTag->setOpacity(0);
	m_magicTag->setPosition(ccp(750,550));
	addChild(m_magicTag);

	m_magicPointer = CCSprite::create(MAGIC_UNAVA_PATH);
	m_magicPointer->setOpacity(0);
	m_magicPointer->setPosition(ccp(750,550));
	addChild(m_magicPointer);
	m_magicAva = CCTextureCache::sharedTextureCache()->addImage(MAGIC_AVA_PATH);
	m_magicUnava = CCTextureCache::sharedTextureCache()->addImage(MAGIC_UNAVA_PATH);

	m_longHPBar = CCProgressTimer::create(CCSprite::create(LONG_HP_BAR));
	m_longHPBar->setType(kCCProgressTimerTypeBar);
	m_longHPBar->setMidpoint(ccp(0,0));
	m_longHPBar->setPercentage(100);
	m_longHPBar->setBarChangeRate(ccp(1,0));
	m_longHPBar->setOpacity(0);
	addChild(m_longHPBar,2);

	m_timeBarEmpty = CCSprite::create(TIME_BAR_EMPTY);
	m_timeBarEmpty->setOpacity(0);
	addChild(m_timeBarEmpty,2);

	m_timeBarFull = CCProgressTimer::create(CCSprite::create(TIME_BAR_FULL));
	m_timeBarFull->setType(kCCProgressTimerTypeBar);
	m_timeBarFull->setMidpoint(ccp(0,0));
	m_timeBarFull->setPercentage(100);
	m_timeBarFull->setBarChangeRate(ccp(1,0));
	m_timeBarFull->setOpacity(0);
	addChild(m_timeBarFull,2);

    return true;
}

MonsterLayer *MonsterLayer::create(map<int,MonsterData*> *dataSet)
{
	MonsterLayer *pLayer = new MonsterLayer();
	if (!pLayer) {
		CC_SAFE_DELETE(pLayer);
		return NULL;
	}
	else {
        int iPlayerCount = dataSet->size();
        pLayer->m_monsters = CCArray::createWithCapacity(iPlayerCount);
        pLayer->m_data = dataSet;
		pLayer->m_status = SLEEP;
        if (pLayer->init()) {
            pLayer->autorelease();
        }
        else {
            CC_SAFE_DELETE(pLayer);
            return NULL;
        }
    }
	return pLayer;
}

void MonsterLayer::onEnter()
{
    CCLayer::onEnter();
	int iPlayerCount = m_monsters->count();
	for(int i=0;i<iPlayerCount;i++) {
		CCSprite *pSprite = (CCSprite *)m_monsters->objectAtIndex(i);
		CCDelayTime* delayAction = CCDelayTime::create(2.0f);
		CCActionInterval *actionTo = CCFadeIn::create(1.0f);
		pSprite->runAction(CCSequence::create(delayAction,actionTo,NULL));
	}
}

bool MonsterLayer::ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent)
{
	if (m_status == SLEEP)
		return false;
	CCPoint touchPos = pTouch->getLocation();
	CCLOG("%f,%f",touchPos.x,touchPos.y);
	int iMonsterCount = m_data->size();
	float fScreenHeight =  CCDirector::sharedDirector()->getVisibleSize().height;
	if (m_status == WAIT_TARGET) {
		if (touchPos.y < PLAYER_SPRITE_HEIGHT) {
			this->setStatus(SLEEP);
			return false;
		}
		else if (touchPos.y > fScreenHeight - TOP_BORDER_HEIGHT) {
			if (m_isMagicMatrixAvailable) {
				CCSize magicTagSize = m_magicTag->getContentSize();
				CCPoint middlePoint = m_magicTag->getPosition();
				if (touchPos.x > middlePoint.x - magicTagSize.width*0.5 
					&& touchPos.x < middlePoint.x + magicTagSize.width*0.5
					&& touchPos.y > middlePoint.y - magicTagSize.height*0.5 
					&& touchPos.y < middlePoint.y + magicTagSize.height*0.5) {
						if (m_magicPointer->getScale() != 1)
							m_magicPointer->setScale(1);
						m_magicPointer->runAction(CCFadeIn::create(0.1f));
						setStatus(SPECIAL_ATTACK_PRE);
						return true;
				}
			}
		}
		else {
			for (int i = 0;i<iMonsterCount;++i)	{
				CCSize size = this->getChildByTag(i)->getContentSize();
				CCPoint middlePoint = this->getChildByTag(i)->getPosition();
				float fLeftCornerX = middlePoint.x - size.width/2;
				if (touchPos.x > fLeftCornerX && touchPos.x < fLeftCornerX + size.width) {
					CCMoveBy *pMoveAction = CCMoveBy::create(0.05f,ccp(10,10));
					this->getChildByTag(i)->runAction(CCRepeat::create(
						CCSequence::createWithTwoActions(pMoveAction,pMoveAction->reverse()),4));
					this->setStatus(TARGET_SELECTED);
					CCLOG("Target is %d",i);
					m_target = i;
					return false;
				}
			}
		}
	}
	return false;
}

void MonsterLayer::ccTouchMoved(CCTouch *pTouch, CCEvent *pEvent)
{
	CCPoint touchPos = pTouch->getLocation();
	int iMonsterCount = m_data->size();
	if(getStatus() == SPECIAL_ATTACK_PRE) {
		m_magicPointer->setPosition(touchPos);
		for (int i = 0;i<iMonsterCount;++i)	{
			if (m_data->at(i)->getStatus() == DEAD 
				|| m_data->at(i)->getProperty(CURRENT_HP) > 0.3*m_data->at(i)->getProperty(MAX_HP))
				continue;
			CCSize size = this->getChildByTag(i)->getContentSize();
			CCPoint middlePoint = this->getChildByTag(i)->getPosition();
			float fLeftCornerX = middlePoint.x - size.width/2;
			float fLeftCornerY = middlePoint.y - size.height/2;
			if (touchPos.x > fLeftCornerX && touchPos.x < fLeftCornerX + size.width
				&& touchPos.y > fLeftCornerY && touchPos.y < fLeftCornerY + size.height) {
				m_magicPointer->setTexture(m_magicAva);
				m_magicPointer->runAction(CCRepeatForever::create(CCRotateBy::create(0.5,90.0)));
				return;
			}
		}
		m_magicPointer->cleanup();
		m_magicPointer->setTexture(m_magicUnava);
	}
}

void MonsterLayer::ccTouchEnded(CCTouch *pTouch, CCEvent *pEvent)
{
	CCPoint touchPos = pTouch->getLocation();
	int iMonsterCount = m_data->size();
	if(getStatus() == SPECIAL_ATTACK_PRE) {
		m_magicPointer->setPosition(touchPos);
		for (int i = 0;i<iMonsterCount;++i)	{
			if (m_data->at(i)->getStatus() == DEAD 
				|| m_data->at(i)->getProperty(CURRENT_HP) > 0.3*m_data->at(i)->getProperty(MAX_HP))
				continue;
			CCSize size = this->getChildByTag(i)->getContentSize();
			CCPoint middlePoint = this->getChildByTag(i)->getPosition();
			float fLeftCornerX = middlePoint.x - size.width/2;
			if (touchPos.x > fLeftCornerX && touchPos.x < fLeftCornerX + size.width) {
				m_magicPointer->setTexture(m_magicAva);
				initSpecialAttack(i);
				CCLOG("Target is %d",i);
				m_target = i;
				this->setStatus(SPECIAL_ATTACK);
				return;
			}
		}
		m_magicPointer->setTexture(m_magicUnava);
		m_magicPointer->runAction(CCSequence::create(
			CCSpawn::create(CCMoveTo::create(0.2f,ccp(750,550)),CCScaleTo::create(0.2f,0.5),NULL),
			CCFadeOut::create(0.1f),NULL));
		this->setStatus(WAIT_TARGET);
	}
}

void MonsterLayer::killMosnter(int i) {
	CCProgressTimer *hpPro = dynamic_cast<CCProgressTimer*>(this->getChildByTag(m_data->size()+i));
	hpPro->runAction(CCSequence::create(CCFadeIn::create(0.2f),CCProgressTo::create(0.3f, 0),CCFadeOut::create(0.2f),NULL));
	this->getChildByTag(i)->runAction(CCFadeOut::create(0.5f));
}

void MonsterLayer::onAttacked(int iNum, int iDamage) {
	CCSprite *pMonster = dynamic_cast<CCSprite*>(this->getChildByTag(iNum));
	int iMonsterCount = m_data->size();
	
	if (pMonster->getOpacity() > 0) {
		//HP bar
		float iCurrentHp = m_data->at(iNum)->getProperty(CURRENT_HP);
		float iMaxHp = m_data->at(iNum)->getProperty(MAX_HP);
		float fFromPercent = ((iCurrentHp+iDamage)/iMaxHp)*100.0f;
		float fToPercent = (iCurrentHp/iMaxHp)*100.0f;
		CCProgressTimer *hpPro = dynamic_cast<CCProgressTimer*>(this->getChildByTag(iMonsterCount+iNum));
		hpPro->runAction(CCSequence::create(CCFadeIn::create(0.3f),
			CCProgressFromTo::create(0.3f, fFromPercent,fToPercent),NULL));
		//Damage number
		m_pFont->setPosition(pMonster->getPosition());
		char cDamage[10];
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32)
		_itoa(iDamage,cDamage,10);
#elif (CC_TARGET_PLATFORM == CC_PLATFORM_MAC)
        sprintf(cDamage,"%d",iDamage);
#endif
		m_pFont->setString(cDamage);
		int iNumCount = m_pFont->getChildrenCount();
		int i = 0;
		for (i=0;i<iNumCount;i++) {
			m_pFont->getChildByTag(i)->runAction(CCSequence::create(
				CCDelayTime::create(0.1f*i),
				CCFadeIn::create(0.1f),
				CCMoveBy::create(0.1f,ccp(0,25)),NULL));
		}
		m_pFont->runAction(CCSequence::create(CCDelayTime::create(0.1f*i),CCFadeOut::create(0.2f),NULL));
		hpPro->runAction(CCSequence::create(CCDelayTime::create(1.0f),CCFadeOut::create(0.2f),NULL));
		m_pFont->setPosition(pMonster->getPosition());
	}
}

void MonsterLayer::onMagicMatrixAvailable()
{
	m_isMagicMatrixAvailable = true;
	if (m_magicTag->getOpacity() == 0)
		m_magicTag->runAction(CCFadeIn::create(0.1f));
}

void MonsterLayer::onMagicMatrixUnavailable()
{
	m_isMagicMatrixAvailable = false;
	if (m_magicTag->getOpacity() > 0)
		m_magicTag->runAction(CCFadeOut::create(0.1f));
}

void MonsterLayer::initSpecialAttack(int monsterNo)
{
	m_magicPointer->cleanup();
	m_magicPointer->runAction(CCFadeOut::create(0.2f));
	CCNode *monsterNode = this->getChildByTag(monsterNo);
	float fScreenWidth =  CCDirector::sharedDirector()->getVisibleSize().width;
	float fScreenHeight =  CCDirector::sharedDirector()->getVisibleSize().height;
	monsterNode->runAction(CCSpawn::create(CCMoveTo::create(0.5f,ccp(fScreenWidth*0.5,fScreenHeight*0.5)),CCScaleBy::create(0.5f,SPECIAL_TARGET_SCALE),NULL));
	CCSize monsterSize = monsterNode->getContentSize();
	CCPoint middlePoint = monsterNode->getPosition();
	m_timeBarEmpty->setPosition(ccp(middlePoint.x,middlePoint.y+monsterSize.height*0.5));
	m_timeBarFull->setPosition(ccp(middlePoint.x,middlePoint.y+monsterSize.height*0.5));
	m_timeBarEmpty->runAction(CCFadeIn::create(0.1f));
	m_timeBarFull->runAction(CCFadeIn::create(0.1f));
	m_longHPBar->setPosition(ccp(middlePoint.x,middlePoint.y-monsterSize.height*0.5));
	m_longHPBar->runAction(CCFadeIn::create(0.1f));
	m_timeBarFull->runAction(CCSequence::create(CCDelayTime::create(1.0f),CCProgressFromTo::create(SPECIAL_ATTACK_DURATION,100.0,0.0),NULL));
	//Create bubbles
	m_bubbles = CCArray::create();
	m_bubbles->initWithCapacity(BUBBLE_MAX_COUNT);
	float bottomBorder = middlePoint.y - SPECIAL_TARGET_SCALE * monsterSize.height;
	float leftBorder = middlePoint.x - SPECIAL_TARGET_SCALE * monsterSize.width;
	float rightBorder = middlePoint.x + SPECIAL_TARGET_SCALE * monsterSize.width;
	while (m_bubbles->count() < m_bubbles->capacity()) {
		CCSprite *bubble;
		if (CCRANDOM_0_1() == 1)
			bubble = CCSprite::createWithTexture(CCTextureCache::sharedTextureCache()->addImage(BUBBLE_SMALL));
		else
			bubble = CCSprite::createWithTexture(CCTextureCache::sharedTextureCache()->addImage(BUBBLE_BIG));
		m_bubbles->addObject(bubble);
		int xpos = leftBorder + CCRANDOM_0_1() * SPECIAL_TARGET_SCALE * monsterSize.width;
		bubble->setPosition(ccp(xpos,bottomBorder));
		bubble->setOpacity(0);
		addChild(bubble,3);
		int delayTime = CCRANDOM_0_1() + SPECIAL_TARGET_SCALE * monsterSize.height/BUBBLE_SPEED;
		bubble->runAction(CCSequence::create(CCDelayTime::create(delayTime),
			CCFadeIn::create(0.1f),
			CCMoveBy::create(SPECIAL_TARGET_SCALE * monsterSize.height/BUBBLE_SPEED,ccp(0,SPECIAL_TARGET_SCALE * monsterSize.height)),
			CCCallFuncN::create(this,callfuncN_selector(MonsterLayer::bubbleCallbackN)),NULL));
	}
	schedule(SEL_SCHEDULE(&MonsterLayer::onSpecialAttack),0.1f);
}

void MonsterLayer::bubbleCallbackN(CCNode *pSender)
{
	CCNode *target = this->getChildByTag(m_target);
	float topBorder = target->getPositionY() + target->getScaleY() * target->getContentSize().height;
	float bottomBorder = target->getPositionY() - target->getScaleY() * target->getContentSize().height;
	if (pSender->getPositionY() >= topBorder) {
		pSender->runAction(CCFadeOut::create(0.1f));
		pSender->setPositionY(bottomBorder);
		int delayTime = CCRANDOM_0_1() + SPECIAL_TARGET_SCALE * (topBorder-bottomBorder)/BUBBLE_SPEED;
		pSender->runAction(CCSequence::create(CCDelayTime::create(delayTime),
			CCMoveBy::create(SPECIAL_TARGET_SCALE * (topBorder-bottomBorder)/BUBBLE_SPEED,ccp(0,SPECIAL_TARGET_SCALE * (topBorder-bottomBorder))),
			CCCallFuncN::create(this,callfuncN_selector(MonsterLayer::bubbleCallbackN)),NULL));
	}
}

void MonsterLayer::onSpecialAttack(float monsterNo)
{
	if (m_timeBarFull->getPercentage() == 0.0) {
		m_timeBarEmpty->runAction(CCFadeOut::create(0.1f));
		m_timeBarFull->cleanup();
		m_timeBarFull->runAction(CCFadeOut::create(0.1f));
		m_longHPBar->runAction(CCFadeOut::create(0.1f));
		setStatus(SPECIAL_ATTACK_FINISHED);
		this->unschedule(SEL_SCHEDULE(&MonsterLayer::onSpecialAttack));
		CCObject *bubblePointer;
		CCARRAY_FOREACH(m_bubbles,bubblePointer) {
			bubblePointer->release();
		}
		m_bubbles->removeAllObjects();
		m_bubbles->release();
		return;
	}
	//refreshBubbles(BUBBLE_SPEED, BUBBLE_MAX_COUNT);
	CCLOG("Time remain:%d",30*m_timeBarFull->getPercentage()/100.0);
}
/*
void MonsterLayer::refreshBubbles(int speed, int total)
{
	CCNode *target = this->getChildByTag(m_target);
	float topBorder = target->getPositionY() + target->getScaleY() * target->getContentSize().height;
	float bottomBorder = target->getPositionY() - target->getScaleY() * target->getContentSize().height;
	float leftBorder = target->getPositionY() - target->getScaleX() * target->getContentSize().width;
	float rightBorder = target->getPositionY() + target->getScaleX() * target->getContentSize().width;
	CCObject *object;
	CCARRAY_FOREACH(m_bubbles,object) {
		CCSprite *bubble = (CCSprite*)object;

	}

}
*/
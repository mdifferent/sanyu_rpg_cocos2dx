#include "MonsterLayer.h"
const float PLAYER_SPRITE_HEIGHT = 180;
const char* const FONT_PATH = "fonts/numbers.fnt";
const char* const MONSTER_HP_BAR_PATH = "sanyu/monster_hpbar.png";

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

    return true;
}

MonsterLayer *MonsterLayer::create(map<int,MonsterData*> *dataSet)
{
	MonsterLayer *pLayer = new MonsterLayer();
	if (!pLayer)
	{
		CC_SAFE_DELETE(pLayer);
		return NULL;
	}
	else
	{
        int iPlayerCount = dataSet->size();
        pLayer->m_monsters = CCArray::createWithCapacity(iPlayerCount);
        pLayer->m_data = dataSet;
		pLayer->m_status = SLEEP;
        if (pLayer->init())
        {
            pLayer->autorelease();
        }
        else
        {
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
	for(int i=0;i<iPlayerCount;i++)
	{
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
	CCLOG("Monster layer is waiting for target selection!");
	if (m_status == WAIT_TARGET)
	{
		for (int i = 0;i<iMonsterCount;++i)
		{
			CCSize size = this->getChildByTag(i)->getContentSize();
			CCPoint middlePoint = this->getChildByTag(i)->getPosition();
			float fLeftCornerX = middlePoint.x - size.width/2;
			if (touchPos.y > PLAYER_SPRITE_HEIGHT)
			{
				if (touchPos.x > fLeftCornerX && touchPos.x < fLeftCornerX + size.width)
				{
					CCMoveBy *pMoveAction = CCMoveBy::create(0.05f,ccp(10,10));
					this->getChildByTag(i)->runAction(CCRepeat::create(
						CCSequence::createWithTwoActions(pMoveAction,pMoveAction->reverse()),4));
					this->setStatus(TARGET_SELECTED);
					CCLOG("Target is %d",i);
					m_target = i;
					return true;
				}
				else
					continue;
			}
			else
			{
				//TODO:Call delegate that get player action again
				this->setStatus(SLEEP);
				return true;
			}
		}
	}
	else
		return false;
	return true;
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
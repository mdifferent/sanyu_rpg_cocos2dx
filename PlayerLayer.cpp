#include "PlayerLayer.h"


PlayerLayer::PlayerLayer(void)
{
}


PlayerLayer::~PlayerLayer(void)
{
}

bool PlayerLayer::init()
{
    if(!CCLayer::init())
        return false;
    int iPlayerCount = m_data->size();
	float fScreenWidth =  CCDirector::sharedDirector()->getVisibleSize().width;
	for (int i = 0;i<iPlayerCount;++i)
	{
		string name = m_data->at(i).getPlayerName();
		const char *pName = name.c_str();
        CCLOG("%s",pName);
		if (pName)
		{
			CCSprite *pSprite = CCSprite::create(pName);
			if (pSprite != NULL)
			{
				//Player header
				float fPlayerWidth = pSprite->getContentSize().width;
				float fPlayerHeight = pSprite->getContentSize().height;
				float fPlayerX = fScreenWidth*0.5+(i-iPlayerCount*0.5+0.5)*fPlayerWidth;
				float fPlayerY = 0-fPlayerHeight*0.5;
				pSprite->setPosition(ccp(fPlayerX,fPlayerY));
				addChild(pSprite,0,i);
				m_players->addObject(pSprite);
				//Player HP bar
				CCProgressTimer *hpBarTimer = CCProgressTimer::create(CCSprite::create("sanyu/hp_bar.png"));
				hpBarTimer->setType(kCCProgressTimerTypeBar);
				hpBarTimer->setMidpoint(ccp(0,0));
				hpBarTimer->setBarChangeRate(ccp(1, 0));
				hpBarTimer->setPosition(ccp(fPlayerX+63,0-fPlayerY-46));
				addChild(hpBarTimer,1,iPlayerCount+i);
				//Player SP bar
				CCProgressTimer *spBarTimer = CCProgressTimer::create(CCSprite::create("sanyu/sp_bar.png"));
				spBarTimer->setType(kCCProgressTimerTypeBar);
				spBarTimer->setMidpoint(ccp(0,0));
				spBarTimer->setBarChangeRate(ccp(1, 0));
				spBarTimer->setPosition(ccp(fPlayerX+57,0-fPlayerY-72));
				addChild(spBarTimer,1,iPlayerCount*2+i);

			}
			else
            {
				CCLOG("Error in create sprite of player %s",pName);
                return false;
            }
		}
		else
        {
			CCLOG("Error in get name of player %s",pName);
            return false;
        }
	}
    return true;
}

PlayerLayer *PlayerLayer::create(map<int,PlayerData> &dataSet)
{
	PlayerLayer *pLayer = new PlayerLayer();
	if (!pLayer)
	{
		CC_SAFE_DELETE(pLayer);
		return NULL;
	}
	else
	{
        int iPlayerCount = dataSet.size();
        pLayer->m_players = CCArray::createWithCapacity(iPlayerCount);
        pLayer->m_data = &dataSet;
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

void PlayerLayer::onEnter()
{
    CCLayer::onEnter();
	float fScreenWidth =  CCDirector::sharedDirector()->getVisibleSize().width;
	int iPlayerCount = m_players->count();
	for(int i=0;i<iPlayerCount;i++)
	{
		CCSprite *pSprite = (CCSprite *)m_players->objectAtIndex(i);
		float fPlayerWidth = pSprite->getContentSize().width;
		float fPlayerHeight = pSprite->getContentSize().height;
		float fPlayerX = fScreenWidth*0.5+(i-iPlayerCount*0.5+0.5)*fPlayerWidth;
		float fPlayerY = fPlayerHeight*0.5;
		CCDelayTime* delayAction = CCDelayTime::create((float)i*0.5);
		CCActionInterval *actionTo = CCMoveTo::create(0.5, ccp(fPlayerX,fPlayerY));
		pSprite->runAction(CCSequence::create(delayAction,actionTo,NULL));

		int iCurrentHp = m_data->at(i).getProperty(CURRENT_HP);
		int iMaxHp = m_data->at(i).getProperty(MAX_HP);
		float fHpPercent = 0;
		if (iCurrentHp == iMaxHp)
			fHpPercent = 100;
		else
			fHpPercent = (iCurrentHp/iMaxHp)*100;
		CCProgressTo *hpPro = CCProgressTo::create(0.5, fHpPercent);
		this->getChildByTag(iPlayerCount+i)->runAction(hpPro);

		int iCurrentSp = m_data->at(i).getProperty(CURRENT_SP);
		int iMaxSp = m_data->at(i).getProperty(MAX_SP);
		float fSpPercent = 0;
		if (iCurrentSp == iMaxSp)
			fSpPercent = 100;
		else
			fSpPercent = (iCurrentSp/iCurrentSp)*100;
		CCProgressTo *spPro = CCProgressTo::create(0.5, fSpPercent);
		this->getChildByTag(iPlayerCount*2+i)->runAction(spPro);
		
	}
}
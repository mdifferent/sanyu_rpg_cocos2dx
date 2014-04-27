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
				float fPlayerWidth = pSprite->getContentSize().width;
				float fPlayerHeight = pSprite->getContentSize().height;
				pSprite->setPosition(ccp(fScreenWidth/2+(i-iPlayerCount/2+1/2)*fPlayerWidth,0-fPlayerHeight/2));
				addChild(pSprite,0,i);
				m_players->addObject(pSprite);
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
		CCActionInterval *actionTo = CCMoveTo::create(0.5, ccp(fScreenWidth/2+(i-iPlayerCount/2+1/2)*fPlayerWidth,fPlayerHeight/2));
		pSprite->runAction(actionTo);
	}
}
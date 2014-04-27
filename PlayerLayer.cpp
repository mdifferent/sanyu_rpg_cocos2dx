#include "PlayerLayer.h"


PlayerLayer::PlayerLayer(void)
{
}


PlayerLayer::~PlayerLayer(void)
{
}


PlayerLayer *PlayerLayer::create(map<int,PlayerData> &dataSet)
{
	PlayerLayer *pLayer = new PlayerLayer();
	if (!pLayer)
	{
		CC_SAFE_DELETE(pLayer);
		return NULL;
	}
	else if (pLayer->init())
	{
		pLayer->autorelease();
	}
	else
	{
		CC_SAFE_DELETE(pLayer);
        return NULL;
	}
	
	int iPlayerCount = dataSet.size();
	pLayer->m_players = CCArray::createWithCapacity(iPlayerCount);
	//int iPlayerWidth = 0;
	//int iPlayerHeight = 0;
	int iScreenWidth =  CCDirector::sharedDirector()->getVisibleSize().width;
	for (int i = 0;i<iPlayerCount;++i)
	{
		string name = dataSet.at(i).getPlayerName();
		const char *pName = name.c_str();
		if (pName)
		{
			CCSprite *pSprite = CCSprite::create(pName);
			if (pSprite)
			{
				int iPlayerWidth = pSprite->getContentSize().width;
				int iPlayerHeight = pSprite->getContentSize().height;
				pSprite->setPosition(ccp(iScreenWidth/2+(i-iPlayerCount/2+1/2)*iPlayerWidth,0-iPlayerHeight/2));
				pLayer->addChild(pSprite,0,i);
				pLayer->m_players->addObject(pSprite);
			}
			else
				CCLOG("Error in create sprite of player %s",pName);
		}
		else
			CCLOG("Error in get name of player %s",pName);
	}
	return pLayer;
}

void PlayerLayer::onEnter()
{
	int iScreenWidth =  CCDirector::sharedDirector()->getVisibleSize().width;
	int iPlayerCount = m_players->count();
	for(int i=0;i<iPlayerCount;i++)
	{
		CCSprite *pSprite = (CCSprite *)m_players->objectAtIndex(i);
		int iPlayerWidth = pSprite->getContentSize().width;
		int iPlayerHeight = pSprite->getContentSize().height;
		CCActionInterval *actionTo = CCMoveTo::create(0.5, ccp(iScreenWidth/2+(i-iPlayerCount/2+1/2)*iPlayerWidth,iPlayerHeight/2));
		pSprite->runAction(actionTo);
	}
}
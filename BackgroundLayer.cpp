#include "BackgroundLayer.h"


BackgroundLayer::BackgroundLayer()
{
}


BackgroundLayer::~BackgroundLayer(void)
{
	//delete m_map;
	m_map.clear();
}

BackgroundLayer *BackgroundLayer::createWithMapName(std::string &mapName)
{
	BackgroundLayer *pRet = new BackgroundLayer();
	if (pRet && !mapName.empty()) 
	{
		pRet->m_map = mapName;
	}
	else 
	{
		pRet->m_map.clear();
		CC_SAFE_DELETE(pRet);
		return NULL;
	}

	if (pRet->init())
    {
        pRet->autorelease();
        return pRet;
    }
    else
    {
        CC_SAFE_DELETE(pRet);
        return NULL;
    }
}

bool BackgroundLayer::init()
{
	if ( !CCLayer::init() )
    {
		CCLOG("Error in init CCLayer!");
        return false;
    }
	
	CCSize visibleSize = CCDirector::sharedDirector()->getVisibleSize();
    CCPoint origin = CCDirector::sharedDirector()->getVisibleOrigin();

	CCSprite* pSprite = NULL;
	if (!m_map.empty())
	{
		pSprite = CCSprite::create(m_map.c_str());
	}
	else
	{
		CCLOG("Error in init create backgroud, map name is null!");
		return false;
	}

	pSprite->setPosition(ccp(visibleSize.width/2 + origin.x, visibleSize.height/2 + origin.y));
	this->addChild(pSprite, 0,0);
	return true;
}

void BackgroundLayer::onEnter()
{
	CCLayer::onEnter();

	CCActionInterval *action1 = CCFadeIn::create(0.5f);
	this->getChildByTag(0)->runAction(action1);
}

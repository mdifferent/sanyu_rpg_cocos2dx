#include "BackgroundLayer.h"


BackgroundLayer::BackgroundLayer()
{
}


BackgroundLayer::~BackgroundLayer(void)
{
	delete m_map;
	m_map = NULL;
}

BackgroundLayer *BackgroundLayer::createWithMapName(const char *mapName)
{
	BackgroundLayer *pRet = new BackgroundLayer();
	if (pRet && mapName != NULL) 
	{
		pRet->m_map = mapName;
	}
	else 
	{
		pRet->m_map = NULL;
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
	if (m_map != NULL)
	{
		pSprite = CCSprite::create(m_map);
	}
	else
	{
		CCLOG("Error in init create backgroud, map name is null!");
		return false;
	}

	pSprite->setPosition(ccp(visibleSize.width/2 + origin.x, visibleSize.height/2 + origin.y));
	this->addChild(pSprite, 0);

	return true;
}
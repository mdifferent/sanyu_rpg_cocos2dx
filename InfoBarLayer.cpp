#include "InfoBarLayer.h"


InfoBarLayer::InfoBarLayer(void)
{
}


InfoBarLayer::~InfoBarLayer(void)
{
}

InfoBarLayer *InfoBarLayer::createWithBarName(std::string &barName)
{
	InfoBarLayer *pRet = new InfoBarLayer();
	if (pRet && !barName.empty()) 
	{
		pRet->m_barName = barName;
	}
	else 
	{
		pRet->m_barName.clear();
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

bool InfoBarLayer::init()
{
	if ( !CCLayer::init() )
    {
		CCLOG("Error in init CCLayer!");
        return false;
    }

	CCSize visibleSize = CCDirector::sharedDirector()->getVisibleSize();
    CCPoint origin = CCDirector::sharedDirector()->getVisibleOrigin();

	CCSprite* pSprite = NULL;
	if (!m_barName.empty())
	{
		pSprite = CCSprite::create(m_barName.c_str());
	}
	else
	{
		CCLOG("Error in init create backgroud, map name is null!");
		return false;
	}

	pSprite->setPosition(ccp(visibleSize.width/2 + origin.x, visibleSize.height/2 + origin.y));
	this->addChild(pSprite,0,0);
	return true;
}

void InfoBarLayer::onEnter()
{
	CCLayer::onEnter();

	CCActionInterval *action1 = CCFadeIn::create(1.0f);
	this->getChildByTag(0)->runAction(action1);
}
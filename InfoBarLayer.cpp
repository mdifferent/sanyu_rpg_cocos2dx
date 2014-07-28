#include "InfoBarLayer.h"
#include "Resources.h"
#include "ConstValues.h"

InfoBarLayer::InfoBarLayer(void)
{
}


InfoBarLayer::~InfoBarLayer(void)
{
}

InfoBarLayer *InfoBarLayer::createWithBarName(std::string &barName,float fFadein)
{
	InfoBarLayer *pRet = new InfoBarLayer();
	if (pRet && !barName.empty()) {
		pRet->m_barName = barName;
		pRet->m_fadein_interval = fFadein;
	}
	else {
		pRet->m_barName.clear();
		CC_SAFE_DELETE(pRet);
		return NULL;
	}

	if (pRet->init()) {
        pRet->autorelease();
        return pRet;
    }
    else {
        CC_SAFE_DELETE(pRet);
        return NULL;
    }
}

bool InfoBarLayer::init()
{
	if ( !CCLayer::init() ) {
		CCLOG("Error in init CCLayer!");
        return false;
    }

	CCSize visibleSize = CCDirector::sharedDirector()->getVisibleSize();
    CCPoint origin = CCDirector::sharedDirector()->getVisibleOrigin();

	CCSprite* pSprite = NULL;
	if (!m_barName.empty()) {
		pSprite = CCSprite::create(m_barName.c_str());
	}
	else { 
		CCLOG("Error in init create backgroud, map name is null!");
		return false;
	}

	pSprite->setPosition(ccp(visibleSize.width/2 + origin.x, visibleSize.height/2 + origin.y));
	this->addChild(pSprite,0,0);
	
	m_infoLabel = CCLabelTTF::create();
	m_infoLabel->setPosition(ccp(visibleSize.width*0.5,visibleSize.height-30));
	return true;
}

void InfoBarLayer::onEnter()
{
	CCLayer::onEnter();

	CCActionInterval *action1 = CCFadeIn::create(m_fadein_interval);
	this->getChildByTag(0)->runAction(action1);
}

void InfoBarLayer::showText(string text,float secs)
{
	if (m_infoLabel->getOpacity() != 0)
		m_infoLabel->setOpacity(0);
	m_infoLabel->setString(text.c_str());
	m_infoLabel->setFontName(NAME_FONT);
	m_infoLabel->setFontSize(NAME_FONT_SIZE);
	m_infoLabel->setDirty(true);

	CCActionInterval *action = CCFadeIn::create(0.1f);
	if (secs <= 0)
		m_infoLabel->runAction(action);
	else
		m_infoLabel->runAction(CCSequence::create(CCDelayTime::create(3.0f),action,CCDelayTime::create(secs),action->reverse(),NULL));
}

void InfoBarLayer::clearText()
{
	if (m_infoLabel->getOpacity() > 0)
		m_infoLabel->runAction(CCFadeOut::create(0.1f));
}
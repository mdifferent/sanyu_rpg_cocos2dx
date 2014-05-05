#include "PlayerLayer.h"

const char *HP_BAR_IMG_FILE_PATH = "sanyu/hp_bar.png";
const char *SP_BAR_IMG_FILE_PATH = "sanyu/sp_bar.png";
const int NAME_FONT_SIZE = 20;
const int MENU_FONT_SIZE = 20;
const int HP_NUM_FONT_SIZE = 16;
const char *NAME_FONT = "Arial";


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
	//this->setTouchEnabled(true);
	CCDirector::sharedDirector()->getTouchDispatcher()->addTargetedDelegate(this, 0, true);
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
				
				//Player HP bar
				CCProgressTimer *hpBarTimer = CCProgressTimer::create(CCSprite::create(HP_BAR_IMG_FILE_PATH));
				hpBarTimer->setType(kCCProgressTimerTypeBar);
				hpBarTimer->setMidpoint(ccp(0,0));
				hpBarTimer->setBarChangeRate(ccp(1, 0));
				hpBarTimer->setPosition(ccp(fPlayerX+63,0-fPlayerY-46));
				addChild(hpBarTimer,1,iPlayerCount+i);

				//Player SP bar
				CCProgressTimer *spBarTimer = CCProgressTimer::create(CCSprite::create(SP_BAR_IMG_FILE_PATH));
				spBarTimer->setType(kCCProgressTimerTypeBar);
				spBarTimer->setMidpoint(ccp(0,0));
				spBarTimer->setBarChangeRate(ccp(1, 0));
				spBarTimer->setPosition(ccp(fPlayerX+57,0-fPlayerY-72));
				addChild(spBarTimer,1,iPlayerCount*2+i);

				//Player Name
				CCLabelTTF* pNameBar = CCLabelTTF::create(pName, NAME_FONT, NAME_FONT_SIZE);
				pNameBar->setPosition(ccp(fPlayerX+65,0-fPlayerY-10));
				pNameBar->setOpacity(0);
				addChild(pNameBar,2,iPlayerCount*3+i);

				//Player HP number
				int iMaxHP = m_data->at(i).getProperty(MAX_HP);
				int iCurrentHP = m_data->at(i).getProperty(CURRENT_HP);
				char cHPPair[15];
				sprintf(cHPPair,"%d/%d",iCurrentHP,iMaxHP);
				CCLabelTTF* pHPLabel = CCLabelTTF::create(cHPPair, NAME_FONT, HP_NUM_FONT_SIZE);
				pHPLabel->setPosition(ccp(fPlayerX+65,0-fPlayerY-45));
				pHPLabel->setOpacity(0);
				addChild(pHPLabel,2,iPlayerCount*4+i);

				//Player SP number
				int iMaxSP = m_data->at(i).getProperty(MAX_SP);
				int iCurrentSP = m_data->at(i).getProperty(CURRENT_SP);
				char cSPPair[15];
				sprintf(cSPPair,"%d/%d",iCurrentSP,iMaxSP);
				CCLabelTTF* pSPLabel = CCLabelTTF::create(cSPPair, NAME_FONT, HP_NUM_FONT_SIZE);
				pSPLabel->setPosition(ccp(fPlayerX+58,0-fPlayerY-70));
				pSPLabel->setOpacity(0);
				addChild(pSPLabel,2,iPlayerCount*5+i);
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
	
	//Add menu
	CCMenuItemLabel *pAttackItem = CCMenuItemLabel::create(CCLabelTTF::create("ATTACK",NAME_FONT,MENU_FONT_SIZE),
                                                           this,menu_selector(PlayerLayer::playerAttackCallback));
	CCMenuItemLabel *pSkillItem = CCMenuItemLabel::create(CCLabelTTF::create("SKILL",NAME_FONT,MENU_FONT_SIZE),
                                                          this,menu_selector(PlayerLayer::playerSkillCallback));
	CCMenuItemLabel *pGuardItem = CCMenuItemLabel::create(CCLabelTTF::create("GUARD",NAME_FONT,MENU_FONT_SIZE),
                                                          this,menu_selector(PlayerLayer::playerGuardCallback));
	CCMenuItemLabel *pEscapeItem = CCMenuItemLabel::create(CCLabelTTF::create("ESCAPE",NAME_FONT,MENU_FONT_SIZE),
                                                           this,menu_selector(PlayerLayer::playerEscapeCallback));
	CCMenu *pMenu = CCMenu::create(pAttackItem,pSkillItem,pGuardItem,pEscapeItem,NULL);
	pMenu->alignItemsVertically();
    pMenu->setOpacity(0);
	addChild(pMenu,3,iPlayerCount*6);
    
    return true;
}

void PlayerLayer::playerAttackCallback(CCObject* pSender)
{
    CCLOG("ATTACK");
}

void PlayerLayer::playerSkillCallback(CCObject* pSender)
{
    CCLOG("SKILL");
}


void PlayerLayer::playerGuardCallback(CCObject* pSender)
{
    CCLOG("GUARD");
}


void PlayerLayer::playerEscapeCallback(CCObject* pSender)
{
    CCLOG("ESCAPE");
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
        //int iPlayerCount = dataSet.size();
        //pLayer->m_players = CCArray::createWithCapacity(iPlayerCount);
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
	int iPlayerCount = m_data->size();
	for(int i=0;i<iPlayerCount;i++)
	{
		//Add head
		CCSprite *pSprite = (CCSprite *)this->getChildByTag(i);
		float fPlayerWidth = pSprite->getContentSize().width;
		float fPlayerHeight = pSprite->getContentSize().height;
		float fPlayerX = fScreenWidth*0.5+(i-iPlayerCount*0.5+0.5)*fPlayerWidth;
		float fPlayerY = fPlayerHeight*0.5;
		CCDelayTime* pPlayerDelayAction = CCDelayTime::create((float)i*0.3);			//Move in in turns
		CCActionInterval *actionTo = CCMoveTo::create(0.5, ccp(fPlayerX,fPlayerY));
		pSprite->runAction(CCSequence::create(pPlayerDelayAction,actionTo,NULL));
		
		//Add HP bar
		CCDelayTime* pBarDelayAction = CCDelayTime::create((float)iPlayerCount*0.4);	//Fill bar after head in position
		int iCurrentHp = m_data->at(i).getProperty(CURRENT_HP);
		int iMaxHp = m_data->at(i).getProperty(MAX_HP);
		float fHpPercent = 0;
		if (iCurrentHp == iMaxHp)
			fHpPercent = 100;
		else
			fHpPercent = (iCurrentHp/iMaxHp)*100;
		CCProgressTo *hpPro = CCProgressTo::create(0.5, fHpPercent);
		this->getChildByTag(iPlayerCount+i)->runAction(CCSequence::create(pBarDelayAction,hpPro,NULL));

		//Add SP bar
		int iCurrentSp = m_data->at(i).getProperty(CURRENT_SP);
		int iMaxSp = m_data->at(i).getProperty(MAX_SP);
		float fSpPercent = 0;
		if (iCurrentSp == iMaxSp)
			fSpPercent = 100;
		else
			fSpPercent = (iCurrentSp/iCurrentSp)*100;
		CCProgressTo *spPro = CCProgressTo::create(0.5, fSpPercent);
		this->getChildByTag(iPlayerCount*2+i)->runAction(CCSequence::create(pBarDelayAction,spPro,NULL));

		//Add Name
		CCActionInterval *showName = CCFadeIn::create(0.5);
		this->getChildByTag(iPlayerCount*3+i)->runAction(CCSequence::create(pPlayerDelayAction,showName,NULL));

		//Add HP & SP number
		this->getChildByTag(iPlayerCount*4+i)->runAction(CCSequence::create(pBarDelayAction,showName,NULL));
		CCActionInterval *showName1 = CCFadeIn::create(0.5);	//CANNOT use same combination in sequence to different sprite?
		this->getChildByTag(iPlayerCount*5+i)->runAction(CCSequence::create(pBarDelayAction,showName1,NULL));
	}
}

bool PlayerLayer::ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent)
{
    CCPoint touchPos = pTouch->getLocation();
    CCLOG("%f,%f",touchPos.x,touchPos.y);
    int iPlayerCount = m_data->size();
    this->getChildByTag(iPlayerCount*6)->runAction(CCFadeOut::create(0.2f));
    if (touchPos.y >= 0 && touchPos.y <= 180) {
        if (touchPos.x >= 0 && touchPos.x <= 200) {
            this->getChildByTag(iPlayerCount*6)->setPosition(ccp(150,150));
        }
        else if (touchPos.x > 200 && touchPos.x <= 400) {
            this->getChildByTag(iPlayerCount*6)->setPosition(ccp(350,150));
        }
        else if (touchPos.x > 400 && touchPos.x <= 600) {
            this->getChildByTag(iPlayerCount*6)->setPosition(ccp(550,150));
        }
        else if (touchPos.x > 600 && touchPos.x <= 800) {
            this->getChildByTag(iPlayerCount*6)->setPosition(ccp(750,150));
        }
        else {
            return false;
        }
        this->getChildByTag(iPlayerCount*6)->runAction(CCFadeIn::create(0.2f));
        return true;
    }
    else
        return false;
}
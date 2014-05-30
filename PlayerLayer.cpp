#include "PlayerLayer.h"

const char *HP_BAR_IMG_FILE_PATH = "sanyu/hp_bar.png";
const char *SP_BAR_IMG_FILE_PATH = "sanyu/sp_bar.png";
const int NAME_FONT_SIZE = 20;
const int MENU_FONT_SIZE = 20;
const int HP_NUM_FONT_SIZE = 16;
const char *NAME_FONT = "Arial";
const int PLAYER_SPRITE_HEIGHT = 180;
const int PLAYER_SPRITE_WIDTH = 200;
const char* const FONT_PATH = "fonts/numbers.fnt";

PlayerLayer::PlayerLayer(void)
{
	m_selectedPlayer = 0;
}


PlayerLayer::~PlayerLayer(void)
{
	
}

bool PlayerLayer::init()
{
    if(!CCLayer::init())
        return false;
	this->setTouchEnabled(true);
	CCDirector::sharedDirector()->getTouchDispatcher()->addTargetedDelegate(this,0,true);
    int iPlayerCount = m_data->size();
	float fScreenWidth =  CCDirector::sharedDirector()->getVisibleSize().width;
	for (int i = 0;i<iPlayerCount;++i)
	{
		string name = m_data->at(i)->getName();
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
				int iMaxHP = m_data->at(i)->getProperty(MAX_HP);
				int iCurrentHP = m_data->at(i)->getProperty(CURRENT_HP);
				char cHPPair[15];
				sprintf(cHPPair,"%d/%d",iCurrentHP,iMaxHP);
				CCLabelTTF* pHPLabel = CCLabelTTF::create(cHPPair, NAME_FONT, HP_NUM_FONT_SIZE);
				pHPLabel->setPosition(ccp(fPlayerX+65,0-fPlayerY-45));
				pHPLabel->setOpacity(0);
				addChild(pHPLabel,2,iPlayerCount*4+i);

				//Player SP number
				int iMaxSP = m_data->at(i)->getProperty(MAX_SP);
				int iCurrentSP = m_data->at(i)->getProperty(CURRENT_SP);
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
	CCMenuItemLabel *pItemItem = CCMenuItemLabel::create(CCLabelTTF::create("ITEM",NAME_FONT,MENU_FONT_SIZE),
                                                           this,menu_selector(PlayerLayer::playerItemCallback));
	CCMenu *pMenu = CCMenu::create(pAttackItem,pSkillItem,pItemItem,pGuardItem,pEscapeItem,NULL);
	pMenu->alignItemsVertically();
	pMenu->setEnabled(false);
	pMenu->setVisible(false);
	pMenu->setPosition(ccp(-10,-10));
	addChild(pMenu,3,iPlayerCount*6);
	
	m_pFont = CCLabelBMFont::create("0",FONT_PATH);
    m_pFont->setColor(ccYELLOW);
	m_pFont->setOpacity(0);
	addChild(m_pFont,4);

    m_status = WAIT_COMMAND;
    return true;
}

PlayerLayer *PlayerLayer::create(map<int,PlayerData*> *dataSet)
{
	PlayerLayer *pLayer = new PlayerLayer();
	if (!pLayer)
	{
		CC_SAFE_DELETE(pLayer);
		return NULL;
	}
	else
	{
		if (dataSet)
		{
			pLayer->m_data = dataSet;
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
		else
		{
			CCLOG("Player data is empty!");
			CC_SAFE_DELETE(pLayer);
			return NULL;
		}
    }
	return pLayer;
}

void PlayerLayer::onEnter()
{
	CCLOG("Player layer onEnter");
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
		int iCurrentHp = m_data->at(i)->getProperty(CURRENT_HP);
		int iMaxHp = m_data->at(i)->getProperty(MAX_HP);
		float fHpPercent = 0;
		if (iCurrentHp == iMaxHp)
			fHpPercent = 100;
		else
			fHpPercent = (iCurrentHp/iMaxHp)*100;
		CCProgressTo *hpPro = CCProgressTo::create(0.5, fHpPercent);
		this->getChildByTag(iPlayerCount+i)->runAction(CCSequence::create(pBarDelayAction,hpPro,NULL));

		//Add SP bar
		int iCurrentSp = m_data->at(i)->getProperty(CURRENT_SP);
		int iMaxSp = m_data->at(i)->getProperty(MAX_SP);
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
	int iPlayerCount = m_data->size();
	CCMenu *pMenu = (CCMenu*)this->getChildByTag(iPlayerCount*6);
	for (int i = 0;i<iPlayerCount;++i) {
		if (m_data->at(i)->getStatus() == DEAD)
			continue;
		CCSize size = this->getChildByTag(i)->getContentSize();
		CCPoint middlePoint = this->getChildByTag(i)->getPosition();
		float fLeftCornerX = middlePoint.x - size.width/2;
		if (touchPos.y >= 0 && touchPos.y <= size.height) {
			if (touchPos.x > fLeftCornerX && touchPos.x < fLeftCornerX + size.width) {
				m_selectedPlayer = i;
				if (m_status == WAIT_TARGET) {
					m_status = TARGET_SELECTED;
				}
				else if (m_status == WAIT_COMMAND){
					pMenu->setEnabled(true);
					pMenu->setVisible(true);
					pMenu->setPosition(ccp(middlePoint.x+50,middlePoint.y+60));
					pMenu->runAction(CCFadeIn::create(0.2f));
				}
				return true;
			}
		}
		else {
			int iOp = pMenu->getOpacity();
			if (iOp>0)
				pMenu->runAction(CCFadeOut::create(0.2f));
		}
	}
	//Default show menu on the left most player who haven't run action
	return false;
}

void PlayerLayer::onPlayerKilled(int i) {
	CCProgressTimer *hpPro = dynamic_cast<CCProgressTimer*>(this->getChildByTag(m_data->size()+i));
	hpPro->runAction(CCSequence::create(CCFadeIn::create(0.2f),CCProgressTo::create(0.3f, 0),CCFadeOut::create(0.2f),NULL));
	this->getChildByTag(i)->runAction(CCFadeOut::create(0.5f));
}

void PlayerLayer::onPlayerHPModified(int iNum, int iDamage) {
	CCSprite *pPlayer = dynamic_cast<CCSprite*>(this->getChildByTag(iNum));
	int iPlayerCount = m_data->size();
	//HP Bar modify
	CCProgressTimer *hpBarTimer = dynamic_cast<CCProgressTimer*>(this->getChildByTag(iPlayerCount + iNum));
	float fCurrentHp = m_data->at(iNum)->getProperty(CURRENT_HP);
	float fMaxHp = m_data->at(iNum)->getProperty(MAX_HP);
	float fFromPercent = ((fCurrentHp - iDamage) / fMaxHp) * 100.0f;
	float fToPercent = (fCurrentHp / fMaxHp) * 100.0f;
	if (fCurrentHp - 0.0 < 1)
		fToPercent = 0.0;
	hpBarTimer->runAction(CCProgressFromTo::create(0.5f,fFromPercent,fToPercent));
	//HP value modify
	CCLabelTTF *pHPLabel = dynamic_cast<CCLabelTTF*>(this->getChildByTag(iPlayerCount*4));
	int iCurrentHP = m_data->at(iNum)->getProperty(CURRENT_HP);
	int iMaxHP = m_data->at(iNum)->getProperty(MAX_HP);
	char cHPPair[15];
	sprintf(cHPPair,"%d/%d",iCurrentHP,iMaxHP);
	pHPLabel->setString(cHPPair);
	//Damage Number
	m_pFont->setPosition(pPlayer->getPosition());
	char cDamage[10];
	if (iDamage < 0) {
		//cDamage[0] = '-';
		_itoa(iDamage,cDamage,10);
		m_pFont->setColor(ccRED);
	}
	else {
		//cDamage[0] = '+';
		_itoa(iDamage,cDamage,10);
		m_pFont->setColor(ccGREEN);
	}
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
	m_pFont->setPosition(pPlayer->getPosition());
}


void PlayerLayer::playerAttackCallback(CCObject* pSender)
{
    CCLOG("ATTACK");
    m_status = ATTACK;
	m_data->at(m_selectedPlayer)->setStatus(NORMAL);
}

void PlayerLayer::playerSkillCallback(CCObject* pSender)
{
    CCLOG("SKILL");
    m_status = SKILL;
	m_data->at(m_selectedPlayer)->setStatus(NORMAL);
}

void PlayerLayer::playerGuardCallback(CCObject* pSender)
{
    CCLOG("GUARD");
	m_data->at(m_selectedPlayer)->setStatus(DEFENSE);
    m_status = GUARD;
	int iPlayerCount = m_data->size();
	CCMenu *pMenu = (CCMenu*)this->getChildByTag(iPlayerCount*6);
	pMenu->runAction(CCFadeOut::create(0.2f));
}

void PlayerLayer::playerEscapeCallback(CCObject* pSender)
{
    CCLOG("ESCAPE");
    m_status = ESCAPE;
	m_data->at(m_selectedPlayer)->setStatus(NORMAL);
}

void PlayerLayer::playerItemCallback(CCObject* pSender) {
	CCLOG("ITEM");
    m_status = ITEM;
	m_data->at(m_selectedPlayer)->setStatus(NORMAL);
}
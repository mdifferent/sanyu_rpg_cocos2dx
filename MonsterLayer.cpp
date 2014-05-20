#include "MonsterLayer.h"
const float PLAYER_SPRITE_HEIGHT = 180;
const char* const FONT_PATH = "sanyu/numbers.fnt";

MonsterLayer::MonsterLayer(void)
{
}


MonsterLayer::~MonsterLayer(void)
{
}

bool MonsterLayer::init()
{
    if(!CCLayer::init())
        return false;
    int iPlayerCount = m_data->size();
	this->setTouchEnabled(true);
	CCDirector::sharedDirector()->getTouchDispatcher()->addTargetedDelegate(this,1,false);
	float fScreenWidth =  CCDirector::sharedDirector()->getVisibleSize().width;
	float fScreenHeight =  CCDirector::sharedDirector()->getVisibleSize().height;
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
				float fPlayerWidth = pSprite->getContentSize().width;
				float fPlayerHeight = pSprite->getContentSize().height;
				pSprite->setPosition(ccp(fScreenWidth*0.5+(i-iPlayerCount*0.5+0.5)*fPlayerWidth,fScreenHeight*0.5));
				pSprite->setOpacity(0);
				addChild(pSprite,0,i);
				m_monsters->addObject(pSprite);
			}
			else
            {
				CCLOG("Error in create sprite of monster %s",pName);
                return false;
            }
		}
		else
        {
			CCLOG("Error in get name of monster %s",pName);
            return false;
        }
	}
	m_pFont = CCLabelBMFont::create("0","fonts/numbers.fnt");
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
	this->getChildByTag(i)->runAction(CCFadeOut::create(0.5f));
}

void MonsterLayer::onAttacked(int iNum, int iDamage) {
	CCSprite *pMonster = dynamic_cast<CCSprite*>(this->getChildByTag(iNum));
	if (pMonster->getOpacity() > 0) {
		m_pFont->setPosition(pMonster->getPosition());
		char cDamage[10];
		_itoa(iDamage,cDamage,10);
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
		m_pFont->setPosition(pMonster->getPosition());
	}
}
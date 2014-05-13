#include "MonsterLayer.h"
const float PLAYER_SPRITE_HEIGHT = 180;

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
		string name = m_data->at(i)->getMonsterName();
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
		CCDelayTime* delayAction = CCDelayTime::create(2.5f);
		CCActionInterval *actionTo = CCFadeIn::create(1.0f);
		pSprite->runAction(CCSequence::create(delayAction,actionTo,NULL));
	}
}

bool MonsterLayer::ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent)
{
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
			//float fLeftCornerY = middlePoint.y - size.height/2;
			if (touchPos.y > PLAYER_SPRITE_HEIGHT)
			{
				if (touchPos.x > fLeftCornerX && touchPos.x < fLeftCornerX + size.width)
				{
					this->getChildByTag(i)->runAction(CCRepeat::create(
						CCSequence::createWithTwoActions(
						CCMoveBy::create(0.05f,ccp(10,10)),CCMoveBy::create(0.05f,ccp(-10,-10))),5));
					this->setStatus(TARGET_SELECTED);
					//TODO:Modify data and judge whether dead
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
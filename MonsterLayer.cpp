#include "MonsterLayer.h"


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
	float fScreenWidth =  CCDirector::sharedDirector()->getVisibleSize().width;
	float fScreenHeight =  CCDirector::sharedDirector()->getVisibleSize().height;
	for (int i = 0;i<iPlayerCount;++i)
	{
		string name = m_data->at(i).getMonsterName();
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

MonsterLayer *MonsterLayer::create(map<int,MonsterData> &dataSet)
{
	MonsterLayer *pLayer = new MonsterLayer();
	if (!pLayer)
	{
		CC_SAFE_DELETE(pLayer);
		return NULL;
	}
	else
	{
        int iPlayerCount = dataSet.size();
        pLayer->m_monsters = CCArray::createWithCapacity(iPlayerCount);
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

void MonsterLayer::onEnter()
{
    CCLayer::onEnter();
	//float fScreenWidth =  CCDirector::sharedDirector()->getVisibleSize().width;
	int iPlayerCount = m_monsters->count();
	for(int i=0;i<iPlayerCount;i++)
	{
		CCSprite *pSprite = (CCSprite *)m_monsters->objectAtIndex(i);
		//float fPlayerWidth = pSprite->getContentSize().width;
		//float fPlayerHeight = pSprite->getContentSize().height;
		//float x = fScreenWidth*0.5+(i-iPlayerCount*0.5+0.5)*fPlayerWidth;
		//CCDelayTime* delayAction = CCDelayTime::create((float)i*0.5);
		CCActionInterval *actionTo = CCFadeIn::create(0.5f);
		pSprite->runAction(actionTo);
	}
}
#include "HelloWorldScene.h"
#include "BackgroundLayer.h"
#include "InfoBarLayer.h"
#include "PlayerLayer.h"
#include "MonsterLayer.h"
#include "BattleData.h"
#include "BattleField.h"

USING_NS_CC;

CCScene* HelloWorld::scene()
{
    // 'scene' is an autorelease object
    //CCScene *scene = CCScene::create();
	BattleField *scene = BattleField::scene(0);
	//HelloWorld *layer = HelloWorld::create();
    //BattleData *data = new BattleData();
	//PlayerLayer *layer = PlayerLayer::create(data->getPlayers());
	//scene->addChild(layer);

    return scene;
}

// on "init" you need to initialize your instance
bool HelloWorld::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !CCLayer::init() )
    {
        return false;
    }
    
    CCSize visibleSize = CCDirector::sharedDirector()->getVisibleSize();
	CCLog("height:%f",visibleSize.height);
	CCLog("width:%f",visibleSize.width);
    CCPoint origin = CCDirector::sharedDirector()->getVisibleOrigin();
	CCLog("x:%f",origin.x);
	CCLog("y:%f",origin.y);

    /////////////////////////////
    // 2. add a menu item with "X" image, which is clicked to quit the program
    //    you may modify it.

    // add a "close" icon to exit the progress. it's an autorelease object
    CCMenuItemImage *pCloseItem = CCMenuItemImage::create(
                                        "CloseNormal.png",
                                        "CloseSelected.png",
                                        this,
                                        menu_selector(HelloWorld::menuCloseCallback));

	pCloseItem->setPosition(ccp(origin.x + visibleSize.width - pCloseItem->getContentSize().width/2 ,
                                origin.y + pCloseItem->getContentSize().height/2));
	

    // create menu, it's an autorelease object
    CCMenu* pMenu = CCMenu::create(pCloseItem,NULL);
    pMenu->setPosition(CCPointZero);
    this->addChild(pMenu,1);

    /////////////////////////////
    // 3. add your codes below...

    // add a label shows "Hello World"
    // create and initialize a label
    /*
    CCLabelTTF* pLabel = CCLabelTTF::create("Hello World", "Arial", 24);
    
    // position the label on the center of the screen
    pLabel->setPosition(ccp(origin.x + visibleSize.width/2,
                            origin.y + visibleSize.height - pLabel->getContentSize().height));

    // add the label as a child to this layer
    this->addChild(pLabel, 1);*/

    // add "HelloWorld" splash screen"
    /*
	CCSprite* pSprite = CCSprite::create("sanyu/actor_1.png");
	CCSprite* pHP = CCSprite::create("sanyu/hp_bar.png");
	CCSprite* pMP = CCSprite::create("sanyu/sp_bar.png");
	char cHPPair[8];
	sprintf(cHPPair,"%d.%d",500,500);
	cHPPair[7]=0;
	CCLabelTTF* pHPLabel = CCLabelTTF::create(cHPPair, "Arial", 20);
	//CCLabelAtlas *pHPLabel = CCLabelAtlas::create("500/500", "fps_images.png");
	CCLabelTTF* pSPLabel = CCLabelTTF::create("500/500", "Arial", 20);
	CCLabelTTF* pName = CCLabelTTF::create("KAYAZUO", "Arial", 20);

    // position the sprite on the center of the screen
    pSprite->setPosition(ccp(400,90));
	pHP->setPosition(ccp(463,44));
	pMP->setPosition(ccp(457,18));
	pHPLabel->setPosition(ccp(472,45));
	pSPLabel->setPosition(ccp(465,20));
	pName->setPosition(ccp(465,80));
    // pSprite->setPosition(ccp(visibleSize.width/2 + origin.x, visibleSize.height/2 + origin.y));

    // add the sprite as a child to this layer
    this->addChild(pSprite,0);
	this->addChild(pHP,1);
	this->addChild(pMP,1);
	this->addChild(pHPLabel,2);
	this->addChild(pSPLabel,2);
	this->addChild(pName,1);
    */
    return true;
}


void HelloWorld::onEnter()
{
	CCLayer::onEnter();
	//CCActionInterval *actionTo = CCMoveTo::create(0.5, ccp(400,90));
	//this->getChildByTag(0)->runAction(actionTo);
}

void HelloWorld::menuCloseCallback(CCObject* pSender)
{
	
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WINRT) || (CC_TARGET_PLATFORM == CC_PLATFORM_WP8)
	CCMessageBox("You pressed the close button. Windows Store Apps do not implement a close button.","Alert");
#else
    CCDirector::sharedDirector()->end();
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    exit(0);
#endif
#endif
}

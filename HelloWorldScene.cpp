#include "HelloWorldScene.h"
#include "BackgroundLayer.h"
#include "InfoBarLayer.h"

USING_NS_CC;

CCScene* HelloWorld::scene()
{
    // 'scene' is an autorelease object
    CCScene *scene = CCScene::create();
    
    // 'layer' is an autorelease object
    //HelloWorld *layer = HelloWorld::create();
	BackgroundLayer *layer = BackgroundLayer::createWithMapName("sanyu/bk.jpg");
    // add layer as a child to scene
    scene->addChild(layer,0);

	InfoBarLayer *layer2 = InfoBarLayer::createWithBarName("sanyu/infobar.png");
	scene->addChild(layer2,1);

    // return the scene
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
    this->addChild(pMenu, 1,1);

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
    this->addChild(pLabel, 1);

    // add "HelloWorld" splash screen"
    CCSprite* pSprite = CCSprite::create("sanyu/bk.jpg");

    // position the sprite on the center of the screen
    pSprite->setPosition(ccp(visibleSize.width/2 + origin.x, visibleSize.height/2 + origin.y));

    // add the sprite as a child to this layer
    this->addChild(pSprite, 0);*/
    
    return true;
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

void HelloWorld::menuStartCallback(CCObject* pSender)
{
	//this->removeChildByTag(1);
	//CCSprite* pSprite = CCSprite::create("sanyu/infobar.png");
	//pSprite->setPosition(ccp(400, 300));
	//this->addChild(pSprite);

}
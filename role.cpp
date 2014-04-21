#include "role.h"
role *ref;
role::role(void)
{
	m_status = STAND;
	m_dir = LEFT;
	run_texture = NULL;
	walk_attack_texture = NULL;
	run_attack_texture = NULL;
}

role::~role(void)
{
}

CCAnimate *role::createAnimate(STATUS actionName) {
	CCArray *spriteFrameArray = 0;
	switch(actionName){
	case RUN:
		spriteFrameArray = CCArray::createWithCapacity(6); 
		for (int i=1;i<=6;i++) {
			CCLOG(CCString::createWithFormat("%s%d.png","Img_ZRun",i)->getCString());
			spriteFrameArray->addObject(CCSpriteFrameCache::sharedSpriteFrameCache()->
				spriteFrameByName(CCString::createWithFormat("%s%d.png","Img_ZRun",i)->getCString()));
		}
		if (run_texture == NULL)
			run_texture = CCSprite::createWithSpriteFrame((CCSpriteFrame*)spriteFrameArray->objectAtIndex(0))->getTexture();
		break;
	case STANDING_ATTACK:
		spriteFrameArray = CCArray::createWithCapacity(16); 
		for (int i=1;i<=16;i++) {
			CCLOG(CCString::createWithFormat("%s%d.png","Img_Zhn",i)->getCString());
			spriteFrameArray->addObject(CCSpriteFrameCache::sharedSpriteFrameCache()->
				spriteFrameByName(CCString::createWithFormat("%s%d.png","Img_Zhn",i)->getCString()));
		}
		if (walk_attack_texture == NULL)
			walk_attack_texture = CCSprite::createWithSpriteFrame((CCSpriteFrame*)spriteFrameArray->objectAtIndex(0))->getTexture();
		break;
	case RUN_ATTACK:
		spriteFrameArray = CCArray::createWithCapacity(8); 
		for (int i=1;i<=8;i++) {
			CCLOG(CCString::createWithFormat("%s%d.png","Img_Zhici",i)->getCString());
			spriteFrameArray->addObject(CCSpriteFrameCache::sharedSpriteFrameCache()->
				spriteFrameByName(CCString::createWithFormat("%s%d.png","Img_Zhici",i)->getCString()));
		}
		if (run_attack_texture == NULL)
			run_attack_texture = CCSprite::createWithSpriteFrame((CCSpriteFrame*)spriteFrameArray->objectAtIndex(0))->getTexture();
		break;
	}
	spriteFrameArray->retain();
	return CCAnimate::create(CCAnimation::createWithSpriteFrames(spriteFrameArray,0.1f));
}

bool role::init()
{
	bool bRet = false;
	ref = this;
	CCDirector::sharedDirector()->getOpenGLView()->setAccelerometerKeyHook(role::keyboardHook);
	CCSize mysize = CCDirector::sharedDirector()->getWinSize();
	CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile("role/total.plist");

	sp = CCSprite::createWithSpriteFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->
			spriteFrameByName("Img_Zhn16.png"));
	sp->setPosition(ccp(mysize.width/4,mysize.height/3));
	m_position = ccp(mysize.width/4,mysize.height/3);
	this->addChild(sp);
	stand_texture = sp->getTexture();

	bRet = true;
	return bRet;
}

CCScene* role::scene()
{
	CCScene *scene = NULL;
	do{
		scene = CCScene::create();
		CC_BREAK_IF(!scene);
		role *layer = role::create();
		CC_BREAK_IF(!layer);
		scene->addChild(layer);
	}while(0);
	return scene;
}

void role::changeStatus(INPUT_KEYS inputAction)
{
	if (inputAction == m_previousKey)
		return;
	else
		m_previousKey = inputAction;
	switch(inputAction) {
	case LEFT_KEY:
		this->stopAllActions();
		sp->stopAllActions();
		sp->setTexture(run_texture);
		m_position = ccpAdd(m_position,ccp(-32,0));
		this->runAction(CCSpawn::create(this->createAnimate(RUN),
			CCMoveBy::create(0.28f, ccp(-32,0)),NULL));
		m_status = RUN;
		m_dir = LEFT;
		break;
	case RIGHT_KEY:
		this->stopAllActions();
		sp->stopAllActions();
		sp->setTexture(run_texture);
		m_position = ccpAdd(m_position,ccp(32,0));
		this->runAction(this->createAnimate(RUN));
		this->runAction(CCMoveBy::create(0.28f, ccp(32,0)));
		m_status = RUN;
		m_dir = RIGHT;
		break;
	case JUMP:
		break;
	case ATTACK:
		this->stopAllActions();
		sp->stopAllActions();
		if (m_status == RUN || m_status == RUN_ATTACK) {
			sp->setTexture(run_attack_texture);
			this->runAction(this->createAnimate(RUN_ATTACK));
			m_status = RUN_ATTACK;
		}
		else {
			sp->setTexture(walk_attack_texture);
			this->runAction(this->createAnimate(STANDING_ATTACK));
			m_status = STANDING_ATTACK;
		}
		break;
	case RELEASE:
		this->stopAllActions();
		sp->stopAllActions();
		sp->setTexture(stand_texture);
		m_status = STAND;
	}
}

void role::keyboardHook(UINT message,WPARAM wParam, LPARAM lParam)
{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32)
// ´¦ÀíWindows°´¼ü
    CCLog("onWin32KeyEvent message %d wParam %d lParam %d", message, wParam, lParam);
    /*
    // Up
    Win32KeyHook message 256 wParam 38 lParam 21495809
    onWin32KeyEvent message 256 wParam 38 lParam 21495809
    Win32KeyHook message 257 wParam 38 lParam -1052246015
    onWin32KeyEvent message 257 wParam 38 lParam -1052246015
    // Down
    Win32KeyHook message 256 wParam 40 lParam 22020097
    onWin32KeyEvent message 256 wParam 40 lParam 22020097
    Win32KeyHook message 257 wParam 40 lParam -1051721727
    onWin32KeyEvent message 257 wParam 40 lParam -1051721727
    // Left
    Win32KeyHook message 256 wParam 37 lParam 21692417
    onWin32KeyEvent message 256 wParam 37 lParam 21692417
    Win32KeyHook message 257 wParam 37 lParam -1052049407
    onWin32KeyEvent message 257 wParam 37 lParam -1052049407
    // Right
    Win32KeyHook message 256 wParam 39 lParam 21823489
    onWin32KeyEvent message 256 wParam 39 lParam 21823489
    Win32KeyHook message 257 wParam 39 lParam -1051918335
    onWin32KeyEvent message 257 wParam 39 lParam -1051918335
    */
	
    if (message == 256)
    {
        switch (wParam)
        {
        case 37:
            ref->changeStatus(LEFT_KEY);
			CCLog("LEFT");
            break;
		case 38:
            ref->changeStatus(JUMP);
			CCLog("JUMP");
            break;
        case 39:
            ref->changeStatus(RIGHT_KEY);
			CCLog("RIGHT");
            break;
		case 40:
            ref->changeStatus(ATTACK);
			CCLog("ATTACK");
            break;
        }
    }
    else if (message == 257)
    {
		ref->changeStatus(RELEASE);
    }
	
#endif
}
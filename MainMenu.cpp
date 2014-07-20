#include "MainMenu.h"
#include "ConstValues.h"

MainMenu::MainMenu(void)
{
}

MainMenu::~MainMenu(void)
{
}
	
bool MainMenu::init()
{
	if (!CCScene::init())
		return false;
	CCSprite *bg = CCSprite::create(MAINMENU_BG_PATH);
	addChild(bg);

	CCMenuItemLabel *startItem = CCMenuItemLabel::create(CCSprite::create(MAINMENU_BTN_START_PATH),this,
		menu_selector(MainMenu::startCallback));
	CCMenuItemLabel *loadItem = CCMenuItemLabel::create(CCSprite::create(MAINMENU_BTN_LOAD_PATH),this,
		menu_selector(MainMenu::loadCallback));
	CCMenuItemLabel *extraItem = CCMenuItemLabel::create(CCSprite::create(MAINMENU_BTN_EXTRA_PATH),this,
		menu_selector(MainMenu::extraCallback));
	CCMenuItemLabel *systemItem = CCMenuItemLabel::create(CCSprite::create(MAINMENU_BTN_SYSTEM_PATH),this,
		menu_selector(MainMenu::systemCallback));
	CCMenuItemLabel *exitItem = CCMenuItemLabel::create(CCSprite::create(MAINMENU_BTN_EXIT_PATH),this,
		menu_selector(MainMenu::exitCallback));
	CCMenu *pMenu = CCMenu::create(startItem,loadItem,extraItem,systemItem,exitItem,NULL);
	pMenu->alignItemsHorizontallyWithPadding(40.0f);
	pMenu->setEnabled(true);
	pMenu->setVisible(true);
	addChild(pMenu,1);

	return true;
}

void MainMenu::startCallback(CCObject* pSender){}
void MainMenu::loadCallback(CCObject* pSender){}
void MainMenu::extraCallback(CCObject* pSender){}
void MainMenu::systemCallback(CCObject* pSender){}
void MainMenu::exitCallback(CCObject* pSender){}
void MainMenu::cgCallback(CCObject* pSender){}
void MainMenu::rewardCallback(CCObject* pSender){}
void MainMenu::musicCallback(CCObject* pSender){}
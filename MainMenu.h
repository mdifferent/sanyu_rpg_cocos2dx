#include "cocos2d.h"

USING_NS_CC;

class MainMenu : public CCScene
{
	MainMenu(void);
	~MainMenu(void);
	bool init();

	void startCallback(CCObject* pSender);
	void loadCallback(CCObject* pSender);
	void extraCallback(CCObject* pSender);
	void systemCallback(CCObject* pSender);
	void exitCallback(CCObject* pSender);
	void cgCallback(CCObject* pSender);
	void rewardCallback(CCObject* pSender);
	void musicCallback(CCObject* pSender);

};
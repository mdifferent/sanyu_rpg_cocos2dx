#pragma once
#include "c:\program files\cocos2d-x-2.2.2\cocos2dx\layers_scenes_transitions_nodes\cclayer.h"
#include "cocos2d.h"
USING_NS_CC;

class InfoBarLayer :
	public CCLayer
{
public:
	InfoBarLayer(void);
	~InfoBarLayer(void);
	bool init();
	static InfoBarLayer *createWithBarName(const char *barName);
	void onEnter();
private:
	const char *m_barName;
};


#pragma once
#include "../cocos2dx/layers_scenes_transitions_nodes/CCLayer.h"
#include "cocos2d.h"
#include <string>
USING_NS_CC;

static const float IB_FADEIN_INTERVAL = 1.0;
class InfoBarLayer :
	public CCLayer
{
public:
	InfoBarLayer(void);
	~InfoBarLayer(void);
	bool init();
	static InfoBarLayer *createWithBarName(std::string &barName,float fFadein=IB_FADEIN_INTERVAL);
	void onEnter();
	void onMagicMatrixAvailable();
	void onMagicMatrixUnavailable();
private:
	std::string m_barName;
	float m_fadein_interval;
	CCSprite *pMagicTag;
};


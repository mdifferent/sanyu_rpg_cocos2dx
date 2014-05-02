#pragma once
#include "../cocos2dx/layers_scenes_transitions_nodes/CCLayer.h"
#include "cocos2d.h"
#include <string>

USING_NS_CC;

static const float BG_FADEIN_INTERVAL = 0.5;

class BackgroundLayer :
	public CCLayer
{
public:
	BackgroundLayer();
	~BackgroundLayer(void);
	bool init();
	static BackgroundLayer *createWithMapName(std::string &mapName,float fFadein=BG_FADEIN_INTERVAL);
	void onEnter();

private:
	std::string m_map;
	float m_fadein_interval;
};


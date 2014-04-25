#pragma once
#include "c:\program files\cocos2d-x-2.2.2\cocos2dx\layers_scenes_transitions_nodes\cclayer.h"
#include "cocos2d.h"
#include <string>

USING_NS_CC;
class BackgroundLayer :
	public CCLayer
{
public:
	BackgroundLayer();
	~BackgroundLayer(void);
	bool init();
	static BackgroundLayer *createWithMapName(std::string &mapName);
	void onEnter();

private:
	std::string m_map;
};


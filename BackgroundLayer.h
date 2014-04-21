#pragma once
#include "c:\program files\cocos2d-x-2.2.2\cocos2dx\layers_scenes_transitions_nodes\cclayer.h"
#include "cocos2d.h"

USING_NS_CC;
class BackgroundLayer :
	public CCLayer
{
public:
	BackgroundLayer();
	~BackgroundLayer(void);
	static BackgroundLayer *createWithMapName(const char *mapName);

private:
	const char *m_map;
};


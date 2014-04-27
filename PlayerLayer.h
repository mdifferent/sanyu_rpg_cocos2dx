#pragma once
#include "../cocos2dx/layers_scenes_transitions_nodes/CCLayer.h"
#include "cocos2d.h"
#include <map>
#include <string>
#include <PlayerData.h>
USING_NS_CC;

class PlayerLayer :
	public CCLayer
{
public:
	PlayerLayer(void);
	~PlayerLayer(void);
	static PlayerLayer *create(map<int,PlayerData> &data);
	void onEnter();
private:
	CCArray *m_players;
};


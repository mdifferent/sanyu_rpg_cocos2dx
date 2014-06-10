#include "TouchEventLayer.h"
const int PLAYER_SPRITE_HEIGHT = 180;
const int PLAYER_SPRITE_WIDTH = 200;

bool TouchEventLayer::init()
{

	return true;
}

bool TouchEventLayer::ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent)
{
	CCPoint touchPos = pTouch->getLocation();
	switch(m_TouchStatus) {
	case INIT:
		break;
	case WAIT_PLAYER_MENU:
		break;
	case PLAYER_WAIT_TARGET:
		break;
	case MONSTER_WAIT_TARGET:
		break;
	case WAIT_SELECT_LIST:
		break;
	case SPECIAL_ATTACK:
		break;
	}
	return true;
}
#pragma once
#include "cocos2d.h"
USING_NS_CC;

enum STATUS {
	STAND,
	RUN,
	STANDING_ATTACK,
	RUN_ATTACK
};

enum INPUT_KEYS {
	LEFT_KEY,
	RIGHT_KEY,
	JUMP,
	ATTACK,
	RELEASE
};

enum HERO_DIR {
	LEFT,
	RIGHT
};

class role :
	public CCLayer
{
public:
	role(void);
	~role(void);
	virtual bool init();
	static CCScene* scene();
	CREATE_FUNC(role);

#if (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32)
	static void keyboardHook(UINT message, WPARAM wParam, LPARAM lParam);
#endif
    void changeStatus(INPUT_KEYS inputAction);
	CCAnimate *role::createAnimate(STATUS actionName);

private:
	
	CCSprite *sp;
	CCPoint m_position;
	/*
	CCArray *walkArray;
	CCArray *runArray;
	CCArray *attackArray;
	CCArray *attackArray2;

	CCAction *stand_action;
	CCFiniteTimeAction *run_action;
	CCAction *walk_attack_animate;
	CCAction *run_attack_animate;
	*/
	CCTexture2D *stand_texture;
	CCTexture2D *run_texture;
	CCTexture2D *walk_attack_texture;
	CCTexture2D *run_attack_texture;

	STATUS m_status;
	HERO_DIR m_dir;
	INPUT_KEYS m_previousKey;
	


};




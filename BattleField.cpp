#include "BattleField.h"

BattleField::BattleField(void)
{
}

BattleField::~BattleField(void)
{
}

CCScene* BattleField::scene(int iSceneNo)
{
	BattleField *pScene = BattleField::create();
	if (scene)
	{
		pScene->m_sceneNo = iSceneNo;
	}
	else
	{
		CC_SAFE_DELETE(pScene);
		return NULL;
	}
	return pScene;
}

bool BattleField::init()
{
	//Load battle data
	m_data = BattleData::loadData(m_sceneNo);
		
	//Init map
	m_bg = BackgroundLayer::createWithMapName(m_data->getMapName());
	if (m_bg)
	{
		this->addChild(m_bg,0);
	}
	else
	{
		CCLOG("Add background layer error!");
		return false;
	}
	
	//Init info bar
	m_info_back = CCLayer::create();
	//Init players layer
	m_players = PlayerLayer::create();
	//Init monsters layer
	m_monsters = MonsterLayer::create();

	return true;
}
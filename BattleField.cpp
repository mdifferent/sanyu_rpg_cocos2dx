#include "BattleField.h"


BattleField::BattleField(void)
{
}

BattleField::~BattleField(void)
{
}

BattleField* BattleField::scene(int iSceneNo)
{
	BattleField *pScene = new BattleField();
	if (pScene)
	{
		pScene->m_sceneNo = iSceneNo;
		if(pScene->init())
		{
			pScene->autorelease();
		}
		else
        {
            CC_SAFE_DELETE(pScene);
            return NULL;
        }
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
	if (!CCScene::init())
	{
		return false;
	}
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
	m_info_back = InfoBarLayer::createWithBarName(m_data->getBarName());
	if (m_info_back)
	{
		this->addChild(m_info_back,1);
	}
	else
	{
		CCLOG("Add info layer error!");
		return false;
	}

	//Init players layer
	m_players = PlayerLayer::create(m_data->getPlayers());
	if (m_players)
	{
		this->addChild(m_players,2);
	}
	else
	{
		CCLOG("Add player layer error!");
		return false;
	}
	//Init monsters layer
	m_monsters = MonsterLayer::create(m_data->getMonsters());
	if (m_monsters)
	{
		this->addChild(m_monsters,2);
	}
	else
	{
		CCLOG("Add monster layer error!");
		return false;
	}

	m_delegate = new ActionDelegate(m_players,m_monsters);
	m_players->setDelegate(m_delegate);
	m_monsters->setDelegate(m_delegate);

	return true;
}

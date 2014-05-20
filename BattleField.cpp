#include "BattleField.h"

const int CELL_WIDHT = 300;
const int CELL_HEIGHT = 40;
const char *CELL_FONT = "Arial";
const int CELL_FONT_SIZE = 25;

BattleField::BattleField(void)
{
}

BattleField::~BattleField(void)
{
	CC_SAFE_DELETE(m_selectlist);
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
	bool bRet = true;
	//Load battle data
	if (!CCScene::init()){
		return false;
	}
	m_data = BattleData::loadData(m_sceneNo);
		
	//Init map
	m_bg = BackgroundLayer::createWithMapName(m_data->getMapName());
	m_info_back = InfoBarLayer::createWithBarName(m_data->getBarName());
	m_players = PlayerLayer::create(m_data->getPlayers());
	m_monsters = MonsterLayer::create(m_data->getMonsters());
	if (m_bg && m_info_back && m_players && m_monsters) {
		this->addChild(m_bg,0);
		this->addChild(m_info_back,1);
		this->addChild(m_players,2);
		this->addChild(m_monsters,2);
		bRet = true;
	}
	else {
		CCLOG("Init layer error!");
		CC_SAFE_DELETE(m_bg);
		CC_SAFE_DELETE(m_info_back);
		CC_SAFE_DELETE(m_players);
		CC_SAFE_DELETE(m_monsters);
		return false;
	}
	//m_selectlist = ListLayer::createWithDataSource(this);

	m_selectlist = new ListLayer();
	m_selectlist->setDataSource(this);
	if (m_selectlist->init()) {
		m_selectlist->setDelegate(this);
		m_selectlist->setVisible(false);
		this->addChild(m_selectlist,3);
	}
	else {
		CCLOG("Init select layer error!");
		CC_SAFE_DELETE(m_selectlist);
		CC_SAFE_DELETE(m_bg);
		CC_SAFE_DELETE(m_info_back);
		CC_SAFE_DELETE(m_players);
		CC_SAFE_DELETE(m_monsters);
		return false;
	}
	m_roundFinish = false;
	this->schedule( schedule_selector(BattleField::updateGame),0.5);
	return true;
}

void BattleField::updateGame(float ft)
{
	switch(m_monsters->getStatus()) {
	case SLEEP:
		CCLOG("MONSTER:SLEEP");
		switch(m_players->getStatus()) {
		case WAIT_COMMAND:
			CCLOG("PLAYER:WAIT_COMMAND");
			return;
		case ATTACK:
			CCLOG("PLAYER:ATTACK");
			m_monsters->setStatus(WAIT_TARGET);
			return;
		case SKILL:
			CCLOG("PLAYER:SKILL");
			m_selectlist->setVisible(true);
			m_selectlist->setContentType(SKILL_LIST);
			return;
		case GUARD:
			CCLOG("PLAYER:GUARD");
			return;
		case ESCAPE:
			CCLOG("PLAYER:ESCAPE");
			return;
		case ITEM:
			CCLOG("PLAYER:ITEM");
			m_selectlist->setVisible(true);
			m_selectlist->setContentType(ITEM_LIST);
			return;
		}
	case WAIT_TARGET:
		CCLOG("MONSTER:WAIT_TARGET");
		break;
	case TARGET_SELECTED:
		CCLOG("MONSTER:TARGET_SELECTED");
		switch(m_players->getStatus()) {
		case ATTACK:
			int iAttackSource = m_players->getSelectedPlayer();
			int iAttackTarget = m_monsters->getTarget();
			int iAttackValue = m_data->getPlayer(iAttackSource)->getProperty(MELEE_ATTACK);
			CCLOG("iAttackValue:%d",iAttackValue);
			int iDefenseValue = m_data->getMonster(iAttackTarget)->getProperty(DEFENSE);
			CCLOG("iDefenseValue:%d",iDefenseValue);
			int iDamage = iAttackValue - iDefenseValue;
			CCLOG("iDamage:%d",iDamage);
            //TODO:BUFF and DEBUFF may be consider in the futrue
            int iMonsterCurrentHP = m_data->getMonster(iAttackTarget)->getProperty(CURRENT_HP);
            if (iMonsterCurrentHP < iDamage) {
                m_data->getMonster(iAttackTarget)->setStatus(DEAD);
				m_monsters->killMosnter(iAttackTarget);
            } else {
                m_data->getMonster(iAttackTarget)->setProperty(CURRENT_HP, iMonsterCurrentHP-iDamage);
				m_monsters->onAttacked(iAttackTarget, iDamage);
            }
			CCLOG("Remain HP:%d",m_data->getMonster(iAttackTarget)->getProperty(CURRENT_HP));
            m_data->getPlayer(iAttackSource)->setStatus(FINISHED);
            break;
		}
		m_players->setStatus(WAIT_COMMAND);
		m_monsters->setStatus(SLEEP);
		//m_players->resetSelectedPlayer();
	}
}

CCTableViewCell *BattleField::tableCellAtIndex(CCTableView *table, unsigned int idx) {
	CCLOG("No of cell=%d",idx);
	int iPlayerNum = m_players->getSelectedPlayer();
	CCTableViewCell *cell = table->dequeueCell();
	if (!cell) {
		cell = new CCTableViewCell();
		cell->init();
		cell->autorelease();
		CCLabelTTF *pLabel = NULL;
		switch (m_selectlist->getContentType()) {
		case ITEM_LIST:	{
				map<string,int>::iterator itemIt = m_data->getPlayer(iPlayerNum)->getItemList()->begin();
				for (int i=0;i<(int)idx;i++)
					itemIt++;
				pLabel = CCLabelTTF::create(itemIt->first.c_str(), CELL_FONT, CELL_FONT_SIZE); 
				break;
			}
		case SKILL_LIST: {
				map<string,int>::iterator skillIt = m_data->getPlayer(iPlayerNum)->getSkillList()->begin();
				for (int i=0;i<(int)idx;i++)
					skillIt++;
				pLabel = CCLabelTTF::create(skillIt->first.c_str(), CELL_FONT, CELL_FONT_SIZE); 
				break;
			}
		default:
			pLabel = CCLabelTTF::create("None", CELL_FONT, CELL_FONT_SIZE); 
		}
        pLabel->setPosition(ccp(40, 0));
        cell->addChild(pLabel,4,456);
	}
	else {
		CCLabelTTF *pLabel = (CCLabelTTF*)cell->getChildByTag(456);
		switch(m_selectlist->getContentType()) {
		case ITEM_LIST: {
			map<string,int>::iterator itemIt = m_data->getPlayer(iPlayerNum)->getItemList()->begin();
			for (int i=0;i<(int)idx;i++)
				itemIt++;
			pLabel->setString(itemIt->first.c_str()); 
			break;
		}
		case SKILL_LIST: {
			map<string,int>::iterator skillIt = m_data->getPlayer(iPlayerNum)->getSkillList()->begin();
			for (int i=0;i<(int)idx;i++)
				skillIt++;
			pLabel->setString(skillIt->first.c_str()); 
			break;
		}
		default:
			pLabel->setString("None");
		}
		pLabel->setDirty(true);
	}
	return cell;
}

unsigned int BattleField::numberOfCellsInTableView(CCTableView *table)
{
	int iPlayerNum = m_players->getSelectedPlayer();
	switch(m_players->getStatus()) {
	case ITEM:
		return m_data->getPlayer(iPlayerNum)->getItemList()->size();
	case SKILL:
		return m_data->getPlayer(iPlayerNum)->getSkillList()->size();
	default:
		return 1;
	}
}

void BattleField::tableCellTouched(CCTableView* table, CCTableViewCell* cell) {
	CCLog("cell touched at index: %i", cell->getIdx());
	m_selectlist->setVisible(false);
	m_monsters->setStatus(WAIT_TARGET);

	if(m_selectlist->isTouchEnabled())
		CCLOG("Touch enable");
	else
		CCLOG("Touch disabled");
}

CCSize BattleField::cellSizeForTable(CCTableView *table) {
	return CCSizeMake(CELL_WIDHT, CELL_HEIGHT);
}

void BattleField::setListContent(LIST_TYPE type) {
	if (type != m_selectlist->getContentType())	{
		m_selectlist->setContentType(type);
	}
}
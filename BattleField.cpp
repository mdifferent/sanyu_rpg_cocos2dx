#include "BattleField.h"

const int CELL_WIDHT = 300;
const int CELL_HEIGHT = 40;
const char *CELL_FONT = "Arial";
const int CELL_FONT_SIZE = 25;
const int TOP_HP = 999;

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
	int iPlayerCount = m_data->getPlayers()->size();
	int iMonsterCount = m_data->getMonsters()->size();
	for (int i=0;i<iPlayerCount;i++)
		m_playersStatus.insert(make_pair<int,bool>(i,false));
	for (int i=0;i<iMonsterCount;i++)
		m_monstersStatus.insert(make_pair<int,bool>(i,true));

	//Init map
	m_bg = BackgroundLayer::createWithMapName(m_data->getMapName());
	m_info_back = InfoBarLayer::createWithBarName(m_data->getBarName());
	m_playerLayer = PlayerLayer::create(m_data->getPlayers());
	m_monsterLayer = MonsterLayer::create(m_data->getMonsters());
	if (m_bg && m_info_back && m_playerLayer && m_monsterLayer) {
		this->addChild(m_bg,0);
		this->addChild(m_info_back,1);
		this->addChild(m_playerLayer,2);
		this->addChild(m_monsterLayer,2);
		bRet = true;
	}
	else {
		CCLOG("Init layer error!");
		CC_SAFE_DELETE(m_bg);
		CC_SAFE_DELETE(m_info_back);
		CC_SAFE_DELETE(m_playerLayer);
		CC_SAFE_DELETE(m_monsterLayer);
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
		CC_SAFE_DELETE(m_playerLayer);
		CC_SAFE_DELETE(m_monsterLayer);
		return false;
	}
	m_roundOwner = PLAYER;
	this->schedule( schedule_selector(BattleField::updateGame),0.5);
	return true;
}

void BattleField::runPlayerRound() {
	switch(m_monsterLayer->getStatus()) {
	case SLEEP:
		CCLOG("MONSTER:SLEEP");
		switch(m_playerLayer->getStatus()) {
		case WAIT_COMMAND:
			CCLOG("PLAYER:WAIT_COMMAND");
			return;
		case ATTACK:
			CCLOG("PLAYER:ATTACK");
			m_monsterLayer->setStatus(WAIT_TARGET);
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
		switch(m_playerLayer->getStatus()) {
		case ATTACK:
			int iAttackSource = m_playerLayer->getSelectedPlayer();
			int iAttackTarget = m_monsterLayer->getTarget();
			int iAttackValue = m_data->getPlayer(iAttackSource)->getProperty(MELEE_ATTACK);
			CCLOG("iAttackValue:%d",iAttackValue);
			int iDefenseValue = m_data->getMonster(iAttackTarget)->getProperty(MELEE_DEFENSE);
			CCLOG("iDefenseValue:%d",iDefenseValue);
			int iDamage = iAttackValue - iDefenseValue;
			CCLOG("iDamage:%d",iDamage);
            //TODO:BUFF and DEBUFF may be consider in the futrue
            int iMonsterCurrentHP = m_data->getMonster(iAttackTarget)->getProperty(CURRENT_HP);
            if (iMonsterCurrentHP <= iDamage) {
                m_data->getMonster(iAttackTarget)->setStatus(DEAD);
				m_data->getMonster(iAttackTarget)->setProperty(CURRENT_HP,0);
				m_monsterLayer->killMosnter(iAttackTarget);
            } else {
                m_data->getMonster(iAttackTarget)->setProperty(CURRENT_HP, iMonsterCurrentHP-iDamage);
				m_monsterLayer->onAttacked(iAttackTarget, iDamage);
            }
			CCLOG("Remain HP:%d",m_data->getMonster(iAttackTarget)->getProperty(CURRENT_HP));
			m_data->getPlayer(iAttackSource)->setStatus(FINISHED);
			m_playersStatus[iAttackSource] = true;
            break;
		}
		m_playerLayer->setStatus(WAIT_COMMAND);
		m_monsterLayer->setStatus(SLEEP);
	}
}

bool BattleField::checkRoundFinished() {
	bool bRes = true;
	if (m_roundOwner == PLAYER) {
		int iPlayerCount = m_playersStatus.size();
		for (int i=0;i<iPlayerCount;i++)
			if (!m_playersStatus[i])		//False = haven't run action
				bRes = false;
	}
	else if (m_roundOwner == COMPUTER) {
		int iMonsterCount = m_monstersStatus.size();
		for (int i=0;i<iMonsterCount;i++)
			if (!m_monstersStatus[i])
				bRes = false;
	}
	return bRes;
}

void BattleField::switchOwner() {
	m_roundOwner = m_roundOwner == PLAYER ? COMPUTER : PLAYER;
}

void BattleField::runComputerRound() {
	map<int,MonsterData*> *pMonsters = m_data->getMonsters();
	map<int,PlayerData*> *pPlayers = m_data->getPlayers();
	int iMosnterCount = pMonsters->size();
	int iPlayerCount = pPlayers->size();
	int iAttackTarget = -1;
	int iMinHP = MAX_HP;
	for (int i=0;i<iMosnterCount;i++) {
		if (pMonsters->at(i)->getStatus() != DEAD) {
			for (int j=0;j<iPlayerCount;j++) {
				if (pPlayers->at(j)->getStatus() != DEAD && 
					pPlayers->at(j)->getProperty(CURRENT_HP) < iMinHP) {
					iMinHP = pPlayers->at(j)->getProperty(CURRENT_HP);
					iAttackTarget = j;
				}
			}
			int iDefenseValue = pPlayers->at(iAttackTarget)->getProperty(MELEE_DEFENSE);
			int iAttackValue = pMonsters->at(i)->getProperty(MELEE_ATTACK);
			int iDamageValue = pPlayers->at(iAttackTarget)->getStatus() == DEFENSE ? iAttackValue-iDefenseValue : iAttackValue;
			int iPlayerCurrentHP = pPlayers->at(iAttackTarget)->getProperty(CURRENT_HP);
			if (iDamageValue >= iPlayerCurrentHP) {
				pPlayers->at(iAttackTarget)->setStatus(DEAD);
				pPlayers->at(iAttackTarget)->setProperty(CURRENT_HP,0);
				m_playerLayer->onPlayerKilled(iAttackTarget);
			}
			else {
				pPlayers->at(iAttackTarget)->setProperty(CURRENT_HP, iPlayerCurrentHP-iDamageValue);
				m_playerLayer->onPlayerAttacked(iAttackTarget,iDamageValue);
			}
		}
	}
}

void BattleField::updateGame(float ft)
{
	switch(m_roundOwner) {
	case PLAYER:
		runPlayerRound();
		break;
	case COMPUTER:
		runComputerRound();
	}
	if (checkRoundFinished())
		switchOwner();
}

CCTableViewCell *BattleField::tableCellAtIndex(CCTableView *table, unsigned int idx) {
	CCLOG("No of cell=%d",idx);
	int iPlayerNum = m_playerLayer->getSelectedPlayer();
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
	int iPlayerNum = m_playerLayer->getSelectedPlayer();
	switch(m_playerLayer->getStatus()) {
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
	m_monsterLayer->setStatus(WAIT_TARGET);

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
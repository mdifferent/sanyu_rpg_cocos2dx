#include "BattleField.h"
#include "InstanceDatabase.h"
#include "ListItemCell.h"
#include "ConstValues.h"

#if (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32)  
#include "../proj.win32/WIN32Util.h"
#endif 


BattleField::BattleField(void)
{
}

BattleField::~BattleField(void)
{
	//CC_SAFE_DELETE(m_selectlist);
}

BattleField* BattleField::scene(int iSceneNo)
{
	BattleField *pScene = new BattleField();
	if (pScene)	{
		pScene->m_sceneNo = iSceneNo;
		if(pScene->init()) {
			pScene->autorelease();
		}
		else {
            CC_SAFE_DELETE(pScene);
            return NULL;
        }
	}
	else {
		CC_SAFE_DELETE(pScene);
		return NULL;
	}
	return pScene;
}

bool BattleField::init()
{
	bool bRet = true;
	//Load battle data
	if (!CCScene::init()) {
		return false;
	}
	m_data = BattleData::loadData(m_sceneNo);
	list<int> p;
	InstanceDatabase::getDatabaseInstance()->initItemSetByIds(p);
	InstanceDatabase::getDatabaseInstance()->initSkillSetByIds(p);
	int iPlayerCount = m_data->getPlayers()->size();
	int iMonsterCount = m_data->getMonsters()->size();
	for (int i=0;i<iPlayerCount;i++)
		m_isPlayerFinished.insert(make_pair<int,bool>(i,false));
	for (int i=0;i<iMonsterCount;i++)
		m_isMonsterFinished.insert(make_pair<int,bool>(i,true));

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
		m_selectlist->setTouchEnabled(false);
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
	bool isMagicMatrixAva = false;
	for (int i=0;i<m_data->getMonsters()->size();i++) {
		int current = m_data->getMonster(i)->getProperty(CURRENT_HP);
		int max = m_data->getMonster(i)->getProperty(MAX_HP)*0.3;
		if ( current < max && m_data->getMonster(i)->getStatus() != DEAD) {
				isMagicMatrixAva = true;
				m_monsterLayer->onMagicMatrixAvailable();
				break;
		}
	}
	if (!isMagicMatrixAva)
		m_monsterLayer->onMagicMatrixUnavailable();
	switch(m_monsterLayer->getStatus()) {
	case MonsterLayer::SLEEP:
		CCLOG("MONSTER:SLEEP");
		switch(m_playerLayer->getStatus()) {
		case PlayerLayer::WAIT_COMMAND:
			CCLOG("PLAYER:WAIT_COMMAND");
			return;
		case PlayerLayer::MENU_OPEN:
			if (m_selectlist->isVisible()) {
				m_selectlist->setVisible(false);
				m_selectlist->setTouchEnabled(false);
			}
			return;
		case PlayerLayer::MENU_SELECTED:
			switch(m_playerLayer->getSelectedMenu()){
			case PlayerLayer::ATTACK:
				CCLOG("PLAYER:ATTACK");
				m_monsterLayer->setStatus(MonsterLayer::WAIT_TARGET);
				return;
			case PlayerLayer::SKILL:
				CCLOG("PLAYER:SKILL");
				m_selectlist->setVisible(true);
				m_selectlist->setTouchEnabled(true);
				m_selectlist->setContentType(SKILL_LIST);
				return;
			case PlayerLayer::ITEM:
				CCLOG("PLAYER:ITEM");
				m_selectlist->setVisible(true);
				m_selectlist->setTouchEnabled(true);
				m_selectlist->setContentType(ITEM_LIST);
				return;
			case PlayerLayer::GUARD:
				CCLOG("PLAYER:GUARD");
				//m_dalta->getPlayer(m_playerLayer->getSelectedPlayer())->setStatus(DEFENSE);
				m_isPlayerFinished[m_playerLayer->getSelectedPlayer()] = true;
				m_playerLayer->setStatus(PlayerLayer::WAIT_COMMAND);
				m_monsterLayer->setStatus(MonsterLayer::SLEEP);
				return;
			case PlayerLayer::ESCAPE:
				CCLOG("PLAYER:ESCAPE");
				return;
			};
		case PlayerLayer::WAIT_TARGET:
			CCLOG("PLAYER:WAIT_TARGET");
			m_selectlist->setVisible(false);
			m_selectlist->setTouchEnabled(false);
			m_isPlayerFinished[m_playerLayer->getSelectedPlayer()] = true;
			//BUG:Cancel after select item, mark player as finished at where?
			//Select command again ? or select target?
			return;
		case PlayerLayer::TARGET_SELECTED:
			//TODO:use item to recover
			int iItemId = getSelectedItemId();
			int iTargetPlayer = m_playerLayer->getSelectedPlayer();
			int iCurrentHP = m_data->getPlayer(iTargetPlayer)->getProperty(CURRENT_HP);
			int iMaxHP =  m_data->getPlayer(iTargetPlayer)->getProperty(MAX_HP);
			ItemData *pItem = InstanceDatabase::getDatabaseInstance()->getItemById(iItemId);
			map<ItemData::EffectAttribute,int> effect = pItem->getItemEffects();
			map<ItemData::EffectAttribute,int>::iterator effIter = effect.begin();
			while (effIter != effect.end()) {
				switch(effIter->first) {
				case ItemData::CURRENT_HP:
					if (iCurrentHP+effIter->second > iMaxHP)
						m_data->getPlayer(iTargetPlayer)->setProperty(CURRENT_HP,iMaxHP);
					else
						m_data->getPlayer(iTargetPlayer)->setProperty(CURRENT_HP,iCurrentHP+effIter->second);
					m_playerLayer->onPlayerPropModified(CURRENT_HP,iTargetPlayer,effIter->second);
					break;
				case ItemData::CURRENT_SP:

					break;
				};
				effIter++;
			}
			m_playerLayer->setStatus(PlayerLayer::WAIT_COMMAND);
			return;
		}
		break;
	case MonsterLayer::WAIT_TARGET:
		if (m_playerLayer->getStatus() == PlayerLayer::MENU_OPEN) {
			m_monsterLayer->setStatus(MonsterLayer::SLEEP);
			return;
		}
		m_isPlayerFinished[m_playerLayer->getSelectedPlayer()] = true;

		CCLOG("MONSTER:WAIT_TARGET");
		break;
	case MonsterLayer::TARGET_SELECTED: {
		CCLOG("MONSTER:TARGET_SELECTED");
		int iAttackTarget = m_monsterLayer->getTarget();
		int iAttackSource = m_playerLayer->getSelectedPlayer();
		switch(m_playerLayer->getSelectedMenu()) {
		case PlayerLayer::ATTACK: {
			int iAttackValue = m_data->getPlayer(iAttackSource)->getProperty(MELEE_ATTACK);
			int iDefenseValue = m_data->getMonster(iAttackTarget)->getProperty(MELEE_DEFENSE);
			int iDamage = iAttackValue - iDefenseValue;
			int iMonsterCurrentHP = m_data->getMonster(iAttackTarget)->getProperty(CURRENT_HP);
            //TODO:BUFF and DEBUFF may be considered in the futrue
            if (iMonsterCurrentHP <= iDamage) {
                m_data->getMonster(iAttackTarget)->setStatus(DEAD);
				m_data->getMonster(iAttackTarget)->setProperty(CURRENT_HP,0);
				m_monsterLayer->killMosnter(iAttackTarget);
            }  
			else {
                m_data->getMonster(iAttackTarget)->setProperty(CURRENT_HP, iMonsterCurrentHP-iDamage);
				m_monsterLayer->onAttacked(iAttackTarget, iDamage);
            }
			CCLOG("Remain HP:%d",m_data->getMonster(iAttackTarget)->getProperty(CURRENT_HP));
			m_data->getPlayer(iAttackSource)->setStatus(FINISHED);
            break;
		}
		case PlayerLayer::ITEM:
			effectOnMonsters(InstanceDatabase::getDatabaseInstance()->getItemById(getSelectedItemId()));
			break;
		case PlayerLayer::SKILL:{
			int iSkillId = getSelectedItemId();
			SkillData *pData = InstanceDatabase::getDatabaseInstance()->getSkillById(iSkillId);
			int iCost = pData->getCost();
			int iCurrentSP = m_data->getPlayer(iAttackSource)->getProperty(CURRENT_SP);
			if (iCost <= iCurrentSP) {
				effectOnMonsters(pData);
				m_data->getPlayer(iAttackSource)->setProperty(CURRENT_SP,iCurrentSP-iCost);
				m_playerLayer->onPlayerPropModified(CURRENT_SP,iAttackSource,0-iCost);
			}
			else
				CCLOG("No enough SP");
			break;
		}
		}		
		m_isPlayerFinished[iAttackSource] = true;
		m_playerLayer->setStatus(PlayerLayer::WAIT_COMMAND);
		m_monsterLayer->setStatus(MonsterLayer::SLEEP);
		break;
		}
	case MonsterLayer::SPECIAL_ATTACK:
		CCLOG("Special Attack");
		m_playerLayer->beforeSpecialAttack();
		break;
	case MonsterLayer::SPECIAL_ATTACK_FINISHED:
		CCLOG("Special Attack Finished");
		if (m_monsterLayer->isBubbleFailed()) {
			int currentHP = m_data->getPlayer(0)->getProperty(CURRENT_HP);
			int maxHP = m_data->getPlayer(0)->getProperty(MAX_HP);
			float damage = maxHP * 0.05;
			if (damage > currentHP) {
				m_data->getPlayer(0)->setStatus(DEAD);
				m_data->getPlayer(0)->setProperty(CURRENT_HP,0);
				m_playerLayer->onPlayerKilled(0);
			}
			else {
				m_data->getPlayer(0)->setProperty(CURRENT_HP,currentHP-damage);
				m_playerLayer->onPlayerPropModified(CURRENT_HP,0,-damage);
			}
		}
		m_playerLayer->afterSpecialAttack();
		m_playerLayer->setStatus(PlayerLayer::WAIT_COMMAND);
		m_monsterLayer->setStatus(MonsterLayer::SLEEP);
		break;
	}
}

void BattleField::effectOnMonsters(AbstractListItemData *pEffectSource) 
{
	if (pEffectSource->getMultiTarget()) {
		map<int,MonsterData*> *monsters = m_data->getMonsters();
		map<int,MonsterData*>::iterator monsterIter = monsters->begin();
		while (monsterIter != monsters->end()) {
			if (monsterIter->second->getStatus() != DEAD) {
				effectOnMonster(monsterIter->first,pEffectSource);
				CCLOG("Attacks on all monsters");
			}
			monsterIter++;
		}
	}
	else{
		int iAttackTarget = m_monsterLayer->getTarget();
		effectOnMonster(iAttackTarget,pEffectSource);
	}
}

void BattleField::effectOnMonster(int monsterNo,AbstractListItemData *pEffectSource) 
{
	map<AbstractListItemData::EffectAttribute,int> effect = pEffectSource->getItemEffects();
	map<AbstractListItemData::EffectAttribute,int>::iterator effIter = effect.begin();
	int iMonsterCurrentHP = m_data->getMonster(monsterNo)->getProperty(CURRENT_HP);
	while (effIter != effect.end()) {
		switch(effIter->first) {
		case ItemData::CURRENT_HP: {
			int iAttackValue = effIter->second;
			if (iMonsterCurrentHP <= iAttackValue) {
				m_data->getMonster(monsterNo)->setStatus(DEAD);
				m_data->getMonster(monsterNo)->setProperty(CURRENT_HP,0);
				m_monsterLayer->killMosnter(monsterNo);
			}
			else {
				m_data->getMonster(monsterNo)->setProperty(CURRENT_HP, iMonsterCurrentHP-iAttackValue);
				m_monsterLayer->onAttacked(monsterNo, iAttackValue);
			}
			break;
		}
		case ItemData::CURRENT_SP:
				//TODO:Other effects
			break;
		}
		effIter++;
	}
}

void BattleField::runComputerRound() 
{
	CCLOG("COMPUTER ROUND");
	map<int,MonsterData*> *pMonsters = m_data->getMonsters();
	map<int,PlayerData*> *pPlayers = m_data->getPlayers();
	int iMosnterCount = pMonsters->size();
	int iPlayerCount = pPlayers->size();
	int iAttackTarget = -1;
	int iMinHP = TOP_HP;
	for (int i=0;i<iMosnterCount;i++) {
		CCLOG("Monster %d",i);
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
				m_playerLayer->onPlayerPropModified(CURRENT_HP,iAttackTarget,0-iDamageValue);
			}
			else {
				pPlayers->at(iAttackTarget)->setProperty(CURRENT_HP, iPlayerCurrentHP-iDamageValue);
				m_playerLayer->onPlayerPropModified(CURRENT_HP,iAttackTarget,0-iDamageValue);
			}
			m_data->getMonster(i)->setStatus(FINISHED);
			m_isMonsterFinished[i] = true;
		}
	}
}

bool BattleField::checkRoundFinished() {
	bool bRes = true;
	if (m_roundOwner == PLAYER) {
		int iPlayerCount = m_isPlayerFinished.size();
		for (int i=0;i<iPlayerCount;i++)
			if (m_isPlayerFinished[i] == false)		//False = haven't run action
				bRes = false;
	}
	else if (m_roundOwner == COMPUTER) {
		int iMonsterCount = m_isMonsterFinished.size();
		for (int i=0;i<iMonsterCount;i++)
			if (m_isMonsterFinished[i] == false)
				bRes = false;
	}
	return bRes;
}

void BattleField::switchOwner() {
	if (m_roundOwner == PLAYER) {
		map<int,bool>::iterator it = m_isMonsterFinished.begin();
		while ( it != m_isMonsterFinished.end()) {
			if (m_data->getMonster(it->first)->getStatus() == DEAD)
				it->second = true;
			else
				it->second = false;
			it++;
		}
		m_roundOwner = COMPUTER;
	}
	else if (m_roundOwner == COMPUTER) {
		map<int,bool>::iterator it = m_isPlayerFinished.begin();
		while ( it != m_isPlayerFinished.end()) {
			if (m_data->getPlayer(it->first)->getStatus() == DEAD)
				it->second = true;
			else
				it->second = false;
			it++;
		}
		m_roundOwner = PLAYER;
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

CCTableViewCell *BattleField::tableCellAtIndex(CCTableView *table, unsigned int idx) 
{
	CCLOG("No of cell=%d",idx);
	int iPlayerNum = m_playerLayer->getSelectedPlayer();
	CCTableViewCell *cell = table->dequeueCell();
	string cellItemName;
	string cellItemTarget;
	int cellCount = 0;
	map<int,int>::const_iterator itemIt;
	AbstractListItemData *item = NULL;
	switch (m_selectlist->getContentType()) {
	case ITEM_LIST:	
		if (m_data->getPlayer(iPlayerNum)->getItemList()->size() > 0) {
			itemIt = m_data->getPlayer(iPlayerNum)->getItemList()->begin();
			for (int i=0;i<(int)idx;i++)
				itemIt++;
			item = InstanceDatabase::getDatabaseInstance()->getItemById(itemIt->first);
			cellCount = itemIt->second;
		}
		break;
	case SKILL_LIST:
		if (m_data->getPlayer(iPlayerNum)->getSkillList()->size() > 0) {
			itemIt = m_data->getPlayer(iPlayerNum)->getSkillList()->begin();
			for (int i=0;i<(int)idx;i++)
				itemIt++;
			item = InstanceDatabase::getDatabaseInstance()->getSkillById(itemIt->first);
			cellCount = dynamic_cast<SkillData*>(item)->getCost();
		}
	};
	if (item != NULL) {
		cellItemName = item->getName();
		if (item->getTargetType() == AbstractListItemData::FRIEND)
			if (item->getMultiTarget())
				cellItemTarget = PLAYER_ALL;
			else
				cellItemTarget = PLAYER_ONE;
		else if (item->getTargetType() == AbstractListItemData::ENEMY)
			if (item->getMultiTarget())
				cellItemTarget = ENEMY_ALL;
			else
				cellItemTarget = ENEMY_ONE;
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32)
		GBKToUTF(cellItemName);
		GBKToUTF(cellItemTarget);
#endif
	}
	if (!cell) {
		cell = ListItemCell::create(cellItemName,cellItemTarget,cellCount);
		return cell;
	}
	else {
		ListItemCell *oldCell = dynamic_cast<ListItemCell*>(cell);
		oldCell->updateLabels(cellItemName,cellItemTarget,cellCount);
		return oldCell;
	}
	return NULL;
}

unsigned int BattleField::numberOfCellsInTableView(CCTableView *table)
{
	int iPlayerNum = m_playerLayer->getSelectedPlayer();
	int iCellCount = 0;
	switch(m_playerLayer->getStatus()) {
	case PlayerLayer::ITEM:
		iCellCount = m_data->getPlayer(iPlayerNum)->getItemList()->size();
		break;
	case PlayerLayer::SKILL:
		iCellCount = m_data->getPlayer(iPlayerNum)->getSkillList()->size();
	}
	return iCellCount;
}

void BattleField::tableCellTouched(CCTableView* table, CCTableViewCell* cell) {
	CCLog("cell touched at index: %i", cell->getIdx());
	//CCSprite *pCellbg = CCSprite::create("sanyu/cellback.png");
	//cell->addChild(pCellbg,3,111);
	int idx = cell->getIdx();
	m_selectlist->setVisible(false);
	int iPlayerNum = m_playerLayer->getSelectedPlayer();
	switch (m_selectlist->getContentType()) {
	case ITEM_LIST:	{
		const map<int,int> *p = m_data->getPlayer(iPlayerNum)->getItemList();
		int iSize = p->size();
		if (idx > iSize || iSize == 0)
			return;
		map<int,int>::const_iterator itemIt = m_data->getPlayer(iPlayerNum)->getItemList()->begin();
		for (int i=0;i<idx;i++)
			itemIt++;
		setSelectedItemId(itemIt->first);
		int iId = itemIt->first;
		ItemData *pItem = InstanceDatabase::getDatabaseInstance()->getItemById(itemIt->first);
		if (pItem->getTargetType() == ItemData::ENEMY) {
			if (!pItem->getMultiTarget())
				m_monsterLayer->setStatus(MonsterLayer::WAIT_TARGET);
			else 
				m_monsterLayer->setStatus(MonsterLayer::TARGET_SELECTED);		
		}
		else if (pItem->getTargetType() == ItemData::FRIEND){
			m_monsterLayer->setStatus(MonsterLayer::SLEEP);		
			if (!pItem->getMultiTarget())
				m_playerLayer->setStatus(PlayerLayer::WAIT_TARGET);
			else 
				m_playerLayer->setStatus(PlayerLayer::WAIT_TARGET);	
		}
		m_data->getPlayer(m_playerLayer->getSelectedPlayer())->useItem(itemIt->first);
		break;
	}
	case SKILL_LIST: {
		const map<int,int> *p = m_data->getPlayer(iPlayerNum)->getSkillList();
		int iSize = p->size();
		if (idx > iSize || iSize == 0)
			return;
		map<int,int>::const_iterator skillIt = m_data->getPlayer(iPlayerNum)->getSkillList()->begin();
		for (int i=0;i<idx;i++)
			skillIt++;
		setSelectedItemId(skillIt->first);
		int iId = skillIt->first;
		SkillData *pItem = InstanceDatabase::getDatabaseInstance()->getSkillById(skillIt->first);
		if (pItem->getTargetType() == SkillData::ENEMY) {
			if (!pItem->getMultiTarget())
				m_monsterLayer->setStatus(MonsterLayer::WAIT_TARGET);
			else 
				m_monsterLayer->setStatus(MonsterLayer::TARGET_SELECTED);
		}
		else if (pItem->getTargetType() == ItemData::FRIEND) {
			m_monsterLayer->setStatus(MonsterLayer::SLEEP);	
			if (!pItem->getMultiTarget())
				m_playerLayer->setStatus(PlayerLayer::WAIT_TARGET);
			else 
				m_playerLayer->setStatus(PlayerLayer::WAIT_TARGET);	
		}
		m_data->getPlayer(m_playerLayer->getSelectedPlayer())->useSkill(iId);
		break;
	}
	};
	
	if(m_selectlist->isTouchEnabled()) {
		m_selectlist->setTouchEnabled(false);
		m_selectlist->setVisible(false);
	}
}

CCSize BattleField::cellSizeForTable(CCTableView *table) {
	return CCSizeMake(CELL_WIDHT, CELL_HEIGHT);
}

void BattleField::setListContent(LIST_TYPE type) {
		m_selectlist->setContentType(type);
}
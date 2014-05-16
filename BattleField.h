#pragma once
#include "../cocos2dx/layers_scenes_transitions_nodes/CCScene.h"
#include "../extensions/GUI/CCScrollView/CCTableView.h"
#include "BattleData.h"
#include "BackgroundLayer.h"
#include "InfoBarLayer.h"
#include "PlayerLayer.h"
#include "MonsterLayer.h"
#include "ListLayer.h"

USING_NS_CC;
using namespace cocos2d::extension;

class BattleField :
	public CCScene,public CCTableViewDataSource,public CCTableViewDelegate
{
public:
	BattleField(void);
	~BattleField(void);
	static BattleField* scene(int iSceneNo);
	bool init();
    void updateGame(float ft);
	
	CCTableViewCell* tableCellAtIndex(CCTableView *table, unsigned int idx);
	unsigned int numberOfCellsInTableView(CCTableView *table);
	void tableCellTouched(CCTableView* table, CCTableViewCell* cell);
	CCSize cellSizeForTable(CCTableView *table);

	void tableCellHighlight(CCTableView* table, CCTableViewCell* cell){}
	void tableCellUnhighlight(CCTableView* table, CCTableViewCell* cell){}
	void scrollViewDidScroll(CCScrollView *){}
	void scrollViewDidZoom(CCScrollView *){}
	
	void setListContent(LIST_TYPE);

private:
	BackgroundLayer *m_bg;
	InfoBarLayer *m_info_back;
	PlayerLayer *m_players;
	MonsterLayer *m_monsters;
	ListLayer *m_selectlist;

	int m_sceneNo;
	BattleData *m_data;
	bool m_roundFinish;
	map<int,bool> m_playersStatus;
};


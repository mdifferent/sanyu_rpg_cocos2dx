#pragma once
#include "../cocos2dx/layers_scenes_transitions_nodes/CCLayer.h"
#include "cocos2d.h"
#include "../extensions/GUI/CCScrollView/CCTableView.h"
#include <string>

USING_NS_CC;
using namespace cocos2d::extension;

enum LIST_TYPE {
	ITEM_LIST,
	SKILL_LIST,
	EMPTY
};

class ListLayer :
	public CCLayer
{
public:
	ListLayer(void);
	~ListLayer(void);
	bool init();
	static ListLayer *createWithDataSource(CCTableViewDataSource *source);

	void setContentType(LIST_TYPE);
	LIST_TYPE getContentType(){return m_type;}
	void setDataSource(CCTableViewDataSource *source){m_datasource = source;}
	void setDelegate(CCTableViewDelegate *pDelegate){m_pTableView->setDelegate(pDelegate);}
	void setTouchEnabled(bool value);

private:
	LIST_TYPE m_type;
	CCTableView *m_pTableView;				//TODO:Should have lower priority than the layer
	CCSprite *m_pBackImg;
	CCLabelTTF *m_pLabel;
	CCTableViewDataSource *m_datasource;
};
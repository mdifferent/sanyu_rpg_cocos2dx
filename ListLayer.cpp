#include "ListLayer.h"
#include "ConstValues.h"
#include "Resources.h"

ListLayer::ListLayer(void)
{
	m_type = EMPTY;
}

ListLayer::~ListLayer(void)
{
	CC_SAFE_DELETE(m_pBackImg);
	CC_SAFE_DELETE(m_pLabel);
	CC_SAFE_DELETE(m_pTableView);
}

ListLayer *ListLayer::createWithDataSource(CCTableViewDataSource *source) {
	ListLayer *pListLayer = new ListLayer();
	if (!pListLayer) {
		CC_SAFE_DELETE(pListLayer);
		return NULL;
	}
	else {
		if (source) {
			pListLayer->m_datasource = source;
		}
		else {
			CCLOG("Datasource is invalid!");
			CC_SAFE_DELETE(pListLayer);
			return NULL;
		}
		if (pListLayer->init()) {
			pListLayer->autorelease();	//Should be done out side factory method, init() need to call object pointer which haven't been return to caller
		}
		else
		{
			CC_SAFE_DELETE(pListLayer);
			return NULL;
		}
	}
	return pListLayer;
}

bool ListLayer::init() {

	if (!CCLayer::init()) {
		return false;
	}

	CCSize winSize = CCDirector::sharedDirector()->getVisibleSize();
	m_pBackImg = CCSprite::create(SELECT_LIST_BG_PATH);
	m_pTableView = CCTableView::create(m_datasource,CCSizeMake(BACK_WIDTH, BACK_HEIGHT-BACK_LABEL_HEIGHT));
	m_pLabel = CCLabelTTF::create(p_skill, "Arial", 18);
	if (m_pBackImg && m_pTableView && m_pLabel) {
		float fCenterX = winSize.width*0.5;
		float fCenterY = winSize.height*0.5;
		float fWinWidth = m_pBackImg->getContentSize().width;
		float fWinHeight = m_pBackImg->getContentSize().height;
		float fLabelWidth = m_pLabel->getContentSize().width;
		float fLabelHeight = m_pLabel->getContentSize().height;
		m_pTableView->setDirection(kCCScrollViewDirectionVertical);
		m_pTableView->setVerticalFillOrder(kCCTableViewFillTopDown);
		m_pTableView->setPosition(ccp(fCenterX-fWinWidth*0.5,fCenterY*1.2-fWinHeight*0.5));
		m_pLabel->setPosition(ccp(fCenterX-fWinWidth*0.5+fLabelWidth*0.5,fCenterY*1.2+fWinHeight*0.5-fLabelHeight*0.5));
		m_pBackImg->setPosition(ccp(fCenterX,fCenterY*1.2));
		this->addChild(m_pBackImg,3);
		this->addChild(m_pLabel,4);
		this->addChild(m_pTableView,4);
		m_type = EMPTY;
		m_pTableView->reloadData();
	}
	else {
		CC_SAFE_DELETE(m_pBackImg);
		CC_SAFE_DELETE(m_pTableView);
		CC_SAFE_DELETE(m_pLabel);
		CCLOG("Create List view error!");
		return false;
	}

	return true;
}

void ListLayer::setContentType(LIST_TYPE type) {
	if (m_type != type) {
		m_type = type;
		switch(m_type) {
		case ITEM_LIST:
			m_pLabel->setString(p_item);
			break;
		case SKILL_LIST:
			m_pLabel->setString(p_skill);
			break;
		case EMPTY:
			m_pLabel->setString("None");
		}
		m_pLabel->setDirty(true);
	}
	m_pTableView->reloadData();
}

void ListLayer::setTouchEnabled(bool value)
{
	CCLayer::setTouchEnabled(value);
	if (m_pTableView)
		m_pTableView->setTouchEnabled(value);
}
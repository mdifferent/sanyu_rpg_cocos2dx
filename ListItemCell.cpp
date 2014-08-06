#include "ListItemCell.h"
#include "ConstValues.h"

ListItemCell::ListItemCell(void)
{
}

ListItemCell::~ListItemCell(void)
{
}

bool ListItemCell::init() 
{
	if(!CCTableViewCell::init()) {
		return false;
	}
	m_pItemName = CCLabelTTF::create("",CELL_FONT,CELL_FONT_SIZE);
	m_pTarget = CCLabelTTF::create("",CELL_FONT,CELL_FONT_SIZE);
	m_pAmount = CCLabelTTF::create("",CELL_FONT,CELL_FONT_SIZE);

	CCSize cellSize = this->getContentSize();
	m_pItemName->setPosition(ccp(50,0));
	addChild(m_pItemName,1);
	m_pTarget->setPosition(ccp(200,0));
	addChild(m_pTarget,1);
	m_pAmount->setPosition(ccp(400,0));
	addChild(m_pAmount,1);
	m_bg = CCNodeRGBA::create();
	m_bg->setOpacity(0);
	m_bg->setColor(ccRED);
	addChild(m_bg,0);
	return true;
}

ListItemCell *ListItemCell::create(const string name, const string target, const int amount)
{
	ListItemCell *cell = new ListItemCell();
	if (!cell) {
		CC_SAFE_DELETE(cell);
		return NULL;
	}
	else {
		if (cell->init())
			cell->autorelease();
		else {
			CC_SAFE_DELETE(cell);
			return NULL;
		}
	}
	cell->updateLabels(name,target,amount);
	return cell;
}

void ListItemCell::updateLabels(const string name, const string target, const int amount)
{
	if (isSelected())
		onDeselected();
	if (name.length() == 0 || amount == 0) {
		m_pItemName->setString("");
		m_pTarget->setString("");
		m_pAmount->setString("");
		return;
	}
	m_pItemName->setString(name.c_str());
	m_pItemName->setDirty(true);
	m_pTarget->setString(target.c_str());
	m_pTarget->setDirty(true);
	char amount_char[15];
	m_pAmount->setString(_itoa(amount,amount_char,10));
	m_pAmount->setDirty(true);
}